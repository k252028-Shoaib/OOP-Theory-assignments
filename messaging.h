#pragma once
#include "date.h"
#include <string>
class message{
    private:
        std::string message_content;
        const int sender_id;
        const int reciever_id;
        date date_sent;
        date edit_date;
        bool edited;
        bool is_read;
    public:
        message(const int sender_id, const int reciever_id);
        //make copy constructor
        void input_message();
        void edit_message();
        void display_message();
        void display_time_elapsed();
        int get_sender_id();
        int get_reciever_id();
};

//create conversation class

// class report{
//     private:
//         message report_description;
//         bool resolved;
//         void* id;//to report a listing, seller, or buyer
//     public:

// };
