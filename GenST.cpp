#include "ST.h"

/**
 * Constructor
 * initializes relevant parameters.
 */
SplashTable::SplashTable(int B, int R, int S, int h){
    this->B = B; //Bucket size
    this->R = R; //Recursive limit
    this->S = S; //2^S number of entries
    this->h = h; //Number of hashes
    init();
}

/**
 * Initializes some core values, hash functions and buckets.
 */
void SplashTable::init(){
    noOfBuckets = exp2(S)/B; //Since B is a power of 2
    totalCount = 0;
    
    //Initializes buckets with bucketsize B
    for(int i = 0; i<noOfBuckets; i++){
        buckets.push_back(Bucket(B));
    }
    
    srand( time(0));

    //Initialize all hash functions with random multiplier
    for(int i = 0; i<h; i++){
        uint r = getRandom(0,UINT_MAX-1);
        hashes.push_back(MHash(r,S,B));
    }
}
/**
 * Public build method, initializes first attempt at insertion
 * uint key: A non-negative key
 * uint payload: A non-negative payload
 */
int SplashTable::build(uint * keys, uint * payloads, int length){
    for(int i = 0; i < length; i++){
        if(!insert(keys[i], payloads[i], 0, -1)){
            return 0;
        }
    }
    return 1;
}


/**
 * Private build method, returns 1 if success, 0 othervise
 * uint key: A non-negative key
 * uint payload: A non-negative payload
 * int l: Attempted insertions, has to below R
 */
int SplashTable::insert(uint key, uint payload, int l, int lastBucket){
    int hashedValue;
    
    int minFilled = B; //Count of least filled bucket
    int leastFilledBucket = 0; //Index of least filled bucket
    int hitLastBucket = 0;
    
    //Loops through all hash functions
    for(int i = 0; i<h; i++){
        hashedValue = hashes[i].hash(key); //Hashes key
        
        if(hashedValue == lastBucket){
            hitLastBucket++;
            continue;
        }
        //Tests if minFilled is bigger than current bucket count
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
        
        // choose a random bucket
        int randomBucket;
        do{
            //Assigns a random bucket from the possible hash functions
            //Run only once if all hash functions hash to the same bucket
            //OR if found bucket is not the same as last attempt
            randomBucket = hashes[getRandom(0, h-1)].hash(key);
        } while (randomBucket == lastBucket & hitLastBucket != h);
        
        //Retrieves index of oldest bucket
        int index = buckets[randomBucket].getIndexOfOldest();
        
        // swap out the old value and put in the new
        int tempKey = buckets[randomBucket].keys[index];
        int tempPayload = buckets[randomBucket].payload[index];
        
        //Insert the (key, payload) in the oldest bucket
        buckets[randomBucket].insert(key, payload);
        
        //Recursive call, increment l,
        return insert(tempKey, tempPayload, ++l, randomBucket);
    } else {
        // we had room, do the storage
        Bucket *bucket = &buckets[leastFilledBucket];
        bucket->insert(key, payload);
        totalCount++; //increments table count
        return 1;
    }
}

/**
 * Public method, probes table and returns payload on match, else 0.
 * uint key: The key to probe the table.
 */
uint SplashTable::probe(uint key){
    int hashedValue;
    
    uint value = 0; //Payload
    int count = 0; //Number of matches in case of bucket collisions
    
    //Loops through each hash value
    for(int i = 0; i<h; i++){
        hashedValue = hashes[i].hash(key); //Hashes key
        
        //Loops through every entry in bucket
        for(int k = 0; k<B; k++){
            //Increments count
            count += (buckets[hashedValue].keys[k] == key);
            
            //Only adds a number to value if count == 1 and the key matches
            //Then it's 1 * payload = payload
            value += ((count == 1) & (buckets[hashedValue].keys[k] == key)) * buckets[hashedValue].payload[k];
        }
    }
    return value; //Returns payload or 0 othervise
}

/**
 * Dump method prints a file in the given format
 * std::string fileName: Name of the file
 */
void SplashTable::dump(std::string fileName){
    std::ofstream dumpfile; //Creates a output filestream
    dumpfile.open(fileName);
    
    //Writing first line of file
    dumpfile << B << " " << S << " " << h << " " << totalCount << "\n";
    
    //Writing hash values
    for(int i = 0; i<h; i++){
        dumpfile << hashes[i].getMultiplier();
        if(i!=(h-1)){ //So the last multiplier don't print a ' ' before \n
            dumpfile << " ";
        }
    }
    dumpfile << "\n";
    
    //Writing all key-value pairs
    for(int i = 0; i<noOfBuckets; i++){
        for(int k = 0; k<B; k++){
            dumpfile << buckets[i].keys[k] << " " << buckets[i].payload[k] << "\n";
        }
    }
    //Close file
    dumpfile.close();
}

/**
 * Used for generating random number in a uniform distribution.
 * External to prevent stack overflow when the recursive limit is > 254
 */
uint SplashTable::getRandom(uint min, uint max){
    if((max-min) == UINT_MAX){
        //Max = UINT_MAX and min = 0
        return (uint) rand();
    } else {
        //Cannot go out of bounds
        return (uint) min + ((uint) rand() % (max - min + 1));
    }
}

/**
 * Used for testing to perform statistics outside SplashTable.
 */
uint SplashTable::getCount(){
    return totalCount;
}

/**
 * Destructor
 * Frees the memory allocated to the bucket arrays.
 */
SplashTable::~SplashTable(){
    for(int i = 0; i<noOfBuckets; i++){
        delete [] buckets[i].keys;
        delete [] buckets[i].payload;
    }
}
