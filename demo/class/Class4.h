/*
 * Class4.h
 *
 *  Created on: 2014年12月18日
 *      Author: zjd
 */

#ifndef CLASS4_H_
#define CLASS4_H_


class Class4 {
public:
	Class4();
	Class4(int age);
	virtual ~Class4();

	virtual void draw()=0;
	virtual void error();
	int getObjectId();

	int getA();
private:
 int b;
};


#endif /* CLASS4_H_ */
