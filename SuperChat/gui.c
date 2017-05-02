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
extern int STOP;


char *choices[] = { //displayed in traversable chatroom window
                        "Public", "Room 2", "Room 3", "Room 4","Room 5",
                        "Room 6", "Room 7", "Room 8", "Room 9","Room 10",
                        (char *)NULL,
                  };

//May need to convert incoming active users array (type int) to char for menu. Or keep as int and adjust menu code. 					
char *num_of_users[] = {		
                        "0",
                        "0",
                        "0",
                        "0",
			"0",
			"0",
			"0",
			"0",
			"0",
			"0",
                        (char *)NULL,
                  };

		//following two arrays displayed in non-traversible list of active users
char list_users[13][8] = {		
                        "       ", "       ", "       ", "       ", "       ",
                        "       ", "       ", "       ", "       ", "       ",
                        "       ", "       ", "       ",
                  };

char list_user_room[13][8] = {	
                   	"       ", "       ", "       ", "       ", "       ",
                        "       ", "       ", "       ", "       ", "       ",
                        "       ", "       ", "       ",
                   };


//I put a number of spaces almost equal to the msg size instead of reallocating based on the msg input size
//Before, since ther was only 1 space (" "), it was only displaying 1 character of the entire msg
char list_msgs[10][155] = {
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
"                                                                                                                                                       ",
};
ITEM **items_msgs, **items_users;
MENU *menu_msgs, *menu_users;
WINDOW *menu_msgs_win, *menu_users_win;
int list_msgs_count, max_msgs, max_users;


void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_in_left(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_in_right(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
//new fx
void send_message(char* );
void recieve_message();
void update_msgs_list(char*);
void erase_msgs_menu();
void draw_msgs_menu();
void draw_users_menu();
void erase_users_menu();
void update_users_list();

void* NCURSES_main(void* null)
{	ITEM **items_rooms ;
	FIELD *field[2];
	FORM  *my_form;				
	MENU *menu_rooms;
	char msg[144];
        WINDOW *menu_rooms_win, *my_form_win;
        int n_choices, i, c, ch, rows, cols;
    	
        max_msgs= ARRAY_SIZE(list_msgs);
       max_users = ARRAY_SIZE(list_users);
	/* Initialize curses */
	initscr();
	start_color();
        cbreak();
        noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);

	/* Create room items */
        n_choices = ARRAY_SIZE(choices);
        items_rooms = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i)
                items_rooms[i] = new_item(choices[i], num_of_users[i]);
	

	/* Create users items */
	items_users = (ITEM **)calloc(max_users+1, sizeof(ITEM *));
	for(i = 0; i < max_users; ++i){
                items_users[i] = new_item(list_users[i], list_user_room[i]);
        }
        items_users[max_users]= (ITEM*)NULL;
	/* Msgs items */
	items_msgs = (ITEM **)calloc(max_msgs+1, sizeof(ITEM *));
	for(i = 0; i < max_msgs; ++i){
            items_msgs[i] = new_item(list_msgs[i], ""); 
	}
        items_msgs[max_msgs]= (ITEM*)NULL;

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

	//set messages window
        set_menu_win(menu_msgs, menu_msgs_win);
        set_menu_sub(menu_msgs, derwin(menu_msgs_win, 0, 0, 3, 1));
        menu_driver(menu_msgs, REQ_TOGGLE_ITEM);
        mvwaddch(menu_msgs_win, 2, 0, ACS_LTEE);
        mvwhline(menu_msgs_win, 2, 1, ACS_HLINE, 144);
        mvwaddch(menu_msgs_win, 2, 145, ACS_RTEE);

	
	/*Messages box*/
	box(menu_msgs_win, 0, 0);
	
	


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
	
        set_menu_fore(menu_msgs, COLOR_PAIR(3) | A_REVERSE);
        set_menu_fore(menu_users, COLOR_PAIR(3) | A_REVERSE);
        set_menu_mark(menu_msgs, " ");
        set_menu_mark(menu_users, " ");
	
        post_menu(menu_rooms);
        post_menu(menu_users);
	post_menu(menu_msgs);
	wrefresh(menu_rooms_win);
	wrefresh(menu_users_win);
	wrefresh(menu_msgs_win);
		
	/*Post Form*/
	post_form(my_form);
	wrefresh(my_form_win);


	attron(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
	refresh();
	
        //help menu display
        attron(COLOR_PAIR(1));
        mvprintw(LINES/8-1, 100, "MENU: UP & DOWN keys to navigate, ENTER to select room. F2 to close.");
        mvprintw(LINES/8, 100, "CHATROOM: /nick yourname to change nickname, F1 to exit room.");
        attroff(COLOR_PAIR(2));
        refresh();
        pos_menu_cursor(menu_rooms);      

		//execute
	/*Loop for Menu Selection*/
	i=0;
	list_msgs_count =0;
	while((c = wgetch(menu_rooms_win)) != KEY_F(2) )
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
		   while( ((ch = wgetch(my_form_win)) != KEY_F(1)) )
		   {	
                     //currently waits for input to receive and display messages as well as update user menu.
                      recieve_message();           
	
                      erase_users_menu(); 
		      update_users_list();
		      draw_users_menu();
 
		      switch(ch)
		      {	   case KEY_BACKSPACE:		//working backspace for typing
			      form_driver(my_form, REQ_PREV_CHAR);
			      form_driver(my_form, REQ_DEL_CHAR);				
     			      break;
     			   case 10:		//send message on ENTER	
			      form_driver(my_form, REQ_VALIDATION);
			      snprintf(msg, 144, "%s", field_buffer(field[0], 0));
	                      if(msg[0]=='/'){
                                  char* token = strtok(msg, " ");
				  if (strcmp(token, "/nick") ==0){
					token = strtok(NULL, " ");
					if(strlen(token) <8){
					   pthread_mutex_lock(&mutex_local);
					   strcpy(local.nick,token);
					   pthread_mutex_unlock(&mutex_local);
					}
				   }
			      } 
			      else{
				      //get local nick and format message
				      pthread_mutex_lock(&mutex_local);
				      char buff[160];
				      strcpy(buff, local.nick);			
				      strcat(buff, ": ");
				      strcat(buff, msg);	     	   
				      pthread_mutex_unlock(&mutex_local);
				      //update list_msgs and menu	
				      erase_msgs_menu();
				      update_msgs_list(buff);
				      draw_msgs_menu();
				      //send message
				      send_message(msg);
				      
			      }
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
	//unpost_menu(menu_msgs);
        free_menu(menu_rooms);
	free_menu(menu_users);
	
        erase_msgs_menu();
        free_menu(menu_msgs);
	
	unpost_form(my_form);
	free_form(my_form);
	free_field(field[0]);
	
        for(i = 0; i < n_choices; ++i){
                free_item(items_rooms[i]);}

	for(i = 0; i < max_users; ++i){
                free_item(items_users[i]);}

/*	for(i = 0; i < n_msgs; ++i){
                free_item(items_msgs[i]);}
*/	
	endwin();
        STOP = 1;
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

void recieve_message(){

   pthread_mutex_lock(&mutex_in);
   if(MESSAGE_BUFFER_IN.get_count() ==0){
      pthread_mutex_unlock(&mutex_in); 
      return;}
   
   char msg[160];
   struct message incoming ;

   incoming = MESSAGE_BUFFER_IN.remove();
   //extract data from message IF chatroomidx==local.chatroomidx
   pthread_mutex_lock(&mutex_local);
   pthread_mutex_lock(&mutex_userlist);
   if(incoming.chatroom_idx == local.chatroom_idx){
	//get user nick
      for(int i=0; i<USERS.get_num_users(); i++){
          if(USERS.get_user(i).uuid == incoming.uuid){
	      strcpy(msg, USERS.get_user(i).nick);
              break;
	   }   
      }
      strcat(msg, ": ");
      strcat(msg, incoming.message);
      update_msgs_list(msg);
   }
   pthread_mutex_unlock(&mutex_in);
   pthread_mutex_unlock(&mutex_userlist);
   pthread_mutex_unlock(&mutex_local);
  
   erase_msgs_menu();
   draw_msgs_menu();
}


void send_message(char* msg){
 	//constructs idl defined message and adds to buffer_out

      struct message test;
      strcpy(test.message, msg);
      pthread_mutex_lock(&mutex_local);
	 test.uuid = local.uuid;
         test.chatroom_idx = local.chatroom_idx;
      pthread_mutex_unlock(&mutex_local);
      test.cksum= 0;
      	
      pthread_mutex_lock(&mutex_out);
	 MESSAGE_BUFFER_OUT.add(test);
      pthread_mutex_unlock(&mutex_out);
}

void draw_msgs_menu(){
        int i=0;
        //Create menu is displayed as messages in chatroom msgout 
        
        items_msgs = (ITEM **)calloc(max_msgs+1, sizeof(ITEM *));
	for(i=0; i < max_msgs; ++i){
            items_msgs[i] = new_item(list_msgs[i], "");
        }
        //putting NULL at end of items without putting it in the actual message array
        items_msgs[max_msgs] = (ITEM *)NULL;

        //point new items to the menu
        set_menu_items(menu_msgs, items_msgs);

        //drawing box/outline
        set_menu_win(menu_msgs, menu_msgs_win);
        set_menu_sub(menu_msgs, derwin(menu_msgs_win, 0, 0, 3, 1));
        mvwaddch(menu_msgs_win, 2, 0, ACS_LTEE);
        mvwhline(menu_msgs_win, 2, 1, ACS_HLINE, 144);
        mvwaddch(menu_msgs_win, 2, 145, ACS_RTEE);
        menu_driver(menu_msgs, REQ_TOGGLE_ITEM);
        box(menu_msgs_win, 0, 0);

        set_menu_fore(menu_msgs, COLOR_PAIR(3) | A_REVERSE);
        set_menu_mark(menu_msgs, " ");
        post_menu(menu_msgs);
        wrefresh(menu_msgs_win);
}

void update_msgs_list(char * msg){
        int i=1;
        //menu displaying messages is full
        if(list_msgs_count == max_msgs)
        {
                //shuffle
                for(i=1; i<max_msgs; i++)
                {
                        strcpy(list_msgs[i-1], list_msgs[i]);
                }
                strcpy(list_msgs[max_msgs-1], msg);
        }
        else
        {
                strcpy(list_msgs[list_msgs_count], msg);
                list_msgs_count++;
        }
}


//unpost and frees items before updating, but does not free menu
void erase_msgs_menu(){
        int i=0;

        unpost_menu(menu_msgs);
        for(i = 0; i < max_msgs+1; ++i){
                free_item(items_msgs[i]); }
}


void draw_users_menu(){

	int i=0;
	/* Create users items */
	items_users = (ITEM **)calloc(max_users+1, sizeof(ITEM *));
	for(i=0; i < max_users; ++i){
		items_users[i] = new_item(list_users[i], list_user_room[i]);
        }
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
        
        set_menu_fore(menu_users, COLOR_PAIR(3) | A_REVERSE);
        set_menu_mark(menu_users, " ");
	
        post_menu(menu_users);
	wrefresh(menu_users_win);
}


void erase_users_menu(){

   int i=0;
   unpost_menu(menu_users);

   for(i = 0; i < max_users+1; ++i){
     free_item(items_users[i]);
   }
}

void update_users_list(){

     	int i=0;
         char empty[8] = "       "; 
	pthread_mutex_lock(&mutex_userlist);

	for(i=0;i<max_users;i++)
	{
           if(i < USERS.get_num_users() ){ 
	      strcpy(list_users[i], USERS.get_user(i).nick);
	      strcpy(list_user_room[i], choices[USERS.get_user(i).chatroom_idx]);
           } 
	   else{
              strcpy(list_users[i], empty);
	      strcpy(list_user_room[i], empty);
           }
 	}
      
	pthread_mutex_unlock(&mutex_userlist);
}


