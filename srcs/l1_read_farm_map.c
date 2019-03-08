/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l1_read_farm_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 15:26:02 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			parse_room_line(
	char *line, t_list **rooms, int *count_rooms, int8_t *room_type)
{
	char			**res;
	t_room			*room;
	bool			check;

	if (!ft_strcmp(line, "##start"))
		*room_type |= ROOM_START;
	else if (!ft_strcmp(line, "##end"))
		*room_type |= ROOM_END;
	else
	{
		res = ft_strsplit(line, ' ');
		check = (res[0] && res[1] && res[2] && !res[3]);
		if (check)
		{
			room = create_room(res[0], res[1], res[2], *room_type);
			ft_lstadd(rooms, ft_lstnew(room, sizeof(t_room)));
			free(room);
			*room_type = 0;
			(*count_rooms)++;
		}
		free_split_result(res);
		return (check);
	}
	return (1);
}

inline static int	read_ants_count(t_farm *farm, char *line)
{
	if ((farm->ants_count = min_atoi(line, "Invalid ants count")) <= 0)
		throw_error(STR_ERROR_VALID, "Invalid ants count");
	return (1);
}

inline static int	read_links(t_farm *farm, char *line)
{
	char	**res;
	bool	check;

	res = ft_strsplit(line, '-');
	check = (res[0] && res[1] && !res[2]);
	if (check)
		!add_edge(farm, res[0], res[1])
			&& throw_error(STR_ERROR_VALID, ERR_NOT_EXIST_ROOM);
	free_split_result(res);
	return (check);
}

inline static int	read_room(
	t_farm *farm, char *line, int8_t *read_status, t_list **rooms)
{
	static int8_t	room_type;

	if (!parse_room_line(line, rooms, &farm->count_rooms, &room_type))
	{
		if (!*rooms)
			throw_error(STR_ERROR_VALID, "Invalid map");
		if (room_type)
			throw_error(STR_ERROR_VALID, "Command (##) was not applied");
		*read_status = 2;
		farm->rooms = create_sort_room_arr(rooms, farm->count_rooms);
		read_links(farm, line);
	}
	return (1);
}

t_farm				*read_farm_map(int fd, t_farm *farm)
{
	char	*line;
	int8_t	r_status;
	t_list	*rooms;

	rooms = NULL;
	r_status = 0;
	while (get_next_line(fd, &line))
	{
		if (!ft_strlen(line))
			break ;
		if (line[0] != '#' || line[1] == '#')
		{
			if (r_status == 0 && ++r_status)
				read_ants_count(farm, line);
			else
			{
				(r_status == 1) && read_room(farm, line, &r_status, &rooms);
				if (r_status == 2)
					if (!read_links(farm, line))
						break ;
			}
		}
		free(line);
	}
	r_status < 1 && throw_error(ERR_MAP_INVALID);
	if (!farm->rooms && rooms)
		farm->rooms = create_sort_room_arr(&rooms, farm->count_rooms);
	return (farm);
}
