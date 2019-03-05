/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:22:46 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/05 21:06:12 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_close(void)
{
	exit(-1);
	return (0);
}

int				read_step(t_visual_farm	*vfarm, char *line)
{
	int		i;
	int		j;
	char	**res;
	char	*room_name;
	int		ant_nbr;
	t_room	*room;
	

	i = -1;
	while (++i < vfarm->farm->count_rooms)
		vfarm->farm->rooms[i]->ant_num = 0;
	res = ft_strsplit(line, ' ');
	i = 0;
	while (res[i])
	{
		j = 1;
		ant_nbr = ft_atoi(res[i] + j);
		while (ft_isdigit(res[i][j]))
			j++;
		j++;
		room_name = ft_strdup(res[i] + j);
		room = find_node_by_name(vfarm->farm->rooms, room_name);
		room->ant_num = ant_nbr;
		ft_printf("room name = %s	ant num = %d	\n", room_name, room->ant_num);
		move_ant(vfarm->ant[ant_nbr - 1], room->x, room->y);
		free(room_name);
		i++;
	}
	return (0);
}

int				lem_in_draw(int key, t_visual_farm	*vfarm)
{
	char	*line;
	
	if (key == KEY_SPACE)
	{
		if (get_next_line(g_fd, &line) == 1)
		{
			ft_printf("%s\n", line);
			if (read_step(vfarm, line))
			{
				free(line);
				mlx_destroy_window(vfarm->visual->mlx_ptr, vfarm->visual->win_ptr);
				exit(0);
			}
			if (line)
				free(line);
			visual_farm(vfarm);
			draw_run_ant(vfarm);
		}
	}
	return (0);
}

void get_abs_val(t_farm	*farm, t_visual_farm	*vfarm)
{
	int	nbr_room;
	double	max_x;
	double	max_y;
	double	min_x;
	double	min_y;

	nbr_room = 0;
	max_x = farm->rooms[nbr_room]->x;
	max_y = farm->rooms[nbr_room]->y;
	min_x = max_x;
	min_y = max_y;
	while (farm->rooms[nbr_room])
	{
		max_x = MAX(max_x, farm->rooms[nbr_room]->x);
		min_x = MIN(min_x, farm->rooms[nbr_room]->x);
		max_y = MAX(max_y, farm->rooms[nbr_room]->y);
		min_y = MIN(min_y, farm->rooms[nbr_room]->y);
		nbr_room++;
	}
	if ((max_x - min_x))
		vfarm->abs_val_x = VISUAL_SIZE / (max_x - min_x);
	else
		vfarm->abs_val_x = 1;
	if ((max_y - min_y))
		vfarm->abs_val_y = VISUAL_SIZE / (max_y - min_y);
	else
		vfarm->abs_val_y = 1;
	if (min_x != max_x)
		vfarm->indent_x = -min_x * vfarm->abs_val_x + ((WIN_SIZE - (max_x - min_x) * vfarm->abs_val_x)  / 2);
	else
		vfarm->indent_x = WIN_SIZE / 2;
	if (min_y != max_y)
		vfarm->indent_y = -min_y * vfarm->abs_val_y + ((WIN_SIZE - (max_y - min_y) * vfarm->abs_val_y) / 2);
	else
		vfarm->indent_y = WIN_SIZE / 2;
}

int	start_visual(t_farm	*farm)
{
	t_visual_farm	*vfarm;

	if (!(vfarm = (t_visual_farm *)ft_memalloc(sizeof(t_visual_farm))))
		return (0);
	get_abs_val(farm, vfarm);
	vfarm->visual = ft_create_window(WIN_SIZE, WIN_SIZE, "KK");
	vfarm->farm = farm;
	arr_ant(vfarm);
	create_farm_image(vfarm);
	visual_farm(vfarm);
	mlx_hook(vfarm->visual->win_ptr, 17, 1L << 17, ft_close, NULL);
	mlx_key_hook(vfarm->visual->win_ptr, lem_in_draw, vfarm);
	mlx_loop(vfarm->visual->mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_farm	*farm;
	t_args	*args;
	
	args = read_args(argc, argv);
	if (args->filename)
	{
		if ((fd = open(args->filename, O_RDONLY)) == -1)
			exit(-1);
	}
	else
		fd = 0;
	g_fd = fd;
	if (!(farm = read_farm_map(g_fd)))
		exit(-1);
	start_visual(farm);
	return (0);
}
