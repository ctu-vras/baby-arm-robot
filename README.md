# Baby Arm Robot

[![IMAGE ALT TEXT](http://img.youtube.com/vi/AjOH3sJS-HM/0.jpg)](https://www.youtube.com/watch?v=AjOH3sJS-HM "A 3D printed Baby Arm")


## 1. The Essential 
Run the demonstration program   

 Prerequisites:   
- Arduino IDE  
- Python  
- Nothing should be connected (make sure to disconnect the robot's power)  

### Step 1:   
* In Arduino, install the board manager “esp32” by Espressif Systems, version 3.0.5.  
* To upload the program, select the board “ESP32 Wrover Kit (all versions).”  

### Step 2:   
* Install the **modified “SCServo” library** on your computer (For installation via the Arduino IDE, see [docs.arduino.cc](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/)).  
* Install the programs *“Random_movement.ino”*, *“Read_Data_Random_Movement.py”* and *“simple_read.py”*  
**Notes 1 :** The examples can help you understand how to use the library functions.     - ID = 254 selects all motors.     - The added function is  "servoReset(ID); ".  
**Notes 2 :** There is more information about the modified library below.

### Step 3:   
* On Linux, open the terminal and run the command  __ls /dev/tty*__. Then connect the robot and run the command  "ls /dev/tty* " again. Note the new serial port that appears. This is the serial port associated with the robot, which should be used in Arduino. Generally, it will be something like  *"port_robot = "/dev/ttyUSB0"*.  
* Without disconnecting the robot, now connect the false skin, then run the command  __ls /dev/tty*__ again. Note the new serial port that appears. This is the serial port associated with the false skin. Generally, it will be something like  *"port_skin= "/dev/ttyUSB1"*.  
* In the Python program *“simple_read.py”*, on line 11, set:    __python arduino = serial.Serial(port="port_robot", baudrate=115200, timeout=0.1)__  
* In *“simple_read.py”* on lines 20/21, set:  __ python port2=port_skin__  (or port1 = port_skin) 
* In the Python program *“Read_Data_Random_Movement.py”* on line 7, set:   __python ser = serial.Serial(port="port_robot", baudrate=115200, timeout=0.1)__

### Step 4:   
* Upload the program to the board and close the Arduino terminal if it is open.  
* In two separate terminals, run the programs  *"simple_read.py"* and  *"Position_Motor_Forward.py"*.  
Connect the robot board to the power generator.  

**And that's it—the robot is working.**  

**Notes:** 
* Having the serial monitor open in Arduino can cause communication issues with the serial ports.  
* Motor link (ST3025): [https://www.waveshare.com/wiki/ST3025_Servo](https://www.waveshare.com/wiki/ST3025_Servo)







## 2. If you want to know more about how the robot was construct. 

### 2.1. Joints Vocabulary

In this part, we will see which joints and which amplitudes were chosen for the robot arm. To do this, it is important to understand how the human body is described in space. Also, it is necessary to start by describing the anatomical reference position of the human body.

<p align="center">
  <img src=https://github.com/user-attachments/assets/fc41979f-ea09-4b0d-a8c2-e40d41473bcb>
  <br> Figure : Anatomical Position Reference
</p>

 Here, it is the position of the arm that interests us. Also the arm in anatomical reference position, corresponding to 0° amplitude, is considered as the point of origin of shoulder movements. From this neutral position, the range of movement of the shoulder is measured in the different directions, which makes it possible to quantify the angular displacements for each movement (flexion, extension, abduction, etc.).

Now that we have the anatomical reference position, we can define the axes and planes of movement using the document below :

<p align="center">
  <img src=https://github.com/user-attachments/assets/9b0214cf-2ebe-412b-adea-a5325c14014c>
  <br> Figure : Axes and planes of movement
</p>

This allows the movements to be defined as follows :

<p align="center">
  <img src=https://github.com/user-attachments/assets/ec88d043-840d-4b9a-b1a2-6d5dd091e7c4>
  <br> Figure : Definition of differents types of movements
</p>



The arms have many joints, however we will focus only on those that interest us: the elbow and the shoulder. The question of having connections at the wrist was raised but quickly dismissed because the baby often keeps his fists closed and uses his wrists little and only with small ranges of movement. This connection has little impact on the general movement of the infant's arm.

### 2.2. Elbow Joints

The elbow allows two main types of movements, each with specific amplitudes

***1. Flexion and Extension :*** The elbow flexion occurs when the forearm approaches the arm and has a maximum amplitude of 160°. During the extension, on the contrary, the forearm moves away from the arm, extending the arm in a straight line, the amplitude of the extension is approximately 4° in an infant.
**2. Internal rotation and external rotation :** Internal rotation commonly called pronation for the hands allows the palm of the hand to be turned downward by approximately 180°, while external rotation called supination for the hands turns the palm upward by a maximum of 45°.


### 2.3. Shoulder Joints

The shoulder is a complex joint that allows us to perform many movements with a large amplitude. Here is an overview of the main movements of the shoulder and their amplitudes [1] and [2].

***1. Flexion and extension :*** Flexion of the shoulder corresponds to raising the arm forward, while extension brings the arm back. These movements occur in the sagittal plane, with flexion up to 180° and extension up to about -90° for an infant under two years old.

**2. Abduction and adduction :** Abduction corresponds to the movement of the arm away from the body to the side, while adduction brings the arm back towards the trunk. Abduction allows the arm to be raised up to approximately 180° in the frontal plane.

***3. Internal rotation and external rotation :*** Internal (or medial) rotation allows the arm to be turned inward approximately 180° toward the torso, while external (or lateral) rotation allows the arm to be turned outward approximately 45°. This movement occurs at the humerus and allows the hand and forearm to be oriented in different directions.

**4. Circumduction :** This movement is a combination of flexion, extension, abduction, and adduction, allowing the shoulder to trace a complete circle. Circumduction allows the shoulder to be mobilized in almost any direction and provides the freedom of movement necessary for gestures such as throwing or catching.


### 2.4. Choice of joints

According to the specifications, the robot must have 2 to 3 degrees of freedom to reproduce basic shoulder and elbow movements, inspired by the natural movements of infants. Also for the rest of the project, we strategically chose the **elbow flexion**, **shoulder flexion** and **shoulder rotation** movements, in particular because these are the main movements made by babies in self-touching gestures and exploration of their body. In addition, by allowing the robot to bend and extend its arm at the elbow, its ability to reach objects at different distances without moving the entire arm is improved, which is important because the 2D touch surface can be fragile, so controlling the force applied to it is essential. Shoulder flexion allows the entire arm to be raised or lowered. This movement is important for directing the arm up or down, thus increasing the robot's vertical range of action. Finally, flexion uses simple, robust and easy-to-maintain linear or rotary mechanisms, which increases its reliability for repetitive tasks and can reduce maintenance costs if necessary. However, even if flexion is advantageous, it is essential for us to rotate the robot arm, in order to be able to reach lateral positions and adjust the orientation of the hand and forearm. Thanks to rotation, the robot can interact with the skin at different angles, which is essential for the complex movements that we are trying to reproduce and which require three-dimensional adaptation.

Here are the movements that we have chosen to keep for the robot and the angular range that corresponds to them and that was tested on the robot:
- Generation of a random position for **motor 1** in the interval **[650, 1561]** or **80°** of freedom - **Elbow flexion**.
- Generation of a random position for **motor 2** in the interval **[3000, 3776]** or **68.2°** of freedom - **Shoulder rotation**.
- Generation of a random position for **motor 3** in the interval **[1000, 2000]** or **87.9°** of freedom - **Shoulder flexion**.


**Bibliography :** 
- [1]  PHYSICAL MEDICINE & REHABILITATION PEDIATRIC RANGE of MOTION Chapter 16 published on Aug 10, 2016
- [2] Range of motion measurements: reference values and a database for comparison studies J. M. SOUCIE, C. WANG, A. FORSYTH, S. FUNK, M. DENNY, K. E. ROACH, D. BOONE, THE HEMOPHILIA TREATMENT CENTER NETWORK published the 11th November of 2010

## 3. ST3025 - Motors

Library Présentation : SCSServo
SCSServo, available on waveshare wiki, is the library associated with ST3025 motors usable on Arduino. This library uses an asynchronous serial communication protocol. Only the sms_sts mode of the library is used, there is a list of the main functions present :


### 3.1. Functions for basic configuration and control :
- CalibrationOfs(int ID): Calibrates the current motor position as its neutral position (new offset).
- Ping(int ID): Checks the connection with the motor by returning its ID if it is accessible.
- unLockEprom(ID): Unlocks access to the protected parameters (EEPROM) of the motor with the specified ID, allowing their modification.
- LockEprom(ID): Locks the EEPROM again after modifications to protect the parameters from accidental changes.
- writeByte(ID, PARAM, VALUE): Modifies a parameter of the motor. It changes the PARAM parameter of the target motor ID to a new value VALUE.



### 3.2. Commands to write positions:
- WritePosEx(int ​​ID, int Position, int Speed, int ACC): Moves motor ID to a given position with a defined speed and acceleration.
- RegWritePosEx(int ​​ID, int Position, int Speed, int ACC): Prepares a position command for a given motor, but waits for a group instruction (RegWriteAction) to execute. This allows the movements of multiple motors to be synchronized.
- RegWriteAction(): Simultaneously executes all commands prepared by RegWritePosEx.
- SyncWritePosEx(byte ID[], int Num, s16 Position[], u16 Speed[], byte ACC[]): Commands multiple motors to move simultaneously to respective positions with specified speeds and accelerations.


### 3.3. Functions to read motor states
- FeedBack(int ID): Retrieves the current parameters of a given motor (position, speed, load, voltage, temperature, motion status, and current).
- ReadPos(int ID): Reads the current position of the motor.
- ReadVoltage(int ID): Reads the current supply voltage of the motor.
- ReadTemper(int ID): Reads the internal temperature of the motor.
- ReadSpeed(int ID): Reads the current speed of the motor.
- ReadLoad(int ID): Reads the load applied to the motor.
- ReadCurrent(int ID): Reads the current consumed by the motor.
- ReadMove(int ID): Checks if the motor is moving.



Additionally, the recommended communication speed with the servo driver is 115200 bits per second on the serial line. This speed, called baudrate, is configured at the beginning of each arduino code.

### Library Modification 

The functions described in the previous part take over the available instructions of the serial protocol except the RESET instruction. 

<p align="center">
  <img src=https://github.com/user-attachments/assets/3c8c7e38-daf6-4314-b24d-36181afc727b>
  <br>Figure : Description of the instruction RESET in the file Communication Protocol User Manual
</p>




For the use of the robot it is important to add the **RESET** instruction that allows to deactivate the motor torque by removing the power supply to the motor without disconnecting the entire board. Thus, the motor no longer opposes active resistance, leaving only the natural mechanical resistance. The objective is to reduce the risk of damaging the components of the robotic arm and the tactile skin that could be damaged by excessive force from the motors.

Thus, the functions needed to use the **RESET** instruction (0x06) in the standard and serial mode of the servomotors have been added in the corresponding source files :

	INST.h : 	#define INST_RESET 0x06 ;
In this file we define a constant that associates the **INST_RESET** command with the hexadecimal value 0x06. 0x06 being the identifier of the reset instruction in the serial communication protocol, it is this value that will be transmitted to the servo driver to indicate that the operation to be performed is a reset.

	SCS.h :		int resetServo (u8 ID);
The previous line is the prototyping of the **resetServo()** method. The **resetServo()** method is accessible to all other parts of the library source code because they all include the SCS.h header file.

	SCS.cpp :
	int SCS :: resetServo(u8 ID)
	{
		rFlushSCS();
		writeBuf(ID, 0, NULL, 0, INST_RESET);
		wFlushSCS();
		return Ack(ID);
	}


Here, the **resetServo()** function is the actual implementation of the function declared in SCS.h. The **rFlushSCS()** functions are used to read and flush the read buffer. The goal is to prepare the system to receive or write new data without interfering with previous data. The **writeBuf()** function sends the **INST_RESET** constant (defined in the inst.h file) specifying the ID of the servomotor that must be reset. The parameters ‘0’, NULL and ‘0’ indicate that there is no data to memorize. The **wFlushSCS()** function is used to flush and send the write buffer to the servomotor, which ensures that the command is transmitted. Finally, the resetServo() function returns the **Ack()** function which ensures that the servomotor has received the command and responded correctly. The **Ack()** function thus returns a success code ‘0’ if the reset was performed correctly and an error code if something failed.

	SMS_STS.h : 	
	class SMS_STS : public SCSerial {
	public:
	...
	virtual int resetServo(u8 ID);
	private: 
	... };

	
Here, we declare a virtual method in the **SMS_STS class** which is a derived class of SCSerial. The **SMS_STS** class is specialized in controlling and managing servo motors and uses the basic serial communication provided by the SCSerial class. The SCSerial class itself is derived from the SCS class and acts as an interface for managing servo motors. The **resetServo()** method takes as a parameter the identifier of the motor to be reset and returns an integer to indicate an error ‘1’ or the success ‘0’ of the reset. This method is an interface to reset a servo motor with a given ID and is defined in the file “SMS_STS.cpp”.

	SMS_STS.cpp : 	
	int SMS_STS::resetServo(u8 ID)
	{
		return SCSerial::resetServo(ID);	
	}


The **SMS_STS::resetServo(u8 ID)** method calls a similar **resetServo()** method belonging to the SCSerial class, which is the parent class responsible for serial communication with servo motors. However, the SCSerial class is itself derived from the SCS class. It is therefore in the SCS.h and SCS.cpp files that the **resetServo()** function was prototyped and defined.












