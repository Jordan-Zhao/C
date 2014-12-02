/*
 * Class3.h
 *
 *  Created on: 2014年11月27日
 *      Author: zjd
 */

#ifndef CLASS3_H_
#define CLASS3_H_

namespace myclass {

class Class3 {
public:
	Class3();
	virtual ~Class3();

	void a(int i);
	void b(int c);
	void c(char * s);

	void f(void (Class3::*addr)(int));
};

} /* namespace myclass */

#endif /* CLASS3_H_ */
