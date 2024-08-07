// קביעת אורך הפעולה
#define NUMBER_OF_LEDS 4
#define NUMBER_OF_BTN 4
#define NUMBER_OF_SPEKER 4

// לדים
#define RedLED 12
#define BlueLED 4
#define YellowLED 3
#define GreenLED 2
// כפתורים
#define RedBTN 6
#define BlueBTN 9
#define YellowBTN 10
#define GreenBTN 11
//ספיקר
#define SPEAKER_PIN 8 
// משתנה לספיקר
const int tonesSPEKER[NUMBER_OF_SPEKER] = { 1000, 1500, 2000, 2500 };
//מתשנים ללדים וכפתורים
const int leds[NUMBER_OF_LEDS] = { RedLED, BlueLED, YellowLED, GreenLED };
const int buttons[NUMBER_OF_BTN] = { RedBTN, BlueBTN, YellowBTN, GreenBTN };

void setup() {
  Serial.begin(9600);// איתחול ספיקר
  pinMode(SPEAKER_PIN, OUTPUT);
  for (int i = 0; i < NUMBER_OF_SPEKER; i++) {
  analogWrite(tonesSPEKER[i],LOW);
  }

  for (int i = 0; i < NUMBER_OF_LEDS; i++) { // איתחול לדים
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i],LOW);
  }

  for (int i = 0; i < NUMBER_OF_BTN; i++) {// איתחול כפתורים
    pinMode(buttons[i], INPUT_PULLUP);
  }
}

void loop() {
  
}





