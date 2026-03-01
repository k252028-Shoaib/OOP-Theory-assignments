#pragma once
#include "date.h"
class message{
    private:
        std::string message_content;
        const int sender_id;
        const int reciever_id;
        date date_sent;
        date edit_date;
    public:
        message(const int sender_id, const int reciever_id);
        void input_message();
        void edit_message();
        void display_message();
        void display_time_elapsed();
};

// class report{
//     private:
//         message report_description;
//         bool resolved;
//         void* id;//to report a listing, seller, or buyer
//     public:

// };
