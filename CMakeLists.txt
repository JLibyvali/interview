cmake_minimum_required ( VERSION 3.28 )
project ( interview )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )
set ( CMAKE_C_FLAGS_DEBUG "-g3 -ggdb3 -O0 -Wall" )
set ( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} )

# ##########################################################
# Datastruct
# ##########################################################
set ( LinkedList_SRC
    DataStruct/LinkedList/doublyList.cpp
    DataStruct/LinkedList/singleList.cpp
    DataStruct/LinkedList/singleList_impl.cpp
    DataStruct/LinkedList/user.cpp

    # header
    DataStruct/LinkedList/doublyList.h
    DataStruct/LinkedList/singleList.h
    DataStruct/LinkedList/singleList_impl.h
)

set ( QandS_SRC
    DataStruct/QandS/queue.cpp
    DataStruct/QansS/stack.cpp

    # header
    DataStruct/QansS/stack.h
    DataStruct/QansS/queue.h
)

set ( Sort_SRC
    DataStruct/Sort/Sort.cpp )

set ( Tree_SRC
    DataStruct/Tree/Tree.cpp

    # header
    DataStruct/Tree/Tree.h )
add_executable ( LinkedList ${LinkedList_SRC} )