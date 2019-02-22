/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_diff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 20:24:56 by wballaba          #+#    #+#             */
/*   Updated: 2019/02/22 20:25:13 by wballaba         ###   ########.fr       */
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
		sum += paths[path_idx]->count_node - paths[i]->count_node;
		i++;
	}
	return (sum);
}
