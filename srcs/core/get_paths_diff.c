/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_diff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 20:24:56 by wballaba          #+#    #+#             */
/*   Updated: 2019/03/05 18:21:53 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	get_paths_diff(t_path_comb *path_comb, int path_idx)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	while (i < path_idx)
	{
		sum += path_comb->paths[path_idx]->size - path_comb->paths[i]->size;
		i++;
	}
	return (sum);
}
