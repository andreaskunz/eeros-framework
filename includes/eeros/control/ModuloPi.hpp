#ifndef ORG_EEROS_CONTROL_MODULOPI_HPP_
#define ORG_EEROS_CONTROL_MODULOPI_HPP_

#include <eeros/control/Block1i1o.hpp>
#include <cmath>


namespace eeros {
	namespace control {

		/**
		 * A ModuloPi block is used to map an arbitrary angle to an angle in the range of -Pi to +Pi.
		 * 
		 * This is for example usefull, when a direction must be calculated
		 * based on a angle difference.
		 * 
		 * @since v0.6
		 */

		class ModuloPi : public Block1i1o<double> {
			
		public:
			/**
			 * Constructs a default ModuloPi instance with Pi of the value of parameter pi.
			 * 
			 * @param pi - Pi to use in the calculation
			 */
			ModuloPi(double pi) : pi(pi) {}


			/**
			 * Runs the ModuloPi algorithm.
			 * 
			 * Sets the output signal value to the value calculated by the ModuloPi algorithm if
			 * the ModuloPi instance is enabled by enable().
			 */
			virtual void run() {
				if(enabled) {
					double input = this->in.getSignal().getValue();
					double output = input - 2*pi*floor((input+pi)/(2*pi));
					this->out.getSignal().setValue(output);

				} else {
					this->out.getSignal().setValue(this->in.getSignal().getValue());
				}

				this->out.getSignal().setTimestamp(this->in.getSignal().getTimestamp());
			}


			/**
			 * Enables the ModuloPi.
			 * 
			 * If enabled, run() will set the output signal value to the calculated value.
			 */
			virtual void enable() {
				enabled = true;
			}


			/**
			 * Disables the ModuloPi.
			 * 
			 * If disabled, run() will set the output signal value to the input signal value.
			 */
			virtual void disable() {
				enabled = false;
			}


			/*
			 * Friend operator overload to give the operator overload outside 
			 * the class access to the private fields.
			 */
			friend std::ostream& operator<<(std::ostream& os, ModuloPi& moduloPi);


		protected:
			double pi;
			bool enabled{true};
		};


		/**
		 * Operator overload (<<) to enable an easy way to print the state of a
		 * ModuloPi instance to an output stream.\n
		 * Does not print a newline control character.
		 */
		std::ostream& operator<<(std::ostream& os, ModuloPi& moduloPi) {
			os << "Block ModuloPi: '" << moduloPi.getName() << "' is enabled=" << moduloPi.enabled; 
		}
	};
};

#endif /* ORG_EEROS_CONTROL_MODULOPI_HPP_ */
