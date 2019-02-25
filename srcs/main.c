/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 18:16:24 by rschuppe         ###   ########.fr       */
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
	a = 1;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 3;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 4;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));
	a = 8;
	ft_dlst_push_back(paths[1][0], ft_create_node(&a, sizeof(int)));

	//	[Comb 2] Path 2
	a = 5;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 6;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 7;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 2;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));
	a = 8;
	ft_dlst_push_back(paths[1][1], ft_create_node(&a, sizeof(int)));


	paths[1][2] = NULL;

	paths[2] = NULL;
	return (paths);
}

void	show_path(t_farm *farm, t_path *path)
{
	t_node	*cur;
	int		room_idx;

	cur = path->head;
	ft_printf("%s", farm->rooms[0]->name);
	while (cur)
	{
		room_idx = *((int*)(cur->content));
		ft_printf(" -> %s[%d]", farm->rooms[room_idx]->name, room_idx);
		cur = cur->next;
	}
	ft_printf("\n");
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

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_farm	*farm;
	t_args	*args;

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
#ifdef DRAW_H
	if (IS_FLAG(FLAG_VISUALISE))
		farm->visualiser = ft_create_window(WIN_SIZE, WIN_SIZE, "lem-in");
	else
		farm->visualiser = NULL;
#endif
	i = 0;
	if (IS_FLAG(FLAG_DEBUG))
	{
		i = -1;
		while (++i < farm->count_rooms)
			ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
		show_incidence_matrix(farm->rooms, farm->incidence, farm->count_rooms);
	}

	t_path ***paths_combs;// = test();
	int max_unique_paths = get_max_count_need_unique_paths(farm->incidence, farm->count_rooms);
	if (IS_FLAG(FLAG_DEBUG))
		ft_printf("max unique paths: %d\n", max_unique_paths);
	paths_combs = ft_memalloc((max_unique_paths + 1) * sizeof(t_path**));
	i = 0;
	// while (i < max_unique_paths)
	// {
	paths_combs[i] = find_unique_paths(farm, i + 1);
	// 	i++;
	// }
	
	int idx = find_best_comb_paths(paths_combs, farm->ants_count);
	farm->best_paths = paths_combs[idx];
	if (IS_FLAG(FLAG_DEBUG))
	{
		ft_printf("Best paths comb:\n");
		i = -1;
		while (++i <= idx)
			show_path(farm, farm->best_paths[i]);
	}
	
	let_ants_to_paths(farm);
	return (0);
}