/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l7_visual_farm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 19:27:35 by wballaba          #+#    #+#             */
/*   Updated: 2019/02/26 19:39:40 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	draw_run_ant(t_params *data, t_farm *farm, int nbr_path)
{
	double	length;
	double	side[3];
	double	sin_a;
	double	cos_a;

	side[1] = data->y2 - data->y;
	side[2] = data->x2 - data->x;
	side[0] = sqrt(pow(side[1], 2) + pow(side[2], 2));
	sin_a = side[1] / side[0];
	cos_a = side[2] / side[0];
	length = side[0];
	while ((int)length > 0)
	{
		mlx_string_put(farm->visualiser->mlx_ptr, farm->visualiser->win_ptr, 
			round(data->x + length * cos_a), round(data->y + length * sin_a),
			COLOR_ANT, ft_itoa(farm->rooms[nbr_path]->ant_num));
		length--;
	}
}

void	draw_ant(t_farm *farm)
{
	t_params *data;
	int nbr_room;

	data = (t_params*)ft_memalloc(sizeof(t_params));
	nbr_room = 0;
	while (farm->rooms[nbr_room])
	{
		data->x = farm->rooms[nbr_room]->x;
		data->y = farm->rooms[nbr_room]->y;
		// draw_run_ant(data, farm, nbr_room);
		if (farm->rooms[nbr_room]->ant_num)
		{
			mlx_string_put(farm->visualiser->mlx_ptr, farm->visualiser->win_ptr,
			data->x - 10, data->y - 10, COLOR_NODE, ft_itoa(farm->rooms[nbr_room]->ant_num));
		}
		nbr_room++;
	}
	free(data);
}

static void	draw_edge(t_farm *farm, t_img *img, int nbr_room)
{
	t_params *data;

	data = (t_params*)ft_memalloc(sizeof(t_params));

	t_list *child = farm->rooms[nbr_room]->childs;
	t_room *room;

	data->x = farm->rooms[nbr_room]->x;
	data->y = farm->rooms[nbr_room]->y;
	while (child)
	{
		room = (t_room*)child->content;
		data->x2 = room->x;
		data->y2 = room->y;
		data->line_width = 1;
		data->img = img;
		ft_draw_line(farm->visualiser, data, COLOR_EDGE);
		child = child->next;
	}
	free(data);
}

void	draw_farm(t_farm *farm)
{
	t_params *data;
	int nbr_room;

	data = (t_params*)ft_memalloc(sizeof(t_params));
	nbr_room = 0;

	farm->image = ft_create_image(farm->visualiser, WIN_SIZE, WIN_SIZE);

	data->width = WIN_SIZE;
	data->height = WIN_SIZE;
	data->img = farm->image;
	ft_draw_bg_gradient(farm->visualiser, data, 0x00FF000, 0xFF00000);
	while (farm->rooms[nbr_room])
	{
		data->img = farm->image;
		data->x = farm->rooms[nbr_room]->x;
		data->y = farm->rooms[nbr_room]->y;
		data->line_width = 1;
		data->radius = 17;
		ft_draw_circle(farm->visualiser, data, COLOR_NODE);
		draw_edge(farm, farm->image, nbr_room);
		nbr_room++;
	}
	free(data);
}

int		press_key_callback(int key, t_farm *farm)
{
	int nbr_room;
	if (key == KEY_SPACE)
	{
		nbr_room = 0;
		mlx_put_image_to_window(
			farm->visualiser->mlx_ptr, 
			farm->visualiser->win_ptr,
			farm->image->img_ptr,
			0, 0);
		while (nbr_room < farm->count_rooms)
		{
			mlx_string_put(farm->visualiser->mlx_ptr, farm->visualiser->win_ptr,
				farm->rooms[nbr_room]->x + 10, farm->rooms[nbr_room]->y + 10,
				COLOR_NODE, farm->rooms[nbr_room]->name);
			nbr_room++;
		}
		if (farm->finished_ants < farm->ants_count)
		{
			draw_ant(farm);
			make_step(farm);
		}
	}
	return (1); 
}
