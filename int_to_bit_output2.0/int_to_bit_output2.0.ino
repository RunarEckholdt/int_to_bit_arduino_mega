
//NB! Remember to torn off linebreak in the serial monitor
//When you start the program chose first how many pins you use and then hvor many numbers you are going to use (integers)

byte numPins = 3;
byte bitPins[] = {13, 12, 11, 10,9,8,7,6}; //define what pins to use, from MSD to LSD
byte sepNums;
const byte buttonPin = 5; //pin for button (optional) there is a while loop at the bottom of the code that must be uncommented for this to be used

void setup() {
  Serial.begin(9600);
  Serial.println();
  setBits();
  antNums();
  
  
  for (int i = 0; i < numPins; i++) { //sets all pins to output and low
    pinMode(bitPins[i], OUTPUT);
    digitalWrite(bitPins[i],LOW);
  }
  pinMode(buttonPin, INPUT);
  
}

void loop() {
  allValues();
}


void setBits(){
  Serial.print("How many total bits/pins? Max 8, Min 1: ");
  while(!Serial.available());
  byte input = Serial.parseInt();
  if(input!=0&&input<9){
    Serial.println(input);
    numPins=input;
    }else{
      Serial.println();
      Serial.println("0 bits is not allowed");
      setBits();
      }
  }

void antNums(){
  Serial.print("How many seperate numbers?: ");
  while(!Serial.available());
  byte input = Serial.parseInt();
  if(numPins%input==0){
    Serial.println(input);
    sepNums=input;
    }else{
      Serial.println("Not valid");
      Serial.println("Answer of (number of bits) mod (input) must be 0");
      Serial.print("In this case ");
      Serial.print(numPins);
      Serial.print(" mod ");
      Serial.print(input);
      Serial.print(" = ");
      Serial.println(numPins%input);
      antNums();
      }
  }


byte getNumber(byte i){
  //getting a number from the Serial
  byte num;
  Serial.print("Insert number ");
  Serial.print(i);
  Serial.print(": ");
  while (!Serial.available());
  num = Serial.parseInt();
  
  if (num < pow(2,numPins/sepNums)){
    Serial.println(num);
    return num;
    }else{
      Serial.println("Outside bitrange");
      getNumber(i);
    }
  
}

void allValues(){
  byte numbers[sepNums];
  for (int i =0;i<sepNums;i++){
     //for the amount of chosen separate numbers getting numbers and adds it to the array Numbers
     numbers[i] = getNumber(i+1);
     
    }
  
  byte m = 0; //brukt for å telle pins 
    for(byte n = 0;n<sepNums;n++){
      Serial.print(numbers[n]);
      Serial.print(" = ");
      byte x = numPins/sepNums;
      for(int i = 0; i < numPins/sepNums; i++) {
        x--;
          bool pinState = bitRead(numbers[n], x); //read bits from MSD to LSD
            digitalWrite(bitPins[m], pinState); 
        Serial.print(pinState);
        m++;
    }
    Serial.println();
    }
    //uncomment the while loop to use the button for sevral values in the Serial monitor
    //while(digitalRead(buttonPin)==LOW&&Serial.available()); 
    delay(500);// ved bruk av knapp kommenter ut delay for mer flyt
    

  
  }








  
