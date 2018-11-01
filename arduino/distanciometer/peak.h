#ifndef __PEAK_H__
#define __PEAK_H__

class Peak{
    public:
        Peak(void);
        ~Peak(void);
        void setDepth(int pDepth);
        void push(int pValue=0);
        int  get(void);
        int  isMax(void);
    private:
        int  _peak;
        int  _depth;
        int* _history;
};

#endif
