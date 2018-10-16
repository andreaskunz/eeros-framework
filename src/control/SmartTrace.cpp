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
      template < typename U >
      std::vector<U> SmartTrace<T>::prepareTrace(std::vector<U> & trace) {
	std::vector<U> resultTrace{};
	
	if (cycle) {
	  resultTrace.resize(maxBufferSize); //reserve space for copy w/o back_inserter
	  std::copy(trace.begin()+index, trace.end(), resultTrace.begin()); // begin copy at front
	  std::copy(trace.begin(), trace.begin()+index, resultTrace.end()-index); // begin copy in the middle.
	  
	} else {
	  std::copy(trace.begin(), trace.end(), std::back_inserter(resultTrace)); // copy 1to1.
	}
	
	return resultTrace;
      }
      
      
      template < typename T >
      std::vector<T> SmartTrace<T>::getTrace() {
	return prepareTrace(traceBuffer);
      }
      

      template < typename T >
      std::vector<timestamp_t> SmartTrace<T>::getTimestampTrace() {
	return prepareTrace(timestampBuffer);
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
