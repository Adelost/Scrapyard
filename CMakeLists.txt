cmake_minimum_required(VERSION 3.6)
project(AberrantEngine)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

set(SOURCES
        Source/main.cpp
        Source/Utils/Assert.cpp
        Source/Utils/Assert.h
        Source/Utils/Cast.h
        Source/Utils/Console.cpp
        Source/Utils/Console.h
        Source/Utils/List.h
        Source/Utils/Math.cpp
        Source/Utils/Math.h
        Source/Utils/Memory.cpp
        Source/Utils/Memory.h
        Source/Utils/Message.cpp
        Source/Utils/Message.h
        Source/Utils/Random.cpp
        Source/Utils/Random.h
        Source/Utils/Algorithm.h
        Source/Utils/StaticInit.h
        Source/Utils/StringConvert.cpp
        Source/Utils/StringConvert.h
        Source/Utils/StringRef.h
        Source/Utils/Time.cpp
        Source/Utils/Time.h
        Source/Utils/Inherit/NonCopyable.h
        Source/Utils/Lists/NativePoolArray.h
        Source/Utils/Lists/PList.h
        Source/Utils/Lists/PoolAllocator.h
        Source/Utils/Lists/PoolArray.h
        Source/Utils/Lists/PoolArrayBase.h
        Source/Utils/Lists/PoolList.h
        Source/Utils/Lists/PoolPtr.h
        Source/Utils/Lists/Queue.h
        Source/Utils/Lists/StablePoolArray.h
        Source/Utils/Lists/Stack.h
        Source/Utils/Lists/StaticClass.h
        Source/Utils/Lists/Traits/IndexableContainer.h
        Source/Utils/__internal__/_WindowsConsole.cpp
        Source/Utils/__internal__/_WindowsConsole.h
        Source/KeyCodes.h
        Source/KeyHook.h
        Source/KeyHook.cpp)

include_directories(Libs/Interception)
link_directories(Libs/Interception/x64)
set(LIBS interception.lib)

add_executable(AberrantEngine ${SOURCES})
target_link_libraries(AberrantEngine ${LIBS} )

#target_link_libraries(AberrantEngine D:/_Windows/Desktop/AberrantTemp/Interception/x64/interception.lib)

#install(TARGETS AberrantEngine DESTINATION bin)
#target_link_libraries(AberrantEngine ${CMAKE_CURRENT_SOURCE_DIR}/Interception/interception.lib)

#include_directories(/Interception/libHelloDll.a)