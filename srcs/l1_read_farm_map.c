/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l1_read_farm_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:47:35 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 16:54:14 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			parse_room_line(
	char *line, t_list **rooms, int *count_rooms, int8_t *room_type)
{
	char			**res;
	t_room			*room;
	int				check;

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
			check += (*room_type == (ROOM_START | ROOM_END));
			room = create_room(res[0], res[1], res[2], *room_type);
			ft_lstadd(rooms, ft_lstnew(room, sizeof(t_room)));
			free(room);
			(*count_rooms)++;
			*room_type = 0;
		}
		free_split_result(res);
		return (check);
	}
	return (1);
}

inline static int	read_links(t_farm *farm, char *line)
{
	char	**res;
	bool	check;

	res = ft_strsplit(line, '-');
	check = (res[0] && res[1] && !res[2]);
	check && (check = add_edge(farm, res[0], res[1]));
	free_split_result(res);
	return (check);
}

inline static int	read_room(
	t_farm *farm, char *line, int8_t *read_status, t_list **rooms)
{
	static int8_t	room_type;
	int				result;

	result = parse_room_line(line, rooms, &farm->count_rooms, &room_type);
	if (result == 2)
		return (0);
	else if (!result)
	{
		if (!*rooms)
			throw_error(STR_ERROR_VALID, "Invalid map");
		if (room_type)
			throw_error(STR_ERROR_VALID, "Command (##) was not applied");
		*read_status = 2;
		farm->rooms = create_sort_room_arr(rooms, farm->count_rooms);
	}
	return (1);
}

static int			read_farm_map_helper(
	t_farm *farm, char *line, t_list **rooms, int8_t *read_status)
{
	if (*read_status == 0)
	{
		if ((farm->ants_count =
			min_atoi(line, STR_ERROR_VALID, "Invalid ants count")) <= 0)
			throw_error(STR_ERROR_VALID, "Invalid ants count");
		(*read_status)++;
	}
	else
	{
		if (*read_status == 1)
			if (!read_room(farm, line, read_status, rooms))
				return (0);
		if (*read_status == 2)
			if (!read_links(farm, line))
				return (0);
	}
	return (1);
}

t_farm				*read_farm_map(int fd, t_farm *farm)
{
	char	*line;
	int8_t	read_status;
	t_list	*rooms;

	rooms = NULL;
	read_status = 0;
	while (get_next_line(fd, &line))
	{
		if (!ft_strlen(line))
			break ;
		if (line[0] != '#' || line[1] == '#')
			if (!read_farm_map_helper(farm, line, &rooms, &read_status))
				break ;
		free(line);
	}
	read_status < 1 && throw_error(ERR_MAP_INVALID);
	if (!farm->rooms && rooms)
		farm->rooms = create_sort_room_arr(&rooms, farm->count_rooms);
	return (farm);
}
