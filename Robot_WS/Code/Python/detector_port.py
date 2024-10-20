import os


DEV_PATH = '/dev'


device_names = os.listdir(DEV_PATH)
##
##print('Connect the robotic arm and press a key')
##input()
##
##device_names_new = os.listdir(DEV_PATH)
##new_devices = sorted(list(set(device_names_new) - set(device_names)))
##
##if new_devices:
##    arm_port = new_devices[-1]
##    with open('arm_port.txt', 'w') as file:
##        file.write(os.path.join(DEV_PATH, arm_port))
##else:
##    print("No new device detected for the robotic arm.")
##    exit(1)
##
##device_names = device_names_new


print('Connect the tactile skin and press a key')
input()


device_names_new = os.listdir(DEV_PATH)
new_devices = sorted(list(set(device_names_new) - set(device_names)))

print(new_devices)

if new_devices:
    skin_port = new_devices[-1]
    with open('skin_port.txt', 'w') as file:
        file.write(os.path.join(DEV_PATH, skin_port))
else:
    print("No new device detected for the tactile skin.")
    exit(1)





