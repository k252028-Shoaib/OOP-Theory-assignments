#include <iostream>
#include "data_management.h"
#include "accounts.h"

std::vector<listing*>& data_management::get_listing_db(){
    return listing_database;
}

std::vector<message*>& data_management::get_message_db(){
    return message_database;
}


user* data_management::sign_up(){
    int choice;
    std::cout << "Enter 1 if you are a buyer, 2 if you are a seller, 3 if you are an admin. ";
    std::cin >> choice;
    user* new_user;
    switch (choice){
    case 1:
        new_user = new buyer();
        break;
    case 2:
        new_user = new seller();
        break;
    case 3:
        new_user = new admin();
        break;
    default:
        std::cout << "Invalid input\n";
        return nullptr;
    }
    user_database.push_back(new_user);
    std::cout << "Sign up successful!\n";
    return new_user;
}
bool data_management::verify_email(std::string email){
    for (int i = 0; i < user_database.size(); i++) {
        if (user_database[i]->get_email() == email) {
            return false; 
        }
    }
    return true;
}
user* data_management::sign_in(){
    int choice;
    std::string email, password;
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your password: ";
    std::cin >> password;
    user* u1 = verify_user(email,password);
    if(u1 == nullptr){
        std::cout << "Sign in failed\n";
        return nullptr;
    }
    else if(u1->get_is_banned()){
        std::cout << "User is banned!\n";
        return nullptr;
    }
    return u1;
}

user* data_management::verify_user(std::string email, std::string password) {
    for (int i = 0; i < user_database.size(); i++) {
        if (user_database[i]->get_email() == email && user_database[i]->get_password() == password) {
            return user_database[i]; 
        }
    }
    return nullptr; 
}