/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:39:25 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 12:45:34 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualiser.h"

inline int	ft_close(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int			ft_key_press_esc_close(int key)
{
	if (key == KEY_ESC)
		ft_close();
	return (0);
}
