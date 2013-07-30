#include "main.hpp"
#include <iostream>

int main()
{
	std::cout << "Encode Tone into MP2 format\n"
              << "The output file will be encodeAudioOutput.mp2";
    
    
    //Registers underling FFMPEG
#warning Need to be replaced with the code to register only MP2
    avcodec_register_all();
    
    
    //The desired codec that we wish to use for encoding
    //for simpilicity sake we will use MP2
    AVCodec *mp2Codec;
    
    //The codec context sets difference aspects of the audio
    //such as the desired bitrate, number of audio channels,
    //sample rate and other audio aspects
    AVCodecContext *mp2EncoderProperties;
    
    //Have FFMPEG see if that specific codec is compiled into the
    //library.
     mp2Codec = avcodec_find_encoder(AV_CODEC_ID_MP2);
    
    //Check the pointer to confirm that the encoder was found
    //beware that a codec may have a DECODER, but no encoder
    //such as SMACKER (as of 7-30-2013)
    if(!mp2Codec)
    {
        std::cout << "Sorry, looks like FFMPEG does not have that codec :(\n";
        exit(-1);
    }
    
    //Now that we have the codec registered and read to go
    //we need to allocate the memory for the properties for
    //for the desired codec.
    mp2EncoderProperties = avcodec_alloc_context3(mp2Codec);
    
    //Check the pointer to confirm that the context was
    //successful at allocating memory. If not fail as
    //most likly not enough memory is availible
    if(!mp2EncoderProperties)
    {
        std::cout << "Could not allocate Codec context. Out of memory?\n";
        exit(-2);
    }
    
    //With the context allocated, we can now start setting different audio
    //properties that we would like to use.
    
    //We will set the bitrate to 64kbps (Low Quality)
    //Common Bitrates (Lowest to highest)
    // 64kbps = 64000
    // 80kbps = 80000
    // 96kbps = 96000
    // 128kbps = 128000
    // 160kbps = 160000
    // 192kbps = 192000
    // 224kbps = 224000
    // 256kbps = 256000
    // 288kbps = 288000
    // 320kbps = 320000
    //But for a tone it is fine.
    mp2EncoderProperties->bit_rate = 64000;
    
    //There are many different type of PCM (Pulse-code Modulation) Audio
    //We need to ensure that the encoder is able to understand the input
    //If not we have to resample the input to fit the codec
    //(In example decodeEncodeResample build target)
    
    
    
	return 0;
}
