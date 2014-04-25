#include "Bucket.h"

/**
 * Initializes bucket based on the bucket size.
 */
Bucket::Bucket(int bucket_size){
    //Initializes count value and allocates memory for arrays
    this->count = 0;
    this->index = -1; //from first insertion, it stays in range [0;3]
    this->bucket_size = bucket_size;
    
    //Initializes arrays with 0's in key and payload
    this->keys = new uint[bucket_size];
    this->payload = new uint[bucket_size];
    for(int i = 0; i < bucket_size; i++){
        this->keys[i] = 0;
        this->payload[i] = 0;
    }
}
/**
 * Returns index of oldest bucket.
 * Is only called after bucket is full.
 */
int Bucket::getIndexOfOldest(){
    return index;
}

/**
 * Handles increment of count and index.
 * Index is the oldest key, the next to be removed.
 */
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
