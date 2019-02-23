/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l7_visual_farm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 19:27:35 by wballaba          #+#    #+#             */
/*   Updated: 2019/02/23 20:11:25 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	draw_node(t_farm *farm)
{
	t_params data;
	int nbr_path;
	
	nbr_path = 0;
	while (farm->rooms[nbr_path])
	{
		data.x = farm->rooms[nbr_path]->x;
		data.y = farm->rooms[nbr_path]->y;
		data.radius = 10;
		ft_draw_circle(farm->visualiser, &data, 0xFFFFFFF);
		nbr_path++;
	}
}


int		press_key_callback(int key, t_farm *farm)
{
	if (key == KEY_SPACE)
	{
		if (farm->finished_ants < farm->ants_count)
		{
			draw_node(farm);
			make_step(farm);
		}
			
	}
	return (1);
}
