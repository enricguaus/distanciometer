#ifndef __MAP_H__
#define __MAP_H__

#define NOISELEVEL 0.1

class Map{
    public:
        Map(void);
        ~Map(void);
        void  initialise(int pInLow=0, int pInHi=0, int pOutLow=0, int pOutHi=0);
        float mapping(int pValue=0);
        void  setAutoscaleMode(int pValue=0);
        void  autoscale(int pValue=0);
    private:
        int _inLow, _inHi, _outLow, _outHi;
        float _m, _b;
        int _autoscaleMode;
        float _autoscaleLow, _autoscaleHi;
};

#endif
