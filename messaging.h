#pragma once
#include "date.h"
class message{
    private:
        const int message_id;
        std::string message_content;
        int sender_id;
        int reciever_id;
        date date_sent;
        bool is_read;
    public:

};

class report{
    private:
        message report_description;
        bool resolved;
        void* id;//to report a listing, seller, or buyer
    public:

};
