/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l7_visual_farm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 19:27:35 by wballaba          #+#    #+#             */
/*   Updated: 2019/02/25 22:11:42 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// void	draw_ant(t_farm *farm)
// {
	
// }

static void	draw_back(t_farm *farm)
{
	int	x;
	int y;

	y = 0;
	while (y < WIN_SIZE)
	{
		x = -1;
		while (++x < WIN_SIZE)
			mlx_pixel_put(farm->visualiser->mlx_ptr, farm->visualiser->win_ptr,
				x, y, COLOR_BACK);
		y++;
	}
}

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

static void	draw_farm(t_farm *farm)
{
	t_params data;
	int nbr_path;
	int	i;
	
	nbr_path = 0;
	while (farm->rooms[nbr_path])
	{
		i = 0;
		data.x = farm->rooms[nbr_path]->x;
		data.y = farm->rooms[nbr_path]->y;
		data.radius = 13;
		ft_draw_circle(farm->visualiser, &data, COLOR_NODE);
		mlx_string_put(farm->visualiser->mlx_ptr, farm->visualiser->win_ptr,
			data.x + 10, data.y + 10, COLOR_NODE, farm->rooms[nbr_path]->name);

		// draw_run_ant(&data, farm, nbr_path)

		if (farm->rooms[nbr_path]->ant_num)  // статичный вывод муравьев в ферме
		{
			mlx_string_put(farm->visualiser->mlx_ptr, farm->visualiser->win_ptr,
			data.x - 10, data.y - 10, COLOR_NODE, ft_itoa(farm->rooms[nbr_path]->ant_num));
		}
		t_list *child = farm->rooms[nbr_path]->childs;
		while (child)
		{
			t_room *room = (t_room*)child->content;
			data.x2 = room->x;
			data.y2 = room->y;
			data.line_width = 1;
			ft_draw_line(farm->visualiser, &data, COLOR_EDGE);
			// draw_run_ant(&data, farm, nbr_path);
			child = child->next;
			
		}
		
		nbr_path++;
	}
}

int		press_key_callback(int key, t_farm *farm)
{
	if (key == KEY_SPACE)
	{
		if (farm->finished_ants < farm->ants_count)
		{
			draw_back(farm);
			draw_farm(farm);
			make_step(farm);
		}
	}
	return (1);
}
