#ifndef ____Bucket__
#define ____Bucket__
typedef unsigned int uint;
class Bucket {
    
public:
    int count; //Number of keys in bucket
    int index;
    int bucket_size;
	uint *keys; //Pointer for key array
    uint *payload; //pointer for payload array

    Bucket(int bucket_size); //Constructer
    int getIndexOfOldest();
    void insert(uint key, uint payload);
};
#endif
