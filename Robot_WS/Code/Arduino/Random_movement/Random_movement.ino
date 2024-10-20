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

    int Pos1;
    int Pos2;
    int Pos3;
    int Load1;
    int Load2;
    int Load3 ;

    Pos1 = sms_sts.ReadPos(1);  // Get the position of the servo with ID 1
    Pos2 = sms_sts.ReadPos(2);  // Get the position of the servo with ID 2
    Pos3 = sms_sts.ReadPos(3);  // Get the position of the servo with ID 3

    Load1 = sms_sts.ReadLoad(1);  // Get the position of the servo with ID 
    Load2 = sms_sts.ReadLoad(2);  // Get the position of the servo with ID 3
    Load3 = sms_sts.ReadLoad(3);  // Get the position of the servo with ID 3

    //Pos1 = sms_sts.ReadMode(2);
    //Pos3 = sms_sts.EnableTorque(2,0);

    // Serial.print("Position  : ");
    // Serial.print(Pos1);
    // Serial.print(", Position 2 : ");
    // Serial.print(Pos2);
    // Serial.print(", Position 3 : ");
    // Serial.println(Pos3);

    // Serial.print("Load 1 : ");
    // Serial.print(Load1);
    // Serial.print(", Load 2 : ");
    // Serial.print(Load2);
    // Serial.print(", Load 3 : ");
    // Serial.println(Load3);



    if (abs(Load1)>24 || abs(Load2)>250 || abs(Load3)>250){
      sms_sts.resetServo(254);

      // Serial.println();
      // Serial.println("Load to high !!");
      char data = Serial.read();

      if (data=='1'){
        Serial.println("La peau a ete touchee");
        Serial.print(Pos1);
        Serial.print(",");
        Serial.print(Pos2);
        Serial.print(",");
        Serial.println(Pos3);

      }
      delay(2000);
      Position_initiale();
      sms_sts.resetServo(254);

      delay(3000);
    }

    // int Skin_touched = random(0,10);

    // if (Skin_touched>8){
    //   sms_sts.resetServo(254);
    //   delay(2000);

    //   Serial.println("La peau a ete touchee");
    //   Serial.print(Pos1);
    //   Serial.print(",");
    //   Serial.print(Pos2);
    //   Serial.print(",");
    //   Serial.println(Pos3);

    //   Position_initiale();
    // }
    if (Serial.available() > 0) {
      char data = Serial.read();
      // Serial.print("Received data: ");
      // Serial.println(data);
      
      if (data == '1') {
        sms_sts.resetServo(254);
        delay(2000);

        Serial.print(Pos1);
        Serial.print(",");
        Serial.print(Pos2);
        Serial.print(",");
        Serial.println(Pos3);

        // Serial.println(sms_sts.ReadPos(2));

        Position_initiale();

        sms_sts.resetServo(254);

        // Serial.println("La peau a ete touchee");

        // Serial.println(sms_sts.ReadPos(2));

        delay(3000);
      }

    }

  }

  //Move servo with ID 3 to two different positions without delay()
  static bool movingToPos1 = true;
  static unsigned long moveStartTime = 0;

  int Position1 = random(650, 1561);
  int Position2 = random(3000, 3776);
  int Position3 = random(1000, 2000);

  if (movingToPos1) {
    // If the servo is not yet moving to position 4095, start moving
    if (millis() - moveStartTime >= 2000) {  // Move after 2 seconds
      sms_sts.WritePosEx(1, 650, 1000, 50);  // Move to position 4095
      sms_sts.WritePosEx(2, 3776, 1000, 50);  // Move to position 4095
      sms_sts.WritePosEx(3, 2000, 1000, 50);  // Move to position 4095

      moveStartTime = millis();
      movingToPos1 = false;
    }
  } else {
    // After the move to position 4095, move back to position 2000
    if (millis() - moveStartTime >= 2000) {  // Move after 2 seconds
      sms_sts.WritePosEx(1, Position1, 1000, 50);  // Move to position 4095
      sms_sts.WritePosEx(2, Position2, 1000, 50);  // Move to position 4095
      sms_sts.WritePosEx(3, Position3, 1000, 50);  // Move to position 2000
      moveStartTime = millis();
      movingToPos1 = true;
    }
  }

  
}


void Position_initiale(){
  sms_sts.WritePosEx(1, 650, 1000, 50);  // Move to position 4095
  sms_sts.WritePosEx(2, 3776, 1000);  // Move to position 4095
  sms_sts.WritePosEx(3, 2000, 1000, 50);  // Move to position 4095

  delay(3000);

}


