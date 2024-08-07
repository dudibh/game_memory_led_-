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
  //ספיקר
  #define SPEAKER_PIN 8
  //קביעת מצבי המשחק סוויץ
  #define startGame 1
  #define startPlayerClick 2
  #define GameWineer 3
  #define GameOver 4
  #define resetGame 5
  // משתנה לספיקר
  const int tonesSPEKER[NUMBER_OF_SPEKER] = { 1000, 1500, 2000, 2500 };
  //מתשנים ללדים וכפתורים
  const int leds[NUMBER_OF_LEDS] = { RedLED, BlueLED, YellowLED, GreenLED };
  const int buttons[NUMBER_OF_BTN] = { RedBTN, BlueBTN, YellowBTN, GreenBTN };

  //מצב נתון

  int CurrBtn;
  int LastBtn= HIGH;


  bool ledisOn[NUMBER_OF_LEDS];
  //משתנים לבדיקת זמן לחיצה
 
  unsigned long lastPressTime;  //זמן לחיצה האחרון

  void setup() {

    Serial.begin(9600);  // איתחול ספיקר
    Serial.println("test");
    randomSeed(analogRead(A1));
    for (int i = 0; i < NUMBER_OF_LEDS; i++) {  // איתחול לדים
      pinMode(leds[i], OUTPUT);
      trunledOFF(i);
    }

    for (int i = 0; i < NUMBER_OF_BTN; i++) {  // איתחול כפתורים
      pinMode(buttons[i], INPUT_PULLUP);
    }
    pinMode(SPEAKER_PIN, OUTPUT);  // איתחול ספיקר
    noTone(SPEAKER_PIN);



    lastPressTime = millis();
   
  }

  void loop() {
    for (int i = 0; i < NUMBER_OF_BTN; i++) {
      CurrBtn = digitalRead(buttons[i]);
     
      if ((CurrBtn == LOW) && (LastBtn == HIGH) && (millis() - lastPressTime > 50)) {
        lastPressTime = millis();

        toggleLed(i);
      }
      LastBtn = CurrBtn;
    }
  }

  void toggleLed(int chenel) {  //מתג

    if (ledisOn[chenel]) {
      trunledOFF(chenel);
    } else {
      trunledON(chenel);
    }
  }

  void trunledON(int chenel) {  // הדלקה לד

    ledisOn[chenel] = true;
    digitalWrite(leds[chenel], HIGH);
  }

  void trunledOFF(int chenel) {  // כיבוי לד

    ledisOn[chenel] = false;
    digitalWrite(leds[chenel], LOW);
  }
