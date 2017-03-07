cmake_minimum_required(VERSION 3.6)
project(AberrantEngine)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Source/Utils/main.cpp
#        Source/Utils/_WindowsConsole.cpp
#        Source/Utils/_WindowsConsole.h
#        Source/Utils/Algorithm.h
        Source/Utils/List.h
#        Source/Utils/ArrayAllocator.h
#        Source/Utils/CallOnce.h
#        Source/Utils/Cast.h
#        Source/Utils/ClassInfo.cpp
#        Source/Utils/ClassInfo.h
#        Source/Utils/Console.cpp
#        Source/Utils/Console.h
#        Source/Utils/CppParser.h
#        Source/Utils/DataTypes.h
#        Source/Utils/DebugOnly.h
#        Source/Utils/FileOpener.cpp
#        Source/Utils/FileOpener.h
#        Source/Utils/FixedPoolAllocator.cpp
#        Source/Utils/Format.cpp
#        Source/Utils/Format.h
#        Source/Utils/Forward.h
#        Source/Utils/IdPoolArray.h
#        Source/Utils/IndexableContainer.h
#        Source/Utils/Inspectable.h
#        Source/Utils/LeakDetection.cpp
#        Source/Utils/LeakDetection.h
        Source/Utils/PList.h
#        Source/Utils/Math.cpp
#        Source/Utils/Math.h
#        Source/Utils/Member.cpp
#        Source/Utils/Member.h
        Source/Utils/Memory.cpp
        Source/Utils/Memory.h
#        Source/Utils/Message.cpp
#        Source/Utils/Message.h
#        Source/Utils/NativePoolArray.h
#        Source/Utils/NonCopyable.h
#        Source/Utils/Output.h
#        Source/Utils/PoolAllocator.h
#        Source/Utils/PoolArray.h
#        Source/Utils/PoolArrayBase.h
#        Source/Utils/PoolList.h
#        Source/Utils/PoolPtr.h
#        Source/Utils/Preforwards.h
#        Source/Utils/Queue.h
#        Source/Utils/Random.cpp
#        Source/Utils/Random.h
#        Source/Utils/RegexSearch.h
#        Source/Utils/StablePoolArray.h
#        Source/Utils/Stack.h
#        Source/Utils/StaticClass.h
#        Source/Utils/StaticInit.h
#        Source/Utils/StopWatch.cpp
#        Source/Utils/StopWatch.h
#        Source/Utils/StringConvert.cpp
#        Source/Utils/StringConvert.h
#        Source/Utils/StringRef.h
#        Source/Utils/tests.cpp
#        Source/Utils/tests.h
#        Source/Utils/Time.cpp
#        Source/Utils/Time.h
#        Source/Utils/UnitTest.h
#        Source/Utils/Utils.h
#        Source/Utils/Utils.vcxproj
#        Source/Utils/Utils.vcxproj.filters
#        Source/Utils/Utils.vcxproj.user
        Source/Utils/XAssert.cpp
        Source/Utils/XAssert.h
        )

add_executable(AberrantEngine ${SOURCE_FILES})