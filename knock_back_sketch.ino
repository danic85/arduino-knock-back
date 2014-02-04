/* Echoing Knock Sensor
 
 This sketch reads a piezo element to detect a knocking sound. 
 It reads an analog pin and compares the result to a set threshold. 
 If the result is greater than the threshold, it stores the value of millis() to an array.
 Following a defined period without additional knocks, the knocks are replayed by the device.
 
 Created by Dan Nicholson <http://dannicholson.co.uk>
 Based on "Knock Sensor" created 25 Mar 2007 by David Cuartielles <http://www.0j0.org> modified 30 Aug 2011 by Tom Igoe
 
 This code is in the public domain.
 
 */

// these constants won't change:
const int ledPin = 9;      			// led connected to digital pin
const int buzzer = 8;                           // output buzzer connected to digital pin.
const int knockSensor = A0; 			// the piezo is connected to analog pin 0
const int threshold = 100;  			// threshold value to decide when the detected sound is a knock or not
const int arraySize = 20;			// Size of knock array (you can remove this in the functions and use sizeof() if you prefer)
const int replayWait = 2000; 			// Number of milliseconds to wait before replaying knock pattern

// these variables will change:
int sensorReading = 0;      			// variable to store the value read from the sensor pin
unsigned long knocks[arraySize];	        // Knock 'buffer' - stores timing of each knock ready for replaying.						
int knockPos = 0; 				// Current position within knocks array
unsigned long lastKnock = false;	        // Time of last knock

void setup() {
  pinMode(ledPin, OUTPUT); 			// declare the ledPin as as OUTPUT
  pinMode(buzzer, OUTPUT);                      // declare buzzer pin as OUTPUT
  Serial.begin(9600);       			// use the serial port
}

void loop() {
  sensorReading = analogRead(knockSensor); // read the sensor
  if (lastKnock && (lastKnock + replayWait) < millis()) replayKnocks(); // Replay knocks if last knock was older than the defined wait time
  else if (sensorReading >= threshold) handleKnock(sensorReading); // If knock detected, handle
  delay(30);
}

void handleKnock(int reading)
{
  lastKnock = millis();
  if (knockPos < arraySize)
  {
    knocks[knockPos++] = lastKnock; // Store timing and increment position variable
    flash(false);
    // Debug output
    Serial.print("Knock: "); 
    Serial.println(reading);
  }
  else
  {
    Serial.println("Buffer full");
  }
}
void flash(boolean buzz)
{
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  if (buzz) tone(buzzer, 1000);
  delay(50);
  digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
  if (buzz) noTone(buzzer);
}
void replayKnocks()
{
  int i;
  lastKnock = false;
  Serial.println("Replaying");
  for (i = 0; i < knockPos; i = i + 1) 
  {
    int prev = i-1;
    if(prev < 0) prev = 0;
    unsigned long d = (knocks[i] - knocks[prev]);
    if (d > 50) d = d-50;
    delay(d);
    Serial.println(i);
    flash(true);
  }
  knockPos = 0; // reset pointer;
}
