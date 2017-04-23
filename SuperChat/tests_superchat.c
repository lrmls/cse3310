void draw_users_menu(){

int i=0;
/* Create users items */

 

items_users = (ITEM **)calloc(max_users+1, sizeof(ITEM *));

for(i; i < max_users; ++i)

                items_users[i] = new_item(list_users[i], list_user_room[i]);
items_users[max_users] = (ITEM *)NULL;
 
set_menu_items(menu_users, items_users);
menu_users_win = newwin(18, 30, 4, 60);
 
set_menu_win(menu_users, menu_users_win);

set_menu_sub(menu_users, derwin(menu_users_win, 0, 0, 3, 1));

set_menu_spacing(menu_users, 8, 1, 1); //8 sets the spacing between menu columns UPDATE?

set_menu_format(menu_users, 10, 1);

box(menu_users_win, 0, 0);

print_in_left(menu_users_win, 1, 0, 30, "User", COLOR_PAIR(2));

print_in_right(menu_users_win, 1, 0, 30, "Room", COLOR_PAIR(2));

mvwaddch(menu_users_win, 2, 0, ACS_LTEE);

mvwhline(menu_users_win, 2, 1, ACS_HLINE, 28);

mvwaddch(menu_users_win, 2, 29, ACS_RTEE);


post_menu(menu_users);
wrefresh(menu_users_win);
}

void erase_users_menu(){

int i=0;

 

unpost_menu(menu_users);

for(i = 0; i < max_users+1; ++i){

                free_item(items_users[i])
   }
}

void update_users_list(){

int i=0;

pthread_mutex_lock(&user_list);

for(i;i<USERS.get_count();i++)
{
 
strcpy(list_users[i], USERS.get_user(i).nick);
strcpy(list_user_room[i], choices[USERS.get_user(i).chatroom_idx]);
 
}

pthread_mutex_unlock(&user_list);

}

