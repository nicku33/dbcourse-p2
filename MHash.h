#ifndef ____MHash__
#define ____MHash__

#include <math.h>
typedef unsigned int uint;

class MHash{

private:
    uint s, p;
    const static uint w = sizeof(int) * 8;
    
public:
    MHash(uint, uint, uint);
    uint hash(uint);
};

#endif