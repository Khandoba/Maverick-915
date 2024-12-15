#include <math.h>

const float ADC_MAX_VOLTAGE = 5.0;
const int ADC_RESOLUTION = 4095;

const float RL_MQ7 = 10.0;
const float RL_MQ137 = 10.0;
const float RL_MQ135 = 10.0;

float R0_MQ7 = 10.0;
float R0_MQ137 = 10.0;
float R0_MQ135 = 10.0;

const int MQ7_PIN = A3;
const int MQ137_PIN = A1;
const int MQ135_PIN = A4;

float calculateCOConcentration(float rsByR0) {
  return pow(10, ((-1.5 * log10(rsByR0)) + 0.8));
}

float calculateNH3Concentration(float rsByR0) {
  return pow(10, ((-2.7 * log10(rsByR0)) + 1.3));
}

float calculateMethanolConcentration(float rsByR0) {
  return pow(10, (-1.5 * log10(rsByR0) + 0.8));
}

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // CO reading  
  int rawValue_MQ7 = analogRead(MQ7_PIN);
  float voltage_MQ7 = (rawValue_MQ7 * ADC_MAX_VOLTAGE) / ADC_RESOLUTION;
  float rs_MQ7 = (RL_MQ7 * (ADC_MAX_VOLTAGE - voltage_MQ7)) / voltage_MQ7;
  float coPPM = calculateCOConcentration(rs_MQ7 / R0_MQ7);

  Serial.print("CO: ");
  Serial.print(coPPM, 2);
  Serial.println(" ppm");

  // NH3 reading 
  int rawValue_MQ137 = analogRead(MQ137_PIN);
  float voltage_MQ137 = (rawValue_MQ137 * ADC_MAX_VOLTAGE) / ADC_RESOLUTION;
  float rs_MQ137 = (RL_MQ137 * (ADC_MAX_VOLTAGE - voltage_MQ137)) / voltage_MQ137;
  float nh3PPM = calculateNH3Concentration(rs_MQ137 / R0_MQ137);

  Serial.print("NH₃ (Ammonia): ");
  Serial.print(nh3PPM, 2);
  Serial.println(" ppm");

  // Methanol reading 
  int rawValue_MQ135 = analogRead(MQ135_PIN);
  float voltage_MQ135 = (rawValue_MQ135 * ADC_MAX_VOLTAGE) / ADC_RESOLUTION;
  float rs_MQ135 = (RL_MQ135 * (ADC_MAX_VOLTAGE - voltage_MQ135)) / voltage_MQ135;
  float methanolPPM = calculateMethanolConcentration(rs_MQ135 / R0_MQ135);

  Serial.print("Methanol: ");
  Serial.print(methanolPPM, 2);
  Serial.println(" ppm");

  Serial.println("-----");

  delay(2000);
}