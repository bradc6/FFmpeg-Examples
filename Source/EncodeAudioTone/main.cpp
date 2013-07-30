#include "main.hpp"
#include <iostream>

int main()
{
	std::cout << "Encode Tone into MP2 format\n"
              << "The output file will be encodeAudioOutput.mp2";
    
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
    
    
    
	return 0;
}
