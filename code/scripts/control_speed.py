#!/usr/bin/python3

import serial
import sys

ser = serial.Serial(sys.argv[1])
ser.baudrate = 9600

opt = str(sys.argv[2])

if opt == 'set':
    motor = int(sys.argv[3])
    dir = int(sys.argv[4])

    motor_settings = (dir << 1) | motor
    motor_speed = min(178, int(sys.argv[5]))
    cmd = [0, motor_settings, motor_speed]
    raw_cmd = bytes(cmd)
    ser.write(raw_cmd)
    print('Set motor', motor, 'with direction', dir, 'at speed', motor_speed, sep=' ')
    print('Raw command: ', raw_cmd)
elif opt == 'get':
    motor = int(sys.argv[3])
    cmd = [1, motor, 0]
    ser.write(bytes(cmd))
    speed = int(ser.read()[0])
    print('Motor ', motor, ' speed is ', speed)
elif opt == 'stats':
    cmd = [1, 0, 1]
    ser.write(bytes(cmd))
    data = ser.read(8)

    motor_a = [int(data[0]), int(data[1]), bool(data[2]), int(data[3])]
    motor_b = [int(data[4]), int(data[5]), bool(data[6]), int(data[7])]

    print('Stats:')
    
    print('\tMotor A:')
    print('\t\tDesired speed (RPM): ', motor_a[0])
    print('\t\tActual speed (RPM): ', motor_a[1])
    print('\t\tSpeed diff (RPM): ', motor_a[0] - motor_a[1])
    print('\t\tPWM: ', motor_a[3])
    print('\t\tDirection: ', motor_a[2])

    print('\tMotor B:')
    print('\t\tDesired speed (RPM): ', motor_b[0])
    print('\t\tActual speed (RPM): ', motor_b[1])
    print('\t\tSpeed diff (RPM): ', motor_b[0] - motor_b[1])
    print('\t\tPWM: ', motor_b[3])
    print('\t\tDirection: ', motor_b[2])