#include "accounts.h"
#include "data_management.h"
#include "date.h"
#include "lisitngs.h"
#include "messaging.h"
#include "vehicle.h"
#include <iostream>

int user::total_users = 0;
int buyer::buyer_count = 0;//for assigning an id
int seller::seller_count = 0;//for assigning an id
int admin::admin_count = 0;//for assigning an id
data_management* user::dbManager = nullptr;
bool user::db_set = false;
int listing::total_listings = 0;
std::vector<std::string> car::car_features_list;
std::vector<std::string> bike::bike_features_list;

int main(){
    data_management database;
    user* active_user = nullptr;
    user::set_database(&database);
    int choice;
    do
    {
        std::cout << "================================== Welcome To Cyber Market! ==================================\n";
        std::cout << "1. Sign up\n2. Sign in\n3. Exit\nEnter choice number: ";
        std::cin >> choice;
        if (choice == 1){
            active_user = user::dbManager->sign_up();
        }
        else if(choice == 2){
            active_user = user::dbManager->sign_in();
        }
        else if (choice == 3){
            std::cout << "Exiting...";
            return 0;
        }
        else if(choice !=3){
            std::cout << "Invalid input.\n";
            continue;
        }
        if(active_user == nullptr){
            std::cout << "Failed to sign up/in\n";
            continue;
        }

        //if program reaches here means user has successfully sign up/in. Next is the user menu
        active_user->Menu();
        //when user exits this, he is signing out. so make active_user = null
        active_user = nullptr;
    } while (choice != 3);
    
    return 0;
}