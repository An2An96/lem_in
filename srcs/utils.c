/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:47:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/06 21:09:32 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define KEY_ESC	53

void	free_lst(void *content, size_t content_size)
{
	free(content);
	content_size = 0;
}

int		ft_close(void)
{
	exit(-1);
	return (0);
}

int ft_key_press_esc_close(int key, void *param)
{
	if (key == KEY_ESC)
		ft_close();
	return (0);
}

void	free_split_result(char **res)
{
	int i;

	i = 0;
	while (res[i])
		free(res[i++]);
	free(res);
}

int		show_path(t_path *path)
{
	t_node	*cur;

	cur = path->head;
	while (cur)
	{
		ft_printf("%s%s",
			cur != path->head ? " -> " : "", ((t_room*)cur->content)->name);
		cur = cur->next;
	}
	ft_printf("\n");
	return (1);
}

int		show_comb(t_path_comb *path_comb)
{
	int i;

	write(1, "Best paths comb:\n", 17);
	i = -1;
	while (path_comb->paths[++i])
		show_path(path_comb->paths[i]);
	return (1);
}

int		min_atoi(const char *str)
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
			throw_error(STR_ERROR_VALID, "Invalid coordinates of the room");
		result = (result * 10) + (str[i] - '0');
		if (result < 0)
			throw_error(STR_ERROR_VALID, "Coordinates out of range type int");
		i++;
	}
	return ((int)result * negative);
}
