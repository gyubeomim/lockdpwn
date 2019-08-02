#ifndef GYRO_MNH_H_
#define GYRO_MNH_H_
/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

//#include <Wire.h>
//#include "Kalman.h" // Source: https://github.com/TKJElectronics/KalmanFilter

#define RESTRICT_PITCH // Comment out to restrict roll to ¡¾90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf
#define GY_SAMPLE_DELAY 16
const uint8_t IMUAddress = 0x68; // AD0 is logic low on the PCB
const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication

class CMpu6050Manager
{
protected:
  Kalman m_kalmanX; // Create the Kalman instances
  Kalman m_kalmanY;
  /* IMU Data */
  double m_accX, m_accY, m_accZ;
  double m_gyroX, m_gyroY, m_gyroZ;
  double m_gyroXangle, m_gyroYangle; // Angle calculate using the gyro only
  double m_compAngleX, m_compAngleY; // Calculated angle using a complementary filter
  double m_kalAngleX, m_kalAngleY; // Calculated angle using a Kalman filter
  uint32_t m_timer;
  long m_lSampleTime;
  
public:
  bool Init()
  {
    uint8_t i2cData[14]; // Buffer for I2C data
    Wire.begin();
    TWBR = ((F_CPU / 400000L) - 16) / 2; // Set I2C frequency to 400kHz

    i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
    i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
    i2cData[2] = 0x00; // Set Gyro Full Scale Range to ¡¾250deg/s
    i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ¡¾2g
    while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
    while (i2cWrite(0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode

    while (i2cRead(0x75, i2cData, 1));
    if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
      return false;
    }

    delay(100); // Wait for sensor to stabilize

    /* Set kalman and gyro starting angle */
    while (i2cRead(0x3B, i2cData, 6));
    m_accX = (i2cData[0] << 8) | i2cData[1];
    m_accY = (i2cData[2] << 8) | i2cData[3];
    m_accZ = (i2cData[4] << 8) | i2cData[5];

    // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
    // atan2 outputs the value of -¥ð to ¥ð (radians) - see http://en.wikipedia.org/wiki/Atan2
    // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
    double roll  = atan2(m_accY, m_accZ) * RAD_TO_DEG;
    double pitch = atan(-m_accX / sqrt(m_accY * m_accY + m_accZ * m_accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
    double roll  = atan(m_accY / sqrt(m_accX * m_accX + m_accZ * m_accZ)) * RAD_TO_DEG;
    double pitch = atan2(-m_accX, m_accZ) * RAD_TO_DEG;
#endif

    m_kalmanX.setAngle(roll); // Set starting angle
    m_kalmanY.setAngle(pitch);
    m_gyroXangle = roll;
    m_gyroYangle = pitch;
    m_compAngleX = roll;
    m_compAngleY = pitch;
    m_timer = micros();
    m_lSampleTime = millis();
    return true;
  }

  void Update() {
    
    long lCurTime = millis();
    if ((lCurTime - m_lSampleTime) < GY_SAMPLE_DELAY)
     return;
    
    m_lSampleTime = lCurTime;
    
    uint8_t i2cData[14]; // Buffer for I2C data
    
    /* Update all the values */
    while (i2cRead(0x3B, i2cData, 14));
    m_accX = ((i2cData[0] << 8) | i2cData[1]);
    m_accY = ((i2cData[2] << 8) | i2cData[3]);
    m_accZ = ((i2cData[4] << 8) | i2cData[5]);
    m_gyroX = (i2cData[8] << 8) | i2cData[9];
    m_gyroY = (i2cData[10] << 8) | i2cData[11];
    m_gyroZ = (i2cData[12] << 8) | i2cData[13];

    double dt = (double)(micros() - m_timer) / 1000000; // Calculate delta time
    m_timer = micros();

    // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
    // atan2 outputs the value of -¥ð to ¥ð (radians) - see http://en.wikipedia.org/wiki/Atan2
    // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
    double roll  = atan2(m_accY, m_accZ) * RAD_TO_DEG;
    double pitch = atan(-m_accX / sqrt(m_accY * m_accY + m_accZ * m_accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
    double roll  = atan(m_accY / sqrt(m_accX * accX + m_accZ * m_accZ)) * RAD_TO_DEG;
    double pitch = atan2(-m_accX, m_accZ) * RAD_TO_DEG;
#endif

    double gyroXrate = m_gyroX / 131.0; // Convert to deg/s
    double gyroYrate = m_gyroY / 131.0; // Convert to deg/s

#ifdef RESTRICT_PITCH
    // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    if ((roll < -90 && m_kalAngleX > 90) || (roll > 90 && m_kalAngleX < -90)) {
      m_kalmanX.setAngle(roll);
      m_compAngleX = roll;
      m_kalAngleX = roll;
      m_gyroXangle = roll;
    } else
      m_kalAngleX = m_kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

    if (abs(m_kalAngleX) > 90)
      gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
    m_kalAngleY = m_kalmanY.getAngle(pitch, gyroYrate, dt);
#else
    // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
    if ((pitch < -90 && m_kalAngleY > 90) || (pitch > 90 && m_kalAngleY < -90)) {
      m_kalmanY.setAngle(pitch);
      m_compAngleY = pitch;
      m_kalAngleY = pitch;
      m_gyroYangle = pitch;
    } else
      m_kalAngleY = m_kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

    if (abs(m_kalAngleY) > 90)
      gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
    m_kalAngleX = m_kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif

    m_gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
    m_gyroYangle += gyroYrate * dt;
  //gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
  //gyroYangle += kalmanY.getRate() * dt;

    m_compAngleX = 0.93 * (m_compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
    m_compAngleY = 0.93 * (m_compAngleY + gyroYrate * dt) + 0.07 * pitch;

  // Reset the gyro angle when it has drifted too much
    if (m_gyroXangle < -180 || m_gyroXangle > 180)
      m_gyroXangle = m_kalAngleX;
    if (m_gyroYangle < -180 || m_gyroYangle > 180)
      m_gyroYangle = m_kalAngleY;
  }
  
  double GetCompAngleX() {return m_compAngleX;}
  double GetCompAngleY() {return m_compAngleY;}
  double GetKalAngleX() {return m_kalAngleX;}
  double GetKalAngleY() {return m_kalAngleY;}
  
private:
/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

  uint8_t i2cWrite(uint8_t registerAddress, uint8_t data, bool sendStop) {
    return i2cWrite(registerAddress, &data, 1, sendStop); // Returns 0 on success
  }

  uint8_t i2cWrite(uint8_t registerAddress, uint8_t *data, uint8_t length, bool sendStop) {
    Wire.beginTransmission(IMUAddress);
    Wire.write(registerAddress);
    Wire.write(data, length);
    uint8_t rcode = Wire.endTransmission(sendStop); // Returns 0 on success
    if (rcode) {
//      Serial.print(F("i2cWrite failed: "));
//      Serial.println(rcode);
    }
    return rcode; // See: http://arduino.cc/en/Reference/WireEndTransmission
  }

  uint8_t i2cRead(uint8_t registerAddress, uint8_t *data, uint8_t nbytes) {
    uint32_t timeOutTimer;
    Wire.beginTransmission(IMUAddress);
    Wire.write(registerAddress);
    uint8_t rcode = Wire.endTransmission(false); // Don't release the bus
    if (rcode) {
//      Serial.print(F("i2cRead failed: "));
  //    Serial.println(rcode);
      return rcode; // See: http://arduino.cc/en/Reference/WireEndTransmission
    }
    Wire.requestFrom(IMUAddress, nbytes, (uint8_t)true); // Send a repeated start and then release the bus after reading
    for (uint8_t i = 0; i < nbytes; i++) {
      if (Wire.available())
        data[i] = Wire.read();
      else {
        timeOutTimer = micros();
        while (((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
        if (Wire.available())
          data[i] = Wire.read();
        else {
//          Serial.println(F("i2cRead timeout"));
          return 5; // This error value is not already taken by endTransmission
        }
      }
    }
    return 0; // Success
  }
};

#endif