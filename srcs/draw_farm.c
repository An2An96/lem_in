/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:27:33 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/04 16:29:47 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_ant(t_visual_farm	*vfarm)
{ 
	t_params data;
	int nbr_room;

	nbr_room = 0;
	while (vfarm->farm->rooms[nbr_room])
	{
		data.x = vfarm->farm->rooms[nbr_room]->x * vfarm->abs_val_x + vfarm->indent_x;
		data.y = vfarm->farm->rooms[nbr_room]->y * vfarm->abs_val_y + vfarm->indent_y;
		// visual_step_ant(vfarm, nbr_room);
		// draw_run_ant(&data, vfarm, nbr_room);
		if (vfarm->farm->rooms[nbr_room]->ant_num)
		{
			mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
			data.x - 10, data.y - 10, COLOR_NODE, ft_itoa(vfarm->farm->rooms[nbr_room]->ant_num));
		}
		nbr_room++;
	}
}

static void	draw_edge(t_visual_farm *vfarm, int nbr_room)
{
	t_params data;

	t_list *child = vfarm->farm->rooms[nbr_room]->neighbors;
	t_room *room;

	data.x = vfarm->farm->rooms[nbr_room]->x * vfarm->abs_val_x  + vfarm->indent_x;
	data.y = vfarm->farm->rooms[nbr_room]->y * vfarm->abs_val_y  + vfarm->indent_y;
	while (child)
	{
		room = vfarm->farm->rooms[*(int*)child->content];
		data.x2 = room->x * vfarm->abs_val_x + vfarm->indent_x;
		data.y2 = room->y * vfarm->abs_val_y + vfarm->indent_y;
		data.line_width = 1;
		data.img = vfarm->image;
		ft_draw_line(vfarm->visual, &data, COLOR_EDGE);
		child = child->next;
	}
}

void	create_farm_image(t_visual_farm *vfarm)
{
	t_params data;
	int nbr_room;

	nbr_room = 0;

	vfarm->image = ft_create_image(vfarm->visual, WIN_SIZE, WIN_SIZE);

	data.width = WIN_SIZE;
	data.height = WIN_SIZE;
	data.img = vfarm->image;
	ft_draw_bg_gradient(vfarm->visual, &data, 0x00FF000, 0xFF00000);
	while (vfarm->farm->rooms[nbr_room])
	{
		data.img = vfarm->image;
		data.x = vfarm->farm->rooms[nbr_room]->x * vfarm->abs_val_x + vfarm->indent_x;
		data.y = vfarm->farm->rooms[nbr_room]->y * vfarm->abs_val_y + vfarm->indent_y;
		data.line_width = 1;
		data.radius = 17;
		ft_draw_circle(vfarm->visual, &data, COLOR_NODE);
		draw_edge(vfarm, nbr_room);
		nbr_room++;
	}
}


void			visual_farm(t_visual_farm	*vfarm)
{
	int nbr_room;

	nbr_room = 0;
	mlx_clear_window(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr);
	mlx_put_image_to_window(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr, vfarm->image->img_ptr, 0, 0);
	while (nbr_room < vfarm->farm->count_rooms)
	{
		mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
			vfarm->farm->rooms[nbr_room]->x * vfarm->abs_val_x + 10  + vfarm->indent_x,
			vfarm->farm->rooms[nbr_room]->y * vfarm->abs_val_y + 10 + vfarm->indent_y,
			COLOR_NODE, vfarm->farm->rooms[nbr_room]->name);
		nbr_room++;
	}
	if (vfarm->farm->finished_ants < vfarm->farm->ants_count)
		draw_ant(vfarm);
}
