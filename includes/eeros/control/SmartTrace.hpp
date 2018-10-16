#ifndef ORG_EEROS_CONTROL_SMARTTRACE_HPP_
#define ORG_EEROS_CONTROL_SMARTTRACE_HPP_

#include <vector>
#include <iterator>
#include <eeros/control/Block1i.hpp>

namespace eeros {
  namespace control {
    
    template < typename T = double>
    class SmartTrace : public Block1i<T> {
    public:
      SmartTrace(int maxSize = 100);
           
      void run();
      
      std::vector<T> getTrace();
      
      
      
  /*    
      virtual timestamp_t* getTimestampTrace() {
	if (cycle) {
	  size = maxBufLen;
	  timestamp_t* tmp = new timestamp_t[maxBufLen];
	  for (int i = 0; i < maxBufLen; i++)
	    tmp[i] = timeBuf[(i + index) % maxBufLen];
	  return tmp;
	} else {
	  size = index;
	  timestamp_t* tmp = new timestamp_t[index];
	  for (int i = 0; i < index; i++)
	    tmp[i] = timeBuf[i];
	  return tmp;
	}
      }
      */
      int getLength();
      
      void enable();
      
      void disable();
      
      
    protected:
      int maxBufferSize;
      int index{0};
      bool cycle{false}; // indicates whether wrap around occured
      bool running{false};
      std::vector<T> traceBuffer{};
      std::vector<timestamp_t> timestampBuffer{};
    };
    
    
    
    /********** Print functions *********
    template <typename T>
    std::ostream& operator<<(std::ostream& os, Trace<T>& trace) {
      os << "Block trace: '" << trace.getName() << "'"; 
    }
    */
  };
};
#endif /* ORG_EEROS_CONTROL_SMARTTRACE_HPP_ */
