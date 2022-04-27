cmake_minimum_required(VERSION 3.21)
project(homework)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

#Set your directories.  The dot representes the root application folder.
#Thus my the path to my domain folder:
set(APP_SRC ./project)
set(APP_HEADS ./project/include)

#Include the directories and now your cpp files will recognize your headers
include_directories(${APP_SRC})
include_directories(${APP_HEADS})

set(
        SOURCE_FILES
        ${APP_SRC}/main.c

        ${APP_HEADS}/utils.h
)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main ${CURSES_LIBRARIES})
