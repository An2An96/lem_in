/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_diff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 20:24:56 by wballaba          #+#    #+#             */
/*   Updated: 2019/02/25 17:10:01 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	get_paths_diff(t_path **paths, int path_idx)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	while (i < path_idx)
	{
		sum += paths[path_idx]->size - paths[i]->size;
		i++;
	}
	return (sum);
}
