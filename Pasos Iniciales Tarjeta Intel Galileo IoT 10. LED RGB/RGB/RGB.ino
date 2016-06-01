
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int analogOutPin2 = 10; 
const int analogOutPin3 = 11; 
int sensorValue = 0;        // value read from the pot
int sensorValue2 = 0;
int sensorValue3 = 0;
int outputValue = 0;        // value output to the PWM (analog out)


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   for (int i=0; i <=1023; i=i+100){
     for (int i2=0; i2 <=1023; i2=i2+100){
       for (int i3=0; i3 <=1023; i3=i3+100){
        
        // sensorValue = 1000;
        // sensorValue2 = 1023-i;
          
         outputValue = map(i, 0, 1023, 0, 255);
         analogWrite(analogOutPin, outputValue);
         outputValue = map(i2, 0, 1023, 0, 255);
         analogWrite(analogOutPin2, outputValue);
          outputValue = map(i3, 0, 1023, 0, 255);
         analogWrite(analogOutPin3, outputValue);
       //  delay(10);
       }
     }
   }
  
}
