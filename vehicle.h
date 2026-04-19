#pragma once
#include <string>
#include <vector>
typedef struct Engine{
    int engine_displacement;
    int hp;
    int torque;
    int cylinders;
    std::string fuel_type;
}Engine;

class vehicle{
    protected:
        Engine engine;
        std::string colour;
        float price;// in pkr
        std::string company;
        std::string model_name;
        std::string model_year;
        int mileage;// in km
        float average;// in km/l
        int top_speed;// in km/h
        float zero_to_60;// time in seconds
        float fuel_tank_capacity;// in litres
        std::string trasmission_type;
        bool used;//true if used, false if new
    public:
        vehicle();
        void calculate_resale_value();
        void calculate_finance();
        virtual void display_all_details();
        virtual bool edit_details() = 0;
        std::string get_company();
        std::string get_model_name();
        std::string get_model_year();
        float get_price();
        int get_mileage();
        virtual ~vehicle() = default;
};

class car : public vehicle{
    private:
        int no_of_seats;
        double trunk_space;
        double ground_clearance;
        std::string drive_train;
        int no_of_doors;
        std::vector<std::string> car_features;
        static std::vector<std::string> car_features_list;//this is a list of features made and managed by the admin, user can add features from this list
    public:
        car();
        void display_all_details() override;
        bool edit_details() override;
        void add_car_features();
        void calculate_road_tax();
        static void admin_add_master_feature(std::string f);
};

class bike : public vehicle{
    private:
        int dry_weight;
        double seat_height;
        std::string drive_type;//4 stroke, 2 stroke etc.
        std::string cooling_system;//air cooled, water cooled etc.
        std::vector<std::string> bike_features;
        static std::vector<std::string> bike_features_list;//this is a list of features made and managed by the admin, user can add features from this list
    public:
        bike();
        void display_all_details() override;
        bool edit_details() override;
        void add_bike_features();
        void check_safety_gear_requirement();
        static void admin_add_master_feature(std::string f);
};

