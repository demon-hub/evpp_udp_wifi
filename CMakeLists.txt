cmake_minimum_required (VERSION 2.8)
project (udpwifi)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11")   
endif(CMAKE_COMPILER_IS_GNUCXX)
include_directories(.)
SET(DEPENDENT_LIBRARIES event glog)
link_libraries(/usr/lib64/libevent.so)
link_libraries(/usr/lib64/libglog.so)

link_libraries(/usr/lib64/mysql/libmysqlclient.so)

link_libraries(/usr/lib64/libevpp_static.a)
include_directories(/usr/include/mysql)
link_directories(/usr/lib64/mysql)
add_executable(udpwifi main.cc IDatabase.h CDatabase.cc CDatabase.h CDbConnection.h CDbConnection.cc CDbResult.h CDbResult.cc CObject.h CObject.cc UdpTypes.h UdpDecoder.h UdpDecoder.cc )


