import time

class MiniSumoRobot:
    def __init__(self):
        # Motor state
        self.motor_in1 = False
        self.motor_in2 = False
        self.motor_speed = 0

        # Sensors
        self.analog_value = 0         # front sensor
        self.downward_sensors = [False, False, False, False]  # [FL, FR, BL, BR] - True = white line

        # Flags
        self.led_on = False
        self.opponent_detected = False
        self.started = False
        self.serial_log = []

    # --- Core actions ---
    def move_forward(self, speed=255):
        self.motor_in1 = True
        self.motor_in2 = False
        self.motor_speed = speed
        self.log("Moving forward")

    def move_backward(self, speed=255):
        self.motor_in1 = False
        self.motor_in2 = True
        self.motor_speed = speed
        self.log("Moving backward")

    def stop(self):
        self.motor_in1 = False
        self.motor_in2 = False
        self.motor_speed = 0
        self.log("Stopped")

    def spin(self, speed=150):
        self.motor_in1 = True
        self.motor_in2 = True
        self.motor_speed = speed
        self.log("Spinning to search")

    # --- Sensor logic ---
    def read_front_sensor(self, analog_value):
        self.analog_value = analog_value
        self.opponent_detected = analog_value > 800  # simulate close opponent
        self.log(f"Front sensor: {analog_value} => Opponent {'DETECTED' if self.opponent_detected else 'not detected'}")

    def read_downward_sensors(self, readings):
        self.downward_sensors = readings  # list of booleans: True if white line
        if any(readings):
            self.log(f"Edge detected! Readings: {readings}")
            return True
        return False

    def recover_from_edge(self):
        self.move_backward(speed=200)
        time.sleep(0.5)
        self.spin(speed=150)
        time.sleep(0.5)
        self.stop()

    # --- Match logic ---
    def wait_for_start_signal(self):
        self.log("Waiting for start button...")
        # simulate button press externally
        self.started = True
        time.sleep(3)
        self.log("Match started!")

    def match_loop(self, front_sensor_values, downward_sensor_sequences):
        self.wait_for_start_signal()
        for i, analog_val in enumerate(front_sensor_values):
            self.read_front_sensor(analog_val)

            # Simulate edge detection
            if self.read_downward_sensors(downward_sensor_sequences[i]):
                self.recover_from_edge()
                continue

            if self.opponent_detected:
                self.move_forward(speed=255)
            else:
                self.spin(speed=180)

            time.sleep(0.2)  # simulate delay between readings

    def log(self, message):
        self.serial_log.append(message)
