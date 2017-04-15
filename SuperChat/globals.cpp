/*
     globals.cpp
     implemetnation of globals.h classes
*/


#include "globals.h"
//*************************message_buffer Implementation******************
       //constructor
message_buffer::message_buffer(){count=0; head=NULL;}

       //getter for message queue & count
struct m_queue* message_buffer::get_head(){ return head; }
int message_buffer::get_count(){return count;}

      //add a message to the buffer tail
void message_buffer::add(struct message inc){
   //content=idl defined message struct; message = string message 
   //copy incoming message into new node 
   struct m_queue* add = new struct m_queue;
   struct m_queue* temp=head;
   strcpy(add->content.message, inc.message);
   add->content.uuid         = inc.uuid;
   add->content.cksum        = inc.cksum;
   add->content.chatroom_idx = inc.chatroom_idx;
   add->next = NULL;
   //insert new message into tail end of buffer
   if(count ==0){ head = add; }
   else{
      while(temp->next != NULL){ temp = temp->next; }
      temp->next = add;
   }
   count++;
}
     //remove a message from the buffer head
struct message message_buffer::remove(){
   //copy message from buffer head into idl defined message struct
   
   struct message outgoing; //wip
   if(count == 0){ printf("ERROR: removing from empty storage\n"); exit(1); }
   
   strcpy(outgoing.message, head->content.message);
   outgoing.uuid         = head->content.uuid;
   outgoing.cksum        = head->content.cksum;
   outgoing.chatroom_idx = head->content.chatroom_idx;
   //remove message from buffer
   head= head->next; 
   count--;

  return outgoing; 
}

//***********************************user_list Implementation**************
   //getters
int user_list::get_num_users(){return num_users;}
struct user user_list::get_user(int index){ return users[index].person ;}

void user_list::add(struct user inc){
     //add a user to the list when you recieve a heartbeat, if not already in list
   if(num_users == 0){ users[0].person=inc; num_users++;}
   else if(num_users == 13){/*wip add to user waiting queue, currently drops user*/ return;}
   else{
      int i;
      for(i=0; i<num_users; i++){
           if(users[i].person.uuid == inc.uuid){users[i].timer=0; return;}
      }
      users[i].person=inc; num_users++;
   }
}

void user_list::remove(unsigned long long id){
   //remove user form the array. shuffle array to fill in hole

   for(int i=0; i<num_users; i++){
       //remove and adjust
       if(users[i].person.uuid == id){
          for(int j=i; j<num_users-1; j++){
             users[j].person = users[j+1].person;
          }
          num_users--;
          return;
       }     
   }
}

void user_list::update(){
   //update all current users timers in userlist by 2 seconds when we send a heartbeat

   for(int i=0; i<num_users; i++){   //remaining users get shuffled back when remove, reprocess current index
      if(users[i].timer > 5){ remove(users[i].person.uuid); num_users--; i--;}
      else{users[i].timer +=2;}
   }
}
