#include "ramp.h"

Ramp::Ramp(void){
    _previous = 0.0;
    setRate(0.99);
}

Ramp::~Ramp(void){
}

void Ramp::setRate(float pRate){
    _rate=pRate;
}

int Ramp::pushget(int pValue){
    if((_previous*_rate) < pValue){ // New value is higher
        _previous = pValue;    
    }else{
        _previous = _previous*_rate;
    }
    return int(_previous);
}
