#include "Notification.h"
#include <iostream>

int Notification::total_notifications = 0;

Notification::Notification(int receiver_id) 
    : notification_id(++total_notifications), receiver_id(receiver_id), is_read(false) {
    // timestamp is automatically initialized to "now" by the date constructor
}

void Notification::mark_as_read() {
    is_read = true;
}

bool Notification::get_is_read() const {
    return is_read;
}

int Notification::get_receiver_id() const {
    return receiver_id;
}

int Notification::get_id() const {
    return notification_id;
}


MessageNotification::MessageNotification(int receiver_id, message* m, std::string sender)
    : Notification(receiver_id), linked_message(m), sender_name(sender) {}

void MessageNotification::display() const {
    std::cout << "[" << get_type() << "] ID: " << notification_id << "\n";
    std::cout << "From: " << sender_name << "\n";
    std::cout << "Received: ";
    timestamp.display_date();
    if (!is_read) std::cout << "** UNREAD **\n";
    std::cout << "------------------------------------------\n";
}

std::string MessageNotification::get_type() const {
    return "New Message";
}

message* MessageNotification::get_message_ptr() const {
    return linked_message;
}



ListingNotification::ListingNotification(int receiver_id, std::string name, std::string status)
    : Notification(receiver_id), listing_name(name), status_update(status) {}

void ListingNotification::display() const {
    std::cout << "[" << get_type() << "] ID: " << notification_id << "\n";
    std::cout << "Listing: " << listing_name << "\n";
    std::cout << "Status: " << status_update << "\n";
    std::cout << "Time: "; timestamp.display_date();
    std::cout << "------------------------------------------\n";
}

std::string ListingNotification::get_type() const { return "Listing Update"; }



PriceAlert::PriceAlert(int receiver_id, std::string name, float old_p, float new_p)
    : Notification(receiver_id), vehicle_name(name), old_price(old_p), new_price(new_p) {}

void PriceAlert::display() const {
    std::cout << "[" << get_type() << "] ID: " << notification_id << "\n";
    std::cout << "Vehicle: " << vehicle_name << "\n";
    std::cout << "Price Change: " << old_price << " -> " << new_price << " PKR\n";
    std::cout << "Time: "; timestamp.display_date();
    std::cout << "------------------------------------------\n";
}

std::string PriceAlert::get_type() const { return "Price Drop Alert"; }



SecurityNotification::SecurityNotification(int receiver_id, std::string msg)
    : Notification(receiver_id), security_msg(msg) {}

void SecurityNotification::display() const {
    std::cout << "[" << get_type() << "] ID: " << notification_id << "\n";
    std::cout << "Security Alert: " << security_msg << "\n";
    std::cout << "Time: "; timestamp.display_date();
    std::cout << "------------------------------------------\n";
}

std::string SecurityNotification::get_type() const { return "Security/Account"; }