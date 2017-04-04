/* Created by Laramie DeBaun for cse 3310 semester group project
   acts as the bridge between the instructor supplied SuperChat and our group designed ncurses GUI

*/
//wip mutexes, localuser 
#include <pthread.h>
#include <stdio.h> 
#include <globals.h>

//out = from local to world;   in=from world to local
//opensplice reads from out and writes to in
//ncurses reads from in and writes to out
class message_buffer MESSAGE_BUFFER_OUT = message_buffer();
class message_buffer MESSAGE_BUFFER_IN  = message_buffer();
extern void* OSPL_main(void*);
void test_init_message_buffer_out();

int main(){

   test_init_message_buffer_out();
  
   pthread_t ospl_thr;
   pthread_create(&ospl_thr, NULL, OSPL_main, NULL);

   pthread_join(ospl_thr, NULL);
   
   struct m_queue* temp = MESSAGE_BUFFER_IN.get_head(); 
   while(temp != NULL){
      printf("        %s\n",temp->content.message);
      temp = temp->next;
   }
}

void test_init_message_buffer_out(){
   //iniitialize message buffer to test interaction with ospl
   int i=0;
   struct message test;
   strcpy(test.message, "cat");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_OUT.add(test);
   i++;
   strcpy(test.message, "dog");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_OUT.add(test);
   i++;
   strcpy(test.message, "elephant");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_OUT.add(test);
   i++;
   strcpy(test.message, "horse");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_OUT.add(test);

}
