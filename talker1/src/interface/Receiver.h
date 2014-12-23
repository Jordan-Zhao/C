/*
 * Receiver.h
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */

#ifndef INTERFACE_RECEIVER_H_
#define INTERFACE_RECEIVER_H_

#include "../common/CommonHeader.h"
#include "../bo/Message.h"
#include "../bo/User.h"

using namespace std;

namespace ns_talker {

class Receiver {
public:
	Receiver();
	virtual ~Receiver();

	virtual void init(User& me)  = 0;
	virtual Message receive() = 0;
};

} /* namespace ns_talker */

#endif /* INTERFACE_RECEIVER_H_ */
