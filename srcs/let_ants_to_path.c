/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_ants_to_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:25:43 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/22 13:43:11 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	let_ants_to_path(t_path **paths, t_node **rooms, t_farm *farm)
{
	int	finished_ants;
	// int index;
	int	nbr_ants;
	int pos;
	int	nbr_rout;
	int k;

	finished_ants = 0;
	nbr_ants = 1;
	nbr_rout = 0;
	// pos = path[0]->count_node;
	// index = path[0]->idx[pos];
	while (finished_ants <= farm->ants_count)
	{
		pos = paths[nbr_rout]->count_node;
		while (pos) // идем с финиша в сторону старта
		{
			k = paths[nbr_rout]->idx[pos];
			// ft_printf("ant_nbr = %d\n", farm->rooms[ paths[nbr_rout]->idx[pos] ]->ant_num);
			// ft_printf("ant_nbr - 1 = %d\n", farm->rooms[ paths[nbr_rout]->idx[pos - 1] ]->ant_num);

			ft_printf("room pos = %s\n", farm->rooms[ paths[nbr_rout]->idx[pos] ]->name);
			ft_printf("room pos - 1 = %d\n", farm->rooms[ paths[nbr_rout]->idx[pos - 1] ]->name);
			return ;
			if (farm->rooms[ paths[nbr_rout]->idx[pos] ]->ant_num == 0)
			{
				if (farm->rooms[ paths[nbr_rout]->idx[pos - 1] ]->ant_num != 0) // если в предшествующей комнате есть муравей
				{
					farm->rooms[ paths[nbr_rout]->idx[pos] ]->ant_num = farm->rooms[ paths[nbr_rout]->idx[pos - 1] ]->ant_num; // перемещаем муравья из предшествующе	комнаты в настоящую
					if (pos == 1) // если предшествующая комната это старт
						farm->rooms[ paths[nbr_rout]->idx[0] ]->ant_num = ++nbr_ants;
					else
						farm->rooms[ paths[nbr_rout]->idx[pos - 1] ]->ant_num = 0;
					// index = path[0]->idx[pos--];
				}
			}
			if (farm->rooms[ paths[nbr_rout]->count_node ]->ant_num != 0) // если муравей дошел до финиша
			{
				farm->rooms[ paths[nbr_rout]->count_node ]->ant_num = 0;
				finished_ants++;
			}
			pos--;
		}	
	}
}