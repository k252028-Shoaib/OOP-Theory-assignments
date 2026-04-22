#include "messaging.h"
#include "CLI_Input.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const message& m) {
    os << "From ID: " << m.sender_id << "\nContent: " << m.message_content;
    return os;
}

message::message(const int sender_id, const int reciever_id): sender_id(sender_id), reciever_id(reciever_id), edit_date(0,0,0,0,0,0){
    std::cout << "--------------------- Message Details ---------------------\n";
    message_content = input->get_paragraphs("Enter your message.");
    edited = false;
    is_read = false;
}

void message::edit_message(){
    int choice;
    choice = input->get_int("Please note the previous message content will be deleted. If you wish to continue, enter 1, else enter 0: ", 0,1);
    if (choice){
        message_content = input->get_paragraphs("Enter your new message.");
        std::cout << "Message sucessfully edited\n";
        edit_date.update_date();
        edited = true;
    }
}

void message::display_message(){
    std::cout << "User ID: " << sender_id << "\n";
    display_time_elapsed();
    date_sent.display_date();
    if(edited){
        std::cout << "Edited on: ";
        edit_date.display_date();
    }
    std::cout << message_content << std::endl;
}

void message::display_time_elapsed() {
    time_t time_sent = date_sent.get_time_t();
    
    time_t elapsed = date::get_time_elapsed(time_sent);
    
    int days = elapsed / (24 * 3600);
    elapsed %= (24 * 3600);
    
    int hours = elapsed / 3600;
    elapsed %= 3600;
    
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    
    std::cout << "Message sent: ";
    if (days > 0) std::cout << days << " days, ";
    if (hours > 0) std::cout << hours << " hours, ";
    if (minutes > 0) std::cout << minutes << " minutes, ";
    std::cout << seconds << " seconds ago." << std::endl;
}

int message::get_sender_id(){
    return sender_id;
}

int message::get_reciever_id(){
    return reciever_id;
}