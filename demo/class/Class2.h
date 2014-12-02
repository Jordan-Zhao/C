/*
 * Class2.h
 *
 *  Created on: 2014年11月25日
 *      Author: zjd
 */

#ifndef CLASS2_H_
#define CLASS2_H_

class Class2 {
	int a;
public:
	Class2();
	/*Class2(Class2 &c2);*/
	virtual ~Class2();

	/**
	 * 值传递
	 */
	Class2 f(Class2 c);

	void setA(int a);
	int getA();
};

#endif /* CLASS2_H_ */
