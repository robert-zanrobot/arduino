const int ledPin = 0;  
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
void setup(){
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(ledPin, ledChannel);
}
void loop(){
  for(int dutyCycle = 0; dutyCycle <= 50; dutyCycle++){   
    ledcWrite(ledChannel, dutyCycle);
    delay(500       );
  }
  for(int dutyCycle = 50; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle); 
    delay(500);
  }}
