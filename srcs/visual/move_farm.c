/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:10:11 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/09 17:02:47 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

static void	assignment_indent(t_vfarm *vfarm)
{
	if (vfarm->val->min_x != vfarm->val->max_x)
		vfarm->indent_x = -vfarm->val->min_x * vfarm->abs_x +
			((WIN_SIZE - (vfarm->val->max_x - vfarm->val->min_x) *
			vfarm->abs_x) / 2);
	else
		vfarm->indent_x = WIN_SIZE / 2;
	if (vfarm->val->min_y != vfarm->val->max_y)
		vfarm->indent_y = -vfarm->val->min_y * vfarm->abs_y +
			((WIN_SIZE - (vfarm->val->max_y - vfarm->val->min_y) *
			vfarm->abs_y) / 2);
	else
		vfarm->indent_y = WIN_SIZE / 2;
}

static void	start_coord_ant(t_vfarm *vfarm)
{
	int i;

	i = 0;
	while (i < vfarm->farm->ants_count)
	{
		vfarm->ant[i]->x = vfarm->farm->rooms[0]->x * vfarm->abs_x;
		vfarm->ant[i]->y = vfarm->farm->rooms[0]->y * vfarm->abs_y;
		vfarm->ant[i]->x2 = vfarm->farm->rooms[0]->x * vfarm->abs_x;
		vfarm->ant[i]->y2 = vfarm->farm->rooms[0]->y * vfarm->abs_y;
		vfarm->ant[i]->drawing = STOP_DRAW;
		i++;
	}
}

void		coord_ant(t_ant *ant, t_room *room, t_vfarm *vfarm)
{
	double	side[3];

	ant->x = ant->x2;
	ant->y = ant->y2;
	ant->x2 = room->x * vfarm->abs_x;
	ant->y2 = room->y * vfarm->abs_y;
	side[1] = ant->y2 - ant->y;
	side[2] = ant->x2 - ant->x;
	side[0] = sqrt(pow(side[1], 2) + pow(side[2], 2));
	ant->sin_a = side[1] / side[0];
	ant->cos_a = side[2] / side[0];
	ant->length = side[0];
}

void		zoom_farm(int key, t_vfarm *vfarm)
{
	int	n_room;
	int i;

	n_room = -1;
	if (key == KEY_E)
	{
		vfarm->abs_x /= 1.5;
		vfarm->abs_y /= 1.5;
	}
	else if (key == KEY_Q)
	{
		vfarm->abs_x *= 1.5;
		vfarm->abs_y *= 1.5;
	}
	start_coord_ant(vfarm);
	assignment_indent(vfarm);
	while (++n_room < vfarm->farm->count_rooms)
		if (vfarm->ant[vfarm->farm->rooms[n_room]->ant_num - 1])
			coord_ant(vfarm->ant[vfarm->farm->rooms[n_room]->ant_num - 1],
			vfarm->farm->rooms[n_room], vfarm);
	
	create_farm_image(vfarm);
	visual_farm(vfarm);
	// draw_run_ant(vfarm);
}

void		move_farm(int key, t_vfarm *vfarm)
{
	if (key == KEY_UP)
		vfarm->indent_y -= 10;
	else if (key == KEY_DOWN)
		vfarm->indent_y += 10;
	else if (key == KEY_LEFT)
		vfarm->indent_x += 10;
	else if (key == KEY_RIGHT)
		vfarm->indent_x -= 10;
	else if (key == KEY_W)
		vfarm->indent_y -= WIN_SIZE / 2;
	else if (key == KEY_S)
		vfarm->indent_y += WIN_SIZE / 2;
	else if (key == KEY_D)
		vfarm->indent_x += WIN_SIZE / 2;
	else if (key == KEY_A)
		vfarm->indent_x -= WIN_SIZE / 2;
	create_farm_image(vfarm);
	visual_farm(vfarm);
	// draw_run_ant(vfarm);
}
