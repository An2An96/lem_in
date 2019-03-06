/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 22:18:05 by rschuppe         ###   ########.fr       */
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

int			main(int argc, char **argv)
{
	int			fd;
	char		*filename;
	t_farm		*farm;
	t_path_comb	*paths_combs;

	SECURE_MALLOC(farm = (t_farm*)ft_memalloc(sizeof(t_farm)));
	filename = read_args(argc, argv, &farm->flags);
	(fd = filename ? open(filename, O_RDONLY) : 0) == -1
		&& throw_error(STR_ERROR_SYS, strerror(errno));
	read_farm_map(fd, farm);
	IS_FLAG(FLAG_DEBUG) && debug_show_rooms(farm);
	if (!(farm->rooms[0]->types == (ROOM_START | ROOM_END)))
	{
		dijkstra_algo(farm);
		IS_FLAG(FLAG_DEBUG) && debug_show_weights(farm);
		paths_combs = find_unique_paths(farm,
			MIN(farm->start_edges, farm->finish_edges));
		IS_FLAG(FLAG_DEBUG) && debug_show_paths(paths_combs);
		let_ants_to_paths(farm, choose_best_comb_paths(paths_combs));
		clear_paths_comb(paths_combs);
	}
	clear_farm(farm);
	return (EXIT_SUCCESS);
}
