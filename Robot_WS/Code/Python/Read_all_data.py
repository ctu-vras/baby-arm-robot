import serial
import csv
import time


# Configure the serial port
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)  # Replace '/dev/ttyUSB0' with the appropriate port


# Function to send position command to Arduino
def send_position_command(motor_id, position):
    command = f"{motor_id} {position}\n"
    ser.write(command.encode())
    print(f"Sent command: {command.strip()}")


# Open the CSV file for writing
with open('servo_load_data.csv', 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(["Position demandee", "Position mesuree", "Charge", "Vitesse charge", "Tension", "Courant", "Mouvement", "Temperature", "Temps(ms)"])


    try:
        while True:
            # Send a test command (change this to your desired positions)
            send_position_command(3, 1500)  # Example: Move motor ID 3 to position 1500


            if ser.in_waiting > 0:
                # Read the serial data
                line = ser.readline().decode('utf-8').strip()
                if line:
                    print(line)  # Print the data (optional)
                    # Split the data and write to CSV
                    data = line.split(',')
                    if len(data) == 9:
                        csvwriter.writerow(data)
            time.sleep(1)  # Adjust the delay as needed
    except KeyboardInterrupt:
        print("Data logging stopped.")
    finally:
        ser.close()






