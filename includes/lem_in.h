/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:47:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 16:17:07 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IH_H
# define LEM_IH_H

# include <stdint.h>
# include <limits.h>
# include <string.h>
# include <errno.h>

# include "libft.h"
# include "ft_printf.h"

# define FLAG_VISUALISE		1
# define FLAG_DEBUG			2

# define ROOM_MID			0
# define ROOM_START			1
# define ROOM_END			2

# define LIST(el, type)		((type)el->content)

# define IS_FLAG(f)			(farm->flags & f)
# define SECURE_MALLOC(a)	!(a) && throw_error(MEMORY_ERR)		

# define COLOR_ERROR		"\x1b[1;31m"
# define COLOR_NONE			"\x1b[0m"

# define STR_ERROR_SYS		COLOR_ERROR"[System Error]: "COLOR_NONE
# define STR_ERROR_VALID	COLOR_ERROR"[Validation Error]: "COLOR_NONE
# define STR_ERROR_PATH		COLOR_ERROR"[Path Error]: "COLOR_NONE

# define MEMORY_ERR			STR_ERROR_SYS, "Not enough memory"

typedef struct s_dlist	t_path;

typedef struct	s_args
{
	int		flags;
	char	*filename;
}				t_args;

typedef struct	s_path_comb
{
	t_path	**paths;
	int		count;
	int		steps;
}				t_path_comb;

typedef struct	s_room
{
	char	*name;
	int		ant_num;
	int		x;
	int		y;
	int8_t	types;
	int		weight;
	t_list	*neighbors;
	t_dlist	*paths;
	bool	processed_paths[10000];
}				t_room;

typedef struct	s_farm
{
	int			flags;
	t_room		**rooms;
	int			count_rooms;
	int			ants_count;
	int			finished_ants;
	int			start_edges;
	int			finish_edges;
	t_path_comb	*best_paths;
	int			cur_comb;
}				t_farm;

/*
**	**********
*/

int			throw_error(const char *title, const char *err);

/*
**	Read farm
*/

t_farm		*read_farm_map();
t_room		**create_sort_room_arr(t_list *rooms_head, int count_rooms);

/*
**	Algorithm
*/

void		dijkstra_algo(t_farm *farm);
t_path_comb	*find_unique_paths(t_farm *farm, int count);
void		sort_paths_by_length(t_path **paths);
int			find_best_comb_paths(t_path_comb **path_combs, int ants_count);
void		let_ants_to_paths(t_farm *farm, t_path_comb *path_comb);
void		make_step(t_farm *farm);

int			get_steps_for_comb(t_path_comb *path_combs, int ants_count);
t_path_comb	*choose_best_comb_paths(t_path_comb *path_combs, int ants_count);

void		show_map_config(t_farm *farm);

/*
**	Utils functions
*/

t_room		*find_node_by_name(t_room **rooms, int count_rooms, char *name);
int			find_node_index_by_name(t_room **rooms, int count_rooms, char *name);
int			get_paths_diff(t_path_comb *path_comb, int path_idx);
void		free_split_result(char **res);
int			show_path(t_path *path);
int			show_comb(t_path_comb *path_comb);
int			min_atoi(const char *str);

#endif
