//============================================================================
// Name        : demo.cpp
// Author      : jordan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <exception>

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


int main() {
//	Class7 c7;
//	Class6<Class7> c6;
//	c6.dosome(c7);
//	cout<<string("zzz").data()<<endl;

//	string s("hello world");
//	cout<<s.find("wo")<<endl;
//	cout<<s.substr(0,2)<<endl;

	string s1("abc");
	string s2("abc");
	if(s1==s2){
		cout<<"cccccc"+1+s1+s2+"sdfsaf"<<endl;
	}

}
