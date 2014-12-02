/*
 * Class2.cpp
 *
 *  Created on: 2014年11月25日
 *      Author: zjd
 */

#include "Class2.h"
#include <iostream>

using namespace std;

Class2::Class2() {
	a=2;
	cout<<"创建Class2.原构造函数"<<endl;

}

Class2::~Class2() {
	cout<<"destroy Class2"<<endl;
}

/*Class2::Class2(Class2 &c){
	cout<<"创建Class2.拷贝构造"<<endl;
}*/

Class2 Class2::f(Class2 c){
	cout<<c.getA()<<endl;
	c.setA(10);
	cout<<"invoke f()"<<endl;
	return c;
}

void Class2::setA(int a){
	this->a=a;
}
int Class2::getA(){
	return a;
}



