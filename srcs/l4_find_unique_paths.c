/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l4_find_unique_paths.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschuppe <rschuppe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:11:32 by rschuppe          #+#    #+#             */
/*   Updated: 2019/03/02 15:28:56 by rschuppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*ft_one_dfs(t_farm *farm, t_room *room)
{
	t_path	*res;
	t_list	*child;

	if (room == farm->rooms[farm->count_rooms - 1])
	{
		res = ft_dlst_create();
		ft_dlst_push_front(res, ft_create_node_ptr(room));
		return (res);
	}
	res = NULL;
	if (room->neighbors)
	{
		child = room->neighbors;
		while (child)
		{
			if (((t_room*)child->content)->visited == false
				&& (res = ft_one_dfs(farm, (t_room*)(child->content))))
			{
				// if (farm->rooms[0] != room)
				ft_dlst_push_front(res, ft_create_node_ptr(room));
				room->visited = true;
				break ;
			}
			child = child->next;
		}
	}
	return (res);
}

//	перенести
void			ft_dlst_remove_node(
	t_dlist *list, t_node *el, void (*del)(void *, size_t))
{
	t_node *cur;

	if (list)
	{
		cur = NULL;
		if (cur == list->head)
		{
			cur = list->head;
			list->head = cur->next;
		}
		else if (list->tail == el)
		{
			cur = list->tail;
			list->tail = cur->prev;
		}
		else
		{
			cur = list->head;
			while (cur)
			{
				if (cur == el)
					break ;
				cur = cur->next;
			}
		}
		if (cur)
		{
			if (cur->prev)
				cur->prev->next = cur->next ? cur->next : NULL;
			else if (cur->next)
				cur->next->prev = NULL;
			if (del)
				del(cur->content, cur->content_size);
			free(cur);
			list->size--;
		}
	}
}

void			choose_paths_comb(t_path ***cur, t_path ***best)
{
	int		i;
	size_t	min[2];

	i = 0;
	min[0] = ~0;
	min[1] = ~0;
	while ((*cur)[i] && (*best)[i])
	{
		if ((*cur)[i]->size < min[0])
			min[0] = (*cur)[i]->size;
		if ((*best)[i]->size < min[1])
			min[1] = (*best)[i]->size;
		i++;
	}
	i = 0;
	if (min[0] < min[1] || !(*best)[i])
	{
		// while ((*best)[i])
		// {
		// 	ft_dlst_del(&((*best)[i]), NULL);
		// 	i++;
		// }
		i = 0;
		while ((*cur)[i] && (*best)[i])
		{
			(*best)[i] = (*cur)[i];
			i++;
		}
		// *best = *cur;
	}
	else
	{
		// while ((*best)[i])
		// {
		// 	ft_dlst_del(&((*cur)[i]), NULL);
		// 	i++;
		// }
	}
}

void	copy_paths_comb(t_path **dst, t_path **src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_dlst_create();
		t_node *el = src[i]->head;
		while (el)
		{
			ft_dlst_push_back(dst[i], ft_create_node_ptr(el->content));
			el = el->next;
		}
		i++;
	}
	// ft_printf("copy_paths_comb src size = %d, ptr = %p, dst size = %d, ptr = %p\n", dst[0]->size, dst[0], src[0]->size, (*src)[0]);
}

/*
**	Находит комбинации уникальных (не пересекающихся) маршрутов
*/

t_path			**find_unique_paths(t_farm *farm, int count)
{
	int i;
	t_path	**cur_paths;
	t_path	**last_paths;
	t_path	**best_paths;
	int		path_num;
	// t_list	*cur;
	int		processed_path;

	best_paths = NULL;
	cur_paths =	(t_path**)ft_memalloc((count + 1) * sizeof(t_path*));
	last_paths = (t_path**)ft_memalloc((count + 1) * sizeof(t_path*));
	best_paths = (t_path**)ft_memalloc((count + 1) * sizeof(t_path*));
	path_num = 0;

	//	идем по правому краю пытаясь дойти до финиша (n раз), исключая пересечения
	while (path_num < count)
	{
		if (!(cur_paths[path_num] = ft_one_dfs(farm, farm->rooms[0])))
		{
			//	такой комбинации нет
			while (--path_num >= 0)
				ft_memdel((void*)&cur_paths[path_num]);
			ft_memdel((void*)&cur_paths);
			return (NULL);
		}
		path_num++;
	}
	i = 0;
	while (i < count)
	{
		best_paths[i] = cur_paths[i];
		i++;
	}

	i = 0;
	while (i < count)
		show_path(farm, best_paths[i++]);
	

	copy_paths_comb(last_paths, cur_paths);

	//	запускаем перебор изменяя путь n-ой комбинации
	processed_path = count - 1;	//	начиная с крайнего пути
	while (processed_path >= 0)
	{
		//	копируем наилучшую комбинацию путей в текущую
		copy_paths_comb(cur_paths, last_paths);
		ft_printf("BEST SIZE %d LAST SIZE %d\n", best_paths[0]->size, last_paths[0]->size);
		
		i = 0;
		while (i < count)
			show_path(farm, cur_paths[i++]);

		int j = processed_path;
		while (j < count)
		{
			t_list *child = NULL;
			if (!cur_paths[j])
			{
				cur_paths[j] = ft_one_dfs(farm, farm->rooms[0]);
			}
			else
			{
				//	берем последнюю комнату
				t_node *cur = cur_paths[j]->tail->prev;
				child = NULL;
				
				//	идем наверх для поиска развилки
				while (cur)
				{
					// ft_printf("room %s\n", ((t_room*)cur->content)->name);
					// ft_printf("childs %d\n", ft_lstlen(((t_room*)cur->content)->neighbors));
					((t_room*)cur->content)->visited = false;
					if (ft_lstlen(((t_room*)cur->content)->neighbors) > 1)
					{
						//	ищем ноду левее той с которой мы пришли
						child = ((t_room*)cur->content)->neighbors;
						while (child)
						{
							if ((t_room*)child->content == (t_room*)cur->next->content)
							{
								child = child->next;
								break ;
							}
							child = child->next;
						}
						if (child)
						{
							ft_dlst_remove_node(cur_paths[j], cur->next, NULL);	//	удаляем ноду из которой мы поднялись из пути
							show_path(farm, cur_paths[j]);
							break ;
						}
					}
					//	ну дубируется и че?
					ft_dlst_remove_node(cur_paths[j], cur->next, NULL);	//	удаляем ноду из которой мы поднялись из пути
					show_path(farm, cur_paths[j]);
					cur = cur->prev;
				}

				//	развилка найдена и определен непосещенный маршрут
				if (cur && child)
				{
					//	пускаем маршрут через непосещенный узел
					t_path *new = ft_one_dfs(farm, (t_room*)child->content);
					// show_path(farm, cur_paths[j]);
					// show_path(farm, new);
					ft_dlst_merge(cur_paths[j], &new);

					show_path(farm, cur_paths[j]);

					//	если это крайний маршрут
					if (j == count - 1)
					{
						//	сравниваем наилучшую комбинацию с вновь найденой и по необходимости обновляем наилучшую
						copy_paths_comb(last_paths, cur_paths);
						choose_paths_comb(&cur_paths, &best_paths);

						show_path(farm, best_paths[j]);

						break ;
					}
					else
					{
						j++;
					}
				}
				else
				{
					processed_path--;
					break ;
				}
			}
		}
	}
	return (best_paths);
}
