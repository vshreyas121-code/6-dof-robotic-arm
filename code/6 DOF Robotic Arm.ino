/*
  6-DOF Arduino Robot Arm with PCA9685 Servo Driver
  - Arduino Mega 2560
  - PCA9685 16-channel servo driver
  - 6 positional servos connected to PCA9685 channels 0..5

  Wiring assumed:
  - Arduino 5V -> PCA9685 VCC
  - Arduino GND -> PCA9685 GND
  - Arduino SDA -> PCA9685 SDA
  - Arduino SCL -> PCA9685 SCL
  - PCA9685 V+ / screw terminal -> 5V servo power rail
  - PCA9685 GND -> common ground with servos

  Angle convention:
  - 90 degrees = middle / neutral position for every joint
  - Angles are accepted from 0 to 180

  Serial Monitor usage:
  - Open Serial Monitor at 115200 baud
  - Type six integers on one line in this order:
    base shoulder elbow wristPitch wristRoll gripper
  - Example:
    90 45 120 90 90 30
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PCA9685 object.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// PCA9685 channel mapping.
const uint8_t CHANNEL_BASE = 0;
const uint8_t CHANNEL_SHOULDER = 1;
const uint8_t CHANNEL_ELBOW = 2;
const uint8_t CHANNEL_WRIST_PITCH = 3;
const uint8_t CHANNEL_WRIST_ROLL = 4;
const uint8_t CHANNEL_GRIPPER = 5;

// Servo pulse width range for 0..180 degrees.
const uint16_t SERVOMIN = 150;
const uint16_t SERVOMAX = 600;

// 50 Hz is the standard update rate for servos.
const uint16_t PWM_FREQUENCY = 50;

const uint8_t POSITION_COUNT = 10;
const uint16_t MOTION_STEP_DELAY_MS = 35;
const uint16_t POSITION_DELAY_MS = 500;

const uint8_t positions[POSITION_COUNT][6] = {
    {90, 90, 90, 100, 0, 130},
    {90, 120, 90, 100, 0, 130},
    {90, 135, 90, 100, 0, 130},
    {90, 135, 90, 100, 0, 90},
    {90, 110, 90, 100, 0, 90},
    {90, 90, 90, 100, 0, 90},
    {130, 90, 90, 100, 0, 90},
    {130, 120, 90, 100, 0, 90},
    {130, 135, 90, 100, 0, 90},
    {130, 135, 90, 100, 0, 130}};

uint8_t currentAngles[6] = {90, 90, 90, 90, 90, 90};
bool sequenceHasRun = false;

// Command one servo to a target angle from 0 to 180 degrees.
void setServoAngle(uint8_t channel, uint8_t angle)
{
  angle = constrain(angle, 0, 180);

  uint16_t pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(channel, 0, pulse);
}

void writeAllAngles(const uint8_t angles[6])
{
  for (uint8_t joint = 0; joint < 6; joint++)
  {
    setServoAngle(joint, angles[joint]);
  }
}

void moveToPosition(const uint8_t targetAngles[6])
{
  uint8_t steps = 0;

  for (uint8_t joint = 0; joint < 6; joint++)
  {
    uint8_t distance = abs((int)targetAngles[joint] - currentAngles[joint]);
    if (distance > steps)
    {
      steps = distance;
    }
  }

  for (uint8_t step = 1; step <= steps; step++)
  {
    uint8_t intermediateAngles[6];

    for (uint8_t joint = 0; joint < 6; joint++)
    {
      int difference = (int)targetAngles[joint] - currentAngles[joint];
      intermediateAngles[joint] = currentAngles[joint] + (difference * step) / steps;
    }

    writeAllAngles(intermediateAngles);
    delay(MOTION_STEP_DELAY_MS);
  }

  for (uint8_t joint = 0; joint < 6; joint++)
  {
    currentAngles[joint] = targetAngles[joint];
  }
}

// Parse a line of six integers from Serial.
bool parseSixAngles(String input, int angles[6])
{
  input.trim();

  if (input.length() == 0)
  {
    return false;
  }

  char buffer[64];
  input.toCharArray(buffer, sizeof(buffer));

  char *token = strtok(buffer, " \t\r\n");
  int count = 0;

  while (token != NULL)
  {
    if (count >= 6)
    {
      return false;
    }

    char *endPtr;
    long value = strtol(token, &endPtr, 10);

    if (endPtr == token || *endPtr != '\0')
    {
      return false;
    }

    angles[count++] = constrain((int)value, 0, 180);
    token = strtok(NULL, " \t\r\n");
  }

  return count == 6;
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(PWM_FREQUENCY);

  // Move all servos to the safe middle position.
  writeAllAngles(currentAngles);

  Serial.println("Robot arm ready.");
  Serial.println("Send 6 angles in this order:");
  Serial.println("base shoulder elbow wristPitch wristRoll gripper");
  Serial.println("Example: 90 45 120 90 90 30");
  Serial.println("Running the 10-position motion sequence.");
}

void loop()
{
  if (!sequenceHasRun)
  {
    for (uint8_t positionIndex = 0; positionIndex < POSITION_COUNT; positionIndex++)
    {
      moveToPosition(positions[positionIndex]);
      delay(POSITION_DELAY_MS);
    }

    sequenceHasRun = true;
  }

  if (Serial.available() > 0)
  {
    String inputLine = Serial.readStringUntil('\n');
    inputLine.trim();

    int angles[6];
    if (parseSixAngles(inputLine, angles))
    {
      uint8_t targetAngles[6];
      for (uint8_t joint = 0; joint < 6; joint++)
      {
        targetAngles[joint] = angles[joint];
      }
      moveToPosition(targetAngles);

      Serial.print("Moved servos to: ");
      Serial.print(angles[0]);
      Serial.print(" ");
      Serial.print(angles[1]);
      Serial.print(" ");
      Serial.print(angles[2]);
      Serial.print(" ");
      Serial.print(angles[3]);
      Serial.print(" ");
      Serial.print(angles[4]);
      Serial.print(" ");
      Serial.println(angles[5]);
    }
    else
    {
      Serial.println("Invalid input. Please send exactly 6 integers.");
      Serial.println("Example: 90 45 120 90 90 30");
    }
  }
}
