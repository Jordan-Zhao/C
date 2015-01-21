/*
 * Class11.cpp
 *
 *  Created on: 2015年1月9日
 *      Author: zjd
 */

#include "Class11.h"
#include <stdio.h>
#include <iostream>

Class11::Class11() {
	std::cout<<"构造 c11"<<std::endl;

}

Class11::~Class11() {
	std::cout<<"析构 c11"<<std::endl;
}

Class11::Class11(Class11& c){
	std::cout<<"拷贝 c11"<<std::endl;
}

//Class11& Class11::operator=(Class11& c){
//	std::cout<<"赋值 c11"<<std::endl;
//	return c;
//}
