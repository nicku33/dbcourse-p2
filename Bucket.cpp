#include "Bucket.h"

//Constructor
Bucket::Bucket(int bucket_size){
        this->count = 0;
        this->keys = new int[bucket_size];
        this->payload = new int[bucket_size];
    }
