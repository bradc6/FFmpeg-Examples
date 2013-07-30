project(ffmpeg_examples)
cmake_minimum_required(VERSION 2.6)

#Set the current version of the ffmpeg examples
set(FFMPEGEXAMPLE_MAJOR_VERSION 0)
set(FFMPEGEXAMPLE_MINOR_VERSION 0)
set(FFMPEGEXAMPLE_PATCH_VERSION 0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

#Find FFMPEG 
find_package(FFMPEG REQUIRED)

#Set FFMPEG Example Sources
set(SOURCE_DIR "./Source")

#Example of encoding a simple sin wave tone
set(ENCODEAUDIOTONE_SOURCE
	${SOURCE_DIR}/EncodeAudioTone/main.hpp
	${SOURCE_DIR}/EncodeAudioTone/main.cpp)

#Decoding a PCM wav file
set(DECODEAUDIOPCMWAV_SOURCE
	${SOURCE_DIR}/DecodeAudioPCMWav/main.hpp
	${SOURCE_DIR}/DecodeAudioPCMWav/main.cpp)

#Detecting the format of a audio file
set(AUDIOFORMATDETECTION_SOURCE
	${SOURCE_DIR}/AudioFormatDetection/main.hpp
	${SOURCE_DIR}/AudioFormatDetection/main.cpp)

#Decoding a PCM wav file then encode to MP2
#Transcoding
set(DECODEENCODE_SOURCE
    ${SOURCE_DIR}/DecodeEncode/main.hpp
    ${SOURCE_DIR}/DecodeEncode/main.cpp)

#Decode WAV PCM then Encode to OGG Vorbis
#Requiring resampling the audio
set(DECODEENCODERESAMPLE_SOURCE
	${SOURCE_DIR}/DecodeEncodeResample/main.hpp
	${SOURCE_DIR}/DecodeEncodeResample/main.cpp)


if (APPLE)
	#For Macports
    set(EXTRA_LIBS ${EXTRA_LIBS} "-framework Cocoa")
    include_directories("/opt/local/include")
    link_directories("/opt/local/lib")
endif()

#If you have a user include/lib directory prefix that
#is not in the standand location
include_directories("~/dev/fakeroot/include")
link_directories("~/dev/fakeroot/lib")

add_executable(encodeAudio ${ENCODEAUDIOTONE_SOURCE})
target_link_libraries(encodeAudio ${FFMPEG_LIBRARIES})

add_executable(decodeAudioPCMWav ${DECODEAUDIOPCMWAV_SOURCE})
target_link_libraries(decodeAudioPCMWav ${FFMPEG_LIBRARIES})

add_executable(audioFormatDetection ${AUDIOFORMATDETECTION_SOURCE})
target_link_libraries(audioFormatDetection ${FFMPEG_LIBRARIES})

add_executable(decodeEncode ${DECODEENCODE_SOURCE})
target_link_libraries(decodeEncode ${FFMPEG_LIBRARIES})

add_executable(decodeEncodeResample ${DECODEENCODERESAMPLE_SOURCE})
target_link_libraries(decodeEncodeResample ${FFMPEG_LIBRARIES})