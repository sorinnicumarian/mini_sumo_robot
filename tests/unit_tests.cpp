import unittest

class TestMiniSumoMotorControl(unittest.TestCase):
    def setUp(self):
        # Simulated motor control states
        self.in1 = False
        self.in2 = False
        self.ena = 0  # PWM speed: 0–255
        self.motor_log = []

    def digital_write(self, pin, state):
        if pin == "in1":
            self.in1 = state
        elif pin == "in2":
            self.in2 = state

    def analog_write(self, pin, value):
        if pin == "ena":
            self.ena = value

    def log_state(self, action):
        self.motor_log.append({
            "action": action,
            "in1": self.in1,
            "in2": self.in2,
            "ena": self.ena
        })

    def test_motor_forward_stop_reverse(self):
        # Move forward
        self.digital_write("in1", True)
        self.digital_write("in2", False)
        self.analog_write("ena", 150)
        self.log_state("forward")
        self.assertTrue(self.in1)
        self.assertFalse(self.in2)
        self.assertEqual(self.ena, 150)

        # Stop
        self.digital_write("in1", False)
        self.digital_write("in2", False)
        self.log_state("stop_1")
        self.assertFalse(self.in1)
        self.assertFalse(self.in2)

        # Reverse
        self.digital_write("in1", False)
        self.digital_write("in2", True)
        self.analog_write("ena", 200)
        self.log_state("reverse")
        self.assertFalse(self.in1)
        self.assertTrue(self.in2)
        self.assertEqual(self.ena, 200)

        # Final stop
        self.digital_write("in1", False)
        self.digital_write("in2", False)
        self.log_state("stop_2")
        self.assertFalse(self.in1)
        self.assertFalse(self.in2)
