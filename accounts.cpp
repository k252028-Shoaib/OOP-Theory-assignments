#include <iostream>
#include "accounts.h"
#include "data_management.h"
#include "messaging.h"
#include "lisitngs.h"
#include "vehicle.h"

//1. User methods:
#pragma region user
user::user():user_id(total_users){ // sign up 
    std::cout << "--------------------- User Details ---------------------\n";
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

void user::set_database(data_management *db){
    if (!db_set) {
        dbManager = db;
        db_set =true;
    }
    else std::cout << "Database is already set!" << std::endl;
}

std::string user::get_full_name(){
    return full_name;
}

int user::get_id(){
    return user_id;
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

void user::set_ban(bool b){
    is_banned = b;
}

void user::displayProfile() const{
    std::cout << "User details:";
    std::cout << "\nEmail: " << email;
    std::cout << "\nPhone number: " << phone_number;
    std::cout << "\nLocation: " << location;
    if(is_banned) std::cout << "\nIs Banned: Yes";
    else std::cout << "\nIs Banned: No";
}

void user::filter_listings() {
    std::vector<listing*>& listing_database = dbManager->get_listing_db();
    int filter_choice;

    std::cout << "================== Filter Vehicles ==================\n";
    std::cout << "1. By Brand (Company)\n";
    std::cout << "2. By Model Name\n";
    std::cout << "3. By Max Price\n";
    std::cout << "4. By Model Year\n";
    std::cout << "5. By Max Mileage\n";
    std::cout << "Enter the option number: ";
    std::cin >> filter_choice;

    std::string string_query;
    float float_query;
    int int_query;
    bool found = false;

    // Gather the search query based on what they chose
    switch (filter_choice) {
        case 1:
            std::cout << "Enter Brand/Company name: ";
            std::cin >> string_query;
            break;
        case 2:
            std::cout << "Enter Model name: ";
            std::cin >> string_query;
            break;
        case 3:
            std::cout << "Enter Maximum Price (PKR): ";
            std::cin >> float_query;
            break;
        case 4:
            std::cout << "Enter Model Year: ";
            std::cin >> string_query;
            break;
        case 5:
            std::cout << "Enter Maximum Mileage (km): ";
            std::cin >> int_query;
            break;
        default:
            std::cout << "Invalid filter option.\n";
            return;
    }

    std::cout << "\n---------------- Filtered Results ----------------\n";
    for (size_t i = 0; i < listing_database.size(); i++) {
        vehicle* v = listing_database[i]->get_vehicle();
        if (v == nullptr) continue; // Safety check in case of empty pointers
        if(!listing_database[i]->get_is_approved()) continue;//don't show if the listing is not approved

        bool match = false;

        // Check if the current vehicle matches the user's query
        switch (filter_choice) {
            case 1: if (v->get_company() == string_query) match = true; break;
            case 2: if (v->get_model_name() == string_query) match = true; break;
            case 3: if (v->get_price() <= float_query) match = true; break;
            case 4: if (v->get_model_year() == string_query) match = true; break;
            case 5: if (v->get_mileage() <= int_query) match = true; break;
        }

        if (match) {
            listing_database[i]->display_summary();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No vehicles found matching your criteria.\n";
    }
    std::cout << "--------------------------------------------------\n";
}

void user::listing_menu(){
    int choice, choice2, ls_id;
    std::vector<listing*>& listing_database = dbManager->get_listing_db();

    std::cout << "---------------------------- All listings ----------------------------\n";
    for (size_t i = 0; i < listing_database.size(); i++){
        if(!listing_database[i]->get_is_approved()) continue;//don't show if the listing is not approved
        listing_database[i]->display_summary();
    }

    do
    {
        std::cout << "================================== Listings Menu ==================================\n";
        std::cout << "1. Re-diplay All Listings \n2. View a listing's details \n3. Filter listings \n4. Exit to Main Menu\n";
        std::cout << "Enter the option number: ";
        std::cin >> choice;
        switch(choice){
            case 1://outside a listing 
                std::cout << "---------------------------- All listings ----------------------------\n";
                for (size_t i = 0; i < listing_database.size(); i++){
                    if(!listing_database[i]->get_is_approved()) continue;//don't show if the listing is not approved
                    listing_database[i]->display_summary();
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            case 2:{//in a listing:
                std::cout << "Enter listing id: ";
                std::cin >> ls_id;
                listing* l = dbManager->find_listing_by_id(ls_id);
                if(l == nullptr) {
                    std::cout << "Listing id not found\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                if(!l->get_is_approved()){
                    std::cout << "Listing is not approved yet\n";
                    break;
                }
                buyer_special_action(l);
                int choice3;
                do{
                    std::cout << "------------------ Lisitng ID: " <<  ls_id <<  " ------------------\n";
                    std::cout << "1. Vehicle Details \n2. Seller Details \n3. Listing details \n4. ";
                    std::cout << get_special_action_name() << "\n5. Exit to listings Menu\n";
                    std::cout << "Enter the option number: ";
                    std::cin >> choice2;
                    switch (choice2){
                        case 1:
                            l->display_vehicle_details();
                            break;
                        case 2:{
                            int seller_id = l->display_seller_details();
                            std::cout << "Do you want to contact the seller? (Enter 1 for yes or 0 for no) : ";
                            std::cin >> choice3;
                            if(choice3){
                                send_message(this, user_id, seller_id);
                            }
                            break;
                        }
                        case 3:
                            l->display_listing_details();
                            break;
                        case 4:
                            perform_special_action(l);
                            break;
                        case 5:
                            break;
                        default:
                            std::cout << "Invalid input\n";
                            break;
                    }
                }while(choice2 != 5);
                break;
                }
            case 3:
                filter_listings();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            case 4:
                std::cout << "Exiting to main Menu...\n";
                return;
            default:
                std::cout << "Invalid input\n";
                break;
        }
    } while (choice != 3);
}

void user::send_message(user* active_user,int sender_id, int reciver_id){
    bool flag = dbManager->create_message(active_user, sender_id, reciver_id);
    if(!flag){
        std::cout << "Failed to send message\n";
    }
    else std::cout << "Message sent successfully\n";
}

void user::view_inbox() {
    if (inbox.empty()) {
        std::cout << "Your inbox is empty.\n";
        return;
    }

    std::cout << "---------------------------- Inbox ----------------------------\n";
    for (size_t i = 0; i < inbox.size(); i++) {
        int other_id = (inbox[i][0]->get_sender_id() == user_id) ? inbox[i][0]->get_reciever_id() : inbox[i][0]->get_sender_id();
        
        user* other_user = dbManager->find_user_by_id(other_id); //
        std::string name = (other_user != nullptr) ? other_user->get_full_name() : "Unknown User";

        std::cout << i + 1 << ". Conversation with " << name << " (ID: " << other_id << ") [" << inbox[i].size() << " messages]\n";
    }

    int chat_choice;
    std::cout << "Enter conversation number to view (or 0 to exit): ";
    std::cin >> chat_choice;

    if (chat_choice > 0 && chat_choice <= (int)inbox.size()) {
        size_t idx = chat_choice - 1;//index
        std::cout << "\n--- Full Conversation ---\n";
        for (message* m : inbox[idx]) {//go through all messages
            m->display_message(); 
            std::cout << "--------------------------\n";
        }
    }
}

void user::add_message_to_inbox(message* m, int user2_id){
    //checking if the conversation exists with the user being the reciever or the sender
    for(size_t i = 0; i < inbox.size(); i++){
        if(inbox[i][0]->get_sender_id() == user2_id || inbox[i][0]->get_reciever_id() == user2_id){//involves the other person or not
            inbox[i].push_back(m);
            return;
        }
    }
    //else create a new column/conversation and add the message there
    inbox.push_back({m});
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

std::string buyer::get_special_action_name() const{
    return "Add to Favourites";
}

void buyer::perform_special_action(listing *l){
    for (size_t i = 0; i < favourites.size(); i++){
        if(favourites[i] == l){
            std::cout << "Listing is already in favourites.\n";
            return;
        }
    }
    //else
    favourites.push_back(l);
    std::cout << "Listing id: " << l->get_listing_id() << " successfully added to favourites\n";
}

void buyer::buyer_special_action(listing *l){
    search_history.push_back(l);
}

void buyer::display_favourites(){
    for (size_t i = 0; i < favourites.size(); i++){
        std::cout << "Listing Number: " << i << "\n";
        favourites[i]->display_summary();
    }
}

void buyer::display_search_history(){
    for (size_t i = 0; i < search_history.size(); i++){
        std::cout << "Listing Number: " << i << "\n";
        search_history[i]->display_summary();
    }
}

void buyer::Menu(){
    int choice;
    do
    {
        std::cout << "---------------------------- Menu ----------------------------\n";
        std::cout << "1. Listings menu\n";
        std::cout << "2. Message a user\n";
        std::cout << "3. Display profile\n";
        std::cout << "4. View favorites list\n";
        std::cout << "5. View search history\n";
        std::cout << "6. View inbox\n";
        std::cout << "7. Sign out\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice){
        case 1:
            user::listing_menu();
            break;
        case 2:{
            int reciever_id;
            std::cout << "Enter reciever id: ";
            std::cin >> reciever_id;
            send_message(this, user_id, reciever_id);
            break;}
        case 3:
            displayProfile();
            break;
        case 4:
            display_favourites();
            break;
        case 5:
            display_search_history();
            break;
        case 6:
            view_inbox();
            break;
        case 7:
            std::cout << "Signing out...\n";
            return;
        default:
            std::cout << "Invalid input\n\n";
            break;
        }
    } while (choice != 7);
}
#pragma endregion


//3. Seller methods:
#pragma region seller
seller::seller() : seller_id(seller_count){
    seller_count++;
    std::cout << "Enter your dealership name (enter 'private seller' if you are not a dealership): ";
    std::getline(std::cin, dealership_name);
}

int seller::get_seller_id(){
    return seller_id;
}

int seller::get_seller_rating(){
    return seller_rating;
}

std::string seller::get_dealership_name(){
    return dealership_name;
}

void seller::displayProfile() const{
    user::displayProfile();
    std::cout << "\nUser type: Seller";
    std::cout << "\nSeller ID: " << seller_id;
    std::cout << "\nSeller rating: " << seller_rating;
    if (dealership_name != "private seller") std::cout << "\nDealership name: " << dealership_name;
    else std::cout << "\nDealership name: ''\n";
    std::cout << "My listings: \n";
    for (int i = 0; i < ad_count; i++){
        ads[i]->display_summary();
    }
}

std::string seller::get_special_action_name() const{
    return "Edit listing";
}

void seller::perform_special_action(listing *l){
    if (l->get_seller_id() == user_id) {
        l->edit_listing(); //
    } else {
        std::cout << "Access Denied: You can only edit your own listings!\n";
    }
}

void seller::buyer_special_action(listing *l){/*do nothing*/}

void seller::view_my_ads(){
    if(ad_count == 0) std::cout << "No ads yet\n";
    for (int i = 0; i < ad_count; i++){
        ads[i]->display_summary();
    }
}

listing* seller::find_listing_by_id(const int id){
    for (int i = 0; i < ad_count; i++){
        if(ads[i]->get_listing_id() == id){
            return ads[i];
        }
    }
    return nullptr;
}

void seller::Menu(){
    int choice;
    do
    {
        std::cout << "---------------------------- Menu ----------------------------\n";
        std::cout << "1. Listings menu\n";
        std::cout << "2. Message a user\n";
        std::cout << "3. Display profile\n";
        std::cout << "4. Create listing\n";
        std::cout << "5. View my listings\n";
        std::cout << "6. Delete a listing\n";
        std::cout << "7. Edit a listing\n";
        std::cout << "8. View inbox\n";
        std::cout << "9. Sign out\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice){
        case 1:
            user::listing_menu();
            break;
        case 2:{
            int reciever_id;
            std::cout << "Enter reciever id: ";
            std::cin >> reciever_id;
            send_message(this, user_id, reciever_id);
            break;}
        case 3:
            displayProfile();
            break;
        case 4:
            ads.push_back(dbManager->create_listing(this));
            ad_count++;
            break;
        case 5:
            view_my_ads();
            break;
        case 6:{
            int ls_id;
            view_my_ads();
            std::cout << "Enter listing id to delete: ";
            std::cin >> ls_id;
            listing* l = find_listing_by_id(ls_id);
            if(l == nullptr) {
                    std::cout << "Invalid listing id\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
            }
            dbManager->delete_listing(l);
            std::erase(ads,l);
            ad_count--;
            std::cout << "Listing successfully deleted\n";
            break;}
        case 7:{
            int ls_id;
            view_my_ads();
            std::cout << "Enter listing id to edit: ";
            std::cin >> ls_id;
            listing* l = find_listing_by_id(ls_id);
            if(l == nullptr) {
                    std::cout << "Invalid listing id\n";
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
            }
            l->edit_listing();
            break;}
        case 8:
            view_inbox();
            break;
        case 9:
            std::cout << "Signing out...\n";
            return;
        default:
            std::cout << "Invalid input\n\n";
            break;
        }
    } while (choice != 9);
}

#pragma endregion


//4. admin methods:
#pragma region admin
admin::admin() : admin_id(admin_count){
    admin_count++;
    std::cout << "Enter 1 if you are a level 1 admin and enter 2 if you are a level 2 admin: ";
    
    while (true) {
        if (std::cin >> admin_level) {
            if (admin_level == 1 || admin_level == 2) {
                break; // Valid input, exit the loop
            } 
            else {
                std::cout << "Invalid input. Enter 1 if you are a level 1 admin and enter 2 if you are a level 2 admin: ";
            }
        }
        else {
            std::cout << "Invalid input type. Please enter a number (1 or 2): ";
            
            std::cin.clear(); 
            
            std::cin.ignore(1000, '\n'); 
        }
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

std::string admin::get_special_action_name() const{
    return "Delete listing";
}

void admin::perform_special_action(listing *l){
    if(admin_level == 2){
        dbManager->delete_listing(l);
        std::cout << "Listing deleted successfully" << std::endl;
    }    
    else std::cout << "Not enough admin priviledges. Need to be lvl 2 admin to be able to delete a listing" << std::endl;
}

void admin::buyer_special_action(listing *l){/*do nothing*/}

void admin::manage_pending_listings(){
    std::vector<listing*>& listing_database = dbManager->get_listing_db();
    
    std::cout << "\n------------------ Pending Approvals ------------------\n";
    for (size_t i = 0; i < listing_database.size(); i++) {
        if (!listing_database[i]->get_is_approved()) {
            listing_database[i]->display_summary();
            
            int action;
            std::cout << "1. Approve \n2. Remove\n";
            std::cin >> action;

            if (action == 1) {
                listing_database[i]->set_is_approved(true);
                std::cout << "Listing approved!\n";
            } 
            else if (action == 2) {
                std::cout << "Send a message to the seller telling the reason for denial\n";
                send_message(this, user_id, listing_database[i]->get_seller_id());
                dbManager->delete_listing(listing_database[i]);
                i--; // Adjust index after deletion
                std::cout << "Listing removed.\n";
            }
        }
    }
}

void admin::Menu(){
    int choice;
    do
    {
        std::cout << "---------------------------- Menu ----------------------------\n";
        std::cout << "1. Listings menu\n";
        std::cout << "2. Message a user\n";
        std::cout << "3. Display profile\n";
        std::cout << "4. Ban a user\n";
        std::cout << "5. Un-Ban a user\n";
        std::cout << "6. Manage pending listings\n";
        std::cout << "7. View inbox\n";
        std::cout << "8. Sign out\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice){
        case 1:
            user::listing_menu();
            break;
        case 2:{
            int reciever_id;
            std::cout << "Enter reciever id: ";
            std::cin >> reciever_id;
            send_message(this, user_id, reciever_id);
            break;}
        case 3:
            displayProfile();
            break;
        case 4:{
            int id;
            std::cout << "Enter user's id: ";
            std::cin >> id;
            if(id == user_id){
                std::cout << "YOU CANNOT BAN YOURSELF!!!\n";
                break;
            }
            user* u = dbManager->find_user_by_id(id);
            if(u == nullptr){
                std::cout << "User with id: " << id << " not found\n";
                break;
            }
            u->set_ban(true);
            std::cout << "User with id: " << id << " banned:(\n";
            break;}
        case 5:{
            int id;
            std::cout << "Enter user's id: ";
            std::cin >> id;
            if(id == user_id){
                std::cout << "You are already un-banned:)\n";
                break;
            }
            user* u = dbManager->find_user_by_id(id);
            if(u == nullptr){
                std::cout << "User with id: " << id << " not found\n";
                break;
            }
            u->set_ban(false);
            std::cout << "User with id: " << id << " un-banned:)\n";
            break;}
        case 6:
            if (admin_level == 1) {
                std::cout << "Not enough admin priviledges. Need to be lvl 2 admin to be able to delete a listing\n";
                break;
            }
            else{
                manage_pending_listings();
            }
            break;
        case 7:
            view_inbox();
            break;
        case 8:
            std::cout << "Signing out...\n";
            return;
        default:
            std::cout << "Invalid input\n\n";
            break;
        }
    } while (choice != 8);
}

#pragma endregion
