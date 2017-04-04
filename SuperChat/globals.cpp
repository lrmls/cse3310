/*
     globals.cpp
     implemetnation of globals.h classes
*/


#include "globals.h"
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
