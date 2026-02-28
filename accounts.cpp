#include <iostream>
#include "accounts.h"
#include "data_management.h"
#include "messaging.h"
#include "lisitngs.h"
#include "orders.h"

int user::total_users = 0;
int buyer_count = 0;//for assigning an id
int seller_count = 0;//for assigning an id
int admin_count = 0;//for assigning an id

//1. User methods:
#pragma region user
user::user(data_management* DB){ // sign up 
    dbManager = DB;
    std::cout << "Please enter your email: ";
    std::cin >> email;
    while(!dbManager->verify_email(email)){
        std::cout << "That email is already registered! Please enter a different email: ";
        std::cin >> email;
    }
    std::cout << "please enter your phone number: ";
    std::cin >> phone_number;
    std::cout << "Please enter your full name: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, full_name);
    std::cout << "Please enter your password: ";
    std::cin >> password;
    std::cout << "Please enter your location: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, location);
    total_users++;
    is_banned = false;
}

std::string user::get_email(){
    return email;
}

std::string user::get_password(){
    return password;
}

bool user::get_is_banned(){
    return is_banned;
}

void user::displayProfile() const{
    std::cout << "User details:";
    std::cout << "\nEmail: " << email;
    std::cout << "\nPhone number: " << phone_number;
    std::cout << "\nLocation: " << location;
}

void user::listing_menu(const int id){
    int choice, choice2, lsn;
    std::vector<listing*>& listing_database = dbManager->get_listing_db();

    std::cout << "---------------------------- All listings ----------------------------\n";
    for (size_t i = 0; i < listing_database.size(); i++){
        std::cout << "Listing Number: " << i << "\n";
        listing_database[i]->display_summary();
    }

    do
    {
        std::cout << "================================== Listings Menu ==================================\n";
        std::cout << "1. Re-diplay All Listings \n2. View a listing's details \n3. Exit to Main Menu\n";
        std::cout << "Enter the option number: ";
        std::cin >> choice;
        switch(choice){
            case 1://outside a listing 
                std::cout << "---------------------------- All listings ----------------------------\n";
                for (size_t i = 0; i < listing_database.size(); i++){
                    std::cout << "Listing Number: " << i << "\n";
                    listing_database[i]->display_summary();
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case 2:{//in a listing:
                std::cout << "Enter listing number: ";
                std::cin >> lsn;
                if(lsn < 0 || lsn > listing_database.size()) {
                    std::cout << "Invalid input. listing number should be between 0 and " << listing_database.size() -1 << "\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                int choice3;
                do{
                    std::cout << "------------------ Lisitng " <<  lsn <<  " ------------------\n";
                    std::cout << "1. Vehicle Details \n2. Seller Details \n3. Listing details \n4. Exit to listings Menu\n";
                    std::cout << "Enter the option number: ";
                    std::cin >> choice2;
                    switch (choice2){
                        case 1:
                            listing_database[lsn]->display_vehicle_details();
                            break;
                        case 2:
                            listing_database[lsn]->display_seller_details();
                            std::cout << "Do you want to contact the seller? (Enter 1 for yes or 0 for no) : ";
                            std::cin >> choice3;
                            if(choice3){
                                //call message create function
                            }
                            break;
                        case 3:
                            listing_database[lsn]->display_listing_details();
                            break;
                        case 4:
                            break;
                        default:
                            std::cout << "Invalid input\n";
                            break;
                    }
                }while(choice2 != 4);
                break;
                }
            case 3:
                std::cout << "Exiting to main menu...\n";
                return;
            default:
                std::cout << "Invalid input\n";
                break;
        }
    } while (choice != 3);
}


void user::menu(){
    
}
#pragma endregion

//2. Buyer methods:
#pragma region buyer
buyer::buyer() : buyer_id(buyer_count){
    buyer_count++;
}

void buyer::displayProfile() const{
    user::displayProfile();
    std::cout << "\nUser type: Buyer";
    std::cout << "\nBuyer ID: " << buyer_id;
    std::cout << "\nBuyer rating: " << buyerrating << std::endl;
}


void buyer::menu(){

}
#pragma endregion


//3. Seller methods:
#pragma region seller
seller::seller() : seller_id(seller_count){
    seller_count++;
    std::cout << "Enter your dealership name (enter 'private seller' if you are not a dealership): ";
    std::getline(std::cin, dealership_name);
}

void seller::displayProfile() const{
    std::vector<listing*>& listing_database = dbManager->get_listing_db();

    user::displayProfile();
    std::cout << "\nUser type: Seller";
    std::cout << "\nSeller ID: " << seller_id;
    std::cout << "\nSeller rating: " << seller_rating;
    if (dealership_name != "private seller") std::cout << "\nDealership name: " << dealership_name;
    else std::cout << "\nDealership name: ''";
    for (int i = 0; i < listing_database.size(); i++){
        std::cout << "\nListing ID: " << listing_database[i]->get_id();
        std::cout << "\nListing Name: " << listing_database[i]->get_name() << std::endl;
    }
}
#pragma endregion


//4. admin methods:
#pragma region admin
admin::admin() : admin_id(admin_count){
    admin_count++;
    std::cout << "Enter 1 if you are a level 1 admin and enter 2 if you are a level 2 admin: ";
    std::cin >> admin_level;
    if(admin_level != 1 && admin_level != 2){
        admin_level = 1;
        std::cout << "Invalid input, admin level set to 1\n";
    }
}


void admin::displayProfile() const{
    user::displayProfile();
    std::cout << "\nUser type: admin";
    std::cout << "\nAdmin ID: " << admin_id;
    std::cout << "\nAdmin level: " << admin_level;
    std::cout << "\nReports resolved: " << reports_resolved;
    std::cout << "\nDepartment: " << department << std::endl;
}
#pragma endregion

//5. Authorisation methods:
#pragma region data_management

#pragma endregion
