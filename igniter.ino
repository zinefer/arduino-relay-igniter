/*

   )                                                       (
  /(       __________                     __________       )\
 {,}______/\         \ Firework Launcher /         /\______{,}
          \/_________/                   \_________\/

  James Kiefer, 2013
*/

// pins
const int CANNONS = 4;
int buttons[] = {2,3,4,5};
int relays[]  = {6,7,8,9};

// settings
const int MODE = 0; //0: instant fire; 1: delayed fire
const int HOT_TIME = 2; //how long the relay will fire
int modes[][CANNONS] = {
   {0,0,0,0},
   {0,15,30,45},
};

//vars
int timeFired[CANNONS];
int i;
int overStimulation = 0;

void setup() {
  //Serial.begin(9600);
  for (i = 0; i < CANNONS; i++) {
    pinMode(relays[i], OUTPUT);
    digitalWrite(buttons[i], HIGH);
    digitalWrite(relays[i], HIGH);
  }
}

void loop() {
  int curTime = millis()/1000;
  for (i = 0; i < CANNONS; i++)
  {
    if ( digitalRead(buttons[i]) == LOW ) {
      if ( timeFired[i] == 0 ) {
        timeFired[i] = curTime;
      } else {
        overStimulation++;
      }
    }

    if (timeFired[i] > 0)
    {
     int fireAt = timeFired[i] + modes[MODE][i];
     if (curTime >= (fireAt+HOT_TIME)) {
        digitalWrite(relays[i], HIGH);
        timeFired[i] = 0;
      } else if ( curTime >= fireAt ) {
        digitalWrite(relays[i], LOW);
      }
    }
  }
}
