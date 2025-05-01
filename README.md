# Mini Sumo Robot – RobotChallenge Vienna 2009

This repository contains a Python simulation of the logic and behavior behind a Mini Sumo Robot I built and competed with at **RobotChallenge Vienna 2009**.

The original robot was built using an **Arduino UNO**, **L298N motor driver**, and a **Sharp GP2D120X infrared sensor** for opponent detection, along with **four downward-facing color sensors** for edge detection.

## Features

- Simulates:
  - Motor control via L298N (forward, backward, spin, stop)
  - Opponent detection using analog distance sensor
  - Edge detection using 4 ground-facing sensors
  - Full match logic: start delay, spin-search-attack loop, edge recovery

- Modular Python design:
  - `MiniSumoRobot` class encapsulates robot logic
  - Unit test classes simulate and validate behavior

## About the Competition

> I participated with this robot at **RobotChallenge Vienna 2009**, one of Europe's major robotics competitions. The robot was fully autonomous, built with low-cost components and optimized for fast edge detection and aggressive attack logic.

## License

MIT
