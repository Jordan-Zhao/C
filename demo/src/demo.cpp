//============================================================================
// Name        : demo.cpp
// Author      : jordan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "../head/Main.h"
#include "../class/People.h"
#include "../class/House.h"
#include "../class/Class1.h"
#include "../class/Class2.h"
#include "../class/Class3.h"

using namespace std;
using namespace myclass;

int main() {
	Class2 c1;
	Class2 *c2 = new Class2();
	c1.setA(1);
	cout<<c1.getA()<<endl;
	Class2 c3 = c2->f(c1);
	cout<<c3.getA()<<endl;

}
