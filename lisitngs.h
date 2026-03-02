#include <string>
#include "accounts.h"
#include "date.h"

class vehicle;
class listing{
    private:
        const int listing_id;
        std::string name;
        seller* Seller;
        vehicle* Veehicle;
        date publish_date;
        date edit_date;
        bool edited;
        std::string description;
        static int total_listings;
    public:
        listing(seller* s);
        int get_id();
        std::string get_name();
        void display_summary();
        int display_seller_details();//return seller id
        void display_vehicle_details();
        void display_listing_details();
        void edit_listing();
};
int listing::total_listings = 0;