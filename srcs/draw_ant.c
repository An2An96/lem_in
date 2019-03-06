/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:15:25 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/06 15:27:41 by wballaba         ###   ########.fr       */
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
		vfarm->ant[i]->x = vfarm->farm->rooms[0]->x;
		vfarm->ant[i]->y = vfarm->farm->rooms[0]->y;
		vfarm->ant[i]->x2 = vfarm->farm->rooms[0]->x;
		vfarm->ant[i]->y2 = vfarm->farm->rooms[0]->y;
		vfarm->ant[i]->drawing = 0;
		i++;
	}
}

/*
**	нахождение координат и тракектории передвижения муравьев
*/

void		move_ant(t_ant *ant, int x, int y, int type_room)
{
	double	side[3];

	if (type_room == ROOM_END)
		ant->drawing = LAST_DRAW;
	else
		ant->drawing = DRAWING;
	ant->x = ant->x2;
	ant->y = ant->y2;
	ant->x2 = x;
	ant->y2 = y;
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

static int	draw_one_ant(t_vfarm *vfarm, t_ant *ant, int ant_nbr, int step)
{
	if (ant->drawing == STOP_DRAW)
		return (0);
	if (step >= ant->length)
	{
		if (ant->drawing == LAST_DRAW)
			ant->drawing = STOP_DRAW;
		step = ant->length;
	}
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) * vfarm->abs_x + vfarm->indent_x,
		round(ant->y + step * ant->sin_a) * vfarm->abs_y + vfarm->indent_y,
		COLOR_ANT, ft_itoa(ant_nbr));
	return (step < ant->length);
}

/*
**	вызов функции отрисовки муравья для каждого
*/

static int	draw_ants(t_vfarm *vfarm)
{
	int ant_nbr;
	int	step;

	if ((vfarm->farm->finished_ants <= vfarm->farm->ants_count)
		&& vfarm->count_func)
	{
		vfarm->count_func = 0;
		visual_farm(vfarm);
		ant_nbr = 1;
		while (ant_nbr <= vfarm->farm->ants_count)
		{
			vfarm->count_func += draw_one_ant(vfarm, vfarm->ant[ant_nbr - 1],
				ant_nbr, vfarm->step);
			ant_nbr++;
		}
		vfarm->step++;
	}
	return (0);
}

/*
**	loop для отрисовки муравьев
*/

void		draw_run_ant(t_vfarm *vfarm)
{
	vfarm->step = 0;
	vfarm->count_func = 1;
	mlx_loop_hook(vfarm->visual->mlx_ptr, draw_ants, vfarm);
	mlx_loop(vfarm->visual->mlx_ptr);
}
