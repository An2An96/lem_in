/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/21 18:22:34 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_farm	*farm;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			exit(-1);
	}
	else
		fd = 0;
	farm = read_farm_map(fd);
	i = 0;
	while (i < farm->count_rooms)
	{
		ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
		i++;
	}
	show_incidence_matrix(farm->rooms, farm->incidence, farm->count_rooms);

	// int max_unique_paths = get_max_count_need_unique_paths(farm->incidence, farm->count_rooms);
	// ft_printf("max unique paths: %d\n", max_unique_paths);
	// find_unique_paths(farm, max_unique_paths);

	t_path ***paths;

	paths = (t_path***)malloc(3 * sizeof(t_path**));
	paths[0] = (t_path**)malloc(sizeof(t_path*));
	paths[0][0] = (t_path*)malloc(sizeof(t_path));
	paths[0][0]->idx = (int*)malloc(3 * sizeof(int));
	paths[0][0]->idx[0] = 1;
	paths[0][0]->idx[1] = 2;
	paths[0][0]->idx[2] = 7;
	paths[0][0]->count_node = 3;

	paths[1] = (t_path**)malloc(2 * sizeof(t_path*));
	paths[1][0] = (t_path*)malloc(sizeof(t_path));
	paths[1][1] = (t_path*)malloc(sizeof(t_path));
	paths[1][0]->idx = (int*)malloc(4 * sizeof(int));
	paths[1][1]->idx = (int*)malloc(4 * sizeof(int));
	paths[1][0]->idx[0] = 1;
	paths[1][0]->idx[1] = 3;
	paths[1][0]->idx[2] = 4;
	paths[1][0]->idx[3] = 7;
	paths[1][0]->count_node = 4;
	
	paths[1][1]->idx[0] = 5;
	paths[1][1]->idx[1] = 6;
	paths[1][1]->idx[2] = 2;
	paths[1][1]->idx[3] = 7;
	paths[1][1]->count_node = 4;

	paths[2] = NULL;

	ft_printf("Best paths:\n");
	int idx = find_best_comb_paths(paths, farm->ants_count);
	i = 0;
	while (i <= idx)
	{
		int j = 0;
		ft_printf("%s", farm->rooms[0]->name);
		while (j < paths[idx][i]->count_node)
		{
			ft_printf(" -> %s", farm->rooms[ paths[idx][i]->idx[j] ]->name);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	return (0);
}