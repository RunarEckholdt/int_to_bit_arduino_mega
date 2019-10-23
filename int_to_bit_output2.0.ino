
//NB! Husk å skru av linjeskift i den serielle overvåkeren
//Når du starter programmet velg først hvor mange totale pins du bruker og velg derretter hvor mange tall du skal bruke

byte numPins = 3; //endre mengden output som brukes
byte bitPins[] = {13, 12, 11, 10,9,8,7,6}; //angi hvilke pinns som brukes, går fra MSD til LSD
byte sepNums;
const byte buttonPin = 5; //pin for knapp (valgfritt) Dersom du velger å bruke den uncomment while loopen lenger nede i koden

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  setBits();
  antNums();
  
  
  for (int i = 0; i < numPins; i++) { //setter alle pinnsa til OUTPUT
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
          bool pinState = bitRead(numbers[n], x); //leser av bit fra MSD til LSD
            digitalWrite(bitPins[m], pinState); 
        Serial.print(pinState);
        m++;
    }
    Serial.println();
    }
    //uncomment while løkka for å bruke knapp ved flere verdier i Serial
    //while(digitalRead(buttonPin)==LOW&&Serial.available()); 
    delay(500);// ved bruk av knapp kommenter ut delay for mer flyt
    

  
  }








  
