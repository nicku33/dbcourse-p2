#include<stdio.h>

int main(int argv, char** argc){

	int a = 1238728137;
	long S = 4;


	/* this is all we need to do to choose the bucket */
	int bucket = (int)((a * S) >> 32);
}
