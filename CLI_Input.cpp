#pragma once
#include "CLI_Input.h"
#include <iostream>

void CLI_Input::clear_buffer(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int CLI_Input::get_int(std::string prompt, int min = std::numeric_limits<int>::lowest(), int max = std::numeric_limits<int>::max()){
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clear_buffer(); // Guard against trailing text
            if (value >= min && value <= max) return value;
            std::cout << "Error: Value out of range (" << min << " to " << max << ").\n";
        } 
        else {
            std::cout << "Error: Invalid integer format.\n";
            std::cin.clear(); // Reset fail state
            clear_buffer();   // Clear the "garbage"
        }
    }
}

float CLI_Input::get_float(std::string prompt, float min, float max) {
    float value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clear_buffer();
            if (value >= min && value <= max) return value;
            std::cout << "Error: Value out of range (" << min << " to " << max << ").\n";
        } else {
            std::cout << "Error: Invalid decimal format.\n";
            std::cin.clear();
            clear_buffer();
        }
    }
}

double CLI_Input::get_double(std::string prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clear_buffer();
            if (value >= min && value <= max) return value;
            std::cout << "Error: Value out of range (" << min << " to " << max << ").\n";
        } else {
            std::cout << "Error: Invalid number format.\n";
            std::cin.clear();
            clear_buffer();
        }
    }
}

std::string CLI_Input::get_word(std::string prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clear_buffer(); // Discard any extra words typed on the same line
            return value;
        }
        std::cout << "Error: Invalid input.\n";
        std::cin.clear();
        clear_buffer();
    }
}

std::string CLI_Input::get_line(std::string prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) return value;
        std::cout << "Error: Input cannot be empty.\n";
    }
}


std::string CLI_Input::get_paragraphs(std::string prompt) {
    std::string total_text, line;
    std::cout << prompt << " (Press Enter twice to finish):\n";
    while (std::getline(std::cin, line) && !line.empty()) {
        total_text += line + "\n";
    }
    return total_text;
}

std::string CLI_Input::get_email(std::string prompt) {
    // Standard email regex pattern
    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    std::string email;
    while (true) {
        email = get_word(prompt);
        if (std::regex_match(email, pattern)) return email;
        std::cout << "Error: Invalid email format (e.g., name@domain.com).\n";
    }
}

std::string CLI_Input::get_password(std::string prompt, size_t min_length) {
    std::string pass;
    while (true) {
        pass = get_word(prompt);
        if (pass.length() >= min_length) return pass;
        std::cout << "Error: Password must be at least " << min_length << " characters.\n";
    }
}

char CLI_Input::get_char(std::string prompt, std::string valid_chars) {
    char c;
    while (true) {
        std::cout << prompt;
        std::cin >> c;
        clear_buffer();
        
        // If valid_chars is empty, accept any char. Otherwise, check if it exists in the set.
        if (valid_chars.empty() || valid_chars.find(c) != std::string::npos) return c;
        std::cout << "Error: Invalid character. Choice must be one of: " << valid_chars << "\n";
    }
}
