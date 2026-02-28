#pragma once
#include <string>
#include <vector>
#include "messaging.h"
#include "lisitngs.h"
#include "orders.h"

class user{
    protected:
        std::string email;
        std::string phone_number;
        std::string full_name;
        std::string password;
        std::string location;
        static int total_users;
        bool is_banned;
    public:
        user();
        virtual void menu();
        //void updateProfile();
        //bool resetPassword();
        virtual void displayProfile() const;
        void see_listings();
        std::string get_email();
        std::string get_password();
        bool get_is_banned();
        virtual ~user() = default;
};

//2.
class buyer : public user{
    private:
        const int buyer_id;
        int buyerrating = 0;
        std::vector<listing*> favourites;
        std::vector<order*> orders;
        //vector<listing*> search_history; implement this later
        std::vector<message*> inbox;
    public:
        buyer();
        void menu() override;
        void displayProfile() const override;
        void add_favourite();
        void place_order();
};

//3.
class seller : public user{
    private:
        const int seller_id;
        int seller_rating = 0;
        std::string dealership_name;//If they are a dealer, otherwise it will be set to ""
        float total_earnings = 0;
        int ad_count = 0;
        std::vector<listing*> ads;
        std::vector<message*> inbox;
    public:
        seller();
        void menu() override;
        void displayProfile() const override;
};

//4.
class admin : public user{
    private:
        int admin_level;//level 1 is to add or remove features and listings, level 2 is to ban ppl and see reports and take action
        const int admin_id;
        int reports_resolved = 0;
        std::vector<message*> inbox;
        std::string department;
    public:
        admin();
        void menu() override;
        void displayProfile() const override;
};

//5.
class authorisation{
    private:
        static std::vector<user*> user_database;
    public:
    static user* sign_up();
    static user* sign_in();
    static bool verify_email(std::string email);
    static user* verify_user(std::string email, std::string password);
};  
