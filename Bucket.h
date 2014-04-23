#ifndef ____Bucket__
#define ____Bucket__

class Bucket {
    
public:
    int count; //Number of keys in bucket
	int *keys; //Pointer for key array
    int *payload; //pointer for payload array

    Bucket(int bucket_size); //Constructer
};
#endif
