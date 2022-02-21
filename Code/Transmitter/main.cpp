#include <Arduino.h>
#include <Wire.h>
#include <RF24.h>
#include <SPI.h>


//Defining pin names
#define encA 3
#define encB 4
#define encButton 2


//Setting up radio pins and adress
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";


//Creating data package for radio to send
struct Data_Package {
  bool ledState = false;
  byte dupa;
};
Data_Package data; //naming it "data"


//Variables:
int counter = 1;
int aState;
int aLastState;
int menuCounter;
int menuPositions = 10;



//SETUP
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW); //  Set the module as receiver

  pinMode(encA, INPUT_PULLUP);
  pinMode(encB, INPUT_PULLUP);
  pinMode(encButton, INPUT_PULLUP);

}


//FUNCTIONS
void encoder1(){
  aState = digitalRead(encA);
  if(aState != aLastState){
    if(digitalRead(encB) != aState && counter < menuPositions * 2){
      counter++;
    }
    else if(counter > 0){
      counter --;
    }
  }
  aLastState = aState;
  menuCounter = counter / 2;

}

void RFupdate(){
  radio.write(&data, sizeof(Data_Package));
}




//LOOP
void loop() {



  encoder1();
  Serial.println(counter);
}


