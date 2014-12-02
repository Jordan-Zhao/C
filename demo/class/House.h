/*
 * House.h
 *
 *  Created on: 2014年11月21日
 *      Author: zjd
 */

#ifndef HOUSE_H_
#define HOUSE_H_

class House {
	enum{height=101,location=500};
	int number;
public:
	House();
	House(int num);
	virtual ~House();

	int getLocation();
	int getNumber();
};

#endif /* HOUSE_H_ */
