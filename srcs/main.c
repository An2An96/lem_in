/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/23 19:24:10 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//	!!! Сортировать маршруты по количеству вершин для каждой комбинации
//	!!! перед передачей в find_best_comb_paths

t_path ***test()
{
	t_path ***paths;

	paths = (t_path***)malloc(3 * sizeof(t_path**));
	paths[0] = (t_path**)malloc(2 * sizeof(t_path*));
	paths[0][0] = (t_path*)malloc(sizeof(t_path));
	paths[0][0]->idx = (int*)malloc(3 * sizeof(int));
	paths[0][0]->idx[0] = 1;
	paths[0][0]->idx[1] = 2;
	paths[0][0]->idx[2] = 8;
	paths[0][0]->count_node = 3;
	paths[0][1] = NULL;

	paths[1] = (t_path**)malloc(3 * sizeof(t_path*));
	paths[1][0] = (t_path*)malloc(sizeof(t_path));
	paths[1][1] = (t_path*)malloc(sizeof(t_path));
	paths[1][0]->idx = (int*)malloc(4 * sizeof(int));
	paths[1][1]->idx = (int*)malloc(5 * sizeof(int));
	paths[1][0]->idx[0] = 1;
	paths[1][0]->idx[1] = 3;
	paths[1][0]->idx[2] = 4;
	paths[1][0]->idx[3] = 8;
	paths[1][0]->count_node = 4;
	
	paths[1][1]->idx[0] = 5;
	paths[1][1]->idx[1] = 6;
	paths[1][1]->idx[2] = 7;
	paths[1][1]->idx[3] = 2;
	paths[1][1]->idx[4] = 8;
	paths[1][1]->count_node = 5;

	paths[1][2] = NULL;

	paths[2] = NULL;
	return (paths);
}

void	show_path(t_farm *farm, t_path *path)
{
	int i;

	i = 0;
	ft_printf("%s", farm->rooms[i]->name);
	while (i < path->count_node)
	{
		ft_printf(" -> %s[%d]", farm->rooms[ path->idx[i] ]->name, path->idx[i]);
		i++;
	}
	ft_printf("\n");
}

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_farm	*farm;

	if (argc > 1)
	{
		if ((fd = open(argv[argc - 1], O_RDONLY)) == -1)
			exit(-1);
	}
	else
		fd = 0;
	
	if (!(farm = read_farm_map(fd)))
		exit(-1);
	
	farm->finished_ants = 0;
	if (!ft_strcmp(argv[1], "-v"))
		farm->visualiser = ft_create_window(WIN_SIZE, WIN_SIZE, "lem-in");
	else
		farm->visualiser = NULL;
	i = 0;
	while (i < farm->count_rooms)
	{
		ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
		i++;
	}
	show_incidence_matrix(farm->rooms, farm->incidence, farm->count_rooms);

	t_path ***paths_combs = test();
	// int max_unique_paths = get_max_count_need_unique_paths(farm->incidence, farm->count_rooms);
	// ft_printf("max unique paths: %d\n", max_unique_paths);
	// find_unique_paths(farm, max_unique_paths);
	
	int idx = find_best_comb_paths(paths_combs, farm->ants_count);
	farm->best_paths = paths_combs[idx];
	ft_printf("Best paths comb:\n");
	i = -1;
	while (++i <= idx)
		show_path(farm, farm->best_paths[i]);

	let_ants_to_paths(farm);
	return (0);
}