/*
 * People.h
 *
 *  Created on: 2014Äê11ÔÂ13ÈÕ
 *      Author: jindong.zjd
 */

#ifndef PEOPLE_H_
#define PEOPLE_H_

class People {
public:
	People();
	virtual ~People();

	public:
		int age;
		char* say(char* words);
};

#endif /* PEOPLE_H_ */
