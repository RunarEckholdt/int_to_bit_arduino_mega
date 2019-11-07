//Runar Eckholdt





//NB! Remember to turn off linebreak in the serial monitor
//When you start the program choose first how many pins you use and then how many numbers you are going to use (integers)

byte maxBits = 8;
byte numPins;
byte bitPins[] = {13, 12, 11, 10,9,8,7,6}; //define what pins to use, from MSB to LSB. If you add more pins remember to change the maxBits variable
byte sepNums;
const byte buttonPin = 5; //pin for button (optional) there is a while loop at the bottom of the code that must be uncommented for this to be used

void setup() {
  Serial.begin(9600);
  Serial.println();
  
  antNums();
  setBits();
  
  
  
  for (int i = 0; i < numPins; i++) { //sets all pins to output and low
    pinMode(bitPins[i], OUTPUT);
    digitalWrite(bitPins[i],LOW);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  
}

void loop() {
  allValues();
}




void antNums(){
  Serial.print("How many numbers? 1-8: ");
  while(!Serial.available());
  byte input = Serial.parseInt();
  if(input!=0 && input <9){
    Serial.println(input);
    sepNums=input;
    }else{
      Serial.println();
      Serial.println("The amount of numbers cannot be 0 or larger than 8");
      antNums();
      }
  }


void setBits(){
  Serial.print("How many bits per number? Min in is 1, max in this case is ");
  Serial.println(int(maxBits/sepNums));
  while(!Serial.available());
  byte input = Serial.parseInt();
  if(input!=0&&input*sepNums<9){
    Serial.println(input);
    numPins=input*sepNums;
    }else{
      Serial.println();
      Serial.print("0 bits is not allowed and cannot be larger than ");
      Serial.println(int(maxBits/sepNums));
      setBits();
      }
  }



byte getNumber(byte i){
  //getting a number from the Serial
  byte num;
  Serial.print("Insert number ");
  Serial.print(i);
  Serial.print(": ");
  while (!Serial.available());//waiting for user input
  num = Serial.parseInt();
  
  if (num < pow(2,numPins/sepNums)){ //checks if number can fit in the given bitsize
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
  
  byte m = 0; //used to count pins 
    for(byte n = 0;n<sepNums;n++){
      Serial.print(numbers[n]);
      Serial.print(" = ");
      for(int i = numPins/sepNums; i != 0; i--) {
          bool pinState = bitRead(numbers[n], i-1); //read bits from MSB to LSB
            digitalWrite(bitPins[m], pinState); //write high or low to pins in the bitPins array 
        Serial.print(pinState);
        m++;
    }
    Serial.println();
    }
    //uncomment the while loop to use the button for sevral values in the Serial monitor
    //while(digitalRead(buttonPin)==LOW&&Serial.available()); 
    delay(500); 
    

  
  }








  
