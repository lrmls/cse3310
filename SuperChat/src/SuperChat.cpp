#include <signal.h>
#include <assert.h>
//#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>

#include "DDSEntityManager.h"
#include "ccpp_SuperChat.h"

#include "../globals.h"

extern class message_buffer MESSAGE_BUFFER_OUT;
extern class message_buffer MESSAGE_BUFFER_IN;
extern class user_list USERS;
extern pthread_mutex_t mutex_in;
extern pthread_mutex_t mutex_out;
extern pthread_mutex_t mutex_userlist;
extern pthread_mutex_t mutex_local;
extern struct user local;


/* This code is derived from the PrismTech HelloWorld examples
   created by Jimmie Davis, modified by Laramie DeBaun
 */



using namespace DDS;
using namespace SuperChat;

// these classes abstract out the sending and recieving of topics
// perhaps with some cleverness, generics could be used to eliminate
// some of the code 

typedef std::vector<chatroom> chatroom_list_t;

class chatroom_data
{
  private:
  DDSEntityManager em;
  chatroomDataWriter_var Writer;
  chatroomDataReader_var Reader;
  public:
  void send ( chatroom messageInstance )
  {
     ReturnCode_t status = Writer->write(messageInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( chatroom_list_t* chatroomList )
  {
     // if any data is available, it returns a list
     assert ( chatroomList );
     chatroomSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       chatroomList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  chatroom_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    chatroomTypeSupport_var T = new chatroomTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = chatroomDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = chatroomDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~chatroom_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};

typedef std::vector<message> message_list_t;

class message_data
{
  private:
  DDSEntityManager em;
  messageDataWriter_var Writer;
  messageDataReader_var Reader;
  public:
  void send ( message messageInstance )
  {
     ReturnCode_t status = Writer->write(messageInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( message_list_t* messageList )
  {
     // if any data is available, it returns a list
     assert ( messageList );
     messageSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       messageList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  message_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    messageTypeSupport_var T = new messageTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = messageDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = messageDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~message_data ()
  {
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};

typedef std::vector<user> user_list_t;

class user_data
{
  private:
  DDSEntityManager em;
  userDataWriter_var Writer;
  userDataReader_var Reader;
  public:
  void send ( user userInstance )
  {
     ReturnCode_t status = Writer->write(userInstance, DDS::HANDLE_NIL);
     checkStatus(status, "Writer::write");
  }
  void recv ( user_list_t* userList )
  {
     // if any data is available, it returns a list
     assert ( userList );
     userSeq msgList;
     SampleInfoSeq infoSeq;
     ReturnCode_t status =  - 1;
     status = Reader->take ( msgList, infoSeq, LENGTH_UNLIMITED,
                             ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE );
     checkStatus(status, "msgDataReader::take");
     for (DDS::ULong j = 0; j < msgList.length(); j++)
     {
       userList->push_back ( msgList[j] );
     }
     status = Reader->return_loan ( msgList, infoSeq );
     checkStatus(status, "MsgDataReader::return_loan");
  }
  user_data (char *topic_name)
  {
    // participant
    em.createParticipant ("");

    // create types
    userTypeSupport_var T = new userTypeSupport ();
    em.registerType ( T.in() );

    // create Topic
    em.createTopic ( topic_name );

    // create Publisher
    em.createPublisher ();

    // create dataWriter
    em.createWriter ( false );
    DataWriter_var dwriter = em.getWriter ();
    Writer = userDataWriter::_narrow ( dwriter.in() );

    //create Subscriber
    em.createSubscriber ();

    // create DataReader
    em.createReader ();
    DataReader_var dreader = em.getReader ();
    Reader = userDataReader::_narrow( dreader.in () );
    checkHandle( Reader.in (), "MsgDataReader::_narrow" );
  }
  ~user_data ()
  {
std::cout << "deconstructor" << '\n';
    // Remove the DataWriters.
    em.deleteWriter ();

    // Remove the DataReaders
    em.deleteReader ();

    // Remove the Publisher.
    em.deletePublisher ();

    // Remove the Subscriber.
    em.deleteSubscriber ();

    // Remove the Topics.
    em.deleteTopic ();

    // Remove Participant.
    em.deleteParticipant ();
  }
};
///////////////////////////////////////////////////////////////////////////////
bool exit_flag = false;

void ctrlc ( int )
{
   exit_flag = true;
}
///////////////////////////////////////////////////////////////////////////////

void* OSPL_main(void* null)
{
  // set up ctrl-c handler
  signal ( SIGINT, ctrlc );

  // instantiate classes
  chatroom_data chatRoom ( (char*) "chatroom" );
  user_data User ( (char*) "user" );
  message_data Message ( (char*) "msg" );

  // set up some variables
  int seconds = 0;

  // the main loop
  for (;!exit_flag;) 
  {
    // send out each topic according to the rules of superchat
    // first is chatroom
    {
    //********************************OUTGOING DATA**********************/
      if (seconds%60 == 0)
      {
        // once a minute change the chatroom name wip
        chatroom messageInstance;
        messageInstance.chatroom_idx = 1;
        
        //chatRoom.send ( messageInstance );
      }
    }
    // user topic outgoing heartbeat
    {
      if (seconds%2 == 0) 
      {
         // 2.0 is less than 2.5, so this is still compliant
         pthread_mutex_lock(&mutex_local);
            User.send ( local );
         pthread_mutex_unlock(&mutex_local);
         USERS.update(); //update timers every 2 seconds for userlist
      }
    }
    // message topic; outgoing message 
    {    //takes message from buffer every second
        pthread_mutex_lock(&mutex_out);
          message messageInstance = MESSAGE_BUFFER_OUT.remove();
        pthread_mutex_unlock(&mutex_out);
        if(messageInstance.chatroom_idx != 9999){//wip sentinel for if buffer is empty
           Message.send ( messageInstance );           
        }
    }
    /*********************************INCOMING DATA*********************/
    // handle any input coming in
    {
      //chatroom name input message
      chatroom_list_t  List;
      chatRoom.recv ( &List );
      for (unsigned int i=0; i<List.size ();i++)
      {
         std::cout << "recieved new chatroom name " << List[i].chatroom_name <<
                      " chatroom index " << List[i].chatroom_idx << '\n';
      }
    } 
    {
      //user heartbeat
      user_list_t  List;
      User.recv ( &List );
      for (unsigned int i=0; i<List.size ();i++)
      {
         if(List[i].uuid != local.uuid){ //ignore own heartbeat
            USERS.add(List[i]);
         }
      }
    } 
    {
      //incoming message
      message_list_t  List;
      Message.recv ( &List );
      for (unsigned int i=0; i<List.size ();i++)
      {
         if(List[i].uuid != local.uuid){  //wip. ignore own outgoing
            pthread_mutex_lock(&mutex_in);
              MESSAGE_BUFFER_IN.add(List[i]);
            pthread_mutex_unlock(&mutex_in);
         }
      }
    } 
    seconds++;
    sleep (1);
  }
  std::cout << "normal exit" << '\n';
  pthread_exit(0);
}
