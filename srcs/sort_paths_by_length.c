/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths_by_length.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 10:21:51 by rschuppe          #+#    #+#             */
/*   Updated: 2019/02/26 10:22:03 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_paths_by_length(t_path **paths)
{

	int i;
	int j;
	int min_idx;
	t_path *tmp;

	i = 0;
	while (paths[i])
	{
		min_idx = i;
		j = min_idx;
		while (paths[++j])
			if (paths[j]->size < paths[min_idx]->size)
				min_idx = j;
		tmp = paths[min_idx];
		j = min_idx - i;
		while (j)
		{
			paths[i + j] = paths[i + j - 1];
			j--;
		}
		paths[i] = tmp;
		i++;
	}
}
