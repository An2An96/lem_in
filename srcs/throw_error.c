/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   throw_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:17:39 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 21:18:05 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	throw_error(const char *title, const char *err)
{
	if (title)
		ft_putstr_fd(title, 2);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
	return (1);
}
