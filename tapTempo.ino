int button1 = 2;
int output1 = 8;
void setup()
{
  pinMode( button1, INPUT );   //tempo button input
  pinMode (4,INPUT);      //hold button input
  pinMode(output1, OUTPUT);    //LED pin out
}


int lastTapState = LOW;  //the last tap button state 
unsigned long currentTimer[2] = { 500, 500 };  // array of most recent tap counts
unsigned long timeoutTime = 0;   //this is when the timer will trigger next 
unsigned long lastTap = 0; //this vairable determines the time of the most recent tap, used when recording data when button is pressed
unsigned long indicatorTimeout; //variable used to determine the duration of the blinks on state

void loop()
{
    //read the button on pin 12, and only pay attention to the
    //HIGH-LOW transition so that it only register when the
    //button is first pressed down 
  int tapState = digitalRead( button1 );
  int holdState = digitalRead(4);
  if( tapState == LOW && tapState != lastTapState )
  {
      //this takes the tap time done before it (measured in millis), sets it one back in the array,
      //and then sets the other slot of the array to the length of the most recent tap time
    currentTimer[1] = currentTimer[0];
    currentTimer[0] = millis() - lastTap;
    lastTap = millis();
    timeoutTime = 0; 
  }
  lastTapState = tapState; //variable used to determine the most recent state of the button

    //checks to see if it is time to turn on the LED
  if( millis() >= timeoutTime )
  {
    indicatorTimeout = millis() + 150;  //determines the length of time that the LED is on
      //this will set the new tempo
    timeoutTime = millis() + ((currentTimer[0] + currentTimer[1])/2);
  }
  
    //turns on led for the length of indicatorTimeout and then turns it off
    if( millis() < indicatorTimeout ) {
      digitalWrite( output1, HIGH );
    } else {
      digitalWrite( output1, LOW );
    }
}
