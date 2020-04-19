#include "lemin.h"

static int		check_for_start_end_link(t_main *main)
{
	t_link	*go_go;

	go_go = main->all_links_here;
	while (go_go)
	{
		if ((go_go->first_room == main->start && go_go->second_room == main->end)
		|| (go_go->first_room == main->end && go_go->second_room == main->start))
			return (1);
		go_go = go_go->next;
	}
	return (0);
}

static void		start_end_way(t_main *main)
{
	t_ant	*ant;

	ant = main->first_ant;
	while (ant)
	{
		print_step(ant->num, main->end->name, main);
		ant = ant->next;
	}
	exit (0);
}


void			start_end_link(t_main *main)
{
	if (check_for_start_end_link(main))
		start_end_way(main);
}