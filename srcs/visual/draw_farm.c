/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_farm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:27:33 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/08 19:47:50 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

/*
**	2 функции ниже высчитывают значения нужные для правильного расположения
**  фермы в окне
*/

static void	assignment_val(t_vfarm *vfarm)
{
	if ((vfarm->val->max_x - vfarm->val->min_x))
		vfarm->abs_x = VISUAL_SIZE / (vfarm->val->max_x - vfarm->val->min_x);
	else
		vfarm->abs_x = 1;
	if ((vfarm->val->max_y - vfarm->val->min_y))
		vfarm->abs_y = VISUAL_SIZE / (vfarm->val->max_y - vfarm->val->min_y);
	else
		vfarm->abs_y = 1;
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

void		get_abs_val(t_farm *farm, t_vfarm *vfarm)
{
	int		n_room;

	vfarm->val = (t_val*)ft_memalloc(sizeof(t_val));

	n_room = 0;
	vfarm->val->max_x = farm->rooms[n_room]->x;
	vfarm->val->max_y = farm->rooms[n_room]->y;
	vfarm->val->min_x = vfarm->val->max_x;
	vfarm->val->min_y = vfarm->val->max_y;
	while (farm->rooms[n_room])
	{
		vfarm->val->max_x = MAX(vfarm->val->max_x, farm->rooms[n_room]->x);
		vfarm->val->min_x = MIN(vfarm->val->min_x, farm->rooms[n_room]->x);
		vfarm->val->max_y = MAX(vfarm->val->max_y, farm->rooms[n_room]->y);
		vfarm->val->min_y = MIN(vfarm->val->min_y, farm->rooms[n_room]->y);
		n_room++;
	}
	assignment_val(vfarm);
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
		data.line_width = 2;
		data.img = vfarm->image;
		// if (data.x2 + 10 < WIN_SIZE && data.y2 + 10 < WIN_SIZE && data.x2 - 10 > 0 && data.y2 - 10 > 0)
			ft_draw_line(vfarm->visual, &data, COLOR_EDGE, WIN_SIZE);
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

	vfarm->image = ft_create_image(vfarm->visual, WIN_SIZE, WIN_SIZE);
	data.width = WIN_SIZE;
	data.height = WIN_SIZE;
	data.img = vfarm->image;
	ft_draw_bg_gradient(vfarm->visual, &data, COLOR_BG1, COLOR_BG2);
	n_room = -1;
	while (vfarm->farm->rooms[++n_room])
	{
		data.img = vfarm->image;
		data.x = vfarm->farm->rooms[n_room]->x * vfarm->abs_x + vfarm->indent_x;
		data.y = vfarm->farm->rooms[n_room]->y * vfarm->abs_y + vfarm->indent_y;
		data.line_width = 2;
		data.radius = NODE_RADIUS;
		draw_edge(vfarm, n_room);
		if (n_room == 0 || n_room == vfarm->farm->count_rooms - 1)
			ft_draw_circle(vfarm->visual, &data, COLOR_START, WIN_SIZE);
		else
			ft_draw_circle(vfarm->visual, &data, COLOR_EDGE, WIN_SIZE);
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
