/*
 * Class3.cpp
 *
 *  Created on: 2014年11月27日
 *      Author: zjd
 */

#include "Class3.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

namespace myclass {

Class3::Class3() {
	// TODO Auto-generated constructor stub

}

Class3::~Class3() {
	// TODO Auto-generated destructor stub
}

void Class3::a(int i){
	cout<<"aaaa"<<i<<endl;
}

void Class3::b(int c){
	cout<<"bbbbb"<<c<<endl;
}

void Class3::c(char * s){
	cout<<"cccccccc"<<s<<endl;
}

void Class3::f(void (Class3::*addr)(int)){
	myclass::Class3 *c3;
	void (myclass::Class3::*f)(int) = addr;
	(c3->*f)(123);
}

} /* namespace myclass */

/**
 * test:通过传递函数地址，执行不同的行为
int main() {
	myclass::Class3 *c3;
	c3->f(&Class3::a);

}

 */
