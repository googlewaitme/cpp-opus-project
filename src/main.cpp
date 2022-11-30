#include <opus/opus.h>
#include <iostream>
#include "encoder.h"
#include <AudioFile.h>


int main()
{
    const char *input_filename = "/home/bulat/music/test.wav";
    const char *output_filename = "/home/bulat/music/output_myprogram.opus";
    AudioFile<double> wav_file;
    wav_file.load(input_filename);

    wav_file.printSummary();

    std::cout << opus_get_version_string() << std::endl;
    Encoder encoder(wav_file);

    encoder.encode(input_filename, output_filename);

    std::cout << "Encoded filename: " << output_filename << std::endl;
    std::cout << "End program" << std::endl;
    return 0;
}
