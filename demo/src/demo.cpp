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
#include "../impl/People.h"

using namespace std;

int main() {
	const People* p1 = new People();
//	p1->age = 100;	//±‡“Î±®¥Ì£∫assignment of member 'People::age' in read-only object
//	People p2 = p1;	//±‡“Î±®¥Ì£∫conversion from 'const People*' to non-scalar type 'People' requested
	cout << p1->age<<endl;
}
