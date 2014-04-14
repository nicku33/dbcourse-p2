#include "ST.h"

SplashTable::SplashTable(int B, int R, int S, int h){
    this->B = B; //Bucket size
    this->R = R; //Recursive limit
    this->S = S; //2^S number of entries
    this->h = h; //Number of hashes
    init();
}

void SplashTable::init(){
    noOfBuckets = exp2(S)/B;
    
    for(int i = 0; i<noOfBuckets; i++){
        buckets.push_back(Bucket(B));
    }
    
    for(int i = 0; i<h; i++){
        //TODO: Generate random number
        uint random = rand();
        hashes.push_back(MHash(random,S,B));
    }
}

int SplashTable::build(uint key, uint payload){
    return build(key, payload, 0); //First attempt
}

int SplashTable::build(uint key, uint payload, int l){
    int hashedValue;
    
    int minFilled = B;
    int leastFilledBucket = 0;
    for(int i = 0; i<h; i++){
        hashedValue = hashes[i].hash(key);
        if(buckets[hashedValue].count < minFilled){
            minFilled = buckets[hashedValue].count;
            leastFilledBucket = hashedValue;
        }
    }
    
    if(minFilled == B){
        // they were all full, we need to do a swap and recurse
        // if we've hit our recursion limit, bad news
        if (l==R){
            return 0;
        }
        // choose a random bucket: TODO, use a better generator
        int randomBucket = rand() % noOfBuckets;
        int randomIndex = rand() % B;
        
        // swap out the old value and put in the new
        int tempKey = buckets[randomBucket].keys[randomIndex];
        int tempPayload = buckets[randomBucket].payload[randomIndex];
        buckets[randomBucket].keys[randomIndex] = key;
        buckets[randomBucket].payload[randomIndex] = payload;
        
        //Recurse
        return build(tempKey, tempPayload, l++);
    } else {
            // we had room, do the storage
			// we need to find the first available spot
            Bucket *bucket = &buckets[leastFilledBucket];
            bucket->keys[bucket->count] = key;
            bucket->payload[bucket->count] = payload;
            bucket->count++;
            return 1;
        }

    }

uint SplashTable::probe(uint key){
    int hashedValue;
    
    //Retrieves all hash values for the given key to probe

    uint value = 0;
    int count = 0;
    
    for(int i = 0; i<h; i++){
        hashedValue = hashes[i].hash(key);
        
        for(int k = 0; k<B; k++){
            //If true, value = 1 * payload
            count += (buckets[hashedValue].keys[k] == key);
            value += ((count == 1) & (buckets[hashedValue].keys[k] == key)) * buckets[hashedValue].payload[k];
        }
    }
    return value;
}

void SplashTable::dump(std::string fileName){
    std::ofstream dumpfile;
    dumpfile.open(fileName);
    
    //Writing first line of file
    dumpfile << B << " " << S << " " << h << " " << R << "\n"; //TODO: R should be N, number of inserted records
    
    //Writing hash values
    for(int i = 0; i<h; i++){
        dumpfile << hashes[i].getMultiplier();
        if(i!=(h-1)){
            dumpfile << " ";
        }
    }
    dumpfile << "\n";
    
    //Writing all key-value pairs
    for(int i = 0; i<noOfBuckets; i++){
        for(int k = 0; k<buckets[i].count; k++){
            dumpfile << buckets[i].keys[k] << " " << buckets[i].payload[k] << "\n";
        }
    }
    //Close file
    dumpfile.close();
}

//Deconstrutor, frees the memory allocated to the bucket arrays
SplashTable::~SplashTable(){
    for(int i = 0; i<noOfBuckets; i++){
        delete [] buckets[i].keys;
        delete [] buckets[i].payload;
    }
}