#include <eeros/control/SmartTrace.hpp>

#include <vector>
#include <iterator>

namespace eeros {
  namespace control {
    
    template < typename T > 
    SmartTrace<T>::SmartTrace(int maxSize) {
	maxBufferSize = (maxSize < 1) ? 100 : maxSize;
      }
      
      
     template < typename T >
     void SmartTrace<T>::run() {
	  if (running) {
	    if(cycle){
	      traceBuffer.at(index) = this->in.getSignal().getValue();
	      timestampBuffer.at(index) = this->in.getSignal().getTimestamp();
	
	    }else {
	      traceBuffer.push_back(this->in.getSignal().getValue());
	      timestampBuffer.push_back(this->in.getSignal().getTimestamp());
	    }
	      index++;
	  
	  if (index == maxBufferSize) {
	    index = 0;
	    cycle = true;
	  }
	}
      }
      
      
      template < typename T >
      std::vector<T> SmartTrace<T>::getTrace() {
	std::vector<T> trace{};
	
	if (cycle) {
	  trace.resize(maxBufferSize); //reserve space for copy w/o back_inserter
	  std::copy(traceBuffer.begin()+index, traceBuffer.end(), trace.begin()); // begin copy at front
	  std::copy(traceBuffer.begin(), traceBuffer.begin()+index, trace.end()-index); // begin copy in the middle.
	  
	} else {
	  std::copy(traceBuffer.begin(), traceBuffer.end(), std::back_inserter(trace)); // copy 1to1.
	}
	
	return trace;
      }
      
      
      template < typename T >
      int SmartTrace<T>::getLength() {
	return traceBuffer.size();
      }
      
      
      template < typename T >
      void SmartTrace<T>::enable() {
	running = true;
      }
      
      
      template < typename T >
      void SmartTrace<T>::disable() {
	running = false;
      }
  };
};