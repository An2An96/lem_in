/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualiser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:22:46 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/02 17:53:44 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_visual_farm	*create_new_dfarm(t_farm	*farm)
{
	t_visual_farm	*vfarm;

	if (!(vfarm = (t_visual_farm *)malloc(sizeof(t_visual_farm))))
		return (0);
	vfarm->visual = ft_create_window(WIN_SIZE, WIN_SIZE, "KK");
	vfarm->farm = farm;
	vfarm->image = ft_create_image(vfarm->visual->mlx_ptr, WIN_SIZE, WIN_SIZE);
	return (vfarm);
}

int	read_step(t_farm	*farm)
{
	t_visual_farm	*vfarm;
	vfarm = create_new_dfarm(farm);
	mlx_loop_hook(vfarm->visual->mlx_ptr, lem_in_draw, vfarm);
	mlx_loop(vfarm->visual->mlx_ptr);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_farm	*farm;

	if ((fd = open(args->filename, O_RDONLY)) == -1)
		exit(-1);
	else
		fd = 0;
	if (!(farm = read_farm_map(fd)))
		exit(-1);
	read_step(farm)
}