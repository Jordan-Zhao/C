/*
 * Util.cpp
 *
 *  Created on: 2014年12月4日
 *      Author: zjd
 */

#include "head/Util.h"

#include <string>
#include <stdio.h>

using namespace std;
namespace ns_email {

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

char* Util::encodeBase64(char* s) {
	int nByteSrc = strlen(s);
	std::string pszSource = s;

	int i = 0;
	for (i; i < nByteSrc; i++)
		if (pszSource[i] < 0 || pszSource[i] > 127)
			throw "can not encode Non-ASCII characters";

	const char *enkey =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	std::string pszEncode(nByteSrc * 4 / 3 + 4, '\0');
	int nLoop = nByteSrc % 3 == 0 ? nByteSrc : nByteSrc - 3;
	int n = 0;
	for (i = 0; i < nLoop; i += 3) {
		pszEncode[n] = enkey[pszSource[i] >> 2];
		pszEncode[n + 1] = enkey[((pszSource[i] & 3) << 4)
				| ((pszSource[i + 1] & 0xF0) >> 4)];
		pszEncode[n + 2] = enkey[((pszSource[i + 1] & 0x0f) << 2)
				| ((pszSource[i + 2] & 0xc0) >> 6)];
		pszEncode[n + 3] = enkey[pszSource[i + 2] & 0x3F];
		n += 4;
	}

	switch (nByteSrc % 3) {
	case 0:
		pszEncode[n] = '\0';
		break;

	case 1:
		pszEncode[n] = enkey[pszSource[i] >> 2];
		pszEncode[n + 1] = enkey[((pszSource[i] & 3) << 4) | ((0 & 0xf0) >> 4)];
		pszEncode[n + 2] = '=';
		pszEncode[n + 3] = '=';
		pszEncode[n + 4] = '\0';
		break;

	case 2:
		pszEncode[n] = enkey[pszSource[i] >> 2];
		pszEncode[n + 1] = enkey[((pszSource[i] & 3) << 4)
				| ((pszSource[i + 1] & 0xf0) >> 4)];
		pszEncode[n + 2] = enkey[((pszSource[i + 1] & 0xf) << 2)
				| ((0 & 0xc0) >> 6)];
		pszEncode[n + 3] = '=';
		pszEncode[n + 4] = '\0';
		break;
	}

	return const_cast<char*>(pszEncode.data());
}
char*  Util::decodeBase64(char* s) {
	s = trim(s);
	int nByteSrc = strlen(s);
	std::string pszSource = s;

	const int dekey[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
			62, // '+'
			-1, -1, -1,
			63, // '/'
			52, 53, 54, 55, 56, 57, 58, 59, 60,
			61, // '0'-'9'
			-1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
			25, // 'A'-'Z'
			-1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
			37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
			};

	if (nByteSrc % 4 != 0)
		throw "bad base64 string";

	std::string pszDecode(nByteSrc * 3 / 4 + 4, '\0');
	int nLoop = pszSource[nByteSrc - 1] == '=' ? nByteSrc - 4 : nByteSrc;
	int b[4];
	int i = 0, n = 0;
	for (i = 0; i < nLoop; i += 4) {
		b[0] = dekey[pszSource[i]];
		b[1] = dekey[pszSource[i + 1]];
		b[2] = dekey[pszSource[i + 2]];
		b[3] = dekey[pszSource[i + 3]];
		if (b[0] == -1 || b[1] == -1 || b[2] == -1 || b[3] == -1)
			throw "bad base64 string";

		pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
		pszDecode[n + 1] = ((b[1] & 0xf) << 4) | ((b[2] & 0x3c) >> 2);
		pszDecode[n + 2] = ((b[2] & 0x3) << 6) | b[3];

		n += 3;
	}

	if (pszSource[nByteSrc - 1] == '=' && pszSource[nByteSrc - 2] == '=') {
		b[0] = dekey[pszSource[i]];
		b[1] = dekey[pszSource[i + 1]];
		if (b[0] == -1 || b[1] == -1)
			throw "bad base64 string";

		pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
		pszDecode[n + 1] = '\0';
	}

	if (pszSource[nByteSrc - 1] == '=' && pszSource[nByteSrc - 2] != '=') {
		b[0] = dekey[pszSource[i]];
		b[1] = dekey[pszSource[i + 1]];
		b[2] = dekey[pszSource[i + 2]];
		if (b[0] == -1 || b[1] == -1 || b[2] == -1)
			throw "bad base64 string";

		pszDecode[n] = (b[0] << 2) | ((b[1] & 0x30) >> 4);
		pszDecode[n + 1] = ((b[1] & 0xf) << 4) | ((b[2] & 0x3c) >> 2);
		pszDecode[n + 2] = '\0';
	}

	if (pszSource[nByteSrc - 1] != '=' && pszSource[nByteSrc - 2] != '=')
		pszDecode[n] = '\0';

	return const_cast<char*>(pszDecode.data());
}

char* Util::stringCat(char* s1,char* s2){
	char* s = new char[strlen(s1)+strlen(s2) +1];
	strcpy(s,s1);
	strcat(s,s2);
	return s;
}

char* Util::strSub(char* from, char* start, char* end){
	const char* s1 = strstr(from,start);
	const char* s2 = strstr(s1,end);
	int len = strlen(s1)-strlen(s2)-strlen(start);
	if(len < 0){
		return NULL;
	}
	char* s3 = new char[len];
	memcpy(s3,s1+strlen(start),len);
	return s3;
}

char* Util:: num2str(int n){
	char* str;
	sprintf(str,"%d",n);
	return str;
}
int Util::str2num(char* str){
	int i;
	sscanf(str,"%d",&i);
	return i;
}

char* Util::trim(char* str)
{
	std::string s = str;
    if (s.empty())
    {
        return const_cast<char*>(s.data());
    }
    while(s.find_first_not_of(" ") > 0
    		|| s.find_last_not_of(" ") < s.length() - 1
    		|| s.find_first_not_of("\r") > 0
    		|| s.find_last_not_of("\r") < s.length() - 1
    		|| s.find_first_not_of("\n") > 0
    		|| s.find_last_not_of("\n") < s.length() - 1){
		s.erase(0,s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);

		s.erase(0,s.find_first_not_of("\r"));
		s.erase(s.find_last_not_of("\r") + 1);

		s.erase(0,s.find_first_not_of("\n"));
		s.erase(s.find_last_not_of("\n") + 1);
    }
    char* to = new char[s.length()];
    return strcpy(to,s.data());
}
} /* namespace ns_email */
