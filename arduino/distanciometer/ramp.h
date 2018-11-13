#ifndef __RAMP_H__
#define __RAMP_H__

class Ramp{
    public:
        Ramp(void);
        ~Ramp(void);
        void setRate(float pRate=0.99);
        int pushget(int pValue=0);
        int  get(void);
    private:
        float _rate;
        float _previous;
};

#endif
