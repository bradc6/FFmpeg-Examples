project(ffmpeg_examples)
cmake_minimum_required(VERSION 2.6)
set(FFMPEGEXAMPLE_VERSION 0.1)

#Set FFMPEG Example Sources

set(SOURCE_DIR "./src")


set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(Boost COMPONENTS system filesystem exception REQUIRED)
find_package(FFMPEG REQUIRED)

set(basicEncodeDecode_SRCS
    ${SOURCE_DIR}/basicEncodeDecode/main.cpp
)


set(basicEncodeDecode_LIBS
	${Boost_LIBRARIES}
	${FFMPEG_LIBRARIES}
)

add_executable(basicEncodeDecode ${basicEncodeDecode_SRCS})
target_link_libraries(basicEncodeDecode ${basicEncodeDecode_LIBS})