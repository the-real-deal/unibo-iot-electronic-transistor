#include <WiFi.h>
#include "secrets.h"
#include "devices/Sonar.hpp"
#include "devices/LED.hpp"
#include "WifiConnection.hpp"
#include <PubSubClient.h>
#include "config.h"

#define MSG_BUFFER_SIZE 50

/* wifi network info */

/**
 * !! ATTENTION !!
 * This information is contained in a ignored file, you will need to define it yourself
 */
const char *ssid = SSID;
const char *password = PASSWORD;

/* MQTT server address */
const char *mqtt_server = SERVER;

/* MQTT topic */
const char *topic = TOPIC;

/* MQTT client management */
WiFiClient espClient;
PubSubClient client(espClient);

Led connectingSignal(BUILTIN_LED);
Led connectedLed(GREEN_LED);
Led disconnectedLed(RED_LED);
Sonar sonar(ECHO, TRIGGER, 30000);

/* Wireles connections */
WifiConnection *wifi;

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        // Create a random client ID
        String clientId = String("esiot-2025-client-") + String(random(0xffff), HEX);

        // Attempt to connect
        if (!client.connect(clientId.c_str()))
        {
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(2000);

    /* initialize devices */
    connectingSignal.init();
    connectedLed.init();
    disconnectedLed.init();
    sonar.init();

    wifi = new WifiConnection(ssid, password, &connectingSignal);

    wifi->connect();
    randomSeed(micros());
    client.setServer(mqtt_server, 1883);
}

void loop()
{
    if (!client.connected())
    {
        disconnectedLed.switchOn();
        connectedLed.switchOff();
        reconnect();
        disconnectedLed.switchOff();
        connectedLed.switchOn();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsgTime > 1000)
    {
        lastMsgTime = now;

        float distance = sonar.getDistance();

        /* creating a msg in the buffer */
        snprintf(msg, MSG_BUFFER_SIZE, "%f", distance);

        /* publishing the msg */
        client.publish(topic, msg);
    }
}