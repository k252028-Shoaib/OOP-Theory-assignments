#pragma once
#include <vector>
#include <string>

class user;
class listing;
class message;

class data_management{
    private:
        std::vector<user*> user_database;
        std::vector<listing*> listing_database;
        std::vector<message*> message_database;
    public:

        // constructor that loads data from the file
        data_management(const data_management&) = delete;
        data_management& operator=(data_management&&)  = delete; //ensuring there is no copy of the database

        std::vector<listing*>& get_listing_db();
        std::vector<message*>& get_message_db(const int id1, const int id2);

        user* sign_up();//no need to send the whole database. only returns one user
        user* sign_in();// ^
        bool verify_email(std::string email);
        user* verify_user(std::string email, std::string password);

        //create will call the constructor and delete will call the destructor
        message* create_message(const int id1, const int id2);
        /*
        delete message

        create listing
        delete listing

        destructor that saves data to the file 
        */
};  