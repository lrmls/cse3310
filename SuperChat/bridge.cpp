/* Created by Laramie DeBaun for cse 3310 semester group project
   acts as the bridge between the instructor supplied SuperChat and our group designed ncurses GUI

*/
//wip mutexes, localuser 
#include <pthread.h>
#include <stdio.h> 
#include <globals.h>
//#include "../../boost_1_63_0/boost/uuid/uuid.hpp"      // uuid class
//#include <boost_1_63_0/boost/uuid/uuid_generators.hpp> // generators
//#include <boost_1_63_0/boost/uuid/uuid_io.hpp>         // streaming operators etc.


//out = from local to world;   in=from world to local
//opensplice reads from out and writes to in
//ncurses reads from in and writes to out
class message_buffer MESSAGE_BUFFER_OUT = message_buffer();
class message_buffer MESSAGE_BUFFER_IN  = message_buffer();
class user_list USERS;
//mutex initialization
pthread_mutex_t mutex_in       = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_out      = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_userlist = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_local    = PTHREAD_MUTEX_INITIALIZER;

//forward declaration of thread functions
extern void* OSPL_main(void*);
extern void* NCURSES_main(void*);

struct user local;

void test_init_message_buffer_out();

int main(){
   //initialize local user data
   strcpy(local.nick, "Default");
   local.uuid = 1 ;
   local.chatroom_idx = 0;
  
   test_init_message_buffer_out();
  
   pthread_t ospl_thr;
   //pthread_t ncurses_thr;
   
   pthread_create(&ospl_thr, NULL, OSPL_main, NULL);
   //pthread_create(&ncurses_thr, NULL, NCURSES_main, NULL);
   
   
   pthread_join(ospl_thr, NULL);
   //pthread_join(ncurses_thr, NULL);
   
   //test incoming messages from ospl
   struct m_queue* temp = MESSAGE_BUFFER_IN.get_head(); 
   while(temp != NULL){
      printf("        %s\n",temp->content.message);
      temp = temp->next;
   }
   for(int i=0; i<USERS.get_num_users(); i++){
      printf("%s\n ",USERS.get_user(i).nick);   
   }

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
