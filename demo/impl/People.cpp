/*
 * People.cpp
 *
 *  Created on: 2014Äê11ÔÂ13ÈÕ
 *      Author: jindong.zjd
 */

#include "People.h"
#include <string.h>

People::People() {
	// TODO Auto-generated constructor stub

}

People::~People() {
	// TODO Auto-generated destructor stub
}

char* People::say(char* words){
	return strcat("hello",words);
}
