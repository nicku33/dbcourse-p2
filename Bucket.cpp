#include "Bucket.h"

//Constructor
Bucket::Bucket(int bucket_size){
    //Initializes count value and allocates memory for arrays
    this->count = 0;
    this->keys = new int[bucket_size];
    this->payload = new int[bucket_size];
    for(int i = 0; i < bucket_size; i++){
        this->keys[i] = 0;
        this->payload[i] = 0;
    }
}
