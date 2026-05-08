#define SCHEDULER_PERIOD_MS 200

#define DHTTYPE DHT11
#define DHTPIN 3
#define LED1 5
#define LED2 6
#define LED3 7
#define BUTTON1 8
#define SONAR_TRIG_PIN 11
#define SONAR_ECHO_PIN 12
// #define NO_OBJECTS -1
#define PIR_PIN 4
#define SERVO_PIN 9
#define CALIBRATION_TIME_SEC 10

// #define SWEEP_TIME 2700

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// [TODO] adjust values
#define D1 5
#define D2 5
#define T1 5
#define T2 5
#define T3 5
#define T4 5
#define Temp1 25
#define Temp2 30

#define TAKEOFF_STATE_MESSAGE F("Take Off")
#define LANDING_STATE_MESSAGE F("Landing")
#define OPERATING_STATE_MESSAGE F("Drone Outside")
#define IDLE_STATE_MESSAGE F("Drone Inside")

#define NORMAL_STATE_MESSAGE F("Normal")
#define ALARM_STATE_MESSAGE F("Alarm")

// #define DEBUG