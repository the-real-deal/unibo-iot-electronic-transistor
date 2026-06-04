#include "WifiConnection.hpp"

WifiConnection::WifiConnection(const String &_ssid, const String &_password, Led *signaling) : ssid(_ssid), password(_password), signal(signaling)
{
    // delete old configurations
    WiFi.disconnect(true);
}

void WifiConnection::connect()
{
    delay(10);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (!isConnected())
    {
        delay(500);
        if (signal->isOn())
            signal->switchOff();
        else
            signal->switchOn();
    }
    signal->switchOff();
}

bool WifiConnection::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}