/*
 * E126Receiver.h
 *
 *  Created on: 2014年12月23日
 *      Author: zjd
 */

#ifndef COMPS_EMAIL_E126RECEIVER_H_
#define COMPS_EMAIL_E126RECEIVER_H_

#include "../../common/CommonHeader.h"
#include "../../interface/Receiver.h"
#include "../../bo/User.h"
#include "../../bo/Message.h"

using namespace std;

namespace ns_talker {

class E126Receiver :public Receiver{
public:
	E126Receiver();
	virtual ~E126Receiver();

	void init(User& me);
	Message receive();

private:
	User* me;
};

} /* namespace ns_talker */

#endif /* COMPS_EMAIL_E126RECEIVER_H_ */
