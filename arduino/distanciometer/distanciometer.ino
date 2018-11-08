
#include "map.h"
#include "peak.h"

#define FIRST_SENSOR_PIN  0
#define N_SENSORS         4
#define FILTER_COEFF      0.01
#define CALIBR_COEFF      0.0001
#define PEAKWIDTH         21
#define GROUNDVALUE       0
#define FULLSCALE       127
#define MEAS_TIME         5

#define AUTOSCALE         0
#define MINVALUE0        15
#define MAXVALUE0       150
#define MINVALUE1         5
#define MAXVALUE1        50
#define MINVALUE2         5
#define MAXVALUE2        80
#define MINVALUE3         5
#define MAXVALUE3        25

float filteredValues[N_SENSORS];
float calibratValues[N_SENSORS];
int   minValues[N_SENSORS]={MINVALUE0,MINVALUE1,MINVALUE2,MINVALUE3};
int   maxValues[N_SENSORS]={MAXVALUE0,MAXVALUE1,MAXVALUE2,MAXVALUE3};
Map   mappedValues[N_SENSORS];
Peak  peakValues[N_SENSORS];

void setup(){
  for(int i=0;i<N_SENSORS;i++) filteredValues[i]=0.0;
  Serial.begin(57600);           // starts the serial monitor
  delay(100);                    // wait for this much time before printing next value
  for(int i=0;i<N_SENSORS;i++){
    mappedValues[i].setAutoscaleMode(AUTOSCALE);
    if(AUTOSCALE==1) mappedValues[i].initialise(0,0,0,FULLSCALE);
    else             mappedValues[i].initialise(minValues[i],maxValues[i],0,FULLSCALE);
    peakValues[i].setDepth(PEAKWIDTH);
    delay(10);
    filteredValues[i] = analogRead(FIRST_SENSOR_PIN+i);
    calibratValues[i] = filteredValues[i];//analogRead(FIRST_SENSOR_PIN+i);
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
    //Serial.print(" | "); Serial.print(filteredValue); Serial.print(" - "); 
    //Serial.print(filteredValue);
    // ---- DEBUG: Monitoring calibration values
    // Serial.print(" | "); Serial.print(int(calibratValues[i])); Serial.print(" - ");
    // ---- Mapping to manually specified dynamic range and peak detection
    //peakValues[i].push(int(mappedValues[i].mapping(filteredValue)));                          // Mapejo primer?
    peakValues[i].push(filteredValue); data=mappedValues[i].mapping(peakValues[i].get());       // O busco els pics primer?
    // ---- Print to Serial port
    Serial.print(int(data));
    if((i<N_SENSORS-1)) Serial.print(" ");
  }
  Serial.println();
  delay(MEAS_TIME);                    // wait for this much time before printing next value
}



