#include<stdio.h>

struct Brick {
	int x;
	int *y;
};

class Test {

	int *a;  // this is an array
	struct Brick *b;
public:

	Test() {
		init();
	}

	void init(){
		this->a =new int[10];
		this->b =new Brick[10];
		for(int i = 1; i< 10; i++){
			this->b[i].y=new int[5];
		}
	}

	~Test() {
		for(int i = 1; i< 10; i++){
			delete[] this->b[i].y;
		}
		
		delete[] this->b;
		delete[] this->a;
	}
};

// new comment 
int main(int argv, char** argc){

	Test *t = new Test();
	delete[] t;
	
}
