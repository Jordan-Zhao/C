/*
 * Util.h
 *
 *  Created on: 2014年12月23日
 *      Author: zjd
 */

#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_

#include <string>
using namespace std;

namespace ns_talker {

class Util {
public:
	Util();
	virtual ~Util();

	static void sendSocketMessage(int socket,string msg);

	static int receiveSocketMsg(int sock, char* buf);

	static void log(char* info);

	static string Base64Encode(string input);

	static string Base64Decode(string input) ;

	static string subStr(string source,string begin,string end);

	static string itoa(int i);
};


} /* namespace ns_talker */

#endif /* COMMON_UTIL_H_ */
