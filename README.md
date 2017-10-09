arduino-knock-back
==================

For a device that listens to a knocking pattern then repeats the pattern back


This is a simple Arduino sketch that was originally designed to experiment with arrays and the built-in timing functionality. I based it on the tutorial sample code http://www.arduino.cc/en/Tutorial/Knock
The system consists of a piezo sensor connected to an analog pin that listens for a knock from the user. The Arduino then stores the time the knock occurred in an array.
After a predefined time without further knocks occurring, the Arduino will ‘play back’ the knocks on a buzzer and LED in time to the original knocking pattern.
The device could be expanded to include a stepper motor or similar suitable output that would recreate the knocks exactly, just replace the output buzzer.
You could also use the piezo input sensor as the output buzzer by altering the code.

For information on building the device see http://www.dannicholson.co.uk/2013/07/25/knock-back-a-knock-echoing-arduino/ or http://www.instructables.com/id/Knock-Back-A-Knock-Echoing-Arduino/
