/*
 * EmailReceiver.h
 *
 *  Created on: 2014年12月5日
 *      Author: zjd
 */

#ifndef EMAIL_EMAILRECEIVER_H_
#define EMAIL_EMAILRECEIVER_H_

namespace ns_email {

struct EmailContent{
	char* from;
	char* subject;
	char* content;
};

class EmailReceiver {
public:
	EmailReceiver();
	virtual ~EmailReceiver();

	virtual EmailContent* receiveMsg() = 0;
};

} /* namespace ns_email */

#endif /* EMAIL_EMAILRECEIVER_H_ */
