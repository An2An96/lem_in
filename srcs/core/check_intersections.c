/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 15:02:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 21:14:14 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	find_intersection(t_path *first, t_path *second)
{
	t_node *fst_node;
	t_node *snd_node;

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

static void	extend_matrix(t_farm *farm, size_t size)
{
	size_t	i;
	bool	**new_matrix;

	SECURE_MALLOC(new_matrix = (bool**)malloc(size * sizeof(bool*)));
	i = 0;
	while (i < size)
	{
		SECURE_MALLOC(new_matrix[i] = (bool*)malloc(size * sizeof(bool)));
		if (i < farm->intersections_length)
			ft_memcpy(new_matrix[i], farm->intersections[i],
				farm->intersections_length * sizeof(bool));
		i++;
	}
	i = 0;
	while (i < farm->intersections_size)
		free(farm->intersections[i++]);
	free(farm->intersections);
	farm->intersections_size = size;
	farm->intersections = new_matrix;
}

static void	check_intersections_helper(
	t_farm *farm, t_node *paths, size_t path_idx, t_node *path)
{
	size_t	j;

	j = 0;
	while (paths)
	{
		if (LIST(path, t_path*) == LIST(paths, t_path*))
			farm->intersections[path_idx][j] = true;
		else
			farm->intersections[path_idx][j] =
				find_intersection(LIST(path, t_path*), LIST(paths, t_path*));
		farm->intersections[j][path_idx] = farm->intersections[path_idx][j];
		paths = paths->next;
		j++;
	}
}

void		check_intersections(t_farm *farm)
{
	t_dlist	*paths;
	t_node	*path;
	size_t	i;

	paths = farm->rooms[farm->count_rooms - 1]->paths;
	if (farm->intersections_length >= paths->size)
		return ;
	if (paths->size >= farm->intersections_size)
		extend_matrix(farm, (paths->size / 100 + 1) * 100);
	i = paths->size - farm->intersections_length - 1;
	path = paths->tail;
	while (i > 0)
		path = path->prev;
	i = farm->intersections_length;
	while (path)
	{
		check_intersections_helper(farm, paths->head, i++, path);
		path = path->next;
	}
	farm->intersections_length = paths->size;
}
