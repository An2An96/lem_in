/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/02 20:19:53 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//	!!! Сортировать маршруты по количеству вершин для каждой комбинации
//	!!! перед передачей в find_best_comb_paths

t_path ***test()
{
	int a;
	t_path ***paths;

	paths = (t_path***)malloc(3 * sizeof(t_path**));

//	Comb 1
	paths[0] = (t_path**)malloc(2 * sizeof(t_path*));

	//	[Comb 1] Path 1
	paths[0][0] = ft_dlst_create();

	a = 1;
	ft_dlst_push_back(paths[0][0], ft_create_node(&a, sizeof(int)));
	a = 2;
	ft_dlst_push_back(paths[0][0], ft_create_node(&a, sizeof(int)));
	a = 8;
	ft_dlst_push_back(paths[0][0], ft_create_node(&a, sizeof(int)));

	paths[0][1] = NULL;

//	Comb 2
	paths[1] = (t_path**)malloc(3 * sizeof(t_path*));
	paths[1][0] = ft_dlst_create();
	paths[1][1] = ft_dlst_create();

	//	[Comb 2] Path 1
	a = 5;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 6;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 7;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 2;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 8;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));

	//	[Comb 2] Path 2
	a = 1;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 3;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 4;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 8;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));


	paths[1][2] = NULL;

	paths[2] = NULL;
	return (paths);
}


int main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_farm	*farm;
	t_args	*args;
	t_path	***paths_combs;

	args = read_args(argc, argv);
	if (args->filename)
	{
		if ((fd = open(args->filename, O_RDONLY)) == -1)
			exit(-1);
	}
	else
		fd = 0;
	
	if (!(farm = read_farm_map(fd)))
		exit(-1);

	// t_list *el = farm->rooms[0]->neighbors;
	// ft_printf("Start childs:\n");
	// while (el)
	// {
	// 	ft_printf("%s\n", LIST(el, t_room*)->name);
	// 	el = el->next;
	// }

	// el = farm->rooms[farm->count_rooms - 1]->neighbors;
	// ft_printf("Finish childs:\n");
	// while (el)
	// {
	// 	ft_printf("%s\n", LIST(el, t_room*)->name);
	// 	el = el->next;
	// }

	farm->finished_ants = 0;
// #ifdef DRAW_H
	// if (IS_FLAG(FLAG_VISUALISE))
	// 	farm->visualiser = ft_create_window(WIN_SIZE, WIN_SIZE, "lem-in");
	// else
	// 	farm->visualiser = NULL;
// #endif
	i = 0;
	if (IS_FLAG(FLAG_DEBUG))
	{
		i = -1;
		while (++i < farm->count_rooms)
			ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
		// show_incidence_matrix(farm->rooms, farm->incidence, farm->count_rooms);
	}

	dijkstra_algo(farm);
	if (IS_FLAG(FLAG_DEBUG))
	{
		for (int i = 0; i < farm->count_rooms; i++)
			ft_printf("room %s (%d) weight: %d\n", farm->rooms[i]->name, i, farm->rooms[i]->weight);
	}


	// paths_combs = test();
	int max_unique_paths = MIN(farm->start_edges, farm->finish_edges);
	if (IS_FLAG(FLAG_DEBUG))
		ft_printf("max unique paths: %d\n", max_unique_paths);
	// paths_combs = ft_memalloc((max_unique_paths + 1) * sizeof(t_path**));
	// i = 0;
	// while (i < max_unique_paths)
	// {
	// 	if (!(paths_combs[i] = find_unique_paths(farm, i + 1)))
	// 	{
	// 		break ;
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (paths_combs[i])
	// {
	// 	int j = 0;
	// 	while (paths_combs[i][j])
	// 	{
	// 		show_path(farm, paths_combs[i][j]);
	// 		j++;
	// 	}
	// 	sort_paths_by_length(paths_combs[i]);
	// 	i++;
	// }
	
	// int idx = find_best_comb_paths(paths_combs, farm->ants_count);
	// farm->best_paths = paths_combs[idx];
	// if (IS_FLAG(FLAG_DEBUG))
	// {
	// 	ft_printf("Best paths comb:\n");
	// 	i = -1;
	// 	while (++i <= idx)
	// 		show_path(farm, farm->best_paths[i]);
	// }
	
	// let_ants_to_paths(farm);
	return (0);
}