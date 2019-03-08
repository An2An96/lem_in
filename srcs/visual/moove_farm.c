/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_farm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:10:11 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/08 20:20:58 by wballaba         ###   ########.fr       */
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

void	move_farm(int key, t_vfarm *vfarm)
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
	else if (key == KEY_A)
		vfarm->indent_x += WIN_SIZE / 2;
	else if (key == KEY_D)
		vfarm->indent_x -= WIN_SIZE / 2;
	else if (key == KEY_E)
	{
		vfarm->abs_x /= 1.5;
		vfarm->abs_y /= 1.5;
		assignment_indent(vfarm);
	}
	else if (key == KEY_Q)
	{
		vfarm->abs_x *= 1.5;
		vfarm->abs_y *= 1.5;
		assignment_indent(vfarm);
	}
	create_farm_image(vfarm);
	visual_farm(vfarm);
	draw_run_ant(vfarm);
}

