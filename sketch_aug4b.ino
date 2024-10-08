// קביעת אורך הפעולה
#define NUMBER_OF_LEDS 4
#define NUMBER_OF_BTN 4
#define NUMBER_OF_SPEKER 4
#define NUMBER_OF_LEDS_RANDOM 3

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

// ספיקר
#define SPEAKER_PIN 8

// קביעת מצבי המשחק סוויץ
#define startGame 14
#define startPlayerClick 15
#define GameWineer 16
#define GameOver 17
#define resetGame 18

// משתנה לספיקר
const int tonesSPEKER[NUMBER_OF_SPEKER] = { 1000, 1500, 2000, 2500 };

// משתנים ללדים וכפתורים
const int leds[NUMBER_OF_LEDS] = { RedLED, BlueLED, YellowLED, GreenLED };
const int buttons[NUMBER_OF_BTN] = { RedBTN, BlueBTN, YellowBTN, GreenBTN };
int numRandomIndexLED[NUMBER_OF_LEDS_RANDOM];

// מצב נתון
int currState;
int CurrBtn[NUMBER_OF_LEDS] ;
int LastBtn[NUMBER_OF_BTN];
bool ledisOn[NUMBER_OF_LEDS];

// משתנים לבדיקת זמן לחיצה
unsigned long lastPressTime;  // זמן לחיצה האחרון

void setup() {
  Serial.begin(9600);  // איתחול ספיקר
  Serial.println("test");
  randomSeed(analogRead(A1));
  
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {  // איתחול לדים
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i],LOW);
  }

  for (int i = 0; i < NUMBER_OF_BTN; i++) {  // איתחול כפתורים
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(SPEAKER_PIN, OUTPUT);  // איתחול ספיקר
  noTone(SPEAKER_PIN);
  lastPressTime = millis();
  currState = startGame;
}

void loop() {
  switch (currState) {  // מכונת מצבים
    case startGame:  // התחלת משחק
      RandomLightsLED();
      currState = startPlayerClick;
      break;

    case startPlayerClick:  // התחלת לחיצה של השחקן
      PreesBtnAndNewTime();
      break;

    case GameWineer:  // משחק ניצחון נורה ירוקה
      break;

    case GameOver:  // משחק כישלון נורה אדומה
      break;

    case resetGame:  // ריסטרט לאחרי המשחק
      break;
  }
}



void RandomLightsLED() {
  for (int i = 0; i < NUMBER_OF_LEDS_RANDOM; i++) {
    Serial.println(i);
    numRandomIndexLED[i] = random(0, NUMBER_OF_LEDS);
    Serial.println(numRandomIndexLED[i]);
    digitalWrite(leds[numRandomIndexLED[i]], HIGH);
    delay(1000);
    digitalWrite(leds[numRandomIndexLED[i]], LOW);
    delay(1000);
  }
  tone(SPEAKER_PIN, tonesSPEKER[0]); 
    delay(200);                         
    noTone(SPEAKER_PIN);            
  
}

void PreesBtnAndNewTime() {
  

  for (int i = 0; i < NUMBER_OF_BTN; i++) {
    CurrBtn[i] = digitalRead(buttons[i]);

    if ((CurrBtn[i] == LOW) && (LastBtn[i] == HIGH) && (millis() - lastPressTime > 50)) {
      lastPressTime = millis();
      trunledON(i);
    }
    else if ((CurrBtn[i] == HIGH) && (LastBtn[i] == LOW)) {
      trunledOFF(i);
      }
    LastBtn[i] = CurrBtn[i];
    
  }
}
// void toggleLed(int chenel) {  // מתג
//   if (ledisOn[chenel]) {
//     trunledOFF(chenel);
//   } else {
//     trunledON(chenel);
//   }
// }

void trunledON(int chenel) {  // הדלקה לד
  ledisOn[chenel] = true;
  digitalWrite(leds[chenel], HIGH);
}

void trunledOFF(int chenel) {  // כיבוי לד
  ledisOn[chenel] = false;
  digitalWrite(leds[chenel], LOW);
}
