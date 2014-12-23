/*
 * Class6.h
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */


#ifndef CLASS6_H_
#define CLASS6_H_

#include "Class7.h"
#include <iostream>
#include <stdio.h>
#include <iostream>

using namespace std;

template<class T>
class Class6 {
public:
	Class6();
	virtual ~Class6();

	void dosome(T& t);

};


template<class T> Class6<T>::Class6() {
	// TODO Auto-generated constructor stub

}

template<class T> Class6<T>::~Class6() {
	// TODO Auto-generated destructor stub
}

template<class T> void Class6<T>::dosome(T& t){
	cout<<t.say()<<endl;
}

#endif /* CLASS6_H_ */
