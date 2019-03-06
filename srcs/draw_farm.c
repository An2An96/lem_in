/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:27:33 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/06 20:04:41 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

/*
**	2 функции ниже высчитывают значения нужные для правильного расположения
**  фермы в окне
*/

static void	assignment_val(t_vfarm *vfarm, t_val *val)
{
	if ((val->max_x - val->min_x))
		vfarm->abs_x = VISUAL_SIZE / (val->max_x - val->min_x);
	else
		vfarm->abs_x = 1;
	if ((val->max_y - val->min_y))
		vfarm->abs_y = VISUAL_SIZE / (val->max_y - val->min_y);
	else
		vfarm->abs_y = 1;
	if (val->min_x != val->max_x)
		vfarm->indent_x = -val->min_x * vfarm->abs_x +
			((WIN_SIZE - (val->max_x - val->min_x) * vfarm->abs_x) / 2);
	else
		vfarm->indent_x = WIN_SIZE / 2;
	if (val->min_y != val->max_y)
		vfarm->indent_y = -val->min_y * vfarm->abs_y +
			((WIN_SIZE - (val->max_y - val->min_y) * vfarm->abs_y) / 2);
	else
		vfarm->indent_y = WIN_SIZE / 2;
}

void		get_abs_val(t_farm *farm, t_vfarm *vfarm)
{
	int		n_room;
	t_val	val;

	n_room = 0;
	val.max_x = farm->rooms[n_room]->x;
	val.max_y = farm->rooms[n_room]->y;
	val.min_x = val.max_x;
	val.min_y = val.max_y;
	while (farm->rooms[n_room])
	{
		val.max_x = MAX(val.max_x, farm->rooms[n_room]->x);
		val.min_x = MIN(val.min_x, farm->rooms[n_room]->x);
		val.max_y = MAX(val.max_y, farm->rooms[n_room]->y);
		val.min_y = MIN(val.min_y, farm->rooms[n_room]->y);
		n_room++;
	}
	assignment_val(vfarm, &val);
}

/*
**	отрисовка ребер
*/

static void	draw_edge(t_vfarm *vfarm, int n_room)
{
	t_params	data;
	t_list		*child;
	t_room		*room;

	child = vfarm->farm->rooms[n_room]->neighbors;
	data.x = vfarm->farm->rooms[n_room]->x * vfarm->abs_x + vfarm->indent_x;
	data.y = vfarm->farm->rooms[n_room]->y * vfarm->abs_y + vfarm->indent_y;
	while (child)
	{
		room = vfarm->farm->rooms[*(int*)child->content];
		data.x2 = room->x * vfarm->abs_x + vfarm->indent_x;
		data.y2 = room->y * vfarm->abs_y + vfarm->indent_y;
		data.line_width = 1;
		data.img = vfarm->image;
		ft_draw_line(vfarm->visual, &data, COLOR_EDGE);
		child = child->next;
	}
}

/*
**	создание изображения фермы из фона градиента, ребер и кругов нод
*/

void		create_farm_image(t_vfarm *vfarm)
{
	t_params	data;
	int			n_room;

	n_room = 0;
	vfarm->image = ft_create_image(vfarm->visual, WIN_SIZE, WIN_SIZE);
	data.width = WIN_SIZE;
	data.height = WIN_SIZE;
	data.img = vfarm->image;
	ft_draw_bg_gradient(vfarm->visual, &data, COLOR_BG1, COLOR_BG2);
	while (vfarm->farm->rooms[n_room])
	{
		data.img = vfarm->image;
		data.x = vfarm->farm->rooms[n_room]->x * vfarm->abs_x + vfarm->indent_x;
		data.y = vfarm->farm->rooms[n_room]->y * vfarm->abs_y + vfarm->indent_y;
		data.line_width = 1;
		data.radius = NODE_RADIUS;
		ft_draw_circle(vfarm->visual, &data, COLOR_NODE);
		draw_edge(vfarm, n_room);
		n_room++;
	}
}

/*
**	отрисовка фермы
*/

void		visual_farm(t_vfarm *vfarm)
{
	int		n_room;
	char	*s_antcount;
	char	*s_finant;
	char	*s_step;

	s_antcount = ft_strjoin("count ant  = ", ft_itoa(vfarm->farm->ants_count));
	s_finant = ft_strjoin("finish ant = ", ft_itoa(vfarm->farm->finished_ants));
	s_step = ft_strjoin("count step = ", ft_itoa(vfarm->count_line));
	mlx_put_image_to_window(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
		vfarm->image->img_ptr, 0, 0);
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr, 10, 5,
		COLOR_ANT, s_antcount);
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr, 10, 25,
		COLOR_ANT, s_finant);
	mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr, 10, 45,
		COLOR_ANT, s_step);
	n_room = -1;
	while (++n_room < vfarm->farm->count_rooms)
		mlx_string_put(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr,
			vfarm->farm->rooms[n_room]->x * vfarm->abs_x + 13 + vfarm->indent_x,
			vfarm->farm->rooms[n_room]->y * vfarm->abs_y + 13 + vfarm->indent_y,
			COLOR_NODE, vfarm->farm->rooms[n_room]->name);
	free(s_antcount);
	free(s_finant);
	free(s_step);
}
