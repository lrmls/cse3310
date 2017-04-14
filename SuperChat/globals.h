/*
    globals.h
    Created By laramie DeBaun
    Globals for data sharing between OSPL and ncurses
*/

#ifndef __GLOBALS
#define __GLOBALS

#include "bin/ccpp_SuperChat.h"
using namespace SuperChat;

                /*buffer class definitions & implementaion*/
//**********message buffer linked list node
struct m_queue{
   struct message content;
   struct m_queue* next;
};

//********message buffer class
class message_buffer{
private:
   int count;
   struct m_queue* head;	

public:
   message_buffer();
   void add(struct message);
   struct message remove();
   struct m_queue* get_head();
};

//**********user list class
struct user_time{
   struct user person;
   int timer;
};

class user_list{
private:
   int num_users;
   struct user_time users[13];

public:
   int get_num_users();
   struct user get_user(int);
   void add(struct user);
   void remove(unsigned long long);
   void update();
};
#endif
