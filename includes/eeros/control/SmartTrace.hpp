#ifndef ORG_EEROS_CONTROL_SMARTTRACE_HPP_
#define ORG_EEROS_CONTROL_SMARTTRACE_HPP_

#include <vector>
#include <iterator>
#include <eeros/control/Block1i.hpp>

namespace eeros {
  namespace control {
    
    template < typename T = double >
    class SmartTrace : public Block1i<T> {
    public:
      SmartTrace(int maxSize = 100);
           
      void run();
      std::vector<T> getTrace();
      std::vector<timestamp_t> getTimestampTrace();
      
      int getLength();
      void enable();
      void disable();
      
      
    protected:
      template < typename U >
      std::vector<U> prepareTrace(std::vector<U> & trace);
      
      int maxBufferSize;
      int index{0};
      bool cycle{false}; // indicates whether wrap around occured
      bool running{false};
      std::vector<T> traceBuffer{};
      std::vector<timestamp_t> timestampBuffer{};
    };
    
    
    //TODO
    /********** Print functions *********
    template <typename T>
    std::ostream& operator<<(std::ostream& os, Trace<T>& trace) {
      os << "Block trace: '" << trace.getName() << "'"; 
    }
    */
    
  };
};
#endif /* ORG_EEROS_CONTROL_SMARTTRACE_HPP_ */
