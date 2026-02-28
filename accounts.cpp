#include <iostream>
#include "accounts.h"

int user::total_users = 0;
int listing::total_listings = 0;
int buyer_count = 0;//for assigning an id
int seller_count = 0;//for assigning an id
int admin_count = 0;//for assigning an id
std::vector<user*> authorisation::user_database;

//1. User methods:
#pragma region user
user::user(){ // sign up 
    std::cout << "Please enter your email: ";
    std::cin >> email;
    while(!authorisation::verify_email(email)){
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
void user::menu(){
    
}
void user::displayProfile() const{
    std::cout << "User details:";
    std::cout << "\nEmail: " << email;
    std::cout << "\nPhone number: " << phone_number;
    std::cout << "\nLocation: " << location;
}
bool user::get_is_banned(){
    return is_banned;
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
    user::displayProfile();
    std::cout << "\nUser type: Seller";
    std::cout << "\nSeller ID: " << seller_id;
    std::cout << "\nSeller rating: " << seller_rating;
    if (dealership_name != "private seller") std::cout << "\nDealership name: " << dealership_name;
    else std::cout << "\nDealership name: ''";
    for (int i = 0; i < ads.size(); i++){
        std::cout << "\nListing ID: " << ads[i]->get_id();
        std::cout << "\nListing Name: " << ads[i]->get_name() << std::endl;
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
#pragma region Authorisation
user* authorisation::sign_up(){
    int choice;
    std::cout << "Enter 1 if you are a buyer, 2 if you are a seller, 3 if you are an admin. ";
    std::cin >> choice;
    user* new_user;
    switch (choice){
    case 1:
        new_user = new buyer();
        break;
    case 2:
        new_user = new seller();
        break;
    case 3:
        new_user = new admin();
        break;
    default:
        std::cout << "Invalid input\n";
        return nullptr;
    }
    user_database.push_back(new_user);
    std::cout << "Sign up successful!\n";
    return new_user;
}
bool authorisation::verify_email(std::string email){
    for (int i = 0; i < user_database.size(); i++) {
        if (user_database[i]->get_email() == email) {
            return false; 
        }
    }
    return true;
}
user* authorisation::sign_in(){
    int choice;
    std::string email, password;
    std::cout << "Enter your email: ";
    std::cin >> email;
    std::cout << "Enter your password: ";
    std::cin >> password;
    user* u1 = verify_user(email,password);
    if(u1 == nullptr){
        std::cout << "Sign in failed\n";
        return nullptr;
    }
    else if(u1->get_is_banned()){
        std::cout << "User is banned!\n";
        return nullptr;
    }
    return u1;
}

user* authorisation::verify_user(std::string email, std::string password) {
    for (int i = 0; i < user_database.size(); i++) {
        if (user_database[i]->get_email() == email && user_database[i]->get_password() == password) {
            return user_database[i]; 
        }
    }
    return nullptr; 
}
#pragma endregion


//6. 
int listing::get_id(){
    return listing_id;
}
std::string listing::get_name(){
    return name;
}


int main(){
    std::cout << "Signing up...\n";
    user* ptr1 = authorisation::sign_up();
    std::cout << "Signing in...\n";
    user* ptr2 = authorisation::sign_in();
    if (ptr2 == nullptr)std::cout << "null ptr\n";
    
    else ptr2->displayProfile();
    return 0;
}