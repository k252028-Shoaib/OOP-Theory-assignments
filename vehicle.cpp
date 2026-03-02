#include "vehicle.h"
#include <iostream>
#include <math.h>

//1. Vehicle methods
vehicle::vehicle(){
    std::cout << "--------------------- Vehicle Details ---------------------\n";
    std::cout << "Enter engine diplacement: ";
    std::cin >> engine.engine_displacement;
    std::cout << "Enter hp: ";
    std::cin >> engine.hp;
    std::cout << "Enter tourque: ";
    std::cin >> engine.torque;
    std::cout << "Enter number of cylinders: ";
    std::cin >> engine.cylinders;
    std::cout << "Enter fuel type (pertrol, hybrid, EV)";
    std::cin >> engine.fuel_type;
    std::cout << "Enter vehicle body colour: ";
    std::cin >> colour;
    std::cout << "Enter the price: ";
    std::cin >> price;
    std::cout << "Enter company name: ";
    std::cin >> company;
    std::cout << "Enter model name: ";
    std::cin >> model_name;
    std::cout << "Enter model year: ";
    std::cin >> model_year;
    std::cout << "Enter mileage (in km): ";
    std::cin >> mileage;
    std::cout << "Enter average (in km/l): ";
    std::cin >> average;
    std::cout << "Enter top speed: ";
    std::cin >> top_speed;
    std::cout << "Enter 0- 60:";
    std::cin >> zero_to_60;
    std::cout << "Enter fuel tank capacity (in l): ";
    std::cin >> fuel_tank_capacity;
    std::cout << "Enter transmission type: ";
    std::cin >> trasmission_type;
    std::cout << "Is the vehicle used? (Enter 1 for yes and 0 for no): ";
    int u;
    std::cin >> u;
    if(u) used = true;
    else used = false;
}

std::string vehicle::get_company(){
    return company;
}

std::string vehicle::get_model_name(){
    return model_name;
}

std::string vehicle::get_model_year(){
    return model_year;
}

float vehicle::get_price(){
    return price;
}

void vehicle::display_all_details(){
    std::cout << "\nCompany: " <<  company;
    std::cout << "\nModel: " << model_name;
    std::cout << "\nModel year: " << model_year;
    std::cout << "\nColour: " << colour;
    std::cout << "\nTop speed: " << top_speed;
    std::cout << "\n0-60mph: " << zero_to_60 << "s";
    std::cout << "\nFuel tank capacity: " << fuel_tank_capacity;
    if(used){
        std::cout << "\nUsed: Yes";
        std::cout << "Mileage: " << mileage;
    }
    else std::cout << "\nUsed: No\n";
}

void vehicle::calculate_resale_value(){
    float resale_value;
    int years;
    std::cout << "Enter the number of years you want to sell after: ";
    std::cin >> years;
    resale_value = price * pow(1-0.1, years);
    std::cout << "Resale Value after " << years << " will be " << resale_value << std::endl; 
}

void vehicle::calculate_finance(){
    float down_payment, monthly_interest_rate, no_months;
    std::cout << "Enter down payment: $";
    std::cin >> down_payment;
    std::cout << "Enter monthly interest rate (e.g., 5.5 for 5.5%): ";
    std::cin >> monthly_interest_rate;
    std::cout << "Enter loan term (number of months): ";
    std::cin >> no_months;
    float principal = price - down_payment;

    float numerator = monthly_interest_rate * pow(1 + monthly_interest_rate, no_months);
    float denominator = pow(1 + monthly_interest_rate, no_months) - 1;
    float monthly_payment = principal * (numerator / denominator);

    // 4. Output results
    float total_cost = (monthly_payment * no_months) + down_payment;
    float total_interest = total_cost - price;

    std::cout << "Monthly Payment: $" << monthly_payment << std::endl;
    std::cout << "Total Interest Paid: $" << total_interest << std::endl;
    std::cout << "Total Cost of Ownership: $" << total_cost << std::endl;
}

//2. Car methods
car::car() : vehicle() {
    std::cout << "Enter number of seats: ";
    std::cin >> no_of_seats;
    std::cout << "Enter trunk space: ";
    std::cin >> trunk_space;
    std::cout << "Enter ground clearance: ";
    std::cin >> ground_clearance;
    std::cout << "Enter drive train (AWD, FWD, RWD): ";
    std::cin >> drive_train;
    std::cout << "Enter number of doors: ";
    std::cin >> no_of_doors;
    add_car_features();
}

void car::display_all_details(){
    std::cout << "\nVehicle Type: Car";
    vehicle::display_all_details();
    std::cout << "No of doors: " << no_of_doors;
    std::cout << "\nNo of seats: " << no_of_seats;
    std::cout << "\nTrunk space: " << trunk_space;
    std::cout << "\nGround Clearance: " << ground_clearance;
    std::cout << "\nDrive trian: " << drive_train;
    std::cout << "\nCar Features: ";
    for (size_t i = 0; i < car_features.size(); i++){
        std::cout << "\n" << i+1;
        std::cout << "\n" << car_features[i];
    }
    std::cout << std::endl;
}

void car::add_car_features() {
    int num;
    std::cout << "How many car features do you want to add?: ";
    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::string feature;
        std::cout << "Enter feature " << i + 1 << ": ";
        std::cin.ignore(); // To clear the buffer for strings
        std::getline(std::cin, feature);
        car_features.push_back(feature);
    }
}

bool car::edit_details() {
    int choice;
    std::cout << "\n--- Edit Car Details ---";
    std::cout << "\n1. Edit Number of Seats";
    std::cout << "\n2. Edit Trunk Space";
    std::cout << "\n3. Edit Ground Clearance";
    std::cout << "\n4. Edit Price";
    std::cout << "\nEnter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter new number of seats: ";
        std::cin >> no_of_seats;
    } else if (choice == 2) {
        std::cout << "Enter new trunk space: ";
        std::cin >> trunk_space;
    } else if (choice == 3) {
        std::cout << "Enter new ground clearance: ";
        std::cin >> ground_clearance;
    } else if (choice == 4) {
        std::cout << "Enter new price: ";
        std::cin >> price;
    } else {
        std::cout << "Invalid choice.";
        return false;
    }
    return true;
}

void car::calculate_road_tax() {
    float tax;
    tax = price * 0.02;
    std::cout << "The calculated Road Tax for this car is: " << tax << " PKR" << std::endl;
}

//3. Bike methods
bike::bike() : vehicle() {
    std::cout << "Enter dry weight: ";
    std::cin >> dry_weight;
    std::cout << "Enter seat height: ";
    std::cin >> seat_height;
    std::cout << "Enter drive type (e.g. Chain, Belt, Shaft): ";
    std::cin >> drive_type;
    std::cout << "Enter cooling system: ";
    std::cin >> cooling_system;
    add_bike_features();
}

void bike::display_all_details(){
    std::cout << "\nVehicle Type: Bike";
    vehicle::display_all_details();
    std::cout << "Dryweight: " << dry_weight;
    std::cout << "\nSeat Hieght: " << seat_height;
    std::cout << "\nDrrive Type: " << drive_type;
    std::cout << "\nCooling system: " << cooling_system;
    for (size_t i = 0; i < bike_features.size(); i++){
        std::cout << "\n" << i+1;
        std::cout << "\n" << bike_features[i];
    }
    std::cout << std::endl;
}

void bike::add_bike_features() {
    int num;
    std::cout << "How many bike features do you want to add?: ";
    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::string feature;
        std::cout << "Enter feature " << i + 1 << ": ";
        std::cin.ignore();
        std::getline(std::cin, feature);
        bike_features.push_back(feature);
    }
}

bool bike::edit_details() {
    int choice;
    std::cout << "\n--- Edit Bike Details ---";
    std::cout << "\n1. Edit Dry Weight";
    std::cout << "\n2. Edit Seat Height";
    std::cout << "\n3. Edit Price";
    std::cout << "\nEnter choice: ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter new dry weight: ";
        std::cin >> dry_weight;
    } else if (choice == 2) {
        std::cout << "Enter new seat height: ";
        std::cin >> seat_height;
    } else if (choice == 3) {
        std::cout << "Enter new price: ";
        std::cin >> price;
    } else {
        std::cout << "Invalid choice.";
        return false;
    }
    return true;
}

void bike::check_safety_gear_requirement() {
    if (engine.hp > 50) {
        std::cout << "High performance bike: Full racing suit and Grade A helmet recommended.\n";
    } else {
        std::cout << "Standard bike: Standard helmet and gloves required.\n";
    }
}