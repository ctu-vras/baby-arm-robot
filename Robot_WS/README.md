Run the demonstration program

Prerequisites:

\- Arduino IDE

\- Python

\- Nothing should be connected (make sure to disconnect the robot\'s
power)

Step 1:

- In Arduino, install the board manager ["]{dir="rtl"}esp32" by
  Espressif Systems, version 3.0.5.

- To upload the program, select the board ["]{dir="rtl"}ESP32 Wrover Kit
  (all versions)."

Step 2:

- Install the modified ["]{dir="rtl"}SCServo" library on your computer
  (For installation via the Arduino IDE, see
  \[docs.arduino.cc\](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/)).

- Install the programs ["]{dir="rtl"}Random_movement.ino,"
  "Read_Data_Random_Movement.py," and ["]{dir="rtl"}simple_read.py."

- Note: The examples can help you understand how to use the library
  functions.  
  - ID = 254 selects all motors.  
  - The added function is \"servoReset(ID); \".

Step 3:

- On Linux, open the terminal and run the command \"*ls /dev/tty\** \".
  Then connect the robot and run the command \"*ls /dev/tty\** \" again.
  Note the new serial port that appears. This is the serial port
  associated with the robot, which should be used in Arduino. Generally,
  it will be something like \"port_robot = \"/dev/ttyUSB0\".

- Without disconnecting the robot, now connect the false skin, then run
  the command \"*ls /dev/tty\** \" again. Note the new serial port that
  appears. This is the serial port associated with the false skin.
  Generally, it will be something like \"port_skin= \"/dev/ttyUSB1\".

- In the Python program ["]{dir="rtl"}simple_read.py," on line 11,
  set:  
  python arduino = serial.Serial(port=\"port_robot\", baudrate=115200,
  timeout=0.1)

- In ["]{dir="rtl"}simple_read.py," on lines 20/21, set:  
  python port2 = port_skin (or port1 = port_skin)

- In the Python program ["]{dir="rtl"}Read_Data_Random_Movement.py," on
  line 7, set:  
  python ser = serial.Serial(port=\"port_robot\", baudrate=115200,
  timeout=0.1)

Step 4:

- Upload the program to the board and close the Arduino terminal if it
  is open.

- In two separate terminals, run the programs \"simple_read.py \" and
  \"Position_Motor_Forward.py \".

- Connect the robot board to the power generator.

And that\'s it---the robot is working.

Notes:

- Having the serial monitor open in Arduino can cause communication
  issues with the serial ports.

- Motor link (ST3025):
  \[https://www.waveshare.com/wiki/ST3025_Servo\](https://www.waveshare.com/wiki/ST3025_Servo)
