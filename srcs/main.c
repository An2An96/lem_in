/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 15:46:02 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// t_path ***test(t_room **rooms)
// {
// 	t_path ***paths;

// 	paths = (t_path***)malloc(3 * sizeof(t_path**));

// //	Comb 1
// 	paths[0] = (t_path**)malloc(2 * sizeof(t_path*));

// 	//	[Comb 1] Path 1
// 	paths[0][0] = ft_dlst_create();
// 	ft_dlst_push_back(paths[0][0], ft_create_node_ptr(rooms[1]));
// 	ft_dlst_push_back(paths[0][0], ft_create_node_ptr(rooms[2]));
// 	ft_dlst_push_back(paths[0][0], ft_create_node_ptr(rooms[8]));
// 	paths[0][1] = NULL;

// //	Comb 2
// 	paths[1] = (t_path**)malloc(3 * sizeof(t_path*));
// 	paths[1][0] = ft_dlst_create();
// 	paths[1][1] = ft_dlst_create();

// 	//	[Comb 2] Path 1
// 	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[5]));
// 	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[6]));
// 	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[7]));
// 	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[2]));
// 	ft_dlst_push_back(paths[1][0], ft_create_node_ptr(rooms[8]));

// 	//	[Comb 2] Path 2
// 	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[1]));
// 	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[3]));
// 	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[4]));
// 	ft_dlst_push_back(paths[1][1], ft_create_node_ptr(rooms[8]));
// 	paths[1][2] = NULL;

// 	paths[2] = NULL;
// 	return (paths);
// }

int	throw_error(const char *title, const char *err)
{
	if (title)
		ft_putstr_fd(title, 2);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
	return (1);
}

static char	*read_args(int argc, char **argv, int *flags)
{
	int		i;
	char	*filename;

	i = 1;
	filename = NULL;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-v"))
			*flags |= FLAG_VISUALISE;
		else if (!ft_strcmp(argv[i], "-d"))
			*flags |= FLAG_DEBUG;
		else if (!ft_strcmp(argv[i], "-f") && i + 1 < argc)
		{
			filename = argv[i + 1];
			i++;
		}
		i++;
	}
	return (filename);
}

int			main(int argc, char **argv)
{
	int			fd;
	int			i;
	char		*filename;
	t_farm		*farm;
	t_path_comb	*paths_combs;

	SECURE_MALLOC(farm = (t_farm*)ft_memalloc(sizeof(t_farm)));

	filename = read_args(argc, argv, &farm->flags);
	(fd = filename ? open(filename, O_RDONLY) : 0) == -1
		&& throw_error(STR_ERROR_SYS, strerror(errno));
	read_farm_map(fd, farm);

	if (IS_FLAG(FLAG_DEBUG))
	{
		i = -1;
		while (++i < farm->count_rooms)
			ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
	}
	if (!(farm->rooms[0]->types == (ROOM_START | ROOM_END)))
	{
		dijkstra_algo(farm);
		if (IS_FLAG(FLAG_DEBUG))
		{
			for (int i = 0; i < farm->count_rooms; i++)
				ft_printf("room %s (%d) weight: %d\n", farm->rooms[i]->name, i, farm->rooms[i]->weight);
		}

		paths_combs = find_unique_paths(farm, MIN(farm->start_edges, farm->finish_edges));

		if (IS_FLAG(FLAG_DEBUG))
		{
			i = 0;
			
			while (paths_combs[i].count)
			{
				ft_printf("%d comb (%d paths, %d steps):\n", i, paths_combs[i].count, paths_combs[i].steps);
				int j = 0;
				while (paths_combs[i].paths[j])
				{
					show_path(paths_combs[i].paths[j]);
					j++;
				}
				i++;
			}
		}

		let_ants_to_paths(farm, choose_best_comb_paths(paths_combs, farm->ants_count));
	}
	return (EXIT_SUCCESS);
}