


class SplashTable


private B,S,h,N;
private HashFunctions[] hashes;

void init(params) {

	/* memory allocate
	 * set up private hash function etc 
	 */


}
void build(ArrayIterator i) {

	while (line = i.next()){

	}

}



void dump( outputIterator o) {


	/* format is 
	 * B S h N * H[0] H[1] ... H[h-1] K[0] P[0] * K[1] P[1]
	 * ...
	 * K[2^S-1] P[2^S-1]
	*/ 
	o.output(B S H N)
	for (i=1:count(H) {
		String hash_string = n[i].dump();
		o.output(hash_string);
	}	

	o.output(H[0] H[1] ...)
	for (i=1:N){
		o.output...()
	}
}



int probe( int key){
	/* returns -1 if not present else paylod */


}


