#pragma once
#include "date.h"
#include <string>

class Notification {
protected:
    const int notification_id;
    const int receiver_id;
    date timestamp;
    bool is_read;
    static int total_notifications;

public:
    Notification(int receiver_id);

    virtual void display() const = 0;
    virtual std::string get_type() const = 0;

    void mark_as_read();
    bool get_is_read() const;
    int get_receiver_id() const;
    int get_id() const;

    virtual ~Notification() = default;
};

class message; // Forward declaration

class MessageNotification : public Notification {
private:
    message* linked_message;
    std::string sender_name;

public:
    MessageNotification(int receiver_id, message* m, std::string sender);
    
    void display() const override;
    std::string get_type() const override;
    
    message* get_message_ptr() const;
};

class ListingNotification : public Notification {
private:
    std::string listing_name;
    std::string status_update;

public:
    ListingNotification(int receiver_id, std::string name, std::string status);
    void display() const override;
    std::string get_type() const override;
};


class PriceAlert : public Notification {
private:
    std::string vehicle_name;
    float old_price;
    float new_price;

public:
    PriceAlert(int receiver_id, std::string name, float old_p, float new_p);
    void display() const override;
    std::string get_type() const override;
};


class SecurityNotification : public Notification {
private:
    std::string security_msg;

public:
    SecurityNotification(int receiver_id, std::string msg);
    void display() const override;
    std::string get_type() const override;
};