#include "vehicle.h"
#include <iostream>
#include "CLI_input.h" // Ensure this includes Input_handler.h
#include <cmath>

extern Input_handler* input; // Global pointer declaration

//1. Vehicle methods
vehicle::vehicle(){
    std::cout << "--------------------- Vehicle Details ---------------------\n";
    engine.engine_displacement = input->get_int("Enter engine displacement: ", 1);
    engine.hp = input->get_int("Enter hp: ", 1);
    engine.torque = input->get_int("Enter torque: ", 1);
    engine.cylinders = input->get_int("Enter number of cylinders: ", 1);
    engine.fuel_type = input->get_word("Enter fuel type (petrol, hybrid, EV): ");
    colour = input->get_word("Enter vehicle body colour: ");
    price = input->get_float("Enter the price: ", 0.0f);
    company = input->get_line("Enter company name: ");
    model_name = input->get_line("Enter model name: ");
    model_year = input->get_word("Enter model year: ");
    mileage = input->get_int("Enter mileage (in km): ", 0);
    average = input->get_float("Enter average (in km/l): ", 0.0f);
    top_speed = input->get_int("Enter top speed: ", 0);
    zero_to_60 = input->get_float("Enter 0-60 time (in seconds): ", 0.0f);
    fuel_tank_capacity = input->get_float("Enter fuel tank capacity (in litres): ", 0.0f);
    trasmission_type = input->get_word("Enter transmission type: ");
    
    int u = input->get_int("Is the vehicle used? (Enter 1 for yes and 0 for no): ", 0, 1);
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

void vehicle::set_price(float p){
    price = p;
}

int vehicle::get_mileage() { 
    return mileage; 
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
        std::cout << "\nMileage: " << mileage;
    }
    else std::cout << "\nUsed: No\n";
}

void vehicle::calculate_resale_value(){
    int years = input->get_int("Enter the number of years you want to sell after: ", 0);
    float resale_value = price * pow(1-0.1, years);
    std::cout << "Resale Value after " << years << " years will be " << resale_value << std::endl; 
}

void vehicle::calculate_finance(){
    float down_payment = input->get_float("Enter down payment: $", 0.0f, price);
    float monthly_interest_rate = input->get_float("Enter monthly interest rate (e.g., 5.5 for 5.5%): ", 0.0f);
    float no_months = input->get_float("Enter loan term (number of months): ", 1.0f);
    
    float principal = price - down_payment;

    float numerator = monthly_interest_rate * pow(1 + monthly_interest_rate, no_months);
    float denominator = pow(1 + monthly_interest_rate, no_months) - 1;
    float monthly_payment = principal * (numerator / denominator);

    // Output results
    float total_cost = (monthly_payment * no_months) + down_payment;
    float total_interest = total_cost - price;

    std::cout << "Monthly Payment: $" << monthly_payment << std::endl;
    std::cout << "Total Interest Paid: $" << total_interest << std::endl;
    std::cout << "Total Cost of Ownership: $" << total_cost << std::endl;
}

//2. Car methods
car::car() : vehicle() {
    no_of_seats = input->get_int("Enter number of seats: ", 1);
    trunk_space = input->get_double("Enter trunk space: ", 0.0);
    ground_clearance = input->get_double("Enter ground clearance: ", 0.0);
    drive_train = input->get_word("Enter drive train (AWD, FWD, RWD): ");
    no_of_doors = input->get_int("Enter number of doors: ", 1);
    add_car_features();
}

void car::display_all_details(){
    std::cout << "\nVehicle Type: Car";
    vehicle::display_all_details();
    std::cout << "\nNo of doors: " << no_of_doors;
    std::cout << "\nNo of seats: " << no_of_seats;
    std::cout << "\nTrunk space: " << trunk_space;
    std::cout << "\nGround Clearance: " << ground_clearance;
    std::cout << "\nDrive train: " << drive_train;
    std::cout << "\nCar Features: ";
    for (size_t i = 0; i < car_features.size(); i++){
        std::cout << "\n" << i+1 << ". " << car_features[i];
    }
    std::cout << std::endl;
}

void car::add_car_features() {
    if (car_features_list.empty()) {
        std::cout << "No features available in master list. Please contact admin.\n";
        return;
    }
    
    for (size_t i = 0; i < car_features_list.size(); i++) {
        std::cout << i + 1 << ". " << car_features_list[i] << "\n";
    }
    
    int choice1, choice2;
    do
    {
        choice1 = input->get_int("Enter the feature number you want to choose: ", 1, car_features_list.size());
        car_features.push_back(car_features_list[choice1-1]);

        choice2 = input->get_int("Enter 1 if you want to add more features, else enter 0: ", 0, 1);
    } while (choice2 == 1);
}

bool car::edit_details() {
    std::cout << "\n--- Edit Car Details ---";
    std::cout << "\n1. Edit Number of Seats";
    std::cout << "\n2. Edit Trunk Space";
    std::cout << "\n3. Edit Ground Clearance";
    std::cout << "\n4. Edit Price";
    
    int choice = input->get_int("\nEnter choice: ", 1, 4);

    if (choice == 1) {
        no_of_seats = input->get_int("Enter new number of seats: ", 1);
    } else if (choice == 2) {
        trunk_space = input->get_double("Enter new trunk space: ", 0.0);
    } else if (choice == 3) {
        ground_clearance = input->get_double("Enter new ground clearance: ", 0.0);
    } else if (choice == 4) {
        price = input->get_float("Enter new price: ", 0.0f);
    } else {
        return false;
    }
    return true;
}

void car::calculate_road_tax() {
    float tax = price * 0.02;
    std::cout << "The calculated Road Tax for this car is: " << tax << " PKR" << std::endl;
}

void car::admin_add_master_feature(std::string f){
    car_features_list.push_back(f);
}

//3. Bike methods
bike::bike() : vehicle() {
    dry_weight = input->get_int("Enter dry weight: ", 1);
    seat_height = input->get_double("Enter seat height: ", 0.0);
    drive_type = input->get_line("Enter drive type (e.g. Chain, Belt, Shaft): ");
    cooling_system = input->get_line("Enter cooling system: ");
    add_bike_features();
}

void bike::display_all_details(){
    std::cout << "\nVehicle Type: Bike";
    vehicle::display_all_details();
    std::cout << "\nDry weight: " << dry_weight;
    std::cout << "\nSeat Height: " << seat_height;
    std::cout << "\nDrive Type: " << drive_type;
    std::cout << "\nCooling system: " << cooling_system;
    std::cout << "\nBike Features: ";
    for (size_t i = 0; i < bike_features.size(); i++){
        std::cout << "\n" << i+1 << ". " << bike_features[i];
    }
    std::cout << std::endl;
}

void bike::add_bike_features() {
    if (bike_features_list.empty()) {
        std::cout << "No features available in master list. Please contact admin.\n";
        return;
    }
    
    for (size_t i = 0; i < bike_features_list.size(); i++) {
        std::cout << i + 1 << ". " << bike_features_list[i] << "\n";
    }
    
    int choice1, choice2;
    do
    {
        choice1 = input->get_int("Enter the feature number you want to choose: ", 1, bike_features_list.size());
        bike_features.push_back(bike_features_list[choice1-1]);

        choice2 = input->get_int("Enter 1 if you want to add more features, else enter 0: ", 0, 1);
    } while (choice2 == 1);
}

bool bike::edit_details() {
    std::cout << "\n--- Edit Bike Details ---";
    std::cout << "\n1. Edit Dry Weight";
    std::cout << "\n2. Edit Seat Height";
    std::cout << "\n3. Edit Price";
    
    int choice = input->get_int("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        dry_weight = input->get_int("Enter new dry weight: ", 1);
    } else if (choice == 2) {
        seat_height = input->get_double("Enter new seat height: ", 0.0);
    } else if (choice == 3) {
        price = input->get_float("Enter new price: ", 0.0f);
    } else {
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

void bike::admin_add_master_feature(std::string f){
    bike_features_list.push_back(f);
}

bool vehicle::operator==(const vehicle& other) const {
    return (this->company == other.company && 
            this->model_name == other.model_name && 
            this->model_year == other.model_year);
}