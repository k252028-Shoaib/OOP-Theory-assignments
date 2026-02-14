#ifndef CLASSES_H
#define CLASSES_H
#include <string>
#include <vector>
#include <ctime>
using namespace std;

//1.
class user{
    private:
        string email;
        string phone_number;
        string full_name;
        string password;
        string location;
        static int total_users;
        bool banned;
    public:

};

//2.
class buyer : public user{
    private:
        const int buyer_id;
        int buyerrating;
        vector<listing> favourites;
        vector<order> orders;
        vector<listing> search_history;
    public:

};

//3.
class seller : public user{
    private:
        const int seller_id;
        int seller_rating;
        string dealership_name;//If they are a dealer, otherwise it will be set to ""
        float total_earnings;
        vector<listing> ads;
};

//4.
class admin : public user{
    private:
        int admin_level;
        const int admin_id;
        int reports_resolved;
        string admin_password;
        string department;
    public:
};

//5.
class listing{
    private:
        const int listing_id;
        string name;
        seller Seller;
        vehicle* obj;
        date publish_date;
        string description;
    public:

};

//6.
class Engine{
    public:
        int engine_displacement;
        int hp;
        int torque;
        int cylinders;
        string fuel_type;
};
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
};

//7.
class car : public vehicle{
    public:
        enum Features{

        };
    private:
        int no_of_seats;
        Features features;
        double trunk_space;
        double ground_clearance;
        string drive_train;
        int no_of_doors;
};

//8.
class bike : public vehicle{
    public:
        enum Features{

        };
    private:
        int dry_weight;
        Features features;
        double seat_height;
        string drive_type;
        string cooling_system;
};

//9. 
class accesory{
    float price;
};

//10.
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


//11.
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

//12.
class report{
    const int report_id;

};

#endif 
