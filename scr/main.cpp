//
// Created by bulat on 16.11.22.
//
#include <opus/opus.h>
#include <iostream>
#include "encoder.h"
#include <string>


int main()
{
    std::cout << opus_get_version_string() << std::endl;

    Encoder encoder;

    std::string input_filename = "input.opus";
    std::string output_filename = encoder.encode_by_name(input_filename);

    std::cout << "Encoded filename: " << output_filename << std::endl;
    return 0;
}