cmake_minimum_required(VERSION 3.24)
project(RedosHunter)

set(CMAKE_CXX_STANDARD 17)
set(regex_class_dir ${PROJECT_SOURCE_DIR}/regex_tree)

include_directories(${PROJECT_SOURCE_DIR} ${regex_class_dir})
add_executable(RedosHunter main.cpp regex_tree/regex.h NQPattern/NQPattern.h print_regex_tree/print_tree.h EODPattern/EODPattern.h EOAPattern/EOAPattern.h NQPattern/NQClass.h Util/Generate_string.h Util/Generate_regex.h Util/Preprocessing_Re.h Util/util_class.h)
