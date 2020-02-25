////////HAT PLEASE

#include "lemin.h"


/*

static int 	check_non_sexy(t_room *room)
{

}

*/






void		next_lvls(t_main *main/*, int checked_rooms*/)
{
	t_link	*link;
	int 	change;
	int k = 0;
	
	link = main->all_links_here;
	change = 0;
	////////ЦИКЛЫ ЛУДЬЩЕЧЕ!!!!
	while (link)
	{
		if (link->checked /*&& проверка на тупик будет здесь*/)
		{
			link = link->next;
			continue;
		}
		if (link->first_room->level == main->max_current_level && !link->second_room->level /*&& !link->second_room->is_dead_end*/)
		{
			link->second_room->level = main->max_current_level + 1;
			link->checked = 1;
			change = 1;
			k++;
		}
		else if (link->second_room->level == main->max_current_level && !link->first_room->level /*&& !link->first_room->is_dead_end*/)
		{
			link->first_room->level = main->max_current_level + 1;
			link->checked = 1;
			change = 1;
			k++;
		}
		link = link->next;
	}
	
	if (change == 1)
	{
		printf("level: %d, rooms: %d", main->max_current_level, k);
		main->max_current_level + 1;
		next_lvls(main);
	}
}