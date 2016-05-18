cmake_minimum_required(VERSION 2.6)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  file(MAKE_DIRECTORY lib)
  add_library(arduinoio STATIC 
    analogPin.cpp 
    counterPin.cpp 
    gpioInputPin.cpp 
    gpioOutputPin.cpp 
    i2cBridge.cpp 
    ioboard.cpp 
    ioentity.cpp 
    pin.cpp 
    serial.cpp 
    servo.cpp
    tags.cpp)
endif()

