#include "Bucket.h"
#include <iostream>

class Bucket {
    
public:
    int count;
	int *keys;
    int *payload;
    
    void hash(int bucket_size){
        this->count = 0;
        this->keys = new int[bucket_size];
        this->payload = new int[bucket_size];
    }
    
    void deleteObject(){
        delete []keys;
        delete []payload;
    }
    
};