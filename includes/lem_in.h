/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:47:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 14:09:26 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IH_H
# define LEM_IH_H

# include <stdint.h>
# include <limits.h>

# include "libft.h"

# include "ft_printf.h"
# include "draw.h"

# define FLAG_VISUALISE		1
# define FLAG_DEBUG			2

# define ROOM_MID			0
# define ROOM_START			1
# define ROOM_END			2




# define LIST(el, type)		((type)el->content)

# define IS_FLAG(f)			(args->flags & f)

int	g_fd;

typedef char bool;
enum
{
	false,
	true
};

typedef struct s_dlist	t_path;

typedef struct	s_args {
	int		flags;
	char	*filename;
}				t_args;

typedef struct	s_room {
	char	*name;
	int		ant_num;
	int		prev_ant;
	int		visited;
	int		x;
	int		y;
	char	type;
	int		weight;
	t_list	*neighbors;
	t_path	*path;
}				t_room;

typedef struct	s_farm {
	t_room		**rooms;
	int			count_rooms;
	t_path		**best_paths;
	int			ants_count;
	int			finished_ants;
	int			start_edges;
	int			finish_edges;
}				t_farm;

/*
**	Read farm
*/

t_farm		*read_farm_map();
t_room		**create_sort_room_arr(t_list *rooms_head, int count_rooms);
t_args		*read_args(int argc, char **argv);

/*
**	Algorithm
*/

void		dijkstra_algo(t_farm *farm);
t_path		**find_unique_paths(t_farm *farm, int count);
void		sort_paths_by_length(t_path **paths);
int			find_best_comb_paths(t_path ***path_combs, int ants_count);
void		let_ants_to_paths(t_farm *farm);
void		make_step(t_farm *farm);

/*
**	Utils functions
*/

t_room		*find_node_by_name(t_room **rooms, char *name);
int			find_node_index_by_name(t_room **rooms, char *name);
int			get_paths_diff(t_path **paths, int path_idx);
void		free_split_result(char **res);
void		show_path(t_farm *farm, t_path *path);

#endif