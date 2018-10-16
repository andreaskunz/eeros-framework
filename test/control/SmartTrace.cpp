#include <eeros/control/SmartTrace.hpp>
#include "../../../src/control/SmartTrace.cpp" // needed by linker
#include <eeros/control/Constant.hpp>

#include <gtest/gtest.h>

using namespace eeros;
using namespace eeros::control;

TEST(SmartTraceUnitTest, runAndGetLengthMethod) {
	SmartTrace<> st{4};
	Constant<double> c1{1.0};
	EXPECT_EQ(st.getLength(), 0);
	
	st.getIn().connect(c1.getOut());
	st.run(); // 1st run with disabled trace.	
	EXPECT_EQ(st.getLength(), 0);
	
	st.enable();
	
	st.run(); // 1st run	
	EXPECT_EQ(st.getLength(), 1);
	
	st.run(); // 2nd run
	EXPECT_EQ(st.getLength(), 2);
	
	st.run(); // 3rd run
	st.run(); // 4th run
	EXPECT_EQ(st.getLength(), 4);
	
	st.run(); // 5th run
	EXPECT_EQ(st.getLength(), 4);
	
	st.run(); // 6th run
	EXPECT_EQ(st.getLength(), 4);
}

TEST(SmartTraceUnitTest, getTraceMethodUncicled) {
	SmartTrace<> st{4};
	Constant<double> c1{1.0};
	
	st.enable();
	st.getIn().connect(c1.getOut());
	c1.run();
	st.run(); // 1st run	
	c1.setValue(2.2);
	c1.run();
	st.run(); // 2nd run
	c1.setValue(3.3);
	c1.run();
	st.run(); // 3rd run
	
	std::vector<double> resTrace{st.getTrace()};
	EXPECT_DOUBLE_EQ (resTrace.at(0), 1.0); 
	EXPECT_DOUBLE_EQ (resTrace.at(1), 2.2);
	EXPECT_DOUBLE_EQ (resTrace.at(2), 3.3);
}

TEST(SmartTraceUnitTest, getTraceMethodCicled1) {
	SmartTrace<> st{4};
	Constant<double> c1{1.0};
	
	st.enable();
	st.getIn().connect(c1.getOut());
	c1.run();
	st.run(); // 1st run	
	c1.setValue(2.2);
	c1.run();
	st.run(); // 2nd run
	c1.setValue(3.3);
	c1.run();
	st.run(); // 3rd run
	c1.setValue(4.4);
	c1.run();
	st.run(); // 4th run
	
	std::vector<double> resTrace{st.getTrace()};
	EXPECT_DOUBLE_EQ (resTrace.at(0), 1.0); 
	EXPECT_DOUBLE_EQ (resTrace.at(1), 2.2);
	EXPECT_DOUBLE_EQ (resTrace.at(2), 3.3);
	EXPECT_DOUBLE_EQ (resTrace.at(3), 4.4);
	

	c1.setValue(5.5);
	c1.run();
	st.run(); // 5th run
	resTrace = st.getTrace();
	EXPECT_DOUBLE_EQ (resTrace.at(0), 2.2);
	EXPECT_DOUBLE_EQ (resTrace.at(1), 3.3);
	EXPECT_DOUBLE_EQ (resTrace.at(2), 4.4);
	EXPECT_DOUBLE_EQ (resTrace.at(3), 5.5);
}


TEST(SmartTraceUnitTest, getTraceMethodCicled2) {
	SmartTrace<> st{4};
	Constant<double> c1{1.0};
	
	st.enable();
	st.getIn().connect(c1.getOut());
	c1.run();
	st.run(); // 1st run	
	c1.setValue(2.2);
	c1.run();
	st.run(); // 2nd run
	c1.setValue(3.3);
	c1.run();
	st.run(); // 3rd run
	c1.setValue(4.4);
	c1.run();
	st.run(); // 4th run
	c1.setValue(5.5);
	c1.run();
	st.run(); // 5th run
	c1.setValue(6.6);
	c1.run();
	st.run(); // 6th run
	
	std::vector<double> resTrace{st.getTrace()};
	EXPECT_DOUBLE_EQ (resTrace.at(0), 3.3); 
	EXPECT_DOUBLE_EQ (resTrace.at(1), 4.4);
	EXPECT_DOUBLE_EQ (resTrace.at(2), 5.5);
	EXPECT_DOUBLE_EQ (resTrace.at(3), 6.6);
}

TEST(SmartTraceUnitTest, getTraceMethodCicled3) {
	SmartTrace<> st{4};
	Constant<double> c1{1.0};
	
	st.enable();
	st.getIn().connect(c1.getOut());
	c1.run();
	st.run(); // 1st run	
	c1.setValue(2.2);
	c1.run();
	st.run(); // 2nd run
	c1.setValue(3.3);
	c1.run();
	st.run(); // 3rd run
	c1.setValue(4.4);
	c1.run();
	st.run(); // 4th run
	c1.setValue(5.5);
	c1.run();
	st.run(); // 5th run
	c1.setValue(6.6);
	c1.run();
	st.run(); // 6th run
	c1.setValue(7.7);
	c1.run();
	st.run(); // 7th run
	c1.setValue(8.8);
	c1.run();
	st.run(); // 8th run
	
	std::vector<double> resTrace{st.getTrace()};
	EXPECT_DOUBLE_EQ (resTrace.at(0), 5.5); 
	EXPECT_DOUBLE_EQ (resTrace.at(1), 6.6);
	EXPECT_DOUBLE_EQ (resTrace.at(2), 7.7);
	EXPECT_DOUBLE_EQ (resTrace.at(3), 8.8);
}