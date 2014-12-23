/*
 * Class5.h
 *
 *  Created on: 2014年12月21日
 *      Author: zjd
 */

#include "Class4.h"

#ifndef CLASS5_H_
#define CLASS5_H_

class Class5:public Class4{
public:
	Class5();
	virtual ~Class5();

	void draw();
	void error();
	int getObjectId();
};

#endif /* CLASS5_H_ */
