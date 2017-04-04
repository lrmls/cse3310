Professor:
This is an example program to help with the semester project
 %   git clone https://github.com/bdavisCSE3320/SuperChat.git
 %  cd SuperChat/
 %  vi scripts/release.com 
 % # Edit the file scripts/release.com to point to the opensplice distribution directory.  
 % # (change the OSPL_HOME environment variable)
 %  make clean
 %  make
 %  bin/SuperChat

Laramie:
make from within /SuperChat
bridge.cpp is main
globals.h , globals.cpp contain my classes that hold the messages as a linked list buffer while they wait to be accessed by wither ospl or ncurses
executable ./bin/SuperChat from within /SuperChat
