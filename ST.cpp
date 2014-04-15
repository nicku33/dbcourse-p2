#include "ST.h"

SplashTable::SplashTable(int B, int R, int S, int h){
    this->B = B; //Bucket size
    this->R = R; //Recursive limit
    this->S = S; //2^S number of entries
    this->h = h; //Number of hashes
    init();
}

void SplashTable::init(){
    noOfBuckets = exp2(S)/B; //Since B is a power of 2
    totalCount = 0;
    
    //Initializes buckets with bucketsize B
    for(int i = 0; i<noOfBuckets; i++){
        buckets.push_back(Bucket(B));
    }
    
    //Initilizes random number generator
    std::random_device rd;
    std::mt19937 engine(rd());
    
    //Since max of 32 bit int is 2^32-1
    std::uniform_int_distribution<> uni_hash(1,exp2(32)-1); //For hashes, only used in init()
    
    //Initialize all hash functions with random multiplier
    for(int i = 0; i<h; i++){
        uint random = uni_hash(engine);
        hashes.push_back(MHash(random,S,B));
    }
}
/**
 * Public build method, initializes first attempt at insertion
 * uint key: A non-negative key
 * uint payload: A non-negative payload
 */
int SplashTable::build(uint key, uint payload){
    return build(key, payload, 0); //First attempt
}


/**
 * Private build method, returns 1 if success, 0 othervise
 * uint key: A non-negative key
 * uint payload: A non-negative payload
 * int l: Attempted insertions, has to below R
 */
int SplashTable::build(uint key, uint payload, int l){
    int hashedValue;
    
    int minFilled = B; //Count of least filled bucket
    int leastFilledBucket = 0; //Index of least filled bucket
    
    //Loops through all hash functions
    for(int i = 0; i<h; i++){
        hashedValue = hashes[i].hash(key); //Hashes key
        
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
        
        //Initilizes random number generator
        std::random_device rd;
        std::mt19937 engine(rd());
        
        //Initialize distributions
        std::uniform_int_distribution<> uni_bucket(0,noOfBuckets-1); //For random bucket
        std::uniform_int_distribution<> uni_index(0,B-1); //For random index

        // choose a random bucket
        int randomBucket = uni_bucket(engine);
        int randomIndex = uni_index(engine);
        
        // swap out the old value and put in the new
        int tempKey = buckets[randomBucket].keys[randomIndex];
        int tempPayload = buckets[randomBucket].payload[randomIndex];
        buckets[randomBucket].keys[randomIndex] = key;
        buckets[randomBucket].payload[randomIndex] = payload;
        
        //Recursive call, increment l
        return build(tempKey, tempPayload, l++);
    } else {
        // we had room, do the storage
        Bucket *bucket = &buckets[leastFilledBucket];
        bucket->keys[bucket->count] = key;
        bucket->payload[bucket->count] = payload; //Since count = index of last key + 1
        bucket->count++; //Increments bucket count
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