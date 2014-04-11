#include<stdlib.h>
#include<random>
#include<ostream>
#include<iostream>
#include "SplashTable.h"
#include "Hash.h" 


void SplashTable::init() {
	// can't do this, as we cannot allocate with new dynamically
	counts=new int[this->s];
	hashes=new Hash*[this->h];

	for(int i=0; i< this->h; i++){
		hashes[i]= new Hash(this->s,i);
	}

	table=new int* [this->s];
	for(int i=0; i< this->s; i++){
		table[i]=new int[this->b];
	}
}


int SplashTable::getBucket(int v){
	/* the idea here is that we multiply by our buckets and just capture the overflow as our bucket number. This is, effectively like:
	   pick a random number 1-100
	   divide by 100 to get fraction 0-1
	   multiply by # of buckets
	   round down to get bucket id
	 */ 
	long z =  v * s;
	return (int)(z>>32);
}


SplashTable::SplashTable(int s, int b, int h, int lim) {
	this->s = s;
	this->b = b;
	this->h = h;   // equiv to (*this).h;
	this->lim=lim;
	init();
}

int SplashTable::insert(int v){
	return insert(v,0);	// make first attempt at insertion[	
}

int SplashTable::insert(int v, int l){

	int min_filled=s;	// this is the smallest bucket 
	int lightest_bucket=0; 
	int * hashed_values;
	hashed_values = new int[this->h];	
	//		int hashed_values[this->h];	// let's store the computed hashes

	// let's gather all the hash values
	for (int i=0; i< h; i++){
		hashed_values[i]=this->hashes[i]->get(v);
		if(counts[i] < min_filled){
			min_filled=counts[i];
			lightest_bucket=i;
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
		int v_swap = table[random_bucket][random_index];
		table[random_bucket][random_index]=v;
		// and recurse
		return insert(v_swap, l++);
	} else {
		// we had room, do the storage
		// we need to find the first available spot

		for(int i=0;i<s;i++){
			if (this->table[lightest_bucket][i] == 0){
				this->table[lightest_bucket][i]=v;
				this->counts[lightest_bucket]++;
				return 0;
			}
		}

		// we shouldn't get here, random code
		throw(100); 
	}
}

void SplashTable::dump() {
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

int SplashTable::probe( int key){
	/* returns -1 if not present else paylod */
	return -1;
}

