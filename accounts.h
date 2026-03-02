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
        static data_management* dbManager;
        const int user_id;
        std::vector<std::vector<message*>> inbox;//2d array of conversations, each element points to a 1d array of messages (a conversation)
        
    public:
        user();
        std::string get_full_name();
        int get_id();
        std::string get_email();
        std::string get_password();
        bool get_is_banned();
        virtual void displayProfile() const;
        virtual void Menu();
        void listing_menu();
        void add_message_to_inbox(message* m, int user2_id);
        //void display_unread_messages();
        virtual std::string get_special_action_name() const = 0;
        virtual void perform_special_action(listing *l) = 0;
        //void updateProfile();
        //bool resetPassword();
        //create conversation
        //reply
        //find conversation
        virtual ~user() = default;
};

//2.
class buyer : public user{
    private:
        const int buyer_id;
        static int buyer_count;
        int buyerrating = 0;
        std::vector<listing*> favourites;
        std::vector<order*> orders;
        //std::vector<listing*> search_history;
    public:
        buyer();
        void displayProfile() const override;
        void place_order();
        std::string get_special_action_name() const override;
        void perform_special_action(listing *l) override;
        //view favourites list
        void Menu() override;
};

//3.
class seller : public user{
    private:
        const int seller_id;
        int seller_rating = 0;
        std::string dealership_name;//If they are a dealer, otherwise it will be set to ""
        std::vector<listing*> ads;
        int ad_count = 0;
        static int seller_count;
    public:
        seller();
        int get_seller_id();
        int get_seller_rating();
        std::string get_dealership_name();
        void displayProfile() const override;
        void add_listing();
        void edit_listing();
        std::string get_special_action_name() const override;
        void perform_special_action(listing *l) override;
        //view ads list
        void Menu() override;
};

//4.
class admin : public user{
    private:
        int admin_level;//level 1 is to add or remove features and listings, level 2 is to ban ppl and see reports and take action
        const int admin_id;
        int reports_resolved = 0;
        static int admin_count;
        std::string department;
    public:
        admin();
        void displayProfile() const override;
        void review_listing();
        void review_report();
        std::string get_special_action_name() const override;
        void perform_special_action(listing *l) override;
        void Menu() override;
};


