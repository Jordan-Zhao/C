/*
 * TalkWindow.h
 *
 *  Created on: 2014年12月9日
 *      Author: zjd
 */

#ifndef TALKWINDOW_H_
#define TALKWINDOW_H_

namespace ns_email {

class TalkWindow {
public:
	TalkWindow();
	virtual ~TalkWindow();

	void start();

private:
	char* myName = new char[30];
	char* friendName = new char[30];

	void startTalk();
};

} /* namespace ns_email */

#endif /* TALKWINDOW_H_ */
