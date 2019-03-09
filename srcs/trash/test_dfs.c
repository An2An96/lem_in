void		test_dfs(t_farm *farm)
{
	t_room *cur = farm->rooms[0];
	t_room *best_next;
	t_list *neighbor_lst;
	t_room *neighbor;
	t_path *path;

	SECURE_MALLOC(path = ft_dlst_create());

	while (cur)
	{
		ft_printf("%s [weight: %d]\n", cur->name, cur->weight);
		ft_dlst_push_back(path, ft_create_node_ptr(cur));
		
		if (cur->types & ROOM_END)
			break ;

		neighbor_lst = cur->neighbors;
		if (!neighbor_lst)
			return ;
		best_next = NULL;
		while (neighbor_lst)
		{
			neighbor = farm->rooms[*LIST(neighbor_lst, int*)];
			if (!(neighbor->types & ROOM_START) && !find_cycle(path, neighbor))
			{	
				if (!best_next || best_next->weight > neighbor->weight)
					best_next = neighbor;
			}
			neighbor_lst = neighbor_lst->next;
		}
		cur = best_next;
	}
	show_path(path);
}
