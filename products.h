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

//7.
class vehicle{
    private:
        Engine engine;
        std::string body_type;
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
};

//8.
class car : public vehicle{
    private:
        int no_of_seats;
        double trunk_space;
        double ground_clearance;
        std::string drive_train;
        int no_of_doors;
        std::vector<std::string> features;
    public:
};

//9. 
class bike : public vehicle{
    private:
        int dry_weight;
        double seat_height;
        std::string drive_type;//4 stroke, 2 stroke etc.
        std::string cooling_system;//air cooled, water cooled etc.
        std::vector<std::string> features;
    public:
};

//10.
typedef struct accesory{
    std::string company;
    float price;
    std::string category;
}accesory;