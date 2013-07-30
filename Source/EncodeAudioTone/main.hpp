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

#endif