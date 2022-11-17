//
// Created by bulat on 16.11.22.
//

#ifndef CPP_OPUS_ENCODER_H
#define CPP_OPUS_ENCODER_H

#include <opus/opus.h>
#include <string>

#include "AudioFile.h"

class Encoder
{
private:
    OpusEncoder *_encoder;
    int _channels;
    opus_int16 _frame_size;
    int _error;


public:
    Encoder(AudioFile<double>);
    ~Encoder();
    std::string encode_by_filenames(std::string, std::string);
};

#endif //CPP_OPUS_ENCODER_H
