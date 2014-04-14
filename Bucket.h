#ifndef ____Bucket__
#define ____Bucket__

class Bucket {
    
public:
    int count;
	int *keys;
    int *payload;

    Bucket(int bucket_size);
};
#endif
