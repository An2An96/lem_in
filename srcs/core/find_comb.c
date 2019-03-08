/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_comb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:00:26 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 18:50:49 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	find_intersection(t_path *first, t_path *second)
{
	// static size_t counter;

	// ft_putnbr(++counter);
	// write(1, "\n", 1);

	t_node *fst_node;
	t_node *snd_node;

	// ft_printf("find_intersection:\n");
	// show_path(first);
	// show_path(second);

	if (!first || !second)
		return (false);
	if (first == second)
		return (true);
	fst_node = first->head;
	while (fst_node)
	{
		snd_node = second->head;
		while (snd_node && snd_node->next)
		{
			if (fst_node->content == snd_node->content)
				return (true);
			snd_node = snd_node->next;
		}
		fst_node = fst_node->next;
	}
	return (false);
}

void	show_matrix(bool **matrix, int size)
{
	int i;
	int j;

	i = 0;
	ft_printf("\n");
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_printf("%d", matrix[i][j]);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	ft_printf("\n");
}

int	check_intersections(t_farm *farm)
{
	t_node *path;
	t_node *cur;
	// bool **new_matrix;
	size_t i;
	size_t j;

	if (farm->intersections_size < farm->rooms[farm->count_rooms - 1]->paths->size)
	{
		// SECURE_MALLOC(new_matrix = (bool**)malloc(farm->rooms[farm->count_rooms - 1]->paths->size * sizeof(bool*)));
		// i = 0;
		// while (i < farm->rooms[farm->count_rooms - 1]->paths->size)
		// {
		// 	SECURE_MALLOC(new_matrix[i] = (bool*)malloc(farm->rooms[farm->count_rooms - 1]->paths->size * sizeof(bool)));
		// 	if (i < farm->intersections_size)
		// 		ft_memcpy(new_matrix[i], farm->intersections[i], farm->intersections_size * sizeof(bool));
		// 	i++;
		// }
		// i = 0;
		// while (i < farm->intersections_size)
		// 	free(farm->intersections[i++]);
		// free(farm->intersections);

		i = farm->rooms[farm->count_rooms - 1]->paths->size - farm->intersections_size - 1;
		path = farm->rooms[farm->count_rooms - 1]->paths->tail;
		while (i > 0)
			path = path->prev;
		i = farm->intersections_size;
		while (path)
		{
			j = 0;
			cur = farm->rooms[farm->count_rooms - 1]->paths->head;
			while (cur)
			{
				farm->intersections[i][j] = find_intersection(LIST(path, t_path*), LIST(cur, t_path*));
				farm->intersections[j][i] = farm->intersections[i][j];
				j++;
				cur = cur->next;
			}
			i++;
			path = path->next;
		}
		// farm->intersections = new_matrix;
		farm->intersections_size = farm->rooms[farm->count_rooms - 1]->paths->size;
	}
	// show_matrix(farm->intersections, farm->intersections_size);
	return (1);
}

static int	find_idx(t_dlist *paths, t_node *node)
{
	int i;
	t_node *cur;

	i = 0;
	cur = paths->head;
	while (cur)
	{
		if (cur == node)
		{
			// ft_printf("find_idx: %d\n", i);
			return (i);
		}
		i++;
		cur = cur->next;
	}
	return (-1);
}

bool		find_comb(
	t_farm *farm, t_dlist *paths, t_stack *result, t_node *cur_path_node, int need_path)
{
	int		i;
	int		cur_idx;
	int		value;
	t_node	*next_path_node;

	// ft_printf("find_comb [%d/%d]\n", result->len, need_path);
	// debug_show_path(LIST(cur_path_node, t_path*));

	if (!cur_path_node)
		return (false);

	while (cur_path_node)
	{
		i = -1;
		cur_idx = find_idx(paths, cur_path_node);
		while (++i < result->len)
		// while (++i < result->last_free_idx)
		{
			// ft_printf("[%d][%d] = %d\n", i, cur_idx, farm->intersections[i][cur_idx]);
			if (farm->intersections[ result->head[i] ][cur_idx])
				return (false);
			// if (find_intersection(result->paths[i], LIST(cur_path_node, t_path*)))
			// 	return (false);
		}
		
		ft_stack_push(result, cur_idx);
		// result->paths[result->last_free_idx++] = (t_path*)cur_path_node->content;
		// if (result->last_free_idx >= need_path)
		if (result->len == result->size)
			return (true);
		next_path_node = cur_path_node->next;
		while (next_path_node)
		{
			if (find_comb(farm, paths, result, next_path_node, need_path))
				return (true);
			next_path_node = next_path_node->next;
		}
		ft_stack_pop(result, &value);
		// result->paths[--result->last_free_idx] = NULL;
		cur_path_node = cur_path_node->next;
	}
	return (false);
}
