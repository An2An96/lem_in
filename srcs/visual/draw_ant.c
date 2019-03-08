/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:15:25 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/08 12:37:48 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

/*
**	создание массива структур муравьев
*/

void		get_arr_ant(t_vfarm *vfarm)
{
	int	i;

	vfarm->ant = (t_ant**)ft_memalloc(vfarm->farm->ants_count * sizeof(t_ant*));
	i = 0;
	while (i < vfarm->farm->ants_count)
	{
		vfarm->ant[i] = (t_ant*)ft_memalloc(sizeof(t_ant));
		vfarm->ant[i]->x = vfarm->farm->rooms[0]->x * vfarm->abs_x;
		vfarm->ant[i]->y = vfarm->farm->rooms[0]->y * vfarm->abs_y;
		vfarm->ant[i]->x2 = vfarm->farm->rooms[0]->x * vfarm->abs_x;
		vfarm->ant[i]->y2 = vfarm->farm->rooms[0]->y * vfarm->abs_y;
		vfarm->ant[i]->drawing = STOP_DRAW;
		i++;
	}
}

/*
**	нахождение координат и тракектории передвижения муравьев
*/

void		move_ant(t_ant *ant, t_room *room, t_vfarm *vfarm)
{
	double	side[3];

	if (room->types & ROOM_END)
	{
		ant->drawing = LAST_DRAW;
		vfarm->farm->finished_ants++;
	}
	else
		ant->drawing = DRAWING;
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

/*
**	отрисовка движения одного муравья
*/

static	int	end_ant_path(int key, t_vfarm *vfarm)
{
	int	i;

	i = 0;
	if (key == KEY_SPACE)
	{
		while (i < vfarm->farm->ants_count)
		{
			if (vfarm->ant[i]->drawing == LAST_DRAW)
				vfarm->ant[i]->drawing = STOP_DRAW;
			i++;
		}
	}
	if (key == KEY_ESC)
		ft_close();
	return (0);
}

/*
**	loop для отрисовки муравьев
*/

void		draw_run_ant(t_vfarm *vfarm)
{
	vfarm->step = 0;
	vfarm->count_func = 1;
	mlx_hook(vfarm->visual->win_ptr, 2, 1L << 17, end_ant_path, vfarm);
	mlx_loop_hook(vfarm->visual->mlx_ptr, draw_ants, vfarm);
	mlx_loop(vfarm->visual->mlx_ptr);
}
