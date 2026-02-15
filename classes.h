#ifndef CLASSES_H
#define CLASSES_H
#include <string>
#include <vector>
#include <ctime>
using namespace std;

class user;
class buyer;
class seller;
class listing;
class order;
class message;

//12.
class date{
    private:
        int second;
        int minute;
        int hour;
        int day;
        int month;
        int year;
    public:
        date();
        date(int s,int m,int h,int d,int mon,int y);
        void display_date();
        void update_date();//updates the date to today
        void change_date(int s,int m,int h,int d,int mon,int y);
        time_t get_time_elapsed(time_t t);
};

//1.
class user{
    protected:
        string email;
        string phone_number;
        string full_name;
        string password;
        string location;
        static int total_users;
        bool is_banned;
    public:
        user();
        virtual void menu();
        void updateProfile();
        bool resetPassword();
        virtual void displayProfile() const;
        void see_listings();
        string get_email();
        string get_password();
        bool get_is_banned();
        virtual ~user() = default;
};

//2.
class buyer : public user{
    private:
        const int buyer_id;
        int buyerrating = 0;
        vector<listing*> favourites;
        vector<order*> orders;
        //vector<listing*> search_history; implement this later
        vector<message*> inbox;
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
        string dealership_name;//If they are a dealer, otherwise it will be set to ""
        float total_earnings = 0;
        int ad_count = 0;
        vector<listing*> ads;
        vector<message*> inbox;
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
        vector<message*> inbox;
        string department;
    public:
        admin();
        void menu() override;
        void displayProfile() const override;
};

//5.
class authorisation{
    private:
        static vector<user*> user_database;
    public:
    static user* sign_up();
    static user* sign_in();
    static bool verify_email(string email);
    static user* verify_user(string email, string password);
};  

//6.
class listing{
    private:
        const int listing_id;
        string name;
        seller* Seller;
        void* item;
        date publish_date;
        string description;
        static int total_listings;
    public:
        int get_id();
        string get_name();
        void display_details();
};

typedef struct Engine{
    int engine_displacement;
    int hp;
    int torque;
    int cylinders;
    string fuel_type;
}Engine;

//7.
class vehicle{
    private:
        Engine engine;
        string body_type;
        string colour;
        float price;// in pkr
        string company;
        string model_name;
        string model_year;
        int mileage;// in km
        float average;// in km/l
        int top_speed;// in km/h
        float zero_to_60;// time in seconds
        float fuel_tank_capacity;// in litres
        string trasmission_type;
        bool used;//true if used, false if new
};

//8.
class car : public vehicle{
    private:
        int no_of_seats;
        double trunk_space;
        double ground_clearance;
        string drive_train;
        int no_of_doors;
        vector<string> features;
    public:
};

//9. 
class bike : public vehicle{
    private:
        int dry_weight;
        double seat_height;
        string drive_type;//4 stroke, 2 stroke etc.
        string cooling_system;//air cooled, water cooled etc.
        vector<string> features;
    public:
};

//10.
typedef struct accesory{
    string company;
    float price;
    string category;
}accesory;

//11.
class order{
    private:
        const int order_id;
        vector<accesory> cart;//each index corresponds to the index in the quantity array.
        vector<int> quantity;//e.g index 1 in quantity array tells the quantity of the item in index 1 of cart array 
        float total;
        date order_date;
        date delivery_date;
        int order_status;//1 is order placed, 2 is order on the way, 3 is order delivered
};

//12.


//13.
class message{
    private:
        const int message_id;
        string message_content;
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

#endif