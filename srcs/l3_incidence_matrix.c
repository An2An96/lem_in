/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3_incidence_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:37:36 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/23 19:15:35 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Создает матрицу инцидентности заданного размера
*/

int8_t	**create_incidence_matrix(int size)
{
	int		i;
	int		j;
	int8_t	**matrix;

	// ft_printf("create matrix: %d\n", size);
	if (!(matrix = (int8_t**)malloc(size * sizeof(int8_t*))))
		exit(-1);
	i = 0;
	while (i < size)
	{
		j = 0;
		if (!(matrix[i] = (int8_t*)malloc(size * sizeof(int8_t))))
			exit(-1);
		while (j < size)
		{
			matrix[i][j] = 0;
			// ft_printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
			j++;
		}
		i++;
	}
	return (matrix);
}

/*
**	Делает смежными две вершины, добавляя соответствие в матрицу инцидентности
*/

int		add_edge(
	t_node **rooms, int8_t **incidence, char *parent_name, char *child_name)
{
	int parent_idx;
	int child_idx;

	// ft_printf("create edge %s -> %s\n", parent_name, child_name);
	parent_idx = find_node_index_by_name(rooms, parent_name);
	child_idx = find_node_index_by_name(rooms, child_name);
	if (parent_idx < 0 || child_idx < 0)
		return (0);
	incidence[parent_idx][child_idx] = 1;
	ft_printf("%d -> %d (%d)\n", parent_idx, child_idx, incidence[parent_idx][child_idx]);
	return (1);
}

/*
**	Выводит матрицу инцидентности заменяя индексы вершин их именами
*/

void	show_incidence_matrix(t_node **rooms, int8_t **incidence, int size)
{
	int i;
	int j;
	int len;

	i = -1;
	len = ft_printf("       ");
	while (++i < size)
		len += ft_printf(" %5s", rooms[i]->name);
	ft_printf("\n");
	i = -1;
	ft_printf("%*s\n", len,
		"________________________________________________");
	i = -1;
	while (++i < size)
	{
		ft_printf("%5s |", rooms[i]->name);
		j = -1;
		if (incidence && incidence[i])
		{
			while (++j < size)
				ft_printf(" %5d", incidence[i][j]);
		}
		
		ft_printf("\n");
	}
}
