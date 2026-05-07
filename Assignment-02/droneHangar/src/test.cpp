// void readTemperature()
// {
//     sensors_event_t event;
//     dht.temperature().getEvent(&event);
//     if (isnan(event.temperature))
//     {
//         Serial.println(F("Error reading temperature!"));
//     }
//     else
//     {
//         Serial.print(F("Temperature: "));
//         Serial.print(event.temperature);
//         Serial.println(F("°C"));
//     }
// }

// float getDistance()
// {
//     /* Triggering stage: sending the impulse */

//     digitalWrite(SONAR_TRIG_PIN, LOW);
//     delayMicroseconds(3);
//     digitalWrite(SONAR_TRIG_PIN, HIGH);
//     delayMicroseconds(5);
//     digitalWrite(SONAR_TRIG_PIN, LOW);

//     /* Receiving the echo */

//     float tUS = pulseIn(SONAR_ECHO_PIN, HIGH);
//     if (tUS > 0)
//     {
//         float t = tUS / 1000.0 / 1000.0 / 2;
//         float d = t * vs;
//         return d;
//     }
//     else
//     {
//         return NO_OBJECTS;
//     }
// }

// void setup()
// {
//     pinMode(PIR_PIN, INPUT);
//     // give the sensor some time to calibrate
//     Serial.print("Calibrating sensor... ");
//     for (int i = 0; i < CALIBRATION_TIME_SEC; i++)
//     {
//         Serial.print(".");
//         delay(1000);
//     }
//     Serial.println(" done");
//     Serial.println("PIR SENSOR READY.");
//     delay(50);

//     dht.begin();
//     Serial.begin(9600);
//     pinMode(LED1, OUTPUT);
//     pinMode(LED2, OUTPUT);
//     pinMode(LED3, OUTPUT);
//     pinMode(BUTTON1, INPUT);
//     pinMode(SONAR_TRIG_PIN, OUTPUT);
//     pinMode(SONAR_ECHO_PIN, INPUT);

//     pMotor = new ServoMotorImpl(9);
//     pos = 0;
//     delta = 20;
// }

// void loop()
// {
//     if (digitalRead(BUTTON1) == HIGH)
//     {
//         digitalWrite(LED1, HIGH);
//         digitalWrite(LED2, HIGH);
//         digitalWrite(LED3, HIGH);
//         readTemperature();
//         float d = getDistance();
//         if (d >= 0)
//         {
//             Serial.println(String(d) + " ");
//         }
//     }
//     else
//     {
//         digitalWrite(LED1, LOW);
//         digitalWrite(LED2, LOW);
//         digitalWrite(LED3, LOW);
//     }
//     int current = digitalRead(PIR_PIN);
//     if (current)
//     {
//         Serial.println("detected!");
//     }
//     else
//     {
//         Serial.println("not detected.");
//     }
//     pMotor->on();
//     pMotor->setPosition(pos);
//     delay(250);
//     for (int i = 0; i < 9; i++)
//     {
//         pos += delta;
//         Serial.println(pos);
//         pMotor->setPosition(pos);
//         delay(90);
//     }
//     pMotor->off();
//     // pos -= delta;
//     delta = -delta;
//     delay(1000);
// }

// DHT_Unified dht(DHTPIN, DHTTYPE);

// uint32_t delayMS;

/* Supposing to run this test
   in an environment with 20 °C
  ì https://en.wikipedia.org/wiki/Speed_of_sound
   */
// const float temperature = 20;
// const float vs = 331.45 + 0.62 * temperature;