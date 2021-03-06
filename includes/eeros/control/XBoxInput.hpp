#ifndef ORG_EEROS_CONTROL_XBOXINPUT_HPP_
#define ORG_EEROS_CONTROL_XBOXINPUT_HPP_

#include <string>
#include <thread>
#include <eeros/control/Block1o.hpp>
#include <eeros/core/System.hpp>
#include <eeros/hal/XBox.hpp>
#include <eeros/math/Matrix.hpp>

using namespace eeros::math;
using namespace eeros::hal;

namespace eeros {
	namespace control {

		class XBoxInput: public Block1o<Matrix<XBOX_AXIS_COUNT>> {
		public:
			XBoxInput(std::string dev, int priority = 20);
			virtual ~XBoxInput();
			
			virtual void run();
			virtual void setInitPos(Matrix<XBOX_AXIS_COUNT> initPos);
			virtual void setSpeedScaleFactor(double speedScale);
			Output<Matrix<XBOX_BUTTON_COUNT,1,bool>>& getButtonOut();
			
			inline void on_button(std::function<void(int, bool)> &&action) {
				x.on_button(std::move(action));
			}
			
			double speedScaleFactor = 1.0;

			double xScale = 0.0001;
			double yScale = 0.0001;
			double zScale = 0.0001;
			double rScale = 0.002;
			double min_x = -0.03;
			double max_x = 0.045;
			double min_y = -0.03;
			double max_y = 0.03;
			double min_z = -0.053;
			double max_z = -0.015;
			double min_r = -2.8;
			double max_r = 2.8;

		protected:
            XBox x;
			Output<Matrix<XBOX_BUTTON_COUNT,1,bool>> buttonOut;
			Matrix<4,4,double> axisScale;
		};

	};
};

#endif /* ORG_EEROS_CONTROL_XBOXINPUT_HPP_ */
