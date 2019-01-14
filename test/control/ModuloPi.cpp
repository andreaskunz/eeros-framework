#include <eeros/control/ModuloPi.hpp>
#include <eeros/control/Constant.hpp>

#include <gtest/gtest.h>


using namespace eeros;
using namespace eeros::control;


TEST(ModuloPiUnitTest, basicPositiveTest) {
	constexpr double pi = 3.141593;

	ModuloPi mp{pi};
	Constant<> c1{1.0};

	mp.getIn().connect(c1.getOut());
	c1.run();

	for(int i = 1; i < 401; i++) {
	  double input = i * 0.05;
	  double result = input - 2*pi*floor((input+pi)/(2*pi));

	  c1.setValue(input);
	  c1.run();
	  mp.run();

	  EXPECT_DOUBLE_EQ (mp.getOut().getSignal().getValue(), result);
	}
}


TEST(ModuloPiUnitTest, basicNegativeTest) {
	constexpr double pi = 3.142;

	ModuloPi mp{pi};
	Constant<> c1{1.0};

	mp.getIn().connect(c1.getOut());
	c1.run();

	for(int i = 1; i < 401; i++) {
	  double input = i * -0.05;
	  double result = input - 2*pi*floor((input+pi)/(2*pi));

	  c1.setValue(input);
	  c1.run();
	  mp.run();

	  EXPECT_DOUBLE_EQ (mp.getOut().getSignal().getValue(), result);
	}
}
