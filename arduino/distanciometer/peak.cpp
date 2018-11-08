#include "peak.h"

Peak::Peak(void){
    _peak    = 0;
}

Peak::~Peak(void){
    if(_history) delete [] _history;
}

void Peak::setDepth(int pDepth){
    _depth   = pDepth;
    _history = new int[_depth];
    for(int i=0;i<_depth;i++) _history[i]==0;
}

void Peak::push(int pValue){
    for(int i=_depth-1;i>0;i--) _history[i]=_history[i-1];
    _history[0]=pValue;
}

int Peak::get(void){
    float meanLow=0.0;
    float meanHi=0.0;
    for(int i=0;i<int(_depth/2);i++){
        meanHi  += float(1.0/float(int(_depth/2))) * _history[i];
        meanLow += float(1.0/float(int(_depth/2))) * _history[1+int(_depth/2)+i];
    }
    if((meanLow<=_history[int(_depth/2)])&&(meanHi<=_history[int(_depth/2)])) _peak=_history[int(_depth/2)];
    return _peak;
}

int Peak::isMax(void){
    return 0;
}

