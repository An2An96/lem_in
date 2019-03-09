/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:47:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 16:46:22 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <time.h>

# include "libft.h"
# include "ft_printf.h"

# define COLOR_BLACK		"\x1b[30m"
# define COLOR_CYAN			"\x1b[36m"
# define COLOR_ERROR		"\x1b[1;31m"
# define COLOR_NONE			"\x1b[0m"

# define BG_COLOR_WHITE		"\x1b[47m"
# define BG_COLOR_NONE		"\x1b[49m"

# define COLOR_BLACK		"\x1b[30m"
# define COLOR_CYAN			"\x1b[36m"
# define COLOR_ERROR		"\x1b[1;31m"
# define COLOR_NONE			"\x1b[0m"

# define BG_COLOR_WHITE		"\x1b[47m"
# define BG_COLOR_NONE		"\x1b[49m"

# define FLAG_PRINT			1
# define FLAG_DEBUG			2
# define FLAG_TIME			4

# define ROOM_MID			0
# define ROOM_START			1
# define ROOM_END			2

# define LIST(el, type)		((type)el->content)
# define IS_FLAG(f)			(farm->flags & f)
# define SECURE_MALLOC(a)	!(a) && throw_error(MEMORY_ERR)

# define DELAY				(double)(g_end - g_begin) / CLOCKS_PER_SEC
# define DELAY_STYLES		BG_COLOR_WHITE COLOR_BLACK
# define CLEAR_STYLES		COLOR_NONE BG_COLOR_NONE
# define DELAY_MESSAGE		DELAY_STYLES "%-30s %f" CLEAR_STYLES "\n"
# define SHOW_DELAY(str)	ft_printf(DELAY_MESSAGE, str, DELAY)

# define START_DELAY		IS_FLAG(FLAG_TIME) && (g_begin = clock())
# define _END_DELAY(str)	((g_end = clock()) && SHOW_DELAY(str))
# define END_DELAY(str)		IS_FLAG(FLAG_TIME) && _END_DELAY(str)

# define STR_ERROR_SYS		COLOR_ERROR"[System Error]: "COLOR_NONE
# define STR_ERROR_ARGS		COLOR_ERROR"[Arguments Error]: "COLOR_NONE
# define STR_ERROR_VALID	COLOR_ERROR"[Validation Error]: "COLOR_NONE
# define STR_ERROR_PATH		COLOR_ERROR"[Path Error]: "COLOR_NONE

# define MEMORY_ERR			STR_ERROR_SYS, "Not enough memory"
# define ERR_MAP_INVALID	STR_ERROR_VALID, "Map contains insufficient data"

/*
**	Для обработки флага -t - замеряющего время выполнения блоков программы
*/

clock_t		g_begin;
clock_t		g_end;

typedef struct s_dlist		t_path;

typedef struct	s_args
{
	int		flags;
	char	*filename;
}				t_args;

typedef struct	s_path_comb
{
	t_path	**paths;
	int		count;
	int		last_free_idx;
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
}				t_room;

typedef struct	s_farm
{
	int			max_paths;
	int			flags;
	t_room		**rooms;
	int			count_rooms;
	int			ants_count;
	int			finished_ants;
	int			start_edges;
	int			finish_edges;
	int			cur_comb;
	bool		**intersections;
	size_t		intersections_size;
	size_t		intersections_length;
}				t_farm;

/*
**	**********
*/

int				throw_error(const char *title, const char *err);
char			*read_args(int argc, char **argv, int *flags, int *max_paths);

/*
**	Read farm
*/

t_farm			*read_farm_map();
t_room			*create_room(char *name, char *x, char *y, int8_t type);
int				add_edge(t_farm *farm, char *parent_name, char *child_name);
t_room			**create_sort_room_arr(t_list **rooms_head, int count_rooms);

/*
**	Algorithm
*/

t_path_comb		*find_unique_paths(t_farm *farm, int count);
bool			find_comb(
	t_farm *farm, t_stack *result, t_node *cur_path_node, int need_path);
void			check_intersections(t_farm *farm);
int				find_best_comb_paths(t_path_comb **path_combs, int ants_count);
int				get_steps_for_comb(t_path_comb *path_combs, int ants_count);
t_path_comb		*choose_best_comb_paths(t_path_comb *path_combs);
int				let_ants_to_paths(t_farm *farm, t_path_comb *path_comb);
void			show_map_config(t_farm *farm);

/*
**	Paths functions
*/

int				find_cycle(t_path *path, t_room *room);
t_path_comb		*allocate_mem_for_paths_combs(int count);
t_path			*make_path_copy(t_path *path);

/*
**	Utils functions
*/

t_room			*find_node_by_name(t_room **rooms, int count_rooms, char *name);
int				find_node_idx_by_name(
	t_room **rooms, int count_rooms, char *name);
int				get_paths_diff(t_path_comb *path_comb, int path_idx);
void			free_lst(void *content, size_t content_size);
void			free_paths(void *content, size_t content_size);
void			free_split_result(char **res);
int				min_atoi(
	const char *str, const char *error_title, const char *error);

/*
**	Debug functions
*/

int				debug_show_rooms(t_farm *farm);
int				debug_show_path(t_path *path);
int				debug_show_comb(t_path_comb *path_comb);
int				debug_show_paths_combs(t_path_comb *paths_combs);
int				debug_show_matrix(bool **matrix, int size);

#endif
