#include "date.h"
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
//void date::display_date(){}
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