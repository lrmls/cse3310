/*
     globals.cpp
     implemetnation of globals.h classes
*/


#include "globals.h"
//*************************message_buffer Implementation******************
       //constructor
message_buffer::message_buffer(){count=0; head=NULL;}

       //getter for message queue
struct m_queue* message_buffer::get_head(){ return head; }
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
   if(count == 0){ outgoing.chatroom_idx = 9999; return outgoing; }
   
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
struct user user_list::get_user(int index){ return users[index] ;}

void user_list::add(struct user inc){
    //add a user to the list when you recieve a heartbeat, if not already in list
   if(num_users == 0){ users[0]=inc;}
   if(num_users == 13){/*add to user waiting queue*/ return;}
   else{
      int i;
      for(i=0; i<num_users-1; i++){
           if(users[i].uuid == inc.uuid){/*updated timer*/ return;}
      }
      users[i]=inc; num_users++;
   }
}

void user_list::remove(unsigned long long id){
   //remove user form the array. shuffle array to fill in whole

   for(int i=0; i<num_users; i++){
       //remove and adjust
       if(users[i].uuid == id){
          for(int j=i; j<num_users-1; j++){
             users[j] = users[j+1];
          }
          num_users--;
          return;
       }
     
   }
}

