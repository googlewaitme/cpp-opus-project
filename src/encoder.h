#pragma once

#include <opus/opus.h>
#include <opus/opusenc.h>
#include <string>

#include <AudioFile.h>


class Encoder
{
private:
    OpusEncoder *_encoder;
    AudioFile<double> _audio_file;
    int _channels;
    opus_int32 _frame_size;
    opus_int32 _rate;
    int _error;
    int _application;

    std::size_t _READ_SIZE_FROM_FILE;
    short* _buf;

public:
    Encoder(const AudioFile<double>&);
    ~Encoder();
    void encode(const char *, const char *);
};
