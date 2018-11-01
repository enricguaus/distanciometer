#include "map.h"

Map::Map(void){
    setAutoscaleMode(0);
    _autoscale_low=0.0;
    _autoscale_hi=0.0;
}

Map::~Map(void){
}

void Map::initialise(int pInLow, int pInHi, int pOutLow, int pOutHi){
    _in_low  = pInLow;
    _in_hi   = pInHi;
    _out_low = pOutLow;
    _out_hi  = pOutHi;
    // y=mx+b -> look for m
    _m=float(float(_out_hi-_out_low)/float(_in_hi-_in_low));
    // y=mx+b -> look for b, with (x,y)=(_in_low,_out_low)
    _b=_out_low-_m*_in_low;
}

float Map::mapping(int pValue){
    if(_autoscale_mode) autoscale(pValue);
    float res = _m * pValue + _b;
    if(res<_out_low) res=_out_low;
    if(res>_out_hi)  res=_out_hi;
    return res;
}

void Map::setAutoscaleMode(int pValue){
    _autoscale_mode=pValue;
}

void Map::autoscale(int pValue){
    if(pValue<_autoscale_low){
        _autoscale_low=pValue;
        _in_low=pValue + NOISELEVEL * (_in_hi-pValue);
        initialise(_in_low, _in_hi, _out_low, _out_hi);
    }
    if(pValue>_autoscale_hi){
        _autoscale_hi=pValue;
        _in_hi=pValue;
        initialise(_in_low, _in_hi, _out_low, _out_hi);
    }
}
