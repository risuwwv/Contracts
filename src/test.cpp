//
// Copyright (c) 2016, RISUWWV (https://github.com/risuwwv). All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <cmath>
#include <iostream>

#include "contracts.h"

using std::cout;
using std::endl;

float checkedSqrt(float x)
{
	float res = 0;

	PRE_CONDITION(x >= 0);//exclude negative numbers
	POST_CONDITION( (fabs(x - res*res) <= ((fabs(x) < fabs(res*res) ? fabs(res*res) : fabs(x)) * 0.001)));//from Knuth

	if(x == 0.0)//in general: some special case
	{
		res = x;
		return res;
	}
	
	//in general: some clever implementation
	res = sqrt(x);
	
	return res;
}

int main()
{
	float res = checkedSqrt(10.0);
	cout << "sqrt(10) " << res << endl;
	
	res = checkedSqrt(-10.0); //PRE_CONDITION "x >= 0" is false at runtime if compiled with checks
	cout << "sqrt(-10) " << res << endl;

	return 0;
}
