#include <string>
#include "accounts.h"
#include "date.h"

class listing{
    private:
        const int listing_id;
        std::string name;
        seller* Seller;
        void* item;
        date publish_date;
        std::string description;
        static int total_listings;
    public:
        int get_id();
        std::string get_name();
        void display_details();
};