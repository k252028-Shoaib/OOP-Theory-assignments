#pragma once
#include <string>
#include <limits>

class Input_handler {
public:
    virtual int get_int(std::string prompt, int min = std::numeric_limits<int>::lowest(), int max = std::numeric_limits<int>::max()) = 0;
    virtual float get_float(std::string prompt, float min = std::numeric_limits<float>::lowest(), float max = std::numeric_limits<float>::max()) = 0;
    virtual double get_double(std::string prompt, double min = std::numeric_limits<double>::lowest(), double max = std::numeric_limits<double>::max()) = 0;

    virtual std::string get_word(std::string prompt) = 0;
    virtual std::string get_line(std::string prompt) = 0;
    virtual std::string get_paragraphs(std::string prompt) = 0;
    
    virtual std::string get_email(std::string prompt) = 0;
    virtual std::string get_password(std::string prompt, size_t min_length = 8) = 0;

    virtual char get_char(std::string prompt, std::string valid_chars = "") = 0;
    
    virtual ~Input_handler() = default;
};

extern Input_handler* input;