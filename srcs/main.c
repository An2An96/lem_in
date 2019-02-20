/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:17:13 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/20 17:46:14 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//	Данные:
//		ant_node[] - Массив с указателями на node'у в которой находится муравей

//	Функции:
//		find_next_node_for_path(node)
//		set_ant_to_node(ant, node)

int main(int argc, char **argv)
{
	t_farm	*farm;
	int fd;

	// ft_printf("%d", ft_strcmp("abs", "baz"));

	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			exit(-1);
	}
	else
		fd = 0;
	farm = read_farm_map(fd);
	return (0);
}