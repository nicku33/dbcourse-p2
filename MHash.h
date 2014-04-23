#ifndef ____MHash__
#define ____MHash__
#include <math.h>
//Needed for 32 bit values
typedef unsigned int uint;

class MHash{

private:
    //explained in .cpp file
    uint s, p;
    //Word size determined by system
    const static uint w = sizeof(int) * 8;
    
public:
    MHash(uint multiplier, uint S, uint B);
    uint hash(uint key);
    uint getMultiplier();
};

#endif
