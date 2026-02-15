#include <iostream>
#include "classes.h"
#include "functions.h"

int user::total_users = 0;
int listing::total_listings = 0;
int buyer_count = 0;//for assigning an id
int seller_count = 0;//for assigning an id
int admin_count = 0;//for assigning an id
vector<user*> authorisation::user_database;

//1. User methods:
#pragma region user
user::user(){ // sign up 
    cout << "Please enter your email: ";
    cin >> email;
    while(!authorisation::verify_email(email)){
        cout << "That email is already registered! Please enter a different email: ";
        cin >> email;
    }
    cout << "please enter your phone number: ";
    cin >> phone_number;
    cout << "Please enter your full name: ";
    cin.ignore(10000, '\n');
    getline(cin, full_name);
    cout << "Please enter your password: ";
    cin >> password;
    cout << "Please enter your location: ";
    cin.ignore(10000, '\n');
    getline(cin, location);
    total_users++;
    is_banned = false;
}
string user::get_email(){
    return email;
}
string user::get_password(){
    return password;
}
void user::menu(){
    
}
void user::displayProfile() const{
    cout << "User details:";
    cout << "\nEmail: " << email;
    cout << "\nPhone number: " << phone_number;
    cout << "\nLocation: " << location;
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
    cout << "\nUser type: Buyer";
    cout << "\nBuyer ID: " << buyer_id;
    cout << "\nBuyer rating: " << buyerrating << endl;
}

void buyer::menu(){

}
#pragma endregion


//3. Seller methods:
#pragma region seller
seller::seller() : seller_id(seller_count){
    seller_count++;
    cout << "Enter your dealership name (enter 'private seller' if you are not a dealership): ";
    getline(cin, dealership_name);
}

void seller::displayProfile() const{
    user::displayProfile();
    cout << "\nUser type: Seller";
    cout << "\nSeller ID: " << seller_id;
    cout << "\nSeller rating: " << seller_rating;
    if (dealership_name != "private seller") cout << "\nDealership name: " << dealership_name;
    else cout << "\nDealership name: ''";
    for (int i = 0; i < ads.size(); i++){
        cout << "\nListing ID: " << ads[i]->get_id();
        cout << "\nListing Name: " << ads[i]->get_name() << endl;
    }
    
}
#pragma endregion


//4. admin methods:
#pragma region admin
admin::admin() : admin_id(admin_count){
    admin_count++;
    cout << "Enter 1 if you are a level 1 admin and enter 2 if you are a level 2 admin: ";
    cin >> admin_level;
    if(admin_level != 1 && admin_level != 2){
        admin_level = 1;
        cout << "Invalid input, admin level set to 1\n";
    }
}


void admin::displayProfile() const{
    user::displayProfile();
    cout << "\nUser type: admin";
    cout << "\nAdmin ID: " << admin_id;
    cout << "\nAdmin level: " << admin_level;
    cout << "\nReports resolved: " << reports_resolved;
    cout << "\nDepartment: " << department << endl;
}
#pragma endregion


//5. Authorisation methods:
#pragma region Authorisation
user* authorisation::sign_up(){
    int choice;
    cout << "Enter 1 if you are a buyer, 2 if you are a seller, 3 if you are an admin. ";
    cin >> choice;
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
        cout << "Invalid input\n";
        return nullptr;
    }
    user_database.push_back(new_user);
    cout << "Sign up successful!\n";
    return new_user;
}
bool authorisation::verify_email(string email){
    for (int i = 0; i < user_database.size(); i++) {
        if (user_database[i]->get_email() == email) {
            return false; 
        }
    }
    return true;
}
user* authorisation::sign_in(){
    int choice;
    string email, password;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    user* u1 = verify_user(email,password);
    if(u1 == nullptr){
        cout << "Sign in failed\n";
        return nullptr;
    }
    else if(u1->get_is_banned()){
        cout << "User is banned!\n";
        return nullptr;
    }
    return u1;
}

user* authorisation::verify_user(string email, string password) {
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
string listing::get_name(){
    return name;
}
//12. Date methods:
#pragma region Date Methods
date::date(){
    time_t now = time(0); // get current time
    tm* time = localtime(&now); //converts to the correct structure
    
    second = time->tm_sec;
    minute = time->tm_min;
    hour = time->tm_hour;
    day = time->tm_mday;
    month = time->tm_mon;
    year = time->tm_year;
}
date::date(int s,int m,int h,int d,int mon,int y){
    second = s;
    minute = m;
    hour = h;
    day = d;
    month = mon;
    year = y;
}
void date::display_date(){

}
void date::update_date(){
    time_t now = time(0); 
    tm* time = localtime(&now);
    
    second = time->tm_sec;
    minute = time->tm_min;
    hour = time->tm_hour;
    day = time->tm_mday;
    month = time->tm_mon;
    year = time->tm_year;
}
void date::change_date(int s,int m,int h,int d,int mon,int y){
    second = s;
    minute = m;
    hour = h;
    day = d;
    month = mon;
    year = y;
}
time_t date::get_time_elapsed(time_t t){
    return time(0) - t;
}
#pragma endregion

int main(){
    cout << "Signing up...\n";
    user* ptr1 = authorisation::sign_up();
    cout << "Signing in...\n";
    user* ptr2 = authorisation::sign_in();
    if (ptr2 == nullptr)cout << "null ptr\n";
    
    else ptr2->displayProfile();
    return 0;
}