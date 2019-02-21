/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/21 14:31:58 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	t_farm	*farm;

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			exit(-1);
	}
	else
		fd = 0;
	farm = read_farm_map(fd);
	i = 0;
	while (i < farm->count_rooms)
	{
		ft_printf("[%2d] -> %s\n", i, farm->rooms[i]->name);
		i++;
	}
	show_incidence_matrix(farm->rooms, farm->incidence, farm->count_rooms);
	return (0);
}