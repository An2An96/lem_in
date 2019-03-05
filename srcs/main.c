/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/05 20:22:58 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//	!!! Сортировать маршруты по количеству вершин для каждой комбинации
//	!!! перед передачей в find_best_comb_paths

t_path ***test(t_room **rooms)
{
	t_path ***paths;

	paths = (t_path***)malloc(3 * sizeof(t_path**));

//	Comb 1
	paths[0] = (t_path**)malloc(2 * sizeof(t_path*));

	//	[Comb 1] Path 1
	paths[0][0] = ft_dlst_create();
	ft_dlst_push_back(paths[0][0], ft_create_node_ptr(rooms[1]));
	ft_dlst_push_back(paths[0][0], ft_create_node_ptr(rooms[2]));
	ft_dlst_push_back(paths[0][0], ft_create_node_ptr(rooms[8]));
	paths[0][1] = NULL;

//	Comb 2
	paths[1] = (t_path**)malloc(3 * sizeof(t_path*));
	paths[1][0] = ft_dlst_create();
	paths[1][1] = ft_dlst_create();

	//	[Comb 2] Path 1
	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[5]));
	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[6]));
	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[7]));
	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[2]));
	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[8]));

	//	[Comb 2] Path 2
	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[1]));
	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[3]));
	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[4]));
	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[8]));
	paths[1][2] = NULL;

	paths[2] = NULL;
	return (paths);
}

t_args	*read_args(int argc, char **argv)
{
	int		i;
	t_args *args;

	if (!(args = (t_args*)ft_memalloc(sizeof(t_args))))
		return (NULL);
	i = 1;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-v"))
			args->flags |= FLAG_VISUALISE;
		else if (!ft_strcmp(argv[i], "-d"))
			args->flags |= FLAG_DEBUG;
		else if (!ft_strcmp(argv[i], "-f") && i + 1 < argc)
		{
			args->filename = argv[i + 1];
			i++;
		}
		i++;
	}
	return (args);
}

void	show_map_params(t_farm *farm)
{
	int i;
	t_list *neighbor_lst;
	int		neighbor_idx;

	ft_putnbr(farm->ants_count);
	write(1, "\n", 1);
	i = 0;
	while (i < farm->count_rooms)
	{
		if (i == 0)
			write(1, "##start\n", 8);
		else if (i == farm->count_rooms - 1)
			write(1, "##end\n", 6);
		ft_putstr(farm->rooms[i]->name);
		write(1, "\n", 1);
		i++;
	}
	i = 0;
	while (i < farm->count_rooms)
	{
		neighbor_lst = farm->rooms[i]->neighbors;
		while (neighbor_lst)
		{
			neighbor_idx = *LIST(neighbor_lst, int*);
			if (neighbor_idx > i)
			{
				ft_putstr(farm->rooms[i]->name);
				write(1, "-", 1);
				ft_putstr(farm->rooms[neighbor_idx]->name);
				write(1, "\n", 1);
			}
			neighbor_lst = neighbor_lst->next;
		}
		i++;
	}
	write(1, "\n", 1);
}

int main(int argc, char **argv)
{
	int			fd;
	int			i;
	t_farm		*farm;
	t_args		*args;
	t_path_comb	*paths_combs;

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

	farm->finished_ants = 0;
	i = 0;
	if (IS_FLAG(FLAG_DEBUG))
	{
		i = -1;
		while (++i < farm->count_rooms)
			ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
	}

	dijkstra_algo(farm);
	if (IS_FLAG(FLAG_DEBUG))
	{
		for (int i = 0; i < farm->count_rooms; i++)
			ft_printf("room %s (%d) weight: %d\n", farm->rooms[i]->name, i, farm->rooms[i]->weight);
	}

	// paths_combs = test(farm->rooms);
	paths_combs = find_unique_paths(farm, MIN(farm->start_edges, farm->finish_edges));

	if (IS_FLAG(FLAG_DEBUG))
	{
		i = 0;
		
		while (paths_combs[i].count)
		{
			ft_printf("%d comb (%d steps):\n", i, paths_combs[i].steps);
			int j = 0;
			while (paths_combs[i].paths[j])
			{
				show_path(paths_combs[i].paths[j]);
				j++;
			}
			i++;
		}
	}
	// farm->best_paths = paths_combs[idx];
	// if (IS_FLAG(FLAG_DEBUG))
	// {
	// 	ft_printf("Best paths comb:\n");
	// 	i = -1;
	// 	while (best_comb->paths[++i])
	// 		show_path(best_comb->paths[i]);
	// }

	show_map_params(farm);
	let_ants_to_paths(farm, choose_best_comb_paths(paths_combs, farm->ants_count));
	return (0);
}