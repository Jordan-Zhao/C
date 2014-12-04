/*
 * Util.h
 *
 *  Created on: 2014年12月4日
 *      Author: zjd
 */

#ifndef EMAIL_UTIL_H_
#define EMAIL_UTIL_H_

#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;
namespace ns_email {

class Util {
public:
	Util();
	virtual ~Util();

	char*  encodeBase64(char* s);
	char*  decodeBase64(char* s);

	char* stringCat(char* s1,char* s2);
};

} /* namespace ns_email */

#endif /* EMAIL_UTIL_H_ */
