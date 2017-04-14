#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>
#include <form.h>
#include<pthread.h>
#include "globals.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

// pthread_mutex_lock(&mutexname);
// pthread_mutex_unlock(&mutexname);
extern class message_buffer MESSAGE_BUFFER_OUT;
extern class message_buffer MESSAGE_BUFFER_IN;
extern class user_list USERS;
extern struct user local;
extern pthread_mutex_t mutex_in;
extern pthread_mutex_t mutex_out;
extern pthread_mutex_t mutex_userlist;
extern pthread_mutex_t mutex_local;



char *choices[] = { //displayed in traversable chatroom window
                        "Public", "Room 2", "Room 3", "Room 4","Room 5",
                        "Room 6", "Room 7", "Room 8", "Room 9","Room 10",
                        (char *)NULL,
                  };

//May need to convert incoming active users array (type int) to char for menu. Or keep as int and adjust menu code. 					
char *num_of_users[] = {		
                        "1",
                        "2",
                        "3",
                        "4",
			"5",
			"6",
			"7",
			"8",
			"9",
			"10",
                        (char *)NULL,
                  };

		//following two arrays displayed in non-traversible list of active users
char *list_users[] = {		
                        "User1",
                        "User2",
                        "User3",
                        "User4",
			"User5",
			"User6",
			"User7",
			"User8",
			"User9",
			"User10",
			"User11",
			"User12",
                        (char *)NULL,
                  };

char *list_user_room[] = {		
                        "Public",
                        "420Blaze",
                        "FunHouse",
                        "room",
			"room 5",
			"room 6",
			"room 7",
			"room 8",
			"room 9",
			"room 10",
			"room 11",
			"room 12",
                        (char *)NULL,
                  };


char *list_msgs[] = {
                        "",
                        "",
                        "",
                        "",
			"",
			"",
			"",
			"",
			"",
			"asdf",
                        (char *)NULL,
                  };


void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_in_left(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_in_right(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
//new fx
void send_message(char* );
void update_chat_display(struct message, int*, char**);


void* NCURSES_main(void* null)
{	ITEM **items_rooms, **items_users, **items_msgs;
	FIELD *field[2];
	FORM  *my_form;				
	MENU *menu_rooms, *menu_users, *menu_msgs;
	char msg[144];
        WINDOW *menu_rooms_win, *menu_users_win, *my_form_win, *menu_msgs_win;
        int n_choices, n_users, n_msgs, i, c, ch, rows, cols;
	
	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);

	/* Create room items */
        n_choices = ARRAY_SIZE(choices);
        items_rooms = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                items_rooms[i] = new_item(choices[i], num_of_users[i]);
	

	/* Create users items */
	n_users = ARRAY_SIZE(list_users);
	items_users = (ITEM **)calloc(n_users, sizeof(ITEM *));
	for(i = 0; i < n_users; ++i)
                items_users[i] = new_item(list_users[i], list_user_room[i]);

	/* Create menu is displayed as messages in chatroom msgout */
	n_msgs = ARRAY_SIZE(list_msgs);
	items_msgs = (ITEM **)calloc(n_msgs, sizeof(ITEM *));
	for(i = 0; i < n_msgs; ++i){
            items_msgs[i] = new_item(list_msgs[i], ""); 
	}
	/* Create menus */
	menu_rooms = new_menu((ITEM **)items_rooms);
	
	menu_users = new_menu((ITEM **)items_users);

	menu_msgs = new_menu((ITEM **)items_msgs);

	/* Create the window to be associated with the menu */
        menu_rooms_win = newwin(10, 40, 4, 4);
        keypad(menu_rooms_win, TRUE);

	menu_users_win = newwin(18, 30, 4, 60);

	menu_msgs_win = newwin(14,160,21,4);	//message ouitput display area
     	
	/* Set room window and sub window */
        set_menu_win(menu_rooms, menu_rooms_win);
        set_menu_sub(menu_rooms, derwin(menu_rooms_win, 6, 38, 3, 1));
	set_menu_spacing(menu_rooms, 8, 1, 1);		//8 sets the spacing between menu colums UPDATE?
	set_menu_format(menu_rooms, 5, 1);
	

	/* Set users window and sub window */
	set_menu_win(menu_users, menu_users_win);
	set_menu_sub(menu_users, derwin(menu_users_win, 0, 0, 3, 1));
	set_menu_spacing(menu_users, 8, 1, 1);		//8 sets the spacing between menu columns UPDATE?
	set_menu_format(menu_users, 10, 1);
		
	/* Set menu mark to the string " -> " */
        set_menu_mark(menu_rooms, " -> ");


	/*Messages "Menu"*/
	set_menu_win(menu_msgs, menu_msgs_win);
	set_menu_sub(menu_msgs, derwin(menu_msgs_win, 0, 0, 3, 1));
	
	

	/* Print a border around the room window and print a title */
        box(menu_rooms_win, 0, 0);
	print_in_left(menu_rooms_win, 1, 0, 40, "Room Name", COLOR_PAIR(2));
	print_in_right(menu_rooms_win, 1, 0, 40, "Active Users", COLOR_PAIR(2));
	mvwaddch(menu_rooms_win, 2, 0, ACS_LTEE);
	mvwhline(menu_rooms_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(menu_rooms_win, 2, 39, ACS_RTEE);
        
	/* Print a border around the users window and print a title */
	box(menu_users_win, 0, 0);
	print_in_left(menu_users_win, 1, 0, 30, "User", COLOR_PAIR(2));
	print_in_right(menu_users_win, 1, 0, 30, "Room", COLOR_PAIR(2));
	mvwaddch(menu_users_win, 2, 0, ACS_LTEE);
	mvwhline(menu_users_win, 2, 1, ACS_HLINE, 28);
	mvwaddch(menu_users_win, 2, 29, ACS_RTEE);
	
	/*Messages box*/
	box(menu_msgs_win, 0, 0);
	
	
	mvwaddch(menu_msgs_win, 2, 0, ACS_LTEE);
	mvwhline(menu_msgs_win, 2, 1, ACS_HLINE, 158);
	mvwaddch(menu_msgs_win, 2, 160, ACS_RTEE);



	/* Initialize the fields */
	field[0] = new_field(1, 143, 0, 1, 0, 0);


	/* Set field options */
	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP); 


	/* Create the form and post it */
	my_form = new_form(field);
	
	/* Calculate the area required for the form */
	scale_form(my_form, &rows, &cols);

	/* Create the window to be associated with the input */
        my_form_win = newwin(rows + 4, cols + 4, 34, 9);            //message input area
        keypad(my_form_win, TRUE);

	/* Set input window and sub window */
        set_form_win(my_form, my_form_win);
        set_form_sub(my_form, derwin(my_form_win, rows, cols, 2, 2));


	/* Print a border around the main window and print a title */
        box(my_form_win, 0, 0);
	//print_in_middle(my_form_win, 1, 0, cols + 4, "Public", COLOR_PAIR(1));

	/* Post the menus */
	post_menu(menu_rooms);
	post_menu(menu_users);
	
	wrefresh(menu_rooms_win);
	wrefresh(menu_users_win);
		
	/*Post Form*/
	post_form(my_form);
	wrefresh(my_form_win);


	attron(COLOR_PAIR(1));
	//mvprintw(LINES - 2, 0, "Use PageUp and PageDown to scoll down or up a page of items");
	//vprintw(LINES - 1, 0, "Arrow Keys to navigate (F1 to Exit)");
	attroff(COLOR_PAIR(2));
	refresh();
	

		//execute
	/*Loop for Menu Selection*/
	i=0;
	while((c = wgetch(menu_rooms_win)) != KEY_F(1))
	{       
	   switch(c)
	   {	case KEY_DOWN:
	   	   menu_driver(menu_rooms, REQ_DOWN_ITEM);
		   if(i<9){ i++; }
		   break;
		case KEY_UP:
		   menu_driver(menu_rooms, REQ_UP_ITEM);
		   if(i!=0){ i--; }				
		   break;
		case KEY_NPAGE:
		   menu_driver(menu_rooms, REQ_SCR_DPAGE);
		   break;
		case KEY_PPAGE:
		   menu_driver(menu_rooms, REQ_SCR_UPAGE);
		   break;
		case 10:
		   post_menu(menu_msgs);
		   print_in_middle(menu_msgs_win, 1, 0, 160, "             ", COLOR_PAIR(2));
		   print_in_middle(menu_msgs_win, 1, 0, 160, choices[i], COLOR_PAIR(2));
		   wrefresh(menu_msgs_win);
		   pthread_mutex_lock(&mutex_local);
		      local.chatroom_idx = (unsigned long)i;
		   pthread_mutex_unlock(&mutex_local);
		   form_driver(my_form, REQ_BEG_FIELD);
		       /* Loop through to get user chat input */
		   while((ch = wgetch(my_form_win)) != KEY_F(1))
		   {	
		      switch(ch)
		      {	   case KEY_BACKSPACE:		//working backspace for typing
			      form_driver(my_form, REQ_PREV_CHAR);
			      form_driver(my_form, REQ_DEL_CHAR);				
     			      break;
     			   case 10:		//send message on ENTER	
			      form_driver(my_form, REQ_VALIDATION);
			      snprintf(msg, 144, "%s", field_buffer(field[0], 0));
					//construct message and add to buffer_out
			      send_message(msg);	
			      
         		      set_field_buffer(field[0], 0, "");
			      wrefresh(my_form_win);
			      break;
			   default:   //end of inner switch statment loop
			       /* If this is a normal character it gets printed in input field*/
			      form_driver(my_form, ch);
			      wrefresh(my_form_win);
			}
                     //last execution before looping inside of message room loop
		     }
		     memset(list_msgs, 0, sizeof(list_msgs));
		     break;  //break from case 10 in outer switch statement,
			     // returning cursor to room selection window
	   }           
            //outside of switch statments, runs right before loop repeats
            wrefresh(menu_rooms_win);
	}	
        //end main execution loop

	/* Unpost and free all the memory taken up */
        unpost_menu(menu_rooms);
	unpost_menu(menu_users);
	unpost_menu(menu_msgs);
        free_menu(menu_rooms);
	free_menu(menu_users);
	free_menu(menu_msgs);
	
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	
        for(i = 0; i < n_choices; ++i){
                free_item(items_rooms[i]);}

	for(i = 0; i < n_users; ++i){
                free_item(items_users[i]);}

	for(i = 0; i < n_msgs; ++i){
                free_item(items_msgs[i]);}
	
	endwin();
        pthread_exit(0);
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void print_in_left(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/8;	//UPDATE
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void print_in_right(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = ((width - length)*7)/8;	//UPDATE
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void send_message(char* msg){
 	//constructs idl defined message and adds to buffer_out

      struct message test;
      strcpy(test.message, msg);
      pthread_mutex_lock(&mutex_local);
	 test.uuid = local.uuid;
      pthread_mutex_unlock(&mutex_local);
	test.cksum= 0;
      pthread_mutex_lock(&mutex_local);
	 test.chatroom_idx = local.chatroom_idx;
      pthread_mutex_unlock(&mutex_local);
		
      pthread_mutex_lock(&mutex_out);
	 MESSAGE_BUFFER_OUT.add(test);
      pthread_mutex_unlock(&mutex_out);
}

void update_chat_display(struct message msg, int* n_msgs, char** msgs_list ){
	//adds "msg.nick: msg.message" to list_msgs, iff full delete list_msgs[0], shuffle, add to end
        //frees and unposts menu_msgs and item_msgs, recreates and reposts
   
    //if message_in buffer empty|| message is not for current chatroom: do nothing
    if(msg.chatroom_idx == 9999 || msg.chatroom_idx != local.chatroom_idx){return;} 
/*   
    unpost_menu(menu_msgs);   
    free_menu(menu_msgs);   
    
    if(*n_msgs ==0){ 
       *n_msgs++;
       strcpy(msgs_list, msg.message);

    }    



    menu_msgs = new_menu((ITEM **)items_msgs);
    set_menu_win(menu_msgs, menu_msgs_win);
    set_menu_sub(menu_msgs, derwin(menu_msgs_win, 0, 0, 3, 1));
    post_menu(menu_msgs);
*/}
