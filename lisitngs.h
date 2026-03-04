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
        bool is_approved;
        std::string description;
        static int total_listings;
    public:
        listing(seller* s);
        int get_listing_id();
        std::string get_name();
        vehicle* get_vehicle();
        bool get_is_approved();
        int get_seller_id();
        void set_is_approved(bool b);
        void display_summary();
        int display_seller_details();//return seller id
        void display_vehicle_details();
        void display_listing_details();
        void edit_listing();
        ~listing();
};
