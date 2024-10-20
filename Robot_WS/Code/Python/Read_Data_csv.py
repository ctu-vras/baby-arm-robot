import serial
import csv
import time


# Configure the serial port
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)  # POZOR to choose the apropriate port cf.file config_port.py


# Open the CSV file for writing
with open('load_data.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(["Time(ms)", "Servo1 Position", "Servo1 Speed(steps/s)", "Servo1 Load", "Servo3 Position", "Servo3 Speed(steps/s)", "Servo3 Load"]);


    try:
        while True:
            if ser.in_waiting > 0:
                # Read the serial data
                line = ser.readline().decode('utf-8').strip()
                if line:
                    print(line)  # Print the data (optional)
                    # Split the data and write to CSV
                    data = line.split(',')
                    if len(data) == 7:  # POZOR ajust the number of len(data). This condition can be remove, depending on the program you use. 
                        csvwriter.writerow(data)
    except KeyboardInterrupt:
        print("Data logging stopped.")
    finally:
        ser.close()
