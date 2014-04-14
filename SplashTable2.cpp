#include <stdlib.h>
#include <random>
#include <ostream>
#include <iostream>
#include <Math.h>
#include "MHash.h"

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

class SplashTable {
	int s; // this is the (initial) number of hash buckets //No, it's the 2^s number of entries in total for all buckets
	int b; // the number of buckets //No, it is the bucket size
	int h; // number of hash functions
	int lim; // maximum number of recursions
    int noOfBuckets = exp2(s)/b;

	int counts[];
	int table[][];
    Bucket buckets[noOfBuckets];
	Hash hashes[h];
    
    

	void init() {
		/* need to allocate memory to zero */
		// TODO: allocate our main struct, memory, etc
	}

	public:

	SplashTable(int s, int b, int h, int lim) {
		this->s = s;
		this->b = b;
		this->h = h;   // equiv to (*this).h;
		this->lim=lim;
		init();
	}

	int insert(int v){
		return insert(v,0);	// make first attempt at insertion[	
	}

	int insert(int v, int l){

		int min_filled=s;	// this is the smallest bucket 
		int lightest_bucket=0; 
		int hashed_values[this->h];	// let's store the computed hashes

		// let's gather all the hash values
		for (int i=0; i< h; i++){
			hashed_values[i]=this->hashes[i].get(v);
			if(buckets[hashed_values[i]]->count < min_filled){
				min_filled=buckets[hashed_values[i]]->count;
				lightest_bucket=hashed_values[i];
			}
		}


		if(min_filled==s){
			// they were all full, we need to do a swap and recurse
			// if we've hit our recursion limit, bad news
			if (l==lim){
				return -1;
			}

			// choose a random bucket: TODO, use a better generator
			int random_bucket=rand() % s;
			int random_index=rand() % b;

			// swap out the old value and put in the new
			int v_new = buckets[hashed_values[random_bucket]]->storage[random_index];
			buckets[hashed_values[random_bucket]]->storage[random_index] = v;

			// and recurse
			return insert(v_new,l++);
		} else {
			// we had room, do the storage
			// we need to find the first available spot
			for(int i=0;i<s;i++){
				if (buckets[hashed_values[lightest_bucket]]->storage[i] == 0){
					buckets[hashed_values[lightest_bucket]]->storage[i]=v;
					buckets[hashed_values[lightest_bucket]]->count++;
					return 0;
				}
			}

			// we shouldn't get here, random code
			throw(100); 
		}
	}
    
    
    /**
     * Both requires #include <iostream> and <fstream>
     */
    
	void dump() {
        dump(someStandardFilenameFromAConstant); //TODO
	}
    
    void dump(string fileName){
        
        ofstream dumpfile;
        dumpfile.open(filename);
        
        //Writing first line of file
        dumpfile << b << " " << s << " " << h << " " << lim << "\n";
        
        //Writing hash values
        for(int i = 0; i<h; i++){
            dumpfile << hashes[i] << " ";
        }
        dumpfile << "\n";
        
        //Writing all key-value pairs
        for(int i = 0; i<NUMBER_OF_BUCKETS; i++){ //TODO find the right number
            for(int k = 0; k<buckets[i]->count; k++){
                dumpfile << buckets[i]->key[k] << " " << buckets[i]->payload[k] << "\n";
            }
        }
        //Close file
        dumpfile.close();
    }

	int probe( int key){
        int hash_values*;
        
        //Retrieves all hash values for the given key to probe
        hash_values = new int[h];
        for(int i = 0; i < h; i++){
            hash_values[i] = hashes[i]->get(key); //get is not descriptive enough, should be getHash at least
        }
        int value = 0;
        for(int i = 0; i<h; i++){
            for(int k = 0; k<b; k++){
                //If true, value = payload
                value = (buckets[hashed_values[i]]->key[k] == key) * buckets[hashed_values[i]]->payload[i]; //Assuming that each bucket holds an array for each keys and payloads)
            }
        }
		return value;
	}

};
