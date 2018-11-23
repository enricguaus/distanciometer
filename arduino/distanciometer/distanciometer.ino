#include "map.h"
#include "peak.h"
#include "ramp.h"

#define FIRST_SENSOR_PIN  0
#define N_SENSORS         4
#define FILTER_COEFF      0.005
#define CALIBR_COEFF      0.0005
#define PEAKWIDTH        21
#define GROUNDVALUE       0
#define FULLSCALE       127
#define RAMPRATE          0.999
#define MEAS_TIME         5

#define AUTOSCALE         0
#define MINVALUE0         5
#define MAXVALUE0       105
#define MINVALUE1         5
#define MAXVALUE1        40
#define MINVALUE2         5
#define MAXVALUE2        25
#define MINVALUE3         5
#define MAXVALUE3        20

float filteredValues[N_SENSORS];
float calibratValues[N_SENSORS];
int   minValues[N_SENSORS]={MINVALUE0,MINVALUE1,MINVALUE2,MINVALUE3};
int   maxValues[N_SENSORS]={MAXVALUE0,MAXVALUE1,MAXVALUE2,MAXVALUE3};
Map   mappedValues[N_SENSORS];
Peak  peakValues[N_SENSORS];
Ramp  rampValues[N_SENSORS];

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
    rampValues[i].setRate(RAMPRATE);
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

    peakValues[i].push(filteredValue); 
    data=mappedValues[i].mapping(peakValues[i].get());       // O busco els pics primer?
    // ---- DEBUG: Monitoring map values
    //Serial.print(" | "); Serial.print(filteredValue); Serial.print(" - "); Serial.print(data); Serial.print(" - "); 
    data=rampValues[i].pushget(data);
    // ---- Print to Serial port
    Serial.print(int(data));
    if((i<N_SENSORS-1)) Serial.print(" ");
  }
  Serial.println();
  delay(MEAS_TIME);                    // wait for this much time before printing next value
}
