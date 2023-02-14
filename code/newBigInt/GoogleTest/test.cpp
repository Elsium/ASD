#include "pch.h"
#include "../BigIntLib/BigInt.h"

TEST(Constructor, Test1) {
	EXPECT_EQ(BigInt("100"),
		BigInt(100));
}
TEST(Constructor, Test2) {
	EXPECT_EQ(BigInt(),
		BigInt(0));
}
TEST(Constructor, Test3) {
	EXPECT_EQ(BigInt(),
		BigInt("0"));
}

TEST(SumTest, Test1) {
	EXPECT_EQ(BigInt(10) + BigInt(90),
		BigInt(100));
}
TEST(SumTest, Test2) {
	EXPECT_EQ(BigInt(22222) + BigInt(33333),
		BigInt(55555));
}
TEST(SumTest, Test3) {
	EXPECT_EQ(BigInt(100) + BigInt(-3),
		BigInt(97));
}
TEST(SumTest, Test4) {
	EXPECT_EQ(BigInt(0) + BigInt(0),
		BigInt(0));
}
TEST(SumTest, Test5) {
	EXPECT_EQ(BigInt(0) + BigInt(11),
		BigInt(11));
}
TEST(SumTest, Test6) {
	EXPECT_EQ(BigInt(33) + BigInt(0),
		BigInt(33));
}
TEST(SumTest, Test7) {
	EXPECT_EQ(BigInt(2) + BigInt(20),
		BigInt(22));
}
TEST(SumTest, Test8) {
	EXPECT_EQ(BigInt(20) + BigInt(2),
		BigInt(22));
}
TEST(SumTest, Test9) {
	EXPECT_EQ(BigInt(19) + BigInt(1),
		BigInt(20));
}
TEST(SumTest, Test10) {
	EXPECT_EQ(BigInt(19) + 1,
		BigInt(20));
}
TEST(SumTest, Test11) {
	EXPECT_EQ(BigInt(5) + 2,
		BigInt(7));
}
TEST(SumTest, Test12) {
	EXPECT_EQ(BigInt(1111111) + BigInt(1999999),
		BigInt(3111110));
}

TEST(SubTest, Test1) {
	EXPECT_EQ(BigInt(100) - BigInt(50),
		BigInt(50));
}
TEST(SubTest, Test2) {
	EXPECT_EQ(BigInt(10) - BigInt(-10),
		BigInt(20));
}
TEST(SubTest, Test3) {
	EXPECT_EQ(BigInt(-10) - BigInt(-10),
		BigInt(0));
}
TEST(SubTest, Test4) {
	EXPECT_EQ(BigInt(-10) - BigInt(10),
		BigInt(-20));
}
TEST(SubTest, Test5) {
	EXPECT_EQ(BigInt(-10) - BigInt(0),
		BigInt(-10));
}
TEST(SubTest, Test6) {
	EXPECT_EQ(BigInt(20) - BigInt(2),
		BigInt(18));
}
TEST(SubTest, Test7) {
	EXPECT_EQ(BigInt(2) - BigInt(20),
		BigInt(-18));
}
TEST(SubTest, Test8) {
	EXPECT_EQ(BigInt(1000) - BigInt(10),
		BigInt(990));
}

TEST(MulTest, Test1) {
	EXPECT_EQ(BigInt(10) * BigInt(10),
		BigInt(100));
}
TEST(MulTest, Test2) {
	EXPECT_EQ(BigInt(20) * BigInt(30),
		BigInt(600));
}
TEST(MulTest, Test3) {
	EXPECT_EQ(BigInt(50) * BigInt(-10),
		BigInt(-500));
}
TEST(MulTest, Test4) {
	EXPECT_EQ(BigInt(-30) * BigInt(100),
		BigInt(-3000));
}
TEST(MulTest, Test5) {
	EXPECT_EQ(BigInt(-3000) * BigInt(-2),
		BigInt(6000));
}
TEST(MulTest, Test6) {
	EXPECT_EQ(BigInt(-3111) * BigInt(-2),
		BigInt(6222));
}
TEST(MulTest, Test7) {
	EXPECT_EQ(BigInt(37) * BigInt(76),
		BigInt(2812));
}
TEST(MulTest, Test8) {
	EXPECT_EQ(BigInt("11111111111111111111111111111111") * BigInt(3),
		BigInt("33333333333333333333333333333333"));
}
TEST(MulTest, Test9) {
	EXPECT_EQ(BigInt("11111111111111111111111111111111") * BigInt(100000),
		BigInt("1111111111111111111111111111111100000"));
}

TEST(DivTest, Test1) {
	EXPECT_EQ(BigInt(1000) / BigInt(10),
		BigInt(100));
}
TEST(DivTest, Test2) {
	EXPECT_EQ(BigInt(1000) / BigInt(1000),
		BigInt(1));
}
TEST(DivTest, Test3) {
	EXPECT_EQ(BigInt(12) / BigInt(10),
		BigInt(1));
}
TEST(DivTest, Test4) {
	EXPECT_EQ(BigInt(20) / BigInt(6),
		BigInt(3));
}
TEST(DivTest, Test5) {
	EXPECT_EQ(BigInt(100) / BigInt(1),
		BigInt(100));
}
TEST(DivTest, Test6) {
	EXPECT_EQ(BigInt(300) / BigInt(3),
		BigInt(100));
}
TEST(DivTest, Test7) {
	EXPECT_EQ(BigInt(700) / BigInt(5),
		BigInt(140));
}

TEST(ModTest, Test1) {
	EXPECT_EQ(BigInt(10) % BigInt(3),
		BigInt(1));
}
TEST(ModTest, Test2) {
	EXPECT_EQ(BigInt(12) % BigInt(3),
		BigInt(0));
}
TEST(ModTest, Test3) {
	EXPECT_EQ(BigInt(55) % BigInt(10),
		BigInt(5));
}
TEST(ModTest, Test4) {
	EXPECT_EQ(BigInt(9) % BigInt(10),
		BigInt(9));
}
TEST(ModTest, Test5) {
	EXPECT_EQ(BigInt(460) % BigInt(360),
		BigInt(100));
}
TEST(ModTest, Test6) {
	EXPECT_EQ(BigInt(7655) % BigInt(91),
		BigInt(11));
}

TEST(PowTest, Test1) {
	EXPECT_EQ(BigInt::pow(BigInt(2), BigInt(2)),
		BigInt(4));
}
TEST(PowTest, Test2) {
	EXPECT_EQ(BigInt::pow(BigInt(10), BigInt(10)),
		BigInt(10000000000));
}
TEST(PowTest, Test3) {
	EXPECT_EQ(BigInt::pow(BigInt(7), BigInt(0)),
		BigInt(1));
}
TEST(PowTest, Test4) {
	EXPECT_EQ(BigInt::pow(BigInt(0), BigInt(2)),
		BigInt(0));
}
TEST(PowTest, Test5) {
	EXPECT_EQ(BigInt::pow(BigInt(-5), BigInt(2)),
		BigInt(25));
}
TEST(PowTest, Test6) {
	EXPECT_EQ(BigInt::pow(BigInt(-5), BigInt(3)),
		BigInt(-125));
}

TEST(MoreTest, Test1) {
	EXPECT_TRUE(BigInt(1000) > BigInt(2));
}
TEST(MoreTest, Test2) {
	EXPECT_TRUE(BigInt(44) > BigInt(43));
}
TEST(MoreTest, Test3) {
	EXPECT_FALSE(BigInt(88) > BigInt(100));
}

TEST(LessTest, Test1) {
	EXPECT_TRUE(BigInt(1000) < BigInt(1001));
}
TEST(LessTest, Test2) {
	EXPECT_TRUE(BigInt(777) < BigInt(800));
}
TEST(LessTest, Test3) {
	EXPECT_FALSE(BigInt(7) < BigInt(7));
}
TEST(LessTest, Test4) {
	EXPECT_TRUE(BigInt(-7) < BigInt(7));
}
TEST(LessTest, Test5) {
	EXPECT_TRUE(BigInt(10) < BigInt(100));
}
TEST(LessTest, Test6) {
	EXPECT_TRUE(BigInt(-8) < BigInt(-3));
}

TEST(EqualTest, Test1) {
	EXPECT_TRUE(BigInt(0) == BigInt(0));
}
TEST(EqualTest, Test2) {
	EXPECT_TRUE(BigInt(0) == BigInt(-0));
}
TEST(EqualTest, Test3) {
	EXPECT_TRUE(BigInt(-0) == BigInt(-0));
}
TEST(EqualTest, Test4) {
	EXPECT_TRUE(BigInt(-1) == BigInt(-1));
}
TEST(EqualTest, Test5) {
	EXPECT_TRUE(BigInt(70) == 70);
}
TEST(EqualTest, Test6) {
	EXPECT_FALSE(BigInt(3) == BigInt(7));
}
TEST(EqualTest, Test7) {
	EXPECT_FALSE(BigInt(0) == 22);
}

TEST(UnEqualTest, Test1) {
	EXPECT_TRUE(BigInt(10) != BigInt(0));
}
TEST(UnEqualTest, Test2) {
	EXPECT_TRUE(BigInt(22) != BigInt(2));
}
TEST(UnEqualTest, Test3) {
	EXPECT_TRUE(BigInt(30) != BigInt(3));
}
TEST(UnEqualTest, Test4) {
	EXPECT_FALSE(BigInt(10) != BigInt(10));
}
TEST(UnEqualTest, Test5) {
	EXPECT_FALSE(BigInt(0) != BigInt(0));
}

TEST(MoreEqualTest, Test1) {
	EXPECT_TRUE(BigInt(666) >= BigInt(666));
}
TEST(MoreEqualTest, Test2) {
	EXPECT_TRUE(BigInt(668) >= BigInt(666));
}
TEST(MoreEqualTest, Test3) {
	EXPECT_FALSE(BigInt(660) >= BigInt(663));
}

TEST(LessEqualTest, Test1) {
	EXPECT_TRUE(BigInt(666) <= BigInt(666));
}
TEST(LessEqualTest, Test2) {
	EXPECT_TRUE(BigInt(633) <= 660);
}
TEST(LessEqualTest, Test3) {
	EXPECT_FALSE(BigInt(700) <= BigInt(400));
}

TEST(DotStringTest, Test1) {
	EXPECT_EQ(BigInt::toString(BigInt(0)),
		std::string("0"));
}
TEST(DotStringTest, Test2) {
	EXPECT_FALSE(BigInt::toString(BigInt(0)) == std::string("-0"));
}
TEST(DotStringTest, Test3) {
	EXPECT_EQ(BigInt::toString(BigInt(-0)),
		std::string("0"));
}
TEST(DotStringTest, Test4) {
	EXPECT_EQ(BigInt::toString(BigInt(-50)),
		std::string("-50"));
}
TEST(DotStringTest, Test5) {
	EXPECT_EQ(BigInt::toString(BigInt(-12300)),
		std::string("-12300"));
}

TEST(isOddTest, Test1) {
	EXPECT_TRUE(BigInt::_isOdd(BigInt("00001")));
}
TEST(isOddTest, Test2) {
	EXPECT_FALSE(BigInt::_isOdd(BigInt("20")));
}