/*
 * User.h
 *
 *  Created on: 2014年12月22日
 *      Author: zjd
 */

#ifndef BO_USER_H_
#define BO_USER_H_

#include "../common/CommonHeader.h"

using namespace std;

namespace ns_talker {

class User {
public:
	User();
	virtual ~User();

	string getId();
	void setId(string id);

private:
	string id;

};

} /* namespace ns_talker */

#endif /* BO_USER_H_ */
