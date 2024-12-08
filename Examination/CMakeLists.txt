cmake_minimum_required ( VERSION 3.28 )

file ( GLOB_RECURSE srcs "*.cpp" )

set ( names )

foreach ( _dir ${srcs} )
    get_filename_component ( _filename ${_dir} NAME_WE )
    add_executable ( ${_filename} ${_dir} )
endforeach ()
