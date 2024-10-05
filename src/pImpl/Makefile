CXX = g++ CXXFLAGS = -std = c++ 17 - Wall - Wextra - pedantic LDFLAGS =

                                SRCS = myClassImpl.cpp main.cpp OBJS = $(SRCS :.cpp =.o)
                                    TARGET = myapp

                                                     .PHONY : all clean

                                                                  all : $(TARGET)

                                                                            $(TARGET)
    : $(OBJS) $(CXX) $(CXXFLAGS) $(LDFLAGS) - o $ @$ ^

                                             %.o
    : %.cpp $(CXX) $(CXXFLAGS) - c $ < -o $ @

                                                     myClassImpl.o
    : myClassImpl.cpp myClassImpl.hpp myClass.hpp main.o : main.cpp myClass.hpp

                                                               clean
    : rm - f $(OBJS) $(TARGET)

#Demonstration
                                                             demo
    : $(TARGET)
          ./ $(TARGET)