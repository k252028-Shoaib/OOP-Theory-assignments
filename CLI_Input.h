#pragma once
#include "Input_handler.h"
#include <iostream>
#include <regex>

class CLI_Input : public Input_handler{
    private:
        void clear_buffer();//Helper to clean the buffer after numeric input. 
    public: 
        int get_int(std::string prompt, int min = std::numeric_limits<int>::lowest(), int max = std::numeric_limits<int>::max()) override;
        float get_float(std::string prompt, float min = std::numeric_limits<float>::lowest(), float max = std::numeric_limits<float>::max()) override;
        double get_double(std::string prompt, double min = std::numeric_limits<double>::lowest(), double max = std::numeric_limits<double>::max()) override;

        std::string get_word(std::string prompt) override;
        std::string get_line(std::string prompt) override;
        std::string get_paragraphs(std::string prompt) override;

        std::string get_email(std::string prompt) override;
        std::string get_password(std::string prompt, size_t min_length = 8) override;

        char get_char(std::string prompt, std::string valid_chars = "") override;
    
};

Input_handler* input = new CLI_Input();