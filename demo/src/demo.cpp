//============================================================================
// Name        : demo.cpp
// Author      : jordan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <exception>
#include <unistd.h>

#include "../head/Main.h"
#include "../class/People.h"
#include "../class/House.h"
#include "../class/Class1.h"
#include "../class/Class2.h"
#include "../class/Class3.h"
#include "../class/Class4.h"
#include "../class/Class5.h"
#include "../class/Class6.h"
#include "../class/Class7.h"
#include "../class/Class8.h"
#include "../class/Class10.h"
#include "../class/Class11.h"
#include "../class/Class12.h"

using namespace std;
using namespace myclass;

char* strCut( char* from, char* start, char* end);


class A{
private:
	int i;
public :
	explicit A(int b){
		i = b;
}
	~A(){}
};


void pa(A a){
	cout<<"qqqqqqq"<<endl;
}

char* strCut(char* from, char* start, char* end){
	const char* s1 = strstr(from,start);
	const char* s2 = strstr(s1,end);
	int len = strlen(s1)-strlen(s2)-strlen(start);
	if(len < 0){
		return NULL;
	}
	char* s3 = new char[len];
	memcpy(s3,s1+strlen(start),len);
	return s3;
}

void test(){
//	Class9 c9;
	Class8 c8;
//	c8.c9 = &c9;
}

int main() {
//	Class7 c7;
//	Class6<Class7> c6;
//	c6.dosome(c7);
//	cout<<string("zzz").data()<<endl;

//	string s("hello world");
//	cout<<s.find("wo")<<endl;
//	cout<<s.substr(0,2)<<endl;

//	string s;
//	cout<<s.size()<<endl;

	Class10 c10;
	cout<<sizeof(c10)<<endl;

	Class10* c = new Class10();
	cout<<sizeof(c)<<endl;

	Class10& c1 = c10;
	cout<<sizeof(c1)<<endl;

	cout<<sizeof(int)<<endl;
//	Class11 c11;
//	c11.a = 1;
//	Class11 c2 = c11;
//	std::cout<<c2.a<<std::endl;
//	Class11 c3;
//	c3.a = 20;
//	c3 = c11;
//	std::cout<<c3.a<<std::endl;

//Class12 c12;
//c12.test();
}


