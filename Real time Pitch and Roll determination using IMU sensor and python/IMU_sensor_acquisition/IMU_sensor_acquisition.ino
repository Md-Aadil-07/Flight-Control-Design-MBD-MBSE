#include <Wire.h>

const int MPU_ADDR = 0x68; // MPU-6050 I2C address
int16_t GyX, GyY, GyZ, AcX, AcY, AcZ;

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Initialize MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // Wake up MPU6050
  Wire.endTransmission(true);

  // Print CSV header
  Serial.println("GyX,GyY,GyZ");
}

void loop() {
  // Request gyro data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x43); // Start with GYRO_XOUT_H register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  // Read gyro data
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  // Read accelerometer data
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  
  // Print data in CSV format
  Serial.print(GyX); Serial.print(",");
  Serial.print(GyY); Serial.print(",");
  Serial.println(GyZ); Serial.print(",");
  Serial.print(AcX); Serial.print(",");
  Serial.print(AcY); Serial.print(",");
  Serial.println(AcZ);

  delay(100);
}
