cmake_minimum_required(VERSION 3.28)
project(DataStructure)

enable_language(C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Global compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -I/usr/lib/clang/18/include")


include_directories(
    .
    LinkedList
    QandS
    Sort
    Tree
)

set(LinkedList_SRC 
LinkedList/singleList.cpp
LinkedList/singleList_impl.cpp
LinkedList/doublyList.cpp
LinkedList/user.cpp

)

set(QandS_SRC
QandS/queue.cpp
QansS/stack.cpp 
)

set(Sort_SRC
Sort/Sort.cpp)

set(Tree_SRC
Tree.cpp)


add_executable(LinkedList ${LinkedList_SRC})
# add_executable(QandS ${QandS_SRC})
# add_executable(Sort ${Sort_SRC})
# add_executable(Tree ${Tree_SRC})
