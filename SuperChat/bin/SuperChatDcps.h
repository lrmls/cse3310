//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: SuperChatDcps.h
//  Source: ./bin/SuperChatDcps.idl
//  Generated: Mon Apr  3 19:42:07 2017
//  OpenSplice V6.4.140407OSS
//  
//******************************************************************
#ifndef _SUPERCHATDCPS_H_
#define _SUPERCHATDCPS_H_

#include "sacpp_mapping.h"
#include "sacpp_DDS_DCPS.h"
#include "SuperChat.h"
#include "dds_dcps.h"


namespace SuperChat
{

   class messageTypeSupportInterface;

   typedef messageTypeSupportInterface * messageTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < messageTypeSupportInterface> messageTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < messageTypeSupportInterface> messageTypeSupportInterface_out;


   class messageDataWriter;

   typedef messageDataWriter * messageDataWriter_ptr;
   typedef DDS_DCPSInterface_var < messageDataWriter> messageDataWriter_var;
   typedef DDS_DCPSInterface_out < messageDataWriter> messageDataWriter_out;


   class messageDataReader;

   typedef messageDataReader * messageDataReader_ptr;
   typedef DDS_DCPSInterface_var < messageDataReader> messageDataReader_var;
   typedef DDS_DCPSInterface_out < messageDataReader> messageDataReader_out;


   class messageDataReaderView;

   typedef messageDataReaderView * messageDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < messageDataReaderView> messageDataReaderView_var;
   typedef DDS_DCPSInterface_out < messageDataReaderView> messageDataReaderView_out;


   class chatroomTypeSupportInterface;

   typedef chatroomTypeSupportInterface * chatroomTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < chatroomTypeSupportInterface> chatroomTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < chatroomTypeSupportInterface> chatroomTypeSupportInterface_out;


   class chatroomDataWriter;

   typedef chatroomDataWriter * chatroomDataWriter_ptr;
   typedef DDS_DCPSInterface_var < chatroomDataWriter> chatroomDataWriter_var;
   typedef DDS_DCPSInterface_out < chatroomDataWriter> chatroomDataWriter_out;


   class chatroomDataReader;

   typedef chatroomDataReader * chatroomDataReader_ptr;
   typedef DDS_DCPSInterface_var < chatroomDataReader> chatroomDataReader_var;
   typedef DDS_DCPSInterface_out < chatroomDataReader> chatroomDataReader_out;


   class chatroomDataReaderView;

   typedef chatroomDataReaderView * chatroomDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < chatroomDataReaderView> chatroomDataReaderView_var;
   typedef DDS_DCPSInterface_out < chatroomDataReaderView> chatroomDataReaderView_out;


   class userTypeSupportInterface;

   typedef userTypeSupportInterface * userTypeSupportInterface_ptr;
   typedef DDS_DCPSInterface_var < userTypeSupportInterface> userTypeSupportInterface_var;
   typedef DDS_DCPSInterface_out < userTypeSupportInterface> userTypeSupportInterface_out;


   class userDataWriter;

   typedef userDataWriter * userDataWriter_ptr;
   typedef DDS_DCPSInterface_var < userDataWriter> userDataWriter_var;
   typedef DDS_DCPSInterface_out < userDataWriter> userDataWriter_out;


   class userDataReader;

   typedef userDataReader * userDataReader_ptr;
   typedef DDS_DCPSInterface_var < userDataReader> userDataReader_var;
   typedef DDS_DCPSInterface_out < userDataReader> userDataReader_out;


   class userDataReaderView;

   typedef userDataReaderView * userDataReaderView_ptr;
   typedef DDS_DCPSInterface_var < userDataReaderView> userDataReaderView_var;
   typedef DDS_DCPSInterface_out < userDataReaderView> userDataReaderView_out;

   struct messageSeq_uniq_ {};
   typedef DDS_DCPSUFLSeq < message, struct messageSeq_uniq_> messageSeq;
   typedef DDS_DCPSSequence_var < messageSeq> messageSeq_var;
   typedef DDS_DCPSSequence_out < messageSeq> messageSeq_out;
   class messageTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef messageTypeSupportInterface_ptr _ptr_type;
      typedef messageTypeSupportInterface_var _var_type;

      static messageTypeSupportInterface_ptr _duplicate (messageTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static messageTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static messageTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static messageTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      messageTypeSupportInterface_ptr _this () { return this; }


   protected:
      messageTypeSupportInterface () {};
      ~messageTypeSupportInterface () {};
   private:
      messageTypeSupportInterface (const messageTypeSupportInterface &);
      messageTypeSupportInterface & operator = (const messageTypeSupportInterface &);
   };

   class messageDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef messageDataWriter_ptr _ptr_type;
      typedef messageDataWriter_var _var_type;

      static messageDataWriter_ptr _duplicate (messageDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static messageDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static messageDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static messageDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      messageDataWriter_ptr _this () { return this; }

      virtual DDS::LongLong register_instance (const message& instance_data) = 0;
      virtual DDS::LongLong register_instance_w_timestamp (const message& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long unregister_instance (const message& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long unregister_instance_w_timestamp (const message& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long write (const message& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long write_w_timestamp (const message& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long dispose (const message& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long dispose_w_timestamp (const message& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long writedispose (const message& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long writedispose_w_timestamp (const message& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long get_key_value (message& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const message& instance_data) = 0;

   protected:
      messageDataWriter () {};
      ~messageDataWriter () {};
   private:
      messageDataWriter (const messageDataWriter &);
      messageDataWriter & operator = (const messageDataWriter &);
   };

   class messageDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef messageDataReader_ptr _ptr_type;
      typedef messageDataReader_var _var_type;

      static messageDataReader_ptr _duplicate (messageDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static messageDataReader_ptr _narrow (DDS::Object_ptr obj);
      static messageDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static messageDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      messageDataReader_ptr _this () { return this; }

      virtual DDS::Long read (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (message& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (message& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (messageSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (message& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const message& instance) = 0;

   protected:
      messageDataReader () {};
      ~messageDataReader () {};
   private:
      messageDataReader (const messageDataReader &);
      messageDataReader & operator = (const messageDataReader &);
   };

   class messageDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef messageDataReaderView_ptr _ptr_type;
      typedef messageDataReaderView_var _var_type;

      static messageDataReaderView_ptr _duplicate (messageDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static messageDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static messageDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static messageDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      messageDataReaderView_ptr _this () { return this; }

      virtual DDS::Long read (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (message& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (message& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (messageSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (messageSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (message& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const message& instance) = 0;

   protected:
      messageDataReaderView () {};
      ~messageDataReaderView () {};
   private:
      messageDataReaderView (const messageDataReaderView &);
      messageDataReaderView & operator = (const messageDataReaderView &);
   };

   struct chatroomSeq_uniq_ {};
   typedef DDS_DCPSUFLSeq < chatroom, struct chatroomSeq_uniq_> chatroomSeq;
   typedef DDS_DCPSSequence_var < chatroomSeq> chatroomSeq_var;
   typedef DDS_DCPSSequence_out < chatroomSeq> chatroomSeq_out;
   class chatroomTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef chatroomTypeSupportInterface_ptr _ptr_type;
      typedef chatroomTypeSupportInterface_var _var_type;

      static chatroomTypeSupportInterface_ptr _duplicate (chatroomTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chatroomTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static chatroomTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chatroomTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      chatroomTypeSupportInterface_ptr _this () { return this; }


   protected:
      chatroomTypeSupportInterface () {};
      ~chatroomTypeSupportInterface () {};
   private:
      chatroomTypeSupportInterface (const chatroomTypeSupportInterface &);
      chatroomTypeSupportInterface & operator = (const chatroomTypeSupportInterface &);
   };

   class chatroomDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef chatroomDataWriter_ptr _ptr_type;
      typedef chatroomDataWriter_var _var_type;

      static chatroomDataWriter_ptr _duplicate (chatroomDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chatroomDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static chatroomDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chatroomDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      chatroomDataWriter_ptr _this () { return this; }

      virtual DDS::LongLong register_instance (const chatroom& instance_data) = 0;
      virtual DDS::LongLong register_instance_w_timestamp (const chatroom& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long unregister_instance (const chatroom& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long unregister_instance_w_timestamp (const chatroom& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long write (const chatroom& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long write_w_timestamp (const chatroom& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long dispose (const chatroom& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long dispose_w_timestamp (const chatroom& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long writedispose (const chatroom& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long writedispose_w_timestamp (const chatroom& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long get_key_value (chatroom& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const chatroom& instance_data) = 0;

   protected:
      chatroomDataWriter () {};
      ~chatroomDataWriter () {};
   private:
      chatroomDataWriter (const chatroomDataWriter &);
      chatroomDataWriter & operator = (const chatroomDataWriter &);
   };

   class chatroomDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef chatroomDataReader_ptr _ptr_type;
      typedef chatroomDataReader_var _var_type;

      static chatroomDataReader_ptr _duplicate (chatroomDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chatroomDataReader_ptr _narrow (DDS::Object_ptr obj);
      static chatroomDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chatroomDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      chatroomDataReader_ptr _this () { return this; }

      virtual DDS::Long read (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (chatroom& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (chatroom& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (chatroom& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const chatroom& instance) = 0;

   protected:
      chatroomDataReader () {};
      ~chatroomDataReader () {};
   private:
      chatroomDataReader (const chatroomDataReader &);
      chatroomDataReader & operator = (const chatroomDataReader &);
   };

   class chatroomDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef chatroomDataReaderView_ptr _ptr_type;
      typedef chatroomDataReaderView_var _var_type;

      static chatroomDataReaderView_ptr _duplicate (chatroomDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static chatroomDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static chatroomDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static chatroomDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      chatroomDataReaderView_ptr _this () { return this; }

      virtual DDS::Long read (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (chatroom& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (chatroom& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (chatroomSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (chatroom& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const chatroom& instance) = 0;

   protected:
      chatroomDataReaderView () {};
      ~chatroomDataReaderView () {};
   private:
      chatroomDataReaderView (const chatroomDataReaderView &);
      chatroomDataReaderView & operator = (const chatroomDataReaderView &);
   };

   struct userSeq_uniq_ {};
   typedef DDS_DCPSUFLSeq < user, struct userSeq_uniq_> userSeq;
   typedef DDS_DCPSSequence_var < userSeq> userSeq_var;
   typedef DDS_DCPSSequence_out < userSeq> userSeq_out;
   class userTypeSupportInterface
   :
      virtual public DDS::TypeSupport
   { 
   public:
      typedef userTypeSupportInterface_ptr _ptr_type;
      typedef userTypeSupportInterface_var _var_type;

      static userTypeSupportInterface_ptr _duplicate (userTypeSupportInterface_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static userTypeSupportInterface_ptr _narrow (DDS::Object_ptr obj);
      static userTypeSupportInterface_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static userTypeSupportInterface_ptr _nil () { return 0; }
      static const char * _local_id;
      userTypeSupportInterface_ptr _this () { return this; }


   protected:
      userTypeSupportInterface () {};
      ~userTypeSupportInterface () {};
   private:
      userTypeSupportInterface (const userTypeSupportInterface &);
      userTypeSupportInterface & operator = (const userTypeSupportInterface &);
   };

   class userDataWriter
   :
      virtual public DDS::DataWriter
   { 
   public:
      typedef userDataWriter_ptr _ptr_type;
      typedef userDataWriter_var _var_type;

      static userDataWriter_ptr _duplicate (userDataWriter_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static userDataWriter_ptr _narrow (DDS::Object_ptr obj);
      static userDataWriter_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static userDataWriter_ptr _nil () { return 0; }
      static const char * _local_id;
      userDataWriter_ptr _this () { return this; }

      virtual DDS::LongLong register_instance (const user& instance_data) = 0;
      virtual DDS::LongLong register_instance_w_timestamp (const user& instance_data, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long unregister_instance (const user& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long unregister_instance_w_timestamp (const user& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long write (const user& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long write_w_timestamp (const user& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long dispose (const user& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long dispose_w_timestamp (const user& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long writedispose (const user& instance_data, DDS::LongLong handle) = 0;
      virtual DDS::Long writedispose_w_timestamp (const user& instance_data, DDS::LongLong handle, const DDS::Time_t& source_timestamp) = 0;
      virtual DDS::Long get_key_value (user& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const user& instance_data) = 0;

   protected:
      userDataWriter () {};
      ~userDataWriter () {};
   private:
      userDataWriter (const userDataWriter &);
      userDataWriter & operator = (const userDataWriter &);
   };

   class userDataReader
   :
      virtual public DDS::DataReader
   { 
   public:
      typedef userDataReader_ptr _ptr_type;
      typedef userDataReader_var _var_type;

      static userDataReader_ptr _duplicate (userDataReader_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static userDataReader_ptr _narrow (DDS::Object_ptr obj);
      static userDataReader_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static userDataReader_ptr _nil () { return 0; }
      static const char * _local_id;
      userDataReader_ptr _this () { return this; }

      virtual DDS::Long read (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (user& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (user& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (userSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (user& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const user& instance) = 0;

   protected:
      userDataReader () {};
      ~userDataReader () {};
   private:
      userDataReader (const userDataReader &);
      userDataReader & operator = (const userDataReader &);
   };

   class userDataReaderView
   :
      virtual public DDS::DataReaderView
   { 
   public:
      typedef userDataReaderView_ptr _ptr_type;
      typedef userDataReaderView_var _var_type;

      static userDataReaderView_ptr _duplicate (userDataReaderView_ptr obj);
      DDS::Boolean _local_is_a (const char * id);

      static userDataReaderView_ptr _narrow (DDS::Object_ptr obj);
      static userDataReaderView_ptr _unchecked_narrow (DDS::Object_ptr obj);
      static userDataReaderView_ptr _nil () { return 0; }
      static const char * _local_id;
      userDataReaderView_ptr _this () { return this; }

      virtual DDS::Long read (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long read_next_sample (user& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long take_next_sample (user& received_data, DDS::SampleInfo& sample_info) = 0;
      virtual DDS::Long read_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long take_next_instance (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ULong sample_states, DDS::ULong view_states, DDS::ULong instance_states) = 0;
      virtual DDS::Long read_next_instance_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long take_next_instance_w_condition (userSeq& received_data, DDS::SampleInfoSeq& info_seq, DDS::Long max_samples, DDS::LongLong a_handle, DDS::ReadCondition_ptr a_condition) = 0;
      virtual DDS::Long return_loan (userSeq& received_data, DDS::SampleInfoSeq& info_seq) = 0;
      virtual DDS::Long get_key_value (user& key_holder, DDS::LongLong handle) = 0;
      virtual DDS::LongLong lookup_instance (const user& instance) = 0;

   protected:
      userDataReaderView () {};
      ~userDataReaderView () {};
   private:
      userDataReaderView (const userDataReaderView &);
      userDataReaderView & operator = (const userDataReaderView &);
   };

}




#endif 
