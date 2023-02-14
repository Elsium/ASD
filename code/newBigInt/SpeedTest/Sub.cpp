#include "pch.h"
#include <iostream>
#include "../BigIntLib/BigInt.h"

BigInt a, b, c;
std::string subF(100001, '8'), subS(100000, '9'), subR(99999, '8'), subAF(100000, '8'), subAS(100000, '9'), subAR(100000, '8');

TEST(SpeedTest, TestSum1) {
	a = subF;
	b = subS;
	c = "7" + subR + "9";
	subF += subAF;
	subS += subAS;
	subR += subAR;
	EXPECT_EQ(a - b, c);
	std::cout << "number length: " << subF.length() << "\n";
}