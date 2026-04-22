#include "date.h"

date::date(){
    time_t now = time(0); // get current time
    tm* t = localtime(&now); //converts to the correct structure
    
    second = t->tm_sec;
    minute = t->tm_min;
    hour = t->tm_hour;
    day = t->tm_mday;
    month = t->tm_mon + 1;
    year = t->tm_year + 1900;
}
date::date(int s,int m,int h,int d,int mon,int y){
    second = s;
    minute = m;
    hour = h;
    day = d;
    month = mon;
    year = y;
}
void date::display_date() const{
    std::cout << "Date: " << day << "/" << month << "/" << year << std::endl;
    std::cout << "Time: " << hour << ":" << minute << ":" << second << std::endl;
}
void date::update_date(){
    time_t now = time(0); 
    tm* t = localtime(&now);
    
    second = t->tm_sec;
    minute = t->tm_min;
    hour = t->tm_hour;
    day = t->tm_mday;
    month = t->tm_mon + 1;
    year = t->tm_year + 1900;
}
void date::change_date(int s,int m,int h,int d,int mon,int y){
    second = s;
    minute = m;
    hour = h;
    day = d;
    month = mon;
    year = y;
}
time_t date::get_time_t() const {
    tm time_struct = {}; // initialise to 0
    time_struct.tm_sec = second;
    time_struct.tm_min = minute;
    time_struct.tm_hour = hour;
    time_struct.tm_mday = day;
    time_struct.tm_mon = month - 1;    
    time_struct.tm_year = year - 1900; 
    time_struct.tm_isdst = -1;         
    
    return mktime(&time_struct);
}
time_t date::get_time_elapsed(time_t t){
    return time(0) - t;
}


// Reasoning: Allows clean output of dates using cout << date_obj;
std::ostream& operator<<(std::ostream& os, const date& d) {
    os << d.day << "/" << d.month << "/" << d.year << " " << d.hour << ":" << d.minute;
    return os;
}

// Reasoning: Allows direct input of date components via cin >> date_obj;
std::istream& operator>>(std::istream& is, date& d) {
    is >> d.day >> d.month >> d.year;
    return is;
}

// Reasoning: Necessary for sorting algorithms to show the latest listings first.
bool date::operator<(const date& other) const {
    return this->get_time_t() < other.get_time_t();
}

// Reasoning: Used to check if two events occurred on the same day.
bool date::operator==(const date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}