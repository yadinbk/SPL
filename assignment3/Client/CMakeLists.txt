cmake_minimum_required(VERSION 3.10)
project(Boost_Echo_Client)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)
IF (Boost_FOUND)
include_directories(${Boost_INCLUDE_DIR})
endif()

set(CMAKE_EXE_LINKER_FLAGS -pthread)
set(CMAKE_EXE_LINKER_FLAGS -lboost_thread)
set(CMAKE_EXE_LINKER_FLAGS -lboost_locale)
set(CMAKE_EXE_LINKER_FLAGS -lboost_system)



include_directories(include)
add_executable(Boost_Echo_Client
    include/connectionHandler.h  src/connectionHandler.cpp src/StompFrame.cpp include/StompFrame.h
        src/InputToStomp.cpp include/InputToStomp.h src/Message.cpp include/Message.h src/User.cpp include/User.h
        src/Book.cpp include/Book.h src/InputTask.cpp include/InputTask.h src/ServerTask.cpp include/ServerTask.h src/StompBookClubClient.cpp)

target_link_libraries( Boost_Echo_Client LINK_PUBLIC ${Boost_LIBRARIES} )
