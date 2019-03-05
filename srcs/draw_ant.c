/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:15:25 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/05 21:03:39 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_ant(t_ant	*ant, int x, int y)
{
	ant->x = ant->x2;
	ant->y = ant->y2;
	ant->x2 = x;
	ant->y2 = y;
	ft_printf("x %d     y %d    x2 %d   y2 %d	\n", ant->x, ant->y, ant->x2, ant->y2);
}

void	arr_ant(t_visual_farm *vfarm)
{
	
	int     i;
	vfarm->ant = (t_ant**)ft_memalloc(vfarm->farm->ants_count * sizeof(t_ant*));
	i = 0;
	while (i < vfarm->farm->ants_count)
	{
		vfarm->ant[i] = (t_ant*)ft_memalloc(sizeof(t_ant));
		vfarm->ant[i]->x = vfarm->farm->rooms[0]->x;
		vfarm->ant[i]->y = vfarm->farm->rooms[0]->y;
		vfarm->ant[i]->x2 = vfarm->farm->rooms[0]->x;
		vfarm->ant[i]->y2 = vfarm->farm->rooms[0]->y;
		i++;
	}
	ft_printf(" Я зашел в функцию arr_ant\n");
}


int	draw_one_ant(t_visual_farm *vfarm, int ant_nbr, int step)
{
	t_params data;
	double	length;
	double	side[3];
	double	sin_a;
	double	cos_a;

	data.x = vfarm->ant[ant_nbr - 1]->x;
	data.y = vfarm->ant[ant_nbr - 1]->y;
	data.x2 = vfarm->ant[ant_nbr - 1]->x2;
	data.y2 = vfarm->ant[ant_nbr - 1]->y2;
	side[1] = data.y2 - data.y;
	side[2] = data.x2 - data.x;
	side[0] = sqrt(pow(side[1], 2) + pow(side[2], 2));
	sin_a = side[1] / side[0];
	cos_a = side[2] / side[0];
	length = side[0];
	if (step >= length)
		step = length;
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr, 
		round(data.x + step * cos_a) * vfarm->abs_val_x + vfarm->indent_x, 
		round(data.y + step * sin_a) * vfarm->abs_val_y + vfarm->indent_y,
		COLOR_ANT, ft_itoa(ant_nbr));
	return (step < length);
}



int		draw_ant(t_visual_farm *vfarm)
{
	int ant_nbr;
	int	step;

	if ((vfarm->farm->finished_ants < vfarm->farm->ants_count) && vfarm->count_func)
	{
		vfarm->count_func = 0;
		visual_farm(vfarm);
		ant_nbr = 1;
		while (ant_nbr <= vfarm->farm->ants_count)
		{
			vfarm->count_func += draw_one_ant(vfarm, ant_nbr, vfarm->step);
			ant_nbr++;
		}
		vfarm->step++;
	}
	return (0);
}

void	draw_run_ant(t_visual_farm *vfarm)
{
	vfarm->step = 0;
	vfarm->count_func = 1;
	mlx_loop_hook(vfarm->visual->mlx_ptr, draw_ant, vfarm);
	mlx_loop(vfarm->visual->mlx_ptr);
}
	
