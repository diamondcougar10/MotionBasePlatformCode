#include <ESP32Servo.h>

int DOFs[][6] = 
{
  {90, 90, 90, 90, 90, 90}, // Home
  {138, 42, 140, 42, 140, 42}, // Heave 1
  {90, 90, 90, 90, 90, 90}, // Home
  {42, 138, 42, 138, 42, 138}, // Heave 2
  {90, 90, 90, 90, 90, 90}, // Home
  {141.33, 112.75, 117.4, 117.4, 112.75, 141.33}, // Surge 1
  {90, 90, 90, 90, 90, 90}, // Home
  {112.75, 141.33, 94.74, 94.74, 141.33, 112.75}, // Surge 2
  {90, 90, 90, 90, 90, 90}, // Home
  {94, 117, 85, 78, 56, 107}, // Sway 1
  {90, 90, 90, 90, 90, 90}, // Home
  {93, 58, 102, 122, 128, 66}, // Sway 2
  {90, 90, 90, 90, 90, 90}, // Home
  {50, 72, 50, 72, 50, 72}, // Yaw 1
  {90, 90, 90, 90, 90, 90}, // Home
  {130, 118, 130, 118, 130, 118}, // Yaw 2
  {90, 90, 90, 90, 90, 90}, // Home
  {70, 110, 85, 85, 110, 70}, // Pitch 1
  {90, 90, 90, 90, 90, 90}, // Home
  {130, 51, 91, 91, 51, 130}, // Pitch 2
  {90, 90, 90, 90, 90, 90}, // Home
  {71, 43, 147, 147, 43, 71}, // Roll 1
  {90, 90, 90, 90, 90, 90}, // Home
  {122, 155, 40, 40, 155, 122} // Roll 2

};

int numDofs = 24;

// int servoIndex = 0;
int dofIndex = 0;
int8_t offs[6] = {0, -2, 0, 0, 2, -2};
Servo servos[6];
int servoPins[6] = {14, 32, 15, 33, 27, 12};
unsigned long prevMillis = 0;
unsigned long timer = 0;

int duration = 500;

void setup()
{
    //Serial.begin(115200);
    for (int i = 0; i < 6; i++)
    {
        servos[i].attach(servoPins[i]);
    }
}

void loop()
{
    unsigned long now = millis();
    unsigned long deltaTime = now - prevMillis;
    prevMillis = now;
    timer += deltaTime;
     float ratio = timer / (float)duration;
   
    if(timer >= duration)
    {
        // change angles to next set
        dofIndex = (dofIndex + 1) % numDofs;
        ratio = 0;
        //Serial.println(dofIndex);
        timer = 0;
    }
   
 //Serial.println(ratio);
    for (int i = 0; i < 6; i++)
    {
        int start = DOFs[dofIndex][i];
        int end = DOFs[(dofIndex + 1) % numDofs][i];
        int servoVal = Lerp(start + offs[i], end + offs[i], ratio);
        //Serial.println(servoVal);
        servos[i].write(servoVal);
    }
    
}

int Lerp(int startPos, int endPos, float t)
{
    return startPos + (endPos - startPos) * t;
}