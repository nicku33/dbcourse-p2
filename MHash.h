#ifndef ____MHash__
#define ____MHash__
#include <math.h>
typedef unsigned int uint;

class MHash{

private:
    //explained in .cpp file
    uint s, p;
    //Word size determined by system
    const static uint w = sizeof(int) * 8;
    
public:
    MHash(uint multiplier, uint S, uint B); //Constructor
    uint hash(uint key); //Hash method
    uint getMultiplier(); //Used in dump()
};

#endif
