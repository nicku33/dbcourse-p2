#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

struct Brick {
	int x;
	int *y;
};

class Test {
private:
	int *a;  // this is an array
	struct Brick *b;
	int size;

	static void log(string s){
		cout << s <<  endl;	
	}
public:

	Test(int size) {
		this->size = size;
		init();
	}

	void init(){
		cerr << "Entering init\n";
		this->a =new int[this->size];
		this->b =new Brick[this->size];
		for(int i = 0; i< size; i++){
			cerr << "making brick" << i << "\n";
			this->b[i].x=i;
			this->b[i].y=new int[5];
		}
	}

	~Test() {
		int sz=10;
		cerr << "Entering destructor\n";
		for(int i = 0; i< 10; i++){
			cerr << "deleting brick " << i << "\n";
			delete[] this->b[i].y;
		}
		
		delete this->b;
		delete[] this->a;
	}
};

// new comment 
int main(int argv, char** argc){

	Test *t = new Test();
	delete t;
	
}
