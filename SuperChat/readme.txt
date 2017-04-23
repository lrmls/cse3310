4/23/17
updates chatroom window sith messages
known bugs: waits to read incoming messages until key press, consuming the key tha was pressed
	   if approx. >3 messages waiting to be read can cause stack smash error
	    userlist not updating properly

//4/16/17
This is the complete operational package with the ospl(opensplice) thread commented out
top priority:
	1) chatroom message display updates upon recieved message and sent message
		upon sent message fisrt, upon recieved message when 4 completes
	2) chatroom menu active user display accurately portrays online users
		USERS = global user_list see globals.cpp for associated functions
	3) user menu accurately portrays current users and their chatroom
		needs to grow dynamically up to MAX_USERS.,i or be static but empty until filled 
	4) ncurses takes messages from MESSAGE_BUFFER_IN whenever there are messages available
		thoughts: ncurses exec loop is driven by key press, could check for incoming
			  messages on key press BUT if no input for a while then when key is finally pressed
			  flood of messages will be displayed. need some way to check inc messages
			  independent of user action
	5) need independent CLOSE fn and window toggle fn,
		 can sync ospl to close with ncurses close fn. Currenly have to close ospl with cntrl c after ncurses closes with 2x f1.
		 set ncurses close fn to close from any window and i change 1 line in ospl to sync.
	
mid-low priority:
	6)add chatroom namechange functionality
		can likely drop if needbe 

GIT commands

sudo get install git
within directory you want to insert files:
	git init
	git pull https://github.com/Lrmls/cse3310.git
cd SuperChat
ls
from within /SuperChat
 make to make, make clean to clean, ./bin/SuperChat to run
