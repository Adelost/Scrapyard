cmake_minimum_required(VERSION 3.6)
project(AberrantEngine)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

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
        #        Source/ScanCodes.cpp
        Source/EnumClassHash.h
        Source/MouseKeyMapper.h
        Source/MouseKeyMapper.cpp
        Source/OSWrap.h
        Source/OSWrap.cpp
        Source/Keys.h
        Source/Keys.cpp
        Source/KeyHook.h
        Source/KeyHook.cpp
        Source/ScanCodes.h
        Source/ScanCodes.cpp
        )

include_directories(Libs/Interception)
link_directories(Libs/Interception/x64)

if (WIN32)
    add_definitions(-D_WIN32_)
    set(LIBS interception.lib)
elseif(APPLE)
    add_definitions(-D_APPLE_)
elseif(UNIX AND NOT APPLE)
    add_definitions(-D_LINUX_)
endif ()

add_executable(AberrantEngine ${SOURCES})
target_link_libraries(AberrantEngine ${LIBS})