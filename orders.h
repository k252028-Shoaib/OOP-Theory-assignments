#pragma once
#include <vector>
#include "date.h"

class accesory;

class order{
    private:
        const int order_id;
        std::vector<accesory> cart;//each index corresponds to the index in the quantity array.
        std::vector<int> quantity;//e.g index 1 in quantity array tells the quantity of the item in index 1 of cart array 
        float total;
        date order_date;
        date delivery_date;
        int order_status;//1 is order placed, 2 is order on the way, 3 is order delivered
};