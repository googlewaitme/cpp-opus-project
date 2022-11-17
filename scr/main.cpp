//
// Created by bulat on 16.11.22.
//
#include <opus/opus.h>
#include <iostream>
#include "encoder.h"
#include "AudioFile.h"
#include <string>


int main()
{
    AudioFile<double> wav_file;
    wav_file.load("/home/bulat/music/test.wav");
    std::cout << "count channels in test.wav" << wav_file.getNumChannels() << std::endl;

    wav_file.printSummary();

    std::cout << opus_get_version_string() << std::endl;
    Encoder encoder(wav_file);

    std::string input_filename = "input.wav";
    std::string output_filename = "output.opus";
    encoder.encode_by_filenames(input_filename, output_filename);

    std::cout << "Encoded filename: " << output_filename << std::endl;
    return 0;
}