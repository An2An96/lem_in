/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:47:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/20 17:51:11 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IH_H
# define LEM_IH_H

# include <stdint.h>

# include "libft.h"
# include "ft_printf.h"

# define	ROOM_START	1
# define	ROOM_END	2

typedef struct	s_node {
	char	*name;
	int		ant_num;
	int		x;
	int		y;
	char	status;
	t_list	*childs;
}				t_node;

typedef struct	s_farm {
	int		ants_count;
	int		*ant_nodes;
	t_node	*start;
	t_node	*rooms;

	int8_t**	incidence;
}				t_farm;

t_node	*find_node_by_name(t_node **rooms, char *name);
int		find_node_index_by_name(t_node **rooms, char *name);

t_farm	*read_farm_map();

#endif