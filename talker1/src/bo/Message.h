/*
 * Message.h
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */

#ifndef BO_MESSAGE_H_
#define BO_MESSAGE_H_

#include "../common/CommonHeader.h"

using namespace std;
namespace ns_talker {

class Message {
public:
	Message();
	virtual ~Message();

	string getContent();
	void setContent(string cnt);

private:
	string content;
};

} /* namespace ns_talker */

#endif /* BO_MESSAGE_H_ */
