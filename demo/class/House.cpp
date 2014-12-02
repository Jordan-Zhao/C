/*
 * House.cpp
 *
 *  Created on: 2014年11月21日
 *      Author: zjd
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "House.h"

using namespace std;

House::House(){}
House::House(int num){
	cout<<"创建House。number："<<num<<endl;
	number = num;
}

House::~House() {
	cout<<"销毁 House。number："<<number<<endl;
}



int House::getLocation(){
	return location;
}

int House::getNumber(){
	return number;
}


