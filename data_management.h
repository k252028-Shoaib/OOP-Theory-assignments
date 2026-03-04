#pragma once
#include <vector>
#include <string>

class user;
class listing;
class message;
class seller;

class data_management{
    private:
        const std::string filename;//will implement file i/o soon
        std::vector<user*> user_database;
        std::vector<listing*> listing_database;
        std::vector<message*> message_database;
    public:
        data_management();
        data_management(const data_management&) = delete;
        data_management& operator=(data_management&&)  = delete; //ensuring there is no copy of the database

        std::vector<listing*>& get_listing_db();
        std::vector<message*>& get_message_db(const int id1, const int id2);

        user* sign_up();//no need to send/return the whole database. only returns one user
        user* sign_in();// ^
        bool verify_email(std::string email);
        user* verify_user(std::string email, std::string password);

        user* find_user_by_id(const int id);
        bool create_message(user* sender, const int sender_id, const int reciever_id);
        
        listing* create_listing(seller* s);
        listing* find_listing_by_id(const int id);
        void delete_listing(listing* l);
};  