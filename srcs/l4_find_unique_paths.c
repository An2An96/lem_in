/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 19:57:58 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Получает максимальное количество необходимых уникальных маршрутов
*/

int				get_max_count_need_unique_paths(int8_t **incidence, int size)
{
	int i;
	int counter[2];

	i = 0;
	counter[0] = 0;
	counter[1] = 0;
	while (i < size)
	{
		counter[0] += incidence[0][i];
		counter[1] += incidence[i][size - 1];
		i++;
	}
	return (MIN(counter[0], counter[1]));
}

void			sort_paths_by_length(t_path **paths)
{

	int i;
	int j;
	int min_idx;
	t_path *tmp;

	i = 0;
	while (paths[i])
	{
		min_idx = i;
		j = min_idx;
		while (paths[++j])
			if (paths[j]->size < paths[min_idx]->size)
				min_idx = j;
		tmp = paths[min_idx];
		j = min_idx - i;
		while (j)
		{
			paths[i + j] = paths[i + j - 1];
			j--;
		}
		paths[i] = tmp;
		i++;
	}
}

static t_path	*ft_one_dfs(
	t_farm *farm, int8_t *used, int node_idx, int node_count)
{
	int		next_node_idx;
	t_path	*res;

	if (node_idx == farm->count_rooms - 1)
		return (ft_dlst_create());
	res = NULL;
	used[node_idx] = 1;
	next_node_idx = 0;
	while (next_node_idx < farm->count_rooms)
	{
		if (farm->incidence[node_idx][next_node_idx] && !used[next_node_idx])
		{
			if ((res = ft_one_dfs(farm, used, next_node_idx, ++node_count)))
			{
				ft_dlst_push_front(res,
					ft_create_node(&next_node_idx, sizeof(next_node_idx)));
				return (res);
			}
		}
		next_node_idx++;
	}
	used[node_idx] = 0;
	return (res);
}

/*
**	Находит комбинации уникальных (не пересекающихся) маршрутов
*/

t_path			**find_unique_paths(t_farm *farm, int count)
{
	int8_t	*used;
	t_path	**cur_paths;
	// t_path	**best_paths;
	int		path_num;
	// t_list	*cur;

	cur_paths = (t_path**)ft_memalloc((count + 1) * sizeof(t_path*));
	path_num = 0;
	if (!(used = (int8_t*)ft_memalloc(farm->count_rooms * sizeof(int8_t))))
		exit(-1);
	cur_paths[path_num] = ft_one_dfs(farm, used, 0, 0);
	return (cur_paths);

	// i = 0;
	// while (i < count)
	// {
	// 	if ((cur_paths[path_num] = ft_one_dfs(farm, used, 0, 0)))
	// 		path_num++;
	// 	else
	// 		break ;
	// 	i++;
	// }
	// if (path_num == count)
	// {
	// 	i = 0;
	// 	while (i < path_num)
	// 	{
	// 		int j = 0;
	// 		ft_printf("%s", farm->rooms[0]->name);
	// 		while (j < cur_paths[i]->count_node)
	// 		{
	// 			ft_printf(" -> %s", farm->rooms[cur_paths[i]->idx[j]]->name);
	// 			j++;
	// 		}
	// 		ft_printf("\n");
	// 		i++;
	// 	}
	// }
	// else
	// 	ft_printf("Paths not found\n");
	return (NULL);
}
