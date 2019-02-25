/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:47:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/25 20:02:00 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IH_H
# define LEM_IH_H

# include <stdint.h>
# include <limits.h>

# include "libft.h"
# include "ft_printf.h"
// # include "draw.h"

# define FLAG_VISUALISE	1
# define FLAG_DEBUG		2

# define ROOM_START		1
# define ROOM_END		2

# define WIN_SIZE		500

# define IS_FLAG(f)		(args->flags & f)

typedef struct	s_args {
	int		flags;
	char	*filename;
}				t_args;

typedef struct	s_room {
	char	*name;
	int		ant_num;
	int		x;
	int		y;
	char	status;
}				t_room;

typedef struct s_dlist	t_path;

typedef struct	s_farm {
	int			ants_count;
	int			finished_ants;
	t_room		**rooms;
	int			count_rooms;
	int8_t**	incidence;
	t_path		**best_paths;
# ifdef DRAW_H
	t_mlx		*visualiser;
# endif
}				t_farm;

/*
**	Read farm
*/
t_farm		*read_farm_map();
t_room		**create_sort_room_arr(t_list *rooms_head, int count_rooms);

/*
**	Incidence matrix
*/
int8_t**	create_incidence_matrix(int size);
int			add_edge(
	t_room **rooms, int8_t **incidence, char *parent_name, char *child_name);
void		show_incidence_matrix(t_room **rooms, int8_t **incidence, int size);

/*
**	Algorithm
*/
int			get_max_count_need_unique_paths(int8_t **incidence, int size);
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

/*
**	Visualisation
*/
int			press_key_callback(int key, t_farm *farm);

#endif