#pragma once
#include <string>
#include <vector>
#include <thread>
#include <chrono>

class listing;
class message;
class data_management;
class Notification;

class user{
    protected:
        std::string email;
        std::string phone_number;
        std::string full_name;
        std::string password;
        std::string location;
        static int total_users;
        bool is_banned;
        const int user_id;
        std::vector<Notification*> notifications; 
        std::vector<std::vector<message*>> inbox;//2d array of conversations, each element points to a 1d array of messages (a conversation)
        
    public:
        user();
        static bool db_set;
        static data_management* dbManager;
        static void set_database(data_management *db);
        std::string get_full_name();
        int get_id();
        std::string get_email();
        std::string get_password();
        bool get_is_banned();
        void set_ban(bool b);
        virtual void displayProfile() const;
        void filter_listings();
        void listing_menu();
        void add_message_to_inbox(message* m, int user2_id);
        void view_inbox();
        //void display_unread_messages();
        void send_message(user* active_user,int sender_id, int reciver_id);
        virtual std::string get_special_action_name() const = 0;
        virtual void perform_special_action(listing *l) = 0;
        virtual void buyer_special_action(listing *l) = 0;
        virtual void remove_listing_references(listing* l) = 0;
        virtual void Menu() = 0;
        void add_notification(Notification* n) { notifications.push_back(n); }
        void view_notifications_menu();

        bool operator==(const user& other) const { return this->user_id == other.user_id; }

        friend class SecurityNotification;
        virtual ~user();
};

//2.
class buyer : public user{
    private:
        const int buyer_id;
        static int buyer_count;
        int buyerrating = 0;
        std::vector<listing*> favourites;
        std::vector<listing*> search_history;
    public:
        buyer();
        void displayProfile() const override;
        //void place_order();
        std::string get_special_action_name() const override;
        void perform_special_action(listing *l) override;//add to favoutites
        void buyer_special_action(listing *l) override;
        void display_favourites();
        void display_search_history();
        void remove_listing_references(listing* l) override;
        bool is_in_favourites(listing* l) const; 
        void Menu() override;
};

//3.
class seller : public user{
    private:
        const int seller_id;
        int seller_rating = 0;
        std::string dealership_name;//If they are a dealer, otherwise it will be set to ""
        std::vector<listing*> ads;
        static int seller_count;
    public:
        seller();
        int get_seller_id();
        int get_seller_rating();
        std::string get_dealership_name();
        void displayProfile() const override;
        std::string get_special_action_name() const override;
        void perform_special_action(listing *l) override;
        void buyer_special_action(listing *l) override;
        void view_my_ads();
        listing* find_listing_by_id(const int id);
        void remove_listing_references(listing* l) override;

        seller& operator++(int) { this->seller_rating++; return *this; }

        void Menu() override;
};

//4.
class admin : public user{
    private:
        int admin_level;//level 1 is to add or remove cars and bikes features, level 2 is to ban ppl and remove listings
        const int admin_id;
        int reports_resolved = 0;
        static int admin_count;
        std::string department;
    public:
        admin();
        void displayProfile() const override;
        std::string get_special_action_name() const override;
        void perform_special_action(listing *l) override;
        void buyer_special_action(listing *l) override;
        void manage_pending_listings();
        void remove_listing_references(listing* l) override {} // Admins don't store listing pointers
        void Menu() override;
};


