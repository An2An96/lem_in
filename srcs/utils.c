/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:47:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/09 16:47:03 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_lst(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

void	free_paths(void *content, size_t content_size)
{
	ft_dlst_del((t_path**)&content, NULL);
	free(content);
	content_size = 0;
}

void	free_split_result(char **res)
{
	int i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
}

int		min_atoi(const char *str, const char *error_title, const char *error)
{
	char	negative;
	int		result;
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		negative = 1 - (2 * (str[i] == '-'));
		i++;
	}
	else
		negative = 1;
	result = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			throw_error(error_title, error);
		result = (result * 10) + (str[i] - '0');
		if (result < 0)
			throw_error(error_title, error);
		i++;
	}
	return ((int)result * negative);
}
