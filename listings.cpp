#include <iostream>
#include "lisitngs.h"
#include "vehicle.h"
#include "accounts.h"
#include "data_management.h"
#include "CLI_Input.h"

listing::listing(seller* s, vehicle *v) : listing_id(total_listings), edit_date(0,0,0,0,0,0), Seller(s), Veehicle(v){
    std::cout << "--------------------- Listing Details ---------------------\n";
    total_listings++;
    std::cout << "Please enter listing name: ";
    std::cin.ignore(1000, '\n');
    std::getline(std::cin, name);
    std::cout << "Please enter listing description. Press enter 2 times when you want to stop: ";

    std::string currentLine;
    while (std::getline(std::cin, currentLine)) {
        if (currentLine.empty()) {
            break;
        }
        description += currentLine + "\n"; 
    } 
    is_approved = false;
}

bool listing::get_is_approved(){
    return is_approved;
}

void listing::set_is_approved(bool b){
    is_approved = b;
}

int listing::get_listing_id(){
    return listing_id;
}

std::string listing::get_name(){
    return name;
}

vehicle* listing::get_vehicle() { return Veehicle; }

int listing::get_seller_id(){
    return Seller->get_id();
}

void listing::display_summary(){
    std::cout << "---------------- Lisitng Summary ----------------";
    std::cout << "\nListing id: " << listing_id;
    std::cout << "\nPublish Date: ";
    publish_date.display_date();
    std::cout << "Seller Name: " << Seller->get_full_name();
    std::cout << "\nVehicle Company/model/year: " <<  Veehicle->get_company() << " / " << Veehicle->get_model_name()
    << " / " <<  Veehicle->get_model_year();
    std::cout << "\nPrice: " << Veehicle->get_price() << "\n" << std::endl;
}

int listing::display_seller_details(){
    std::cout << "---------------- Seller Details ----------------";
    std::cout << "\nSeller ID: " << Seller->get_seller_id();
    std::cout << "\nSeller Name: " << Seller->get_full_name();
    std::cout << "\nSeller's contact id (user id): " << Seller->get_id();
    std::cout << "\nSeller email: " << Seller->get_email();
    std::cout << "\nSeller rating: " << Seller->get_seller_rating();
    if (Seller->get_dealership_name() != "private seller") std::cout << "\nDealership name: " << Seller->get_dealership_name() << "\n";
    else std::cout << "\nDealership name: ''\n";
    return Seller->get_id();
}

void listing::display_vehicle_details(){
    std::cout << "---------------- Vehicle Details ----------------";
    Veehicle->display_all_details();
    std::cout << "Description: " << description << std::endl;
}

void listing::display_listing_details(){
    std::cout << "---------------- Lisitng Details ----------------";
    std::cout << "\nLisitng ID: " << listing_id;
    std::cout << "\nPublish Date: ";
    publish_date.display_date();
    if(edited){
        std::cout << "Edited on: ";
        edit_date.display_date();
    }
}

void listing::edit_listing(){
    int choice;
    std::cout << "Do you want to change the listing name? (1 for yes and 0 for no) : ";
    std::cin >> choice;
    std::cin.ignore(10000, '\n');
    if(choice){
        std::cout << "Enter the new name: ";
        std::getline(std::cin, name);
        edited = true;
    }

    std::cout << "Do you want to change the listing description? (1 for yes and 0 for no. NOTE: The prev. desciption will be deleted, proceed with caution) : ";
    std::cin >> choice;
    std::cin.ignore(10000, '\n');
    if(choice){
        description = "";
        std::cout << "Enter the new description. Press enter 2 times when you want to stop: ";
        std::string currentLine;
        while (std::getline(std::cin, currentLine)) {
            if (currentLine.empty()) {
                break;
            }
            description += currentLine + "\n"; 
        }
        edited = true;
    }

    std::cout << "Do you want to change the Veehicle details? (1 for yes and 0 for no) : ";
    std::cin >> choice;
    std::cin.ignore(10000, '\n');
    if(choice){
        if(Veehicle->edit_details()) edited = true;
    }

    float old_price = Veehicle->get_price();
    
    // Use the new input handler for validation
    int choice = input->get_int("Edit price? (1 for yes, 0 for no): ", 0, 1);
    
    if (choice == 1) {
        float new_price = input->get_float("Enter new price: ", 0.0f);
        // Assume you add a set_price method to vehicle
        Veehicle->set_price(new_price); 
        
        if (new_price < old_price) {
            // Logic to notify followers
            user::dbManager->trigger_price_alert(this, old_price, new_price);
        }
    }

    if(edited){
        edit_date.update_date();
        std::cout << "Listing successfully edited" << std::endl;
    }
    else std::cout << "Listing was not edited" << std::endl;
}

listing::~listing(){
    delete Veehicle;
}

seller* listing::get_seller_ptr() const{
    return Seller;
}


// Reasoning: Used in data_management to find and remove specific listings from vectors.
bool listing::operator==(const listing& other) const {
    return this->listing_id == other.listing_id;
}

// Reasoning: Simplifies printing listing summaries in loops (cout << *listing_ptr).
std::ostream& operator<<(std::ostream& os, const listing& l) {
    os << "Listing [" << l.listing_id << "]: " << l.name << " | Price: " << l.Veehicle->get_price();
    return os;
}