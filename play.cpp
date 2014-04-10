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

	static void log(string s){
		cout << s <<  endl;	
	}
public:

	Test() {
		init();
	}

	void init(){
		cerr << "Entering init\n";
		this->a =new int[10];
		this->b =new Brick[10];
		for(int i = 0; i< 10; i++){
			cerr << "making brick" << i << "\n";
			this->b[i].x=i;
			this->b[i].y=new int[5];
		}
	}

	~Test() {
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
