#include <SCServo.h>


SMS_STS sms_sts;


// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 18
#define S_TXD 19


unsigned long previousMillis = 0;  // Variable to store last time position was read
const long interval = 1000;         // Interval at which to read position (in ms)


void setup() {
  Serial.begin(115200);
  Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  sms_sts.pSerial = &Serial1;
  delay(1000);
}


void loop() {
  unsigned long currentMillis = millis();


  // Read the servo position every 'interval' milliseconds
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Request feedback from servo with ID 3
    int Pos1;
    int Pos;
    int Load;

    if (sms_sts.FeedBack(2) != -1) {
      Pos = sms_sts.ReadPos(2);  // Get the position of the servo with ID 1
      // Pos3 = sms_sts.ReadPos(2);  // Get the position of the servo with ID 3

      Load = sms_sts.ReadLoad(2);
      if (Pos != -1) {
        Serial.print("Position : ");
        Serial.print(Pos);
      } else {
        Serial.println("Error reading servo position.");
      }

    Load = sms_sts.ReadLoad(2);   // Get load feedback
    if(Load!=-1){
      Serial.print(", Load:");
      Serial.println(Load);
      delay(10);
    }else{
      Serial.println("read Load err");
      delay(500);    
    }

    } else {
      Serial.println("Feedback error.");
    }

    if (abs(Load)>300){
      sms_sts.resetServo(254);

      Serial.println();
      Serial.println("Load to high !!");
    }


    int Touched_skin = random(0,10);

    if (Touched_skin>8){
      sms_sts.resetServo(254);

      Serial.println(Touched_skin);
      Serial.println("La peau a ete touchee");

      Serial.println(Pos);

      delay(10000);
    }

  }

  // Move servo with ID 3 to two different positions without delay()
  static bool movingToPos1 = true;
  static unsigned long moveStartTime = 0;

  if (movingToPos1) {
    // If the servo is not yet moving to position 4095, start moving
    if (millis() - moveStartTime >= 3000) {  // Move after 2 seconds
      sms_sts.WritePosEx(2, 1000, 1500, 50);  // Move to position 4095
      moveStartTime = millis();
      movingToPos1 = false;
    }
  } else {
    // After the move to position 4095, move back to position 2000
    if (millis() - moveStartTime >= 3000) {  // Move after 2 seconds
      sms_sts.WritePosEx(2, 3120, 1500, 50);  // Move to position 2000
      moveStartTime = millis();
      movingToPos1 = true;
    }
  }

  
}
