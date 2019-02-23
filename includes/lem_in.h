/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:47:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/23 19:21:11 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IH_H
# define LEM_IH_H

# include <stdint.h>
# include <limits.h>

# include "libft.h"
# include "ft_printf.h"
# include "draw.h"

# define	ROOM_START	1
# define	ROOM_END	2

# define	WIN_SIZE	500

typedef struct	s_node {
	char	*name;
	int		ant_num;
	int		x;
	int		y;
	char	status;
}				t_node;

typedef struct	s_path {
	int			*idx;
	int			count_node;
}				t_path;

typedef struct	s_farm {
	int			ants_count;
	int			finished_ants;
	t_node		**rooms;
	int			count_rooms;
	int8_t**	incidence;
	t_path		**best_paths;
	t_mlx		*visualiser;
}				t_farm;

/*
**	Read farm
*/
t_farm		*read_farm_map();
t_node		**create_sort_room_arr(t_list *rooms_head, int count_rooms);

/*
**	Incidence matrix
*/
int8_t**	create_incidence_matrix(int size);
int			add_edge(
	t_node **rooms, int8_t **incidence, char *parent_name, char *child_name);
void		show_incidence_matrix(t_node **rooms, int8_t **incidence, int size);

/*
**	Algorithm
*/
int			get_max_count_need_unique_paths(int8_t **incidence, int size);
t_path		***find_unique_paths(t_farm *farm, int count);
int			find_best_comb_paths(t_path ***path_combs, int ants_count);
void		let_ants_to_paths(t_farm *farm);
void		make_step(t_farm *farm);

/*
**	Utils functions
*/
t_node		*find_node_by_name(t_node **rooms, char *name);
int			find_node_index_by_name(t_node **rooms, char *name);
int			get_paths_diff(t_path **paths, int path_idx);

#endif