/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:22:46 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/08 20:26:18 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

static void	read_step_ant(t_vfarm *vfarm, char *res)
{
	t_room	*room;
	int		i;
	int		ant_nbr;
	char	*room_name;

	i = 1;
	if ((ant_nbr = ft_atoi(res + i)) > vfarm->farm->ants_count)
		throw_error(STR_ERROR_VALID, "The number ants is greater than stated");
	while (ft_isdigit(res[i]))
		i++;
	i++;
	room_name = ft_strdup(res + i);
	room = find_node_by_name(
		vfarm->farm->rooms, vfarm->farm->count_rooms, room_name);
	room->ant_num = ant_nbr;
	move_ant(vfarm->ant[ant_nbr - 1], room, vfarm);
	free(room_name);
}

static int	read_line(t_vfarm *vfarm, char *line)
{
	int		i;
	char	**res;

	i = -1;
	while (++i < vfarm->farm->count_rooms)
		vfarm->farm->rooms[i]->ant_num = 0;
	res = ft_strsplit(line, ' ');
	i = 0;
	while (res[i])
	{
		read_step_ant(vfarm, res[i]);
		i++;
	}
	vfarm->count_line++;
	return (0);
}

static int	lem_in_draw(int key, t_vfarm *vfarm)
{
	char	*line;

	if (key == KEY_SPACE)
	{
		if (get_next_line(vfarm->fd, &line) == 1)
		{
			if (vfarm->farm->flags & FLAG_PRINT)
				ft_printf("%s\n", line);
			if (read_line(vfarm, line))
			{
				free(line);
				mlx_destroy_window(vfarm->visual->mlx_ptr,
					vfarm->visual->win_ptr);
				exit(0);
			}
			if (line)
				free(line);
			visual_farm(vfarm);
			draw_run_ant(vfarm);
		}
	}
	else if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D ||
		key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_Q || key == KEY_E)
		move_farm(key, vfarm);
	return (0);
}

static int	start_visual(int fd, t_farm *farm)
{
	t_vfarm	*vfarm;

	if (!(vfarm = (t_vfarm *)ft_memalloc(sizeof(t_vfarm))))
		return (0);
	vfarm->fd = fd;
	vfarm->visual = ft_create_window(WIN_SIZE, WIN_SIZE, "KK");
	vfarm->farm = farm;
	vfarm->count_line = 0;
	get_abs_val(farm, vfarm);
	get_arr_ant(vfarm);
	create_farm_image(vfarm);
	visual_farm(vfarm);
	mlx_hook(vfarm->visual->win_ptr, 2, 1L << 17, ft_key_press_esc_close, NULL);
	mlx_hook(vfarm->visual->win_ptr, 17, 1L << 17, ft_close, NULL);
	mlx_key_hook(vfarm->visual->win_ptr, lem_in_draw, vfarm);
	mlx_loop(vfarm->visual->mlx_ptr);
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_farm	*farm;
	char	*filename;

	SECURE_MALLOC(farm = (t_farm*)ft_memalloc(sizeof(t_farm)));
	filename = read_args(argc, argv, &farm->flags);
	(fd = filename ? open(filename, O_RDONLY) : 0) == -1
		&& throw_error(STR_ERROR_SYS, strerror(errno));
	read_farm_map(fd, farm);
	start_visual(fd, farm);
	return (0);
}
