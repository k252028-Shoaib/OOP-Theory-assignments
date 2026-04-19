#pragma once
#include <ctime>
class date{ 
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
        void display_date() const;
        void update_date();//updates the date to today
        void change_date(int s,int m,int h,int d,int mon,int y);
        static time_t get_time_elapsed(time_t t);
        time_t get_time_t() const;

        friend std::ostream& operator<<(std::ostream& os, const date& d);
        friend std::istream& operator>>(std::istream& is, date& d);

        // Member Operators
        bool operator<(const date& other) const; 
        bool operator==(const date& other) const;
};