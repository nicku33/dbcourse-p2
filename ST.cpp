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
    totalCount = 0; //For dump file
    
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
 * uint *keys: An array of all non-negative keys
 * uint *payloads: An array of all non-negative payloads
 */
int SplashTable::build(uint * keys, uint * payloads, int length){
    //Insert every key-payload pair in table
    for(int i = 0; i < length; i++){
        //lastBucket = -1 will not generate any hits
        if(!insert(keys[i], payloads[i], 0, -1)){
            //If it fails, return false
            return 0;
        }
    }
    //Every key inserted into table
    return 1;
}


/**
 * Private insert method, returns 1 if success, 0 otherwise
 * uint key: A non-negative key
 * uint payload: A non-negative payload
 * int l: Attempted insertions, has to be below R
 * int lastBucket: In case a key is re-inserted into H-lastBucket buckets
 */
int SplashTable::insert(uint key, uint payload, int l, int lastBucket){
    int hashedValue;
    
    int minFilled = B; //Count of least filled bucket
    int leastFilledBucket = 0; //Index of least filled bucket
    int hitLastBucket = 0; //For hash collisions
    
    //Loops through all hash functions
    for(int i = 0; i<h; i++){
        hashedValue = hashes[i].hash(key); //Hashes key
        
        if(hashedValue == lastBucket){
            //Do not attempt to insert into old bucket
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
        return 1; //Success
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
    //Initialize random device and random engine
    std::random_device rd;
    std::mt19937 engine(rd());
    
    //Initialize uniform distribution
    std::uniform_int_distribution<> uniform(min,max);
    
    //Return a number from the distribution
    return uniform(engine);
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