// the setup function runs once when you press reset or power the board
int a; //loop counter
int digit1 = 0; //first digit
int digit2 = 0; //second digit
int digit3 = 0; //third digit
int digit4 = 0; // fourth digit
char buf [5]; // array to store the value in text
int guess = 0; // current guess
bool found = false;

int pinSelect = 2;
int pinPower = 3;
int pinUp = 4;
// int pinDown = 5;

const int analogInPin = A0;  // Analog input pin connected to the LDR sensor/resistor voltage divider
int sensorValue;
int lowestSensorValue = 1000;
int lowDigit1 = 0;
int lowDigit2 = 0;
int lowDigit3 = 0;
int lowDigit4 = 0;

void setup() {
//Initialize serial and wait for port to open:
Serial.begin(9600);

// initialize digital pins as output pins
pinMode(pinSelect, OUTPUT); // select: CH1 (HIGH = button pressed)
pinMode(pinPower, OUTPUT); // power: CH2 (HIGH = button pressed)
pinMode(pinUp, OUTPUT); // up: CH3 (HIGH = button pressed)
// pinMode(pinDown, OUTPUT); // down: CH4 (HIGH = button pressed)

Serial.println("Guessing game");
Serial.println("waiting 5 seconds");
delay(5000); //wait 5 seconds before starting 
}


void poweron(){
  digitalWrite(pinPower, HIGH);   // turn power switch on 
  delay(2000);              // wait for a 2 seconds to simulate a long press
  digitalWrite(pinPower, LOW);    // turn power switch off
  delay(200);
}

void up(){
  digitalWrite(pinUp, HIGH);   // turn up switch on 
  delay(150);
  digitalWrite(pinUp, LOW);   // turn up switch on
  delay(150);
}
  
void next(){
  digitalWrite(2, HIGH);   // turn power switch on 
  delay(200);              // wait for a 200 mseconds
  digitalWrite(2, LOW);    // turn power switch off
  delay(200);
}

void makeguess(){ //function to step through each digit by using up and next buttons
  Serial.print(digit1);
  Serial.print(digit2);
  Serial.print(digit3);
  Serial.print(digit4);

  for (a=0;a<digit1;a++){ // for first digit enter guess by pressing correct number of times
    up();
  }

  next();

  for (a=0;a<digit2;a++){ // for second digit enter guess by pressing correct number of times
    up();
  }

  next();

  for (a=0;a<digit3;a++){ // for third digit enter guess by pressing correct number of times
    up();
  }

  next();

  for (a=0;a<digit4;a++){ // for fourth digit enter guess by pressing correct number of times
    up();
  }

  next();				// press next a final time to enter guess

  sensorValue = analogRead(analogInPin); // read current sensor value
  Serial.print(" Sensor = ");
  Serial.print(sensorValue);

  if (sensorValue < lowestSensorValue) {
    lowestSensorValue = sensorValue;
    lowDigit1 = digit1;
    lowDigit2 = digit2;
    lowDigit3 = digit3;
    lowDigit4 = digit4;
  }

  Serial.print(" Lowest value: ");
  Serial.print(lowestSensorValue);
  Serial.print(", Code: ");
  Serial.print(lowDigit1);
  Serial.print(lowDigit2);
  Serial.print(lowDigit3);
  Serial.println(lowDigit4);

  if (sensorValue < 700){ // if sensor value is low enough the screen must be showing white backgroud which signifies its worked!
    Serial.print("Correct answer found! ");
    Serial.println(guess);

    found = true;
  }

  if (digit1 == 9 && digit2 == 9 && digit3 == 9 && digit4 == 8) {
    Serial.println("Iteration complete, correct code not found... ");
    Serial.print("Lowest value: ");
    Serial.print(lowestSensorValue);
    Serial.print(", Code: ");
    Serial.print(lowDigit1);
    Serial.print(lowDigit2);
    Serial.print(lowDigit3);
    Serial.println(lowDigit4);

    found = true;
  }
   
}

void foundLoop() {
  unsigned long elapsedTime = millis();
  int seconds = elapsedTime/(1000);
  int minutes = seconds / 60;
  int hours = minutes / 60;
  minutes = minutes % 60;

  Serial.print("Hours, minutes: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.println(minutes);

  while (found) {
    delay(10000);
  }
}

 // the loop function runs over and over again forever
void loop() {
  

  for (guess=0000;guess<9999;guess++){ // you can run three guesses before the screen powers off.. this was a very quick hack.
    poweron();

    sprintf (buf, "%04i", guess); //takes current guess variable value and creates all digital values
    digit1 = buf [0] - '0';
    digit2 = buf [1] - '0';
    digit3 = buf [2] - '0';
    digit4 = buf [3] - '0';
    makeguess(); // try this guess
    delay(500);

    if (found == true) {
      foundLoop();
    }

    guess++; 
    sprintf (buf, "%04i", guess); //repeat for next guess
    digit1 = buf [0] - '0';
    digit2 = buf [1] - '0';
    digit3 = buf [2] - '0';
    digit4 = buf [3] - '0';
    makeguess();
    delay(500);

    if (found == true) {
      foundLoop();
    }

    guess++;
    sprintf (buf, "%04i", guess); //repeat for next guess
    digit1 = buf [0] - '0';
    digit2 = buf [1] - '0';
    digit3 = buf [2] - '0';
    digit4 = buf [3] - '0';
    makeguess();
    delay(1000);

    if (found == true) {
      foundLoop();
    }
  }
}
