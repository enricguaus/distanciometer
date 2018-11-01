#include "map.h"

Map::Map(void){
    setAutoscaleMode(0);
    _autoscaleLow=0.0;
    _autoscaleHi=0.0;
}

Map::~Map(void){
}

void Map::initialise(int pInLow, int pInHi, int pOutLow, int pOutHi){
    _inLow  = pInLow;
    _inHi   = pInHi;
    _outLow = pOutLow;
    _outHi  = pOutHi;
    // Look for m (y=mx+b)
    _m=float(float(_outHi-_outLow)/float(_inHi-_inLow));
    // Look for b, with (x,y)=(_inLow,_outLow) (y=mx+b)
    _b=_outLow-_m*_inLow;
}

float Map::mapping(int pValue){
    if(_autoscaleMode) autoscale(pValue);
    float res = _m * pValue + _b;
    if(res<_outLow) res=_outLow;
    if(res>_outHi)  res=_outHi;
    return res;
}

void Map::setAutoscaleMode(int pValue){
    _autoscaleMode=pValue;
}

void Map::autoscale(int pValue){
    if(pValue<_autoscaleLow){
        _autoscaleLow=pValue;
        _inLow=pValue + NOISELEVEL * (_inHi-pValue);
        initialise(_inLow, _inHi, _outLow, _outHi);
    }
    if(pValue>_autoscaleHi){
        _autoscaleHi=pValue;
        _inHi=pValue;
        initialise(_inLow, _inHi, _outLow, _outHi);
    }
}
