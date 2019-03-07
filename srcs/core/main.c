/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/07 19:09:50 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		clear_paths_comb(t_path_comb *paths_combs)
{
	int		i;

	if (paths_combs)
	{
		i = 0;
		while (paths_combs[i].count)
		{
			free(paths_combs[i].paths);
			i++;
		}
		free(paths_combs);
	}
}

void		clear_farm(t_farm *farm)
{
	int		i;
	t_list	*el;
	t_list	*tmp;

	if (farm)
	{
		el = farm->ways;
		while (el)
		{
			tmp = el->next;
			ft_dlst_del((t_path**)&el->content, NULL);
			free(el);
			el = tmp;
		}
		i = -1;
		while (++i < farm->count_rooms)
		{
			free(farm->rooms[i]->name);
			ft_lstdel(&farm->rooms[i]->neighbors, free_lst);
			ft_dlst_del(&farm->rooms[i]->paths, NULL);
			free(farm->rooms[i]);
		}
		free(farm->rooms);
		free(farm);
	}
}

void		test_dfs(t_farm *farm)
{
	t_room *cur = farm->rooms[0];
	t_room *best_next;
	t_list *neighbor_lst;
	t_room *neighbor;
	t_path *path;

	SECURE_MALLOC(path = ft_dlst_create());

	while (cur)
	{
		ft_printf("%s [weight: %d]\n", cur->name, cur->weight);
		ft_dlst_push_back(path, ft_create_node_ptr(cur));
		
		if (cur->types & ROOM_END)
			break ;

		neighbor_lst = cur->neighbors;
		if (!neighbor_lst)
			return ;
		best_next = NULL;
		while (neighbor_lst)
		{
			neighbor = farm->rooms[*LIST(neighbor_lst, int*)];
			if (!(neighbor->types & ROOM_START) && !find_cycle(path, neighbor))
			{	
				if (!best_next || best_next->weight > neighbor->weight)
					best_next = neighbor;
			}
			neighbor_lst = neighbor_lst->next;
		}
		cur = best_next;
	}
	show_path(path);
}



int			main(int argc, char **argv)
{
	int			fd;
	char		*filename;
	t_farm		*farm;
	t_path_comb	*paths_combs;
	clock_t		begin;
	clock_t		end;

	// begin = clock();
	SECURE_MALLOC(farm = (t_farm*)ft_memalloc(sizeof(t_farm)));
	filename = read_args(argc, argv, &farm->flags);
	(fd = filename ? open(filename, O_RDONLY) : 0) == -1
		&& throw_error(STR_ERROR_SYS, strerror(errno));
	read_farm_map(fd, farm);
	// end = clock();
	// ft_printf("read farm time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
	IS_FLAG(FLAG_DEBUG) && debug_show_rooms(farm);
	if (!(farm->rooms[0]->types == (ROOM_START | ROOM_END)))
	{
		// IS_FLAG(FLAG_TIME) && (begin = clock());
		// dijkstra_algo(farm);
		// IS_FLAG(FLAG_TIME) && (end = clock());
		// IS_FLAG(FLAG_TIME) && ft_printf("set weights rooms time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
		// IS_FLAG(FLAG_DEBUG) && debug_show_weights(farm);

		// test_dfs(farm);

		IS_FLAG(FLAG_TIME) && (begin = clock());
		paths_combs = find_unique_paths(farm,
			MIN(farm->start_edges, farm->finish_edges));
		IS_FLAG(FLAG_TIME) && (end = clock());
		IS_FLAG(FLAG_TIME) && ft_printf("find pathes time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
		IS_FLAG(FLAG_DEBUG) && debug_show_paths(paths_combs);
		IS_FLAG(FLAG_TIME) && (begin = clock());
		let_ants_to_paths(farm, choose_best_comb_paths(paths_combs));
		IS_FLAG(FLAG_TIME) && (end = clock());
		IS_FLAG(FLAG_TIME) && ft_printf("let ants time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
		IS_FLAG(FLAG_TIME) && (begin = clock());
		clear_paths_comb(paths_combs);
		IS_FLAG(FLAG_TIME) && (end = clock());
		IS_FLAG(FLAG_TIME) && ft_printf("clear time: %f\n", (double)(end - begin) / CLOCKS_PER_SEC);
	}
	clear_farm(farm);
	return (EXIT_SUCCESS);
}
