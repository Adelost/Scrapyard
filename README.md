# Utils
A collection of classes and utilities useful in general programming. Syntax mostly inspired by Qt, Python, Java, C# and Dart.

# Another generic C++ class library, why should I care?

AberrantUtils aim to improve convenience and readablilty of C++ code without sacrificing performance. It is targeted to those who work with a variety of programming languages, including C++, but prefer the syntax commonly seen in the standard libraries of other languages. It also packs a lot of useful classes that, although existing in other libraries, is not part of the standard C++ library. In addition to this, the included source files are extensively documented, and I dare say "human readable", and therefore should be easy to modify and extend, or to provide an alternative insigt into the design of common data strucutes. This is in contrast to libraries 

The design philosophy of the library is to optimize  

If you really must, write() and print() is also defined directly in the ae-namespace.

Altough at an early stage, AberrantUtils includes working introspection of Class fields.


### Content
Overview of content.
- **Addons** - Features which may be added to a class, usually through inheritance.
    - Inspectable - Allows introspection of subclasses. Only supports introspection of member variables currently.
    - NonCopyable - Other classes can inherit from this class to disallow copying of the the 
      class, e.g. "class SomeClass : private NonCopyable {};".
- **Libs** - Functions collected as static methods of various classes.
    - Algorithm - Facilitates algorithms, such as sorting.
    - Console - Makes writing console applications more convenient. Also allows outputting various classes using standard ostream
    - Cast - Utility class to make casting more convenient and helps prevent code duplication when implementing identical const and non-const methods.
    - StringConvert - Facilitate strings conversion.
    - Format - Make formating strings easier.
    - Math - Math utility class.
    - Memory - Makes managing memory in an application more convenient.
    - Random - Randomization utility class.
    - Time - Utility class for managing time.
- **Misc** - Macros and defines.
    - XAssert - Custom assert macros. More safe than standard assert, and a prints a nicer call stack. 
    - DataTypes - Portable data types. 
    - CallOnce - Make sure code in input parameter is only run once.
    - DebugOnly - Make sure code is only run in debug or release.
    - IgnoreMemleak - Ignore all memory leaks caused by memory allocations within parenthesis.
    - StaticCall - Allows code to be called automatically during the start of the program. Only to be used in .cpp files.
- **Tools** - Various classes.
    - PoolAlloc - Allow fast allocation of objects. This is usually much faster than standard allocation using "new" and "delete".
    - Array - Dynamic array implementation. 
    - Queue - Array like FIFO-queue implementation. 
    - StableArray - Similar to a dynamic-array, but which do not reallocate the memory address of the stored elements when growing. However, elements are not guaranteed to be stored in adjacent memory locations.
    - PoolArray - A mix between a pool allocator and a dynamic array. Elements are stored based on a index.
    - IdPoolArray - Similar to PoolArray, but elements are stored based on a id as well as index.
    - PoolList - A mix between a linked list and a pool allocator. Faster to add and remove elements than in a ordinary linked list.
    - StopWatch - High-precision time measuring class.

### ToDo
- Implementing const iteratores.
- Better taxonomy of classes?
- Should I force people to use people to write the prefix, e.g. Math::round(), by using static methods, or should I use functions within namespaces and allow them to choose?
- How to add introspection of methods (perhaps using lambda functions?).

### License
Licensed under CC BY 4.0. In short, do what you want (within reasonable limits) as long as you give credits, include copyright and state any significat changes. See LICENCE.md if unsure.