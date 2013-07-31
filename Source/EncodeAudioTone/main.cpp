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
    
    //There are many different types of Audio input
    //We need to ensure that the encoder is able to understand the input
    //If not we have to resample the input to fit the codec
    //(In example decodeEncodeResample build target)
    //We will attempt to use s16 PCM Audio
    
    //We can work to ensure this input format works by querying
    //the different inputs offered with out own little function.
    if(CheckCodecSupportofSampleFormat(mp2Codec, AV_SAMPLE_FMT_S16))
    {
        mp2EncoderProperties->sample_fmt = AV_SAMPLE_FMT_S16;
    }
    else
    {
        std::cout << "The input sample format is not available for that specific codec\n";
        exit(-3);
    }
    
    //For out purposes (We are generating a tone to encode)
    //We will simple use the max available settings of the codec
    mp2EncoderProperties->sample_rate = GetHighestSamplerate(mp2Codec);
    
    //Next we will set the channel layout with the most available
    //channels
    mp2EncoderProperties->channel_layout = GetHighestChannelLayout(mp2Codec);
    
    //Now that we have the channel layout to be using, for this example the
    //tone we generate will be for the maximum channels available in the layout
    mp2EncoderProperties->channels = av_get_channel_layout_nb_channels(mp2EncoderProperties->channel_layout);
    
    //We have finally got all the properties of the encoder (mp2Codec)
    //and it's properties configured (mp2EncoderProperties) lets open the Encoder
    //When opening the codec fails it will return a negative value, which can be caught
    //and controll the error. For this example simple fail out of the app
    if(avcodec_open2(mp2EncoderProperties, mp2Codec, NULL))
    {
        std::cout << "Not able to open the codec. One of the properties set incorrectly?\n";
        exit(-4);
    }
    
    //AVFrame is a data structure that contains the raw audio
    //from the inputed audio file/source
    AVFrame *currentAudioFrame;
    
    //We need to allocate the memory for this AVFrame
    currentAudioFrame = avcodec_alloc_frame();
    
    //If memory for the frame could not be allocated
    //We need to fail out
    if(!currentAudioFrame)
    {
        std::cout << "Could allocate enough memory for an AVFrame\n";
        exit(-5);
    }
    
    //With the AVFrame allocated
    //We will set the AVFrame with the same settings as out mp2EncoderProperties
    //Set the number of samples expected for the frame
    currentAudioFrame->nb_samples = mp2EncoderProperties->frame_size;
    
    //Set the AVFrame sample format to expect
    currentAudioFrame->format = mp2EncoderProperties->sample_fmt;
    
    //Set the AVFrame channel layout to expect
    currentAudioFrame->channel_layout = mp2EncoderProperties->channel_layout;
    
    //Now that the encoder is ready lets open the file to write to
    std::ofstream outMP2Audio;
    outMP2Audio.open("encodeAudioOutput.mp2");
    
    //Finished writing to the file
    //Close the file to rid us of the lock
    outMP2Audio.close();
	return 0;
}

bool CheckCodecSupportofSampleFormat(const AVCodec *targetCodec, const enum AVSampleFormat targetSampleFormat)
{
    //Make a pointer to a enumeration of all the supported
    //sample formats, then run down that list in search of that sample format
    for(const enum AVSampleFormat *currentSampleFormatAttempt = targetCodec->sample_fmts;
        *currentSampleFormatAttempt != AV_SAMPLE_FMT_NONE;
        currentSampleFormatAttempt++)
    {
        if(*currentSampleFormatAttempt == targetSampleFormat)
        {
            return true;
        }
    }
    return false;
}

int GetHighestSamplerate(const AVCodec *targetCodec)
{
    //The best supported sample rate we have
    //found so far
    int bestSampleRate = 0;

    //If the codec does not have a set of sampleRates
    //set a default accepted value
    if(!targetCodec->supported_samplerates)
    {
        return 44100;
    }
    
    const int *currentSampleRateAttempt = targetCodec->supported_samplerates;
    
    //Otherwise lets roll through the different sample rates that are offered
    for(; *currentSampleRateAttempt; currentSampleRateAttempt++)
    {
        bestSampleRate = FFMAX(*currentSampleRateAttempt, bestSampleRate);
    }
    
    return bestSampleRate;
}

int GetHighestChannelLayout(AVCodec *targetCodec)
{
    const uint64_t *currentChannelLayoutAttempt;
    int bestNumberofAvailableChannels = 0;
    uint64_t bestChannelLayout = 0;
    
    //If the codec does not have a list of
    //supported channel layouts, default to stereo
    if(!targetCodec->channel_layouts)
    {
        return AV_CH_LAYOUT_STEREO;
    }
    
    currentChannelLayoutAttempt = targetCodec->channel_layouts;
    
    for(;currentChannelLayoutAttempt; currentChannelLayoutAttempt++)
    {
        int numberOfChannelsAvailable = av_get_channel_layout_nb_channels(*currentChannelLayoutAttempt);
        
        if(bestNumberofAvailableChannels < numberOfChannelsAvailable)
        {
            bestChannelLayout = *currentChannelLayoutAttempt;
            bestNumberofAvailableChannels = numberOfChannelsAvailable;
        }
    }
    return bestChannelLayout;
}