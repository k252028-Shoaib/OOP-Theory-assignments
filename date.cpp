#include "date.h"
#include <iostream>

date::date(){
    time_t now = time(0); // get current time
    tm* time = localtime(&now); //converts to the correct structure
    
    second = time->tm_sec;
    minute = time->tm_min;
    hour = time->tm_hour;
    day = time->tm_mday;
    month = time->tm_mon + 1;
    year = time->tm_year + 1900;
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
    std::cout << "Date: " << day << "/" << month << "/" << year << std::endl;
    std::cout << "Time: " << hour << ":" << minute << ":" << second << std::endl;
}
void date::update_date(){
    time_t now = time(0); 
    tm* time = localtime(&now);
    
    second = time->tm_sec;
    minute = time->tm_min;
    hour = time->tm_hour;
    day = time->tm_mday;
    month = time->tm_mon + 1;
    year = time->tm_year + 1900;
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