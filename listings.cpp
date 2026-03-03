#include "lisitngs.h"
#include <iostream>
#include "vehicle.h"

listing::listing(seller* s) : listing_id(total_listings), edit_date(0,0,0,0,0,0){
    Seller = s;
    int choice;
    std::cout << "Do you want to add a car or a bike, enter 1 for car and 2 for bike: ";
    std::cin >> choice;
    while(choice != 1 && choice != 2){
        std::cout << "Invalid input. Enter 1 for car and 2 for bike: ";
        std::cin >> choice;
    }
    if (choice == 1) Veehicle = new car();
    else Veehicle = new bike();
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

int listing::get_id(){
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
    std::cout << "---------------- Lisitng Summary ----------------";
    std::cout << "\nLisitng ID: " << listing_id;
    std::cout << "\nPublish Date: ";
    publish_date.display_date();
    if(!edited){
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

    std::cout << "Do you want to change the listing description? (1 for yes and 0 for no) : ";
    std::cin >> choice;
    std::cin.ignore(10000, '\n');
    if(choice){
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

    if(edited){
        edit_date.update_date();
        std::cout << "Listing successfully edited" << std::endl;
    }
    else std::cout << "Listing was not edited" << std::endl;
}

listing::~listing(){
    delete Veehicle;
}