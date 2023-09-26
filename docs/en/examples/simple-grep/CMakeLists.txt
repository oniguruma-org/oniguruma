cmake_minimum_required(VERSION 3.25)
project(simple-grep)

find_package(oniguruma REQUIRED)
add_executable(simple-grep main.c)
target_link_libraries(simple-grep oniguruma::oniguruma)
