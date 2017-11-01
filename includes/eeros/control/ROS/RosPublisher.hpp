#ifndef ORG_EEROS_CONTROL_ROSPUBLISHER_HPP_
#define ORG_EEROS_CONTROL_ROSPUBLISHER_HPP_

#include <ros/ros.h>
#include <ros/callback_queue.h>
// #include <eeros/core/System.hpp>
#include <eeros/control/ROS/EerosRosTools.hpp>
#include <eeros/control/Block1i.hpp>

namespace eeros {
	namespace control {
		template < typename TRosMsg, typename SigInType >
		class RosPublisher : public Block1i<SigInType> {

		public:
			RosPublisher(ros::NodeHandle& rosNodeHandler, const std::string& topic, uint32_t queueSize=1000, bool callNewest=false) :
				rosNodeHandler(rosNodeHandler),
				topic (topic)
// 				callNewest(callNewest)
			{
				publisher = rosNodeHandler.advertise<TRosMsg>(topic, queueSize);
				ROS_DEBUG_STREAM("RosBlockPublisher, reading from topic: '" << topic << "' created.");
			}

			virtual void setRosMsg( TRosMsg& msg ) = 0;
			
			void run() {
				setRosMsg(msg);
				publisher.publish(msg);
			}


		protected:
			//ROS variables
			ros::NodeHandle& rosNodeHandler;
			ros::Publisher publisher;
			const std::string& topic;
// 			bool callNewest;
			TRosMsg msg;

		private:
		};
	}
}

#endif /* ORG_EEROS_CONTROL_ROSPUBLISHER_HPP_ */