/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_algo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 21:05:56 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/02 18:03:05 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Нерекурсивный обход графа в ширину с помощью стека (BFS)
**	для расчет весов комнат на основе удаленности от финиша (алгоритм Дейкстра)
*/

void		dijkstra_algo(t_farm *farm)
{
	t_stack	*stack;
	t_list	*parent;
	t_room	*room;
	int		cur_room;

	if (!(stack = ft_stack_new(farm->count_rooms)))
		exit(-1);
	farm->rooms[farm->count_rooms - 1]->weight = 0;
	ft_stack_push(stack, farm->count_rooms - 1);
	while (ft_stack_pop(stack, &cur_room))
	{
		parent = farm->rooms[cur_room]->neighbors;
		while (parent)
		{
			room = farm->rooms[*(int*)parent->content];
			if (room->weight == -1)
				ft_stack_push(stack, *(int*)parent->content);
			if (room->weight == -1
				|| room->weight > farm->rooms[cur_room]->weight + 1)
				room->weight = (farm->rooms[cur_room]->weight + 1);
			parent = parent->next;
		}
	}
}