/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wballaba <wballaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:07:21 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/08 16:36:15 by wballaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*read_args(int argc, char **argv, int *flags)
{
	int		i;
	char	*filename;

	i = 1;
	filename = NULL;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-p"))
			*flags |= FLAG_PRINT;
		else if (!ft_strcmp(argv[i], "-d"))
			*flags |= FLAG_DEBUG;
		else if (!ft_strcmp(argv[i], "-t"))
			*flags |= FLAG_TIME;
		else if (!ft_strcmp(argv[i], "-f") && i + 1 < argc)
		{
			filename = argv[i + 1];
			i++;
		}
		i++;
	}
	return (filename);
}
