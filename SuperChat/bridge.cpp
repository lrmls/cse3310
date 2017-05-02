/* Created by Laramie DeBaun for cse 3310 semester group project
   acts as the bridge between the instructor supplied SuperChat and our group designed ncurses GUI

*/

#include <pthread.h>
#include <stdio.h> 
#include <globals.h>
#include <ctime>
//#include "../../boost_1_63_0/boost/uuid/uuid.hpp"      // uuid class
//#include <boost_1_63_0/boost/uuid/uuid_generators.hpp> // generators
//#include <boost_1_63_0/boost/uuid/uuid_io.hpp>         // streaming operators etc.

//*****************************Global declarations
//out = from local to world;   in=from world to local
//opensplice reads from out and writes to in
//ncurses reads from in and writes to out
class message_buffer MESSAGE_BUFFER_OUT = message_buffer();
class message_buffer MESSAGE_BUFFER_IN  = message_buffer();
class user_list USERS = user_list();
struct user local;
int STOP = 0;
//***************************mutex initialization
pthread_mutex_t mutex_in       = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_out      = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_userlist = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_local    = PTHREAD_MUTEX_INITIALIZER;

//***************************forward declaration of thread functions
extern void* OSPL_main(void*);
extern void* NCURSES_main(void*);

//*************************test functions
void test_main();
void test_init_message_buffer_out();
void test_init_message_buffer_in();


int main(){
   //initialize local user data
  
   strcpy(local.nick, "Default");
   local.uuid = (unsigned long long)time(0) ;
   local.chatroom_idx = 0;
  
//   test_init_message_buffer_in();
  // test_init_message_buffer_out();
  //set up threads
   pthread_t ospl_thr;
   pthread_t ncurses_thr;
   
   pthread_create(&ospl_thr, NULL, OSPL_main, NULL);
   pthread_create(&ncurses_thr, NULL, NCURSES_main, NULL);
      
   pthread_join(ospl_thr, NULL);
   pthread_join(ncurses_thr, NULL);
   
   test_main();
  
}
// start from stack overflow
// http://stackoverflow.com/questions/3247861/example-of-uuid-generation-using-boost-in-c


/*int uuid_generation() {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    std::cout << uuid << std::endl;
    long long int x;
    // lets go old school, and copy it over
    memcpy ( &x, &uuid, sizeof (x) );
    std::cout << "as a number " << std::hex << x << std::endl;
    return 0;
}*/
//end from stack overflow

void test_main(){

 //test contents of a message_buffer post execution, change out/in as desired
   struct m_queue* tempin = MESSAGE_BUFFER_IN.get_head(); 
   struct m_queue* tempout = MESSAGE_BUFFER_OUT.get_head(); 
   printf("BUFFER_IN contents:\n");
   while(tempin != NULL){
      printf("       Room %u: %s\n",tempin->content.chatroom_idx, tempin->content.message);
      tempin = tempin->next;
   }
    printf("BUFFER_OUT contents:\n");
   while(tempout != NULL){
      printf("       Room %u: %s\n",tempout->content.chatroom_idx, tempout->content.message);
      tempout = tempout->next;
   }
   //test contents of user_list post execution
    printf("User List contents:\n");
   for(int i=0; i<USERS.get_num_users(); i++){
      printf("        user %d: %s\n " , i,USERS.get_user(i).nick);   
   }

   printf("end chatroom idx=%d\n", local.chatroom_idx);
   printf("local uuid=%d\n", local.uuid);
}

void test_init_message_buffer_out(){
   //iniitialize message buffer to test outgoing interaction with ospl
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
void test_init_message_buffer_in(){
   //iniitialize message buffer to test outgoing interaction with ospl
   int i=0;
   struct message test;
   strcpy(test.message, "Roof");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_IN.add(test);
   i++;
   strcpy(test.message, "Ceiling");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_IN.add(test);
   i++;
   strcpy(test.message, "floor");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_IN.add(test);
   i++;
   strcpy(test.message, "Universe");
      test.uuid = i+8*i;
      test.cksum = 5*i; 
      test.chatroom_idx = i;
      MESSAGE_BUFFER_IN.add(test);

}
