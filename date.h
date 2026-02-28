#pragma once
#include <ctime>
class date{ //date class test
    private:
        int second;
        int minute;
        int hour;
        int day;
        int month;
        int year;
    public:
        date();
        date(int s,int m,int h,int d,int mon,int y);
        void display_date();
        void update_date();//updates the date to today
        void change_date(int s,int m,int h,int d,int mon,int y);
        time_t get_time_elapsed(time_t t);
};