cmake_minimum_required ( VERSION 3.28 )
project ( interview )

set ( CMAKE_CXX_STANDARD 20 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )
set ( CMAKE_C_FLAGS_DEBUG "-g3 -ggdb3 -O0 -Wall -pg" )
set ( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} )

# ##########################################################
# Add google benchmark
# ##########################################################
# find_package ( benchmark REQUIRED )

# ##########################################################
# Datastruct
# ##########################################################
set ( LinkedList_SRC
    DataStruct/LinkedList/doublyList.cpp
    DataStruct/LinkedList/singleList.cpp
    DataStruct/LinkedList/singleList_impl.cpp
    DataStruct/LinkedList/instructive.c
    DataStruct/LinkedList/instructive.cpp
    DataStruct/LinkedList/user.cpp

    # header
    DataStruct/LinkedList/instructive.h
    DataStruct/LinkedList/instructive.hpp
    DataStruct/LinkedList/doublyList.h
    DataStruct/LinkedList/singleList.h
    DataStruct/LinkedList/singleList_impl.h
)

set ( QandS_SRC
    DataStruct/Q_S/queue.cpp
    DataStruct/Q_S/stack.cpp

    # header
    DataStruct/Q_S/stack.h
    DataStruct/Q_S/queue.h
)

set ( Sort_SRC
    DataStruct/Sort/sort.cpp
    DataStruct/Sort/user.cpp
    DataStruct/Sort/insert.cpp
    DataStruct/Sort/quick.cpp
    DataStruct/Sort/shell.cpp

    # header
    DataStruct/Sort/sort.hpp
)

set ( Tree_SRC
    DataStruct/Tree/Tree.cpp

    # header
    DataStruct/Tree/Tree.h )

add_executable ( LinkedList ${LinkedList_SRC} )
add_executable ( Sort ${Sort_SRC} )

# ###################################################
# Examination
# ###################################################
add_subdirectory ( Examination )