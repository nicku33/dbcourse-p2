#ifndef ____Bucket__
#define ____Bucket__
typedef unsigned int uint;
class Bucket {
    
public:
    int count; //Number of keys in bucket
    int index; //A "pointer" for next insertion
    int bucket_size; //Size of bucket
	uint *keys; //Pointer for key array
    uint *payload; //pointer for payload array

    Bucket(int bucket_size); //Constructer
    int getIndexOfOldest(); //Returns index of oldest entry
    void insert(uint key, uint payload); //Insert new entry at oldest index
};
#endif
