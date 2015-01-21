/*
 * Class12.cpp
 *
 *  Created on: 2015年1月19日
 *      Author: zjd
 */

#include "Class12.h"

#include <iostream>
#include <pthread.h>
#include <fstream>
#include <unistd.h>

using namespace std;

Class12::Class12() {
	// TODO Auto-generated constructor stub

}

Class12::~Class12() {
	// TODO Auto-generated destructor stub
}

int d[2];

void * take(void *)
{
	char buffer[100];
	read(d[0],buffer,100);
	cout << "get data "<< buffer <<endl;

	return NULL;
}

void * put(void *)
{
	write(d[1],"hello pipe!",20);
	cout << "write data " <<endl;

	return NULL;
}

void Class12::test(){
	void* ret;
	pthread_t customer,producer;
	pipe(d);

	pthread_create(&customer, NULL, take, NULL);

	sleep(2);

	pthread_create(&producer, NULL, put, NULL);

	pthread_join(customer, &ret);
	pthread_join(producer, &ret);

}

