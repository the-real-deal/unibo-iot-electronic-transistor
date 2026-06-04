#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "devices/LED.hpp"

class WifiConnection
{
private:
    String ssid;
    String password;
    Led *signal;

public:
    WifiConnection(const String &_ssid, const String &_password, Led *signaling);
    ~WifiConnection() = default;

    /**
     * Used to connect to the wifi with ssid and pwd given in the constructor
     */
    void connect();

    /**
     * Checks if the board is currently connected to the internet
     */
    bool isConnected();
};