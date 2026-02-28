#pragma once
#include <string>
#include <vector>
#include <thread>
#include <chrono>

class order;
class listing;
class message;
class data_management;

class user{
    protected:
        std::string email;
        std::string phone_number;
        std::string full_name;
        std::string password;
        std::string location;
        static int total_users;
        bool is_banned;
        data_management* dbManager;
    public:
        user(data_management* DB);
        std::string get_email();
        std::string get_password();
        bool get_is_banned();
        virtual void displayProfile() const;
        virtual void menu();
        virtual void listing_menu(const int id);
        //void updateProfile();
        //bool resetPassword();
        //message
        virtual ~user() = default;
};

//2.
class buyer : public user{
    private:
        const int buyer_id;
        int buyerrating = 0;
        std::vector<listing*> favourites;
        std::vector<order*> orders;
        //vector<listing*> search_history;
        std::vector<message*> inbox;
    public:
        buyer();
        void displayProfile() const override;
        void add_favourite();
        void place_order();
        void menu() override;
};

//3.
class seller : public user{
    private:
        const int seller_id;
        int seller_rating = 0;
        std::string dealership_name;//If they are a dealer, otherwise it will be set to ""
        float total_earnings = 0;
        int ad_count = 0;
        std::vector<message*> inbox;
    public:
        seller();
        void displayProfile() const override;
        void add_listing();
        void update_listing();
        void menu() override;
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
        void displayProfile() const override;
        void review_listing();
        void review_report();
        void menu() override;
};


