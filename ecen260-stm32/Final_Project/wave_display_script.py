import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

# === CONFIGURATION ===
SERIAL_PORT = 'COM7'        # Your actual COM port
BAUD_RATE = 115200          # Must match MCU UART config
BUFFER_SIZE = 100           # Number of points on screen
ADC_MAX_VALUE = 4095
VREF = 3.3                  # ADC reference voltage

# === SETUP ===
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
channel1_data = deque([0]*BUFFER_SIZE, maxlen=BUFFER_SIZE)
channel2_data = deque([0]*BUFFER_SIZE, maxlen=BUFFER_SIZE)

fig, ax = plt.subplots()
line1, = ax.plot(channel1_data, label="Channel 1")
line2, = ax.plot(channel2_data, label="Channel 2")
ax.set_ylim(0, VREF)  # Voltage range
ax.set_title("UART Oscilloscope")
ax.set_xlabel("Sample")
ax.set_ylabel("Voltage (V)")
ax.legend()

# === ANIMATION UPDATE FUNCTION ===
def update(frame):
    try:
        line = ser.readline().decode('utf-8').strip()
        if line:
            values = line.split(',')
            if len(values) == 2:
                ch1_adc = int(values[0])
                ch2_adc = int(values[1])
                ch1_v = (ch1_adc / ADC_MAX_VALUE) * VREF
                ch2_v = (ch2_adc / ADC_MAX_VALUE) * VREF
                channel1_data.append(ch1_v)
                channel2_data.append(ch2_v)
                line1.set_ydata(channel1_data)
                line2.set_ydata(channel2_data)
    except Exception as e:
        print("Error:", e)

    return line1, line2

# === START ANIMATION ===
ani = animation.FuncAnimation(fig, update, interval=20, blit=True)
plt.tight_layout()
plt.show()

