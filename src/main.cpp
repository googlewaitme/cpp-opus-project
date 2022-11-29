#include <opus/opus.h>
#include <ogg/ogg.h>
#include <iostream>
#include "encoder.h"
#include <AudioFile.h>
#include <string>


int main()
{
    AudioFile<double> wav_file;
    wav_file.load("/home/bulat/music/test.wav");
    std::cout << "count channels in test.wav" << wav_file.getNumChannels() << std::endl;

    std::cout << "get_num_samples " << wav_file.getNumSamplesPerChannel() << std::endl;
    wav_file.printSummary();

    std::cout << opus_get_version_string() << std::endl;
    Encoder encoder(wav_file);

    const char *input_filename = "/home/bulat/music/input.wav";
    const char *output_filename = "/home/bulat/music/output_myprogram.opus";
    encoder.encode(input_filename, output_filename);


    std::cout << "Encoded filename: " << output_filename << std::endl;
    return 0;
}
