
#include "map.h"
#include "peak.h"

#define FIRST_SENSOR_PIN  0
#define N_SENSORS         4
#define FILTER_COEFF      0.05
#define CALIBR_COEFF      0.0001
#define PEAKWIDTH         7
#define GROUNDVALUE       0
#define FULLSCALE       127
#define MAXVALUE0       300
#define MAXVALUE1       127
#define MAXVALUE2       127
#define MAXVALUE3       127
#define MEAS_TIME        10

float filteredValues[N_SENSORS];
float calibratValues[N_SENSORS];
int   minValues[N_SENSORS]={10,15,0,-40};
int   maxValues[N_SENSORS]={MAXVALUE0,MAXVALUE1,MAXVALUE2,MAXVALUE3};
Map   mappedValues[N_SENSORS];
Peak  peakValues[N_SENSORS];

void setup(){
  for(int i=0;i<N_SENSORS;i++) filteredValues[i]=0.0;
  Serial.begin(57600);           // starts the serial monitor
  delay(100);                    // wait for this much time before printing next value
  for(int i=0;i<N_SENSORS;i++){
    //mappedValues[i].initialise(minValues[i],maxValues[i],0,FULLSCALE);
    mappedValues[i].setAutoscaleMode(1);
    peakValues[i].setDepth(PEAKWIDTH);
    filteredValues[i] = analogRead(FIRST_SENSOR_PIN+i);
    calibratValues[i] = analogRead(FIRST_SENSOR_PIN+i);
  }
}
 
void loop(){
  float data=0.0;
  float filteredValue=0.0;
  Serial.print("0 ");
  for(int i=0;i<N_SENSORS;i++){
    // ---- DEGUG: Send raw data 
    //Serial.print(analogRead(FIRST_SENSOR_PIN+i));
    // ---- Fast (smoothing) and Slow (calibration) Low-pass filters:
    data=analogRead(FIRST_SENSOR_PIN+i);
    filteredValues[i] = filteredValues[i] + ((data - filteredValues[i]) * FILTER_COEFF);
    calibratValues[i] = calibratValues[i] + ((data - calibratValues[i]) * CALIBR_COEFF);
    filteredValue = filteredValues[i]-calibratValues[i];
    // ---- DEBUG: Monitoring filtered values
    Serial.print(" | "); Serial.print(filteredValue); Serial.print(" - "); 
    // ---- DEBUG: Monitoring calibration values
    // Serial.print(" | "); Serial.print(int(calibratValues[i])); Serial.print(" - ");
    // ---- Mapping to manually specified dynamic range and peak detection
    peakValues[i].push(int(mappedValues[i].mapping(filteredValue)));
    // ---- Print to Serial port
    Serial.print(peakValues[i].get());
    if((i<N_SENSORS-1)) Serial.print(" ");
  }
  Serial.println();
  delay(MEAS_TIME);                    // wait for this much time before printing next value
}



