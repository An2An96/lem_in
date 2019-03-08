/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_ant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:56:19 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/08 16:09:35 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

static void	animation1(t_vfarm *vfarm, t_ant *ant, int step)
{
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) + vfarm->indent_x - 14,
		round(ant->y + step * ant->sin_a) + vfarm->indent_y - 23,
		COLOR_ANT, "\\o/");
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) + vfarm->indent_x - 14,
		round(ant->y + step * ant->sin_a) + vfarm->indent_y - 11,
		COLOR_ANT, "-0-");
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) + vfarm->indent_x - 14,
		round(ant->y + step * ant->sin_a) + vfarm->indent_y,
		COLOR_ANT, "/'\\ ");
}

static void	animation2(t_vfarm *vfarm, t_ant *ant, int step)
{
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) + vfarm->indent_x - 14,
		round(ant->y + step * ant->sin_a) + vfarm->indent_y - 23,
		COLOR_ANT, "_o_");
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) + vfarm->indent_x - 14,
		round(ant->y + step * ant->sin_a) + vfarm->indent_y - 11,
		COLOR_ANT, ">0<");
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		round(ant->x + step * ant->cos_a) + vfarm->indent_x - 14,
		round(ant->y + step * ant->sin_a) + vfarm->indent_y,
		COLOR_ANT, " ' ");
}

/*
**	функция отрисовки для одного муравья
*/

static int	draw_one_ant(t_vfarm *vfarm, t_ant *ant, int step)
{
	int	stop;

	stop = 0;
	if (ant->drawing == STOP_DRAW)
		return (0);
	if (step >= ant->length)
	{
		if (ant->drawing == LAST_DRAW)
			ant->drawing = STOP_DRAW;
		step = ant->length;
		stop = 1;
	}
	if (((step % 3) == 0) && stop == 0)
		animation2(vfarm, ant, step);
	else
		animation1(vfarm, ant, step);
	return (step < ant->length);
}

/*
**	вызов функции отрисовки муравья для каждого
*/

int			draw_ants(t_vfarm *vfarm)
{
	int ant_nbr;

	if ((vfarm->farm->finished_ants <= vfarm->farm->ants_count)
		&& vfarm->count_func)
	{
		vfarm->count_func = 0;
		visual_farm(vfarm);
		ant_nbr = 1;
		while (ant_nbr <= vfarm->farm->ants_count)
		{
			vfarm->count_func +=
				draw_one_ant(vfarm, vfarm->ant[ant_nbr - 1], vfarm->step);
			ant_nbr++;
		}
		vfarm->step += SPEED_ANIMATION;
	}
	return (0);
}
