#ifndef EncodeAudio_Header
#define EncodeAudio_Header

//Since the libraries are written in C, we need to tell
//the linker to link the libraries as C code. Otherwise
//compilation will still succeed but linking will not
//due to expected symbol locations
extern "C"
{
    #include <libavutil/opt.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/channel_layout.h>
    #include <libavutil/common.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/mathematics.h>
    #include <libavutil/samplefmt.h>
}

#include <math.h>

//!Checks whether a specific sample format is compatible
/*! Checks whether a specific sample format is compatible
 *  with the offered codec
 * \pre Codec must be registered and defined
 * \returns true If the Sample format is compatible
 * \returns false If the Sample format is NOT compatible
 * \note NA*/
bool CheckCodecSupportofSampleFormat(const AVCodec *targetCodec, const enum AVSampleFormat targetSampleFormat);

//Finds the highest available sample rate for targetCodec
/*! Find the highest possible sample rate for a particular codec
 * \pre targetCodec must be defined and preloaded
 * \post Returns the maximum sample rate provided by the codec
 *\note NA*/
int GetHighestSamplerate(const AVCodec *targetCodec);

//Finds the highest available channel layout for targetCodec
/*! Find the highest possible channel layout for a particular codec
 * \pre targetCodec must be defined and preloaded
 * \post Returns the maximum channel layout provided by the codec
 *\note NA*/
int GetHighestChannelLayout(const AVCodec *targetCodec);

#endif