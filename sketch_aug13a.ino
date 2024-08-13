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
#define SPEAKER_PIN 5

// קביעת מצבי המשחק סוויץ
#define START_GAME 14
#define START_PLAYER_CLICK 15
#define CHECK_ANSWER 16
#define GOOD_GAME 17
#define OVER_GAME 18
#define RESET_GAME 19

// משתנה לספיקר
const int tonesSPEKER[NUMBER_OF_SPEKER] = { 300, 1000, 2000, 3000 };

// משתנים ללדים וכפתורים
const int leds[NUMBER_OF_LEDS] = { RedLED, BlueLED, YellowLED, GreenLED };
const int buttons[NUMBER_OF_BTN] = { RedBTN, BlueBTN, YellowBTN, GreenBTN };
int numRandomIndexLED[NUMBER_OF_LEDS_RANDOM];  //הכנסת לדים אחרי העירבוב
int indexInLED[NUMBER_OF_LEDS];
unsigned long lastPressTime;  // זמן סוף לחיצה שלא יהיה לחיצות כפולות
//מצב נתון של הכפתור
int CurrBtn[NUMBER_OF_LEDS];  // בדיקת כפתור
int LastBtn[NUMBER_OF_BTN];
bool ledisOn[NUMBER_OF_LEDS];
int currState;  // מכונת מצבים מצב נתון
//הכנסת כפתורים שנלחצו לתוך מערך
int PreesBtn[NUMBER_OF_BTN];

int cunterprees = 0;// משתנה שסופר אם הגעת ל 3 הוף את הנעילה לטרו
// מניעת לחיצה על כפתורים אחרי 3 פעמים
bool buttonsLocked = false;
//משתנים לבדיקת הזמן
unsigned long firstclick;//לקיחת זמן לחיצה ראשונה
unsigned long Lastthreeclick;//לקיחת זמן עזיבת כפתור שלישי
unsigned long chektimepassed;

void setup() {
  Serial.begin(9600);  // איתחול ספיקר

  Serial.println("test setup");
  randomSeed(analogRead(A1));
  lastPressTime = millis();  // קביעת זמן התחלה
  Serial.print("lastPressTime : ");
  Serial.println(lastPressTime);

  for (int i = 0; i < NUMBER_OF_LEDS; i++) {  // איתחול לדים
    pinMode(leds[i], OUTPUT);
    trunledOFF(i);
    // Serial.print("leds : ");
    // Serial.println(leds[i]);
  }
  for (int i = 0; i < NUMBER_OF_BTN; i++) {  // איתחול כפתורים
    pinMode(buttons[i], INPUT_PULLUP);
    // Serial.print("buttons : ");
    // Serial.println(buttons[i]);
  }
  pinMode(SPEAKER_PIN, OUTPUT);  // איתחול ספיקר
  noTone(SPEAKER_PIN);
  currState = START_GAME;  // שליחת למכונת מצבים התחלת משחק
}

void loop() {
  switch (currState) {  // מכונת מצבים
    case START_GAME:    // התחלת משחק
      Serial.println("START_GAME----");
      RandomLightsLED();  // שליחה לפונקצייה ערבוב הלדים + הכנסה למערך  והדלקה של 3 לדים מתוך 4
      delay(1000);
      currState = START_PLAYER_CLICK;

      break;
    case START_PLAYER_CLICK:  // התחלת לחיצה של השחקן

      PreesBtnAndNewTime();

      break;
    case CHECK_ANSWER:  // בדיקת הלחיצות

      break;
    case GOOD_GAME:  // תצוגת הלדים אדום או ירוק
      goodgmae();
      break;
    case OVER_GAME:  // תצוגת הלדים אדום או ירוק
      lossgmae();
      break;
    case RESET_GAME:  // ריסטרט לאחרי המשחק
      break;
  }
  
}
void RandomLightsLED() {                             // הדלקת הלדים
  selectRandomLEDs();                                //פנייה פונקצייה שמערבבת את האינדקס
  for (int i = 0; i < NUMBER_OF_LEDS_RANDOM; i++) {  // הדלקה של כל הלדים
    digitalWrite(numRandomIndexLED[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < NUMBER_OF_LEDS_RANDOM; i++) {  // כיבוי כל הלדים
    digitalWrite(numRandomIndexLED[i], LOW);
  }
  delay(500);
  tone(SPEAKER_PIN, tonesSPEKER[2]);
  // Serial.println("test speker");
  delay(500);
  noTone(SPEAKER_PIN);
}
void selectRandomLEDs() {  //ערבוב הלדים

  for (int i = 0; i < NUMBER_OF_LEDS; i++) {  // שומר 4 מתוך 4  לע"מ לערבב את הלדים כי המשתנה הראשון הוא קונסט ולא ניתן לשנות
    indexInLED[i] = leds[i];
    // Serial.print("indexInLED : ");
    // Serial.println(indexInLED[i]);
  }


  for (int i = NUMBER_OF_LEDS - 1; i > 0; i--) {  //מערבב את המערך
    int j = random(0, i + 1);
    int change = indexInLED[i];
    indexInLED[i] = indexInLED[j];
    indexInLED[j] = change;
  }
  for (int i = 0; i < NUMBER_OF_LEDS_RANDOM; i++) {  // שומר 3 מתוך 4 אחרי שעורבב
    numRandomIndexLED[i] = indexInLED[i];
    // Serial.print("numRandomIndexLED: ");
    // Serial.println(numRandomIndexLED[i]);
  }
}
void PreesBtnAndNewTime() {  // פונקצייה להתחלת משחק

  if (buttonsLocked) {  // בדיקה לפני הלחיצה אם הכפתורים נעולים
    return;
  }

  for (int i = 0; i < NUMBER_OF_BTN; i++) {  // תנאי לחיצה על הכתפור
    CurrBtn[i] = digitalRead(buttons[i]);    // בודק את מצב הלחיצה במקום ה i

    if ((CurrBtn[i] == LOW) && (LastBtn[i] == HIGH) && (millis() - lastPressTime > 150)) {
      lastPressTime = millis();  // אם כל התנאים מתקיימים אז קביעת זמן לתחילת הלחיצה זה בשביל למנוע לחיצה כפולה בטעות
           Serial.print("lastPressTime: ");
      Serial.println(lastPressTime);

      firstclick = millis();
      Serial.print("firstclick: ");
      Serial.println(firstclick);
      trunledON(i);              // שליחה לפונקציית הדלקת הלד
      // Serial.print("leds: ");
      // Serial.println(leds[i]);
      PreesBtn[i] = leds[i];  //מכניס את הכפתורים לתוך מערך במיקום של הלדים ואז אני יכול להשוות אותם בהמשך
      // Serial.print("PreesBtn: ");
      // Serial.println(PreesBtn[i]);
      cunterprees++;  // קאונטר שסופר את הלחיצות מוגדר כ 0 בהתחלה מתי שהוא מגיע ל 3 זה עוצר את הלחיצות ויוצא לבדיקה
      // Serial.print("cunterprees: ");
      // Serial.println(cunterprees);
    } else if ((CurrBtn[i] == HIGH) && (LastBtn[i] == LOW)) {  // המצב שלוקח את העזיבה של הכפתור
      trunledOFF(i);
      if (cunterprees == 3) {
             Lastthreeclick = millis();
      Serial.print("Lastthreeclick: ");
      Serial.println(Lastthreeclick);

        buttonsLocked = true;  // מנע לחיצות נוספות
        
        checkAnswer();         // יוצא לפונקציית בדיקה אחרי שהגיע ל 3 לחיצות
      
      }
    }
    LastBtn[i] = CurrBtn[i];  
  }
}

void trunledON(int chenel) {  // הדלקה לד
  ledisOn[chenel] = true;     //
  digitalWrite(leds[chenel], HIGH);
}

void trunledOFF(int chenel) {  // כיבוי לד
  ledisOn[chenel] = false;
  digitalWrite(leds[chenel], LOW);
}
void checkAnswer() {  // פונקצייה שבודקת את הלחיצות

  int counterledandbtgood = 0;// קאונטר אם ההתאמה נכונה זה עולה ב1
  for (int i = 0; i < NUMBER_OF_LEDS_RANDOM; i++) { 
    for (int j = 0; j < NUMBER_OF_BTN; j++) {
      if (PreesBtn[j] == numRandomIndexLED[i]) {// אם הכפתור נכון תעצור
        counterledandbtgood++;// תוסיף 1 לקאונטר 
        
      }
      
    }
  }
     

    if (counterledandbtgood == NUMBER_OF_LEDS_RANDOM) { // אם הקאונטר שווה ל 3 לתעבור למשחק נצחון
       
    currState = GOOD_GAME;
  } else {
    currState = OVER_GAME;// אם לא תעבור למשחק שגוי 
  }
  
   
  
  
}
void goodgmae() { // משחק טוב
     
    

  
  // הדלקת לד ורמקול
  digitalWrite(leds[3], HIGH); 
  tone(SPEAKER_PIN, tonesSPEKER[3]);
  delay(3000);
  digitalWrite(leds[3], LOW);
  noTone(SPEAKER_PIN);
  delay(1000);

  currState = RESET_GAME;
}

void lossgmae() {// משחק שגוי   
  // הדלקת לד ורמקול שגוי
  digitalWrite(leds[0], HIGH);
  tone(SPEAKER_PIN, tonesSPEKER[0]);
  delay(3000);
  digitalWrite(leds[0], LOW);
  noTone(SPEAKER_PIN);
  delay(1000);


  currState = RESET_GAME;
}
void checkTime(){
  Serial.print("firstclick: ");
  Serial.print(firstclick);
  chektimepassed = millis() - firstclick;
  if(firstclick> 2000){
    Serial.println("OVER_GAME");
    currState = OVER_GAME;
    

  }
  }
