//
// Created by bulat on 16.11.22.
//

#ifndef CPP_OPUS_ENCODER_H
#define CPP_OPUS_ENCODER_H

#include <opus/opus.h>
#include <string>

class Encoder
{
private:

public:
    Encoder();
    std::string encode_by_name(std::string);
};

#endif //CPP_OPUS_ENCODER_H
