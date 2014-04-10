#include<stdlib.h>
#include<random>
#include<ostream>
#include<iostream>

struct Bucket {
	int count;
	int storage[];
};

class Hash {

	int seed;
	int s;
public:
	Hash(int s, int seed) {
		this->s = s;
		this->seed = seed;
	}
	
	// TODO: This is a garbage implementation

	int get( int v){
		float f = 1/seed;
		int a = (int) v * f;
		return a % s; 

	}
};

class SplashTable {
	int s; // this is the (initial) number of hash buckets 
	int b; // the number of buckets
	int h; // number of hash functions
	int lim; // maximum number of recursions

	int counts[];
	int table[][];
	Hash hashes[];

	void init() {
		/* need to allocate memory to zero */
		// TODO: allocate our main struct, memory, etc
	}

	int getBucket(int v){
		/* the idea here is that we multiply by our buckets and just capture the overflow as our bucket number. This is, effectively like:
		   pick a random number 1-100
		   divide by 100 to get fraction 0-1
		   multiply by # of buckets
		   round down to get bucket id
		 */ 
		long z =  v * s;
		return (int)(z>>32);
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

	void dump() {


		/* format is 
		 * B S h N * h[0] H[1] ... H[h-1] K[0] P[0] * K[1] P[1]
		 * ...
		 * K[2^S-1] P[2^S-1]
		 */ 
		std::cout << b << s << "\n";
		for (int i=0; i<h; i++) {
			/* TODO something about how to paramaterize hashes */
		}	

	}



	int probe( int key){
		/* returns -1 if not present else paylod */
		return -1;
	}

};
