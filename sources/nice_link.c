#include "lemin.h"

/*static	void delete_nice_link(t_link *deadman, t_main *main)
{
	t_link *executor;

	executor = main->all_links_here;
	if (executor == deadman)
	{
		executor = deadman->next;
		free(deadman);
		deadman = NULL;
		main->all_links_here = executor;
	}
	else
	{
		while (executor && executor->next != deadman)
			executor = executor->next;
		executor->next = deadman->next;
		free(deadman);
		deadman = NULL;

	}
}*/

static int check_for_nice_link(t_main *main)
{
	t_link *go_go;

	go_go = main->all_links_here;
	while (go_go)
	{
		if ((go_go->first_room == main->start && go_go->second_room == main->end) ||
				(go_go->first_room == main->end && go_go->second_room == main->start))
		{
	//		delete_nice_link(go_go, main);
			return (1);
		}
		go_go = go_go->next;
	}
	return (0);
}

/*static void add_nice_path(t_main *main)
{
	t_path *nice_path;

	if (!(nice_path = ft_memalloc(sizeof(t_path))))
		ft_error("malloc failed");
	if (!main->paths)//////////delete this, doing just in case
		main->paths = nice_path;
	/////////should add list cycle in case of moving this shit somewhere else
	nice_path->current = main->start;
	nice_path->current->where = main->end;
}*/
static void nice_ways(t_main *main)
{
	t_ant *ant;

	ant = main->first_ant;
	while (ant)
	{
		print_step(ant->num, main->end->name, main);
		ant = ant->next;
	}
	exit (0);
}


void 	nice_link(t_main *main)
{
	if (check_for_nice_link(main))
	//	add_nice_path(main);
		nice_ways(main);

}