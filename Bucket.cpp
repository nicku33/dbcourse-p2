#include "Bucket.h"

//Constructor
Bucket::Bucket(int bucket_size){
    //Initializes count value and allocates memory for arrays
    this->count = 0;
    this->index = -1;
    this->bucket_size = bucket_size;
    this->keys = new uint[bucket_size];
    this->payload = new uint[bucket_size];
    for(int i = 0; i < bucket_size; i++){
        this->keys[i] = 0;
        this->payload[i] = 0;
    }
}

int Bucket::getIndexOfOldest(){
    return index;
}

void Bucket::insert(uint key, uint payload){
    if(count < bucket_size){
        this->keys[count] = key;
        this->payload[count] = payload;
        count++;
    } else {
        this->keys[index] = key;
        this->payload[index] = payload;
    }
    index = (index + 1) % bucket_size;
}
