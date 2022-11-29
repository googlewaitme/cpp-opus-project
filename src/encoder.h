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
    int _max_frame_size;
    int _error;
    int _application;
    opus_int16 *_inbuf;
    unsigned char *_outbuf;
    unsigned char *_fbytes;

    std::vector<opus_int16> _pcm;

    std::string _artist;
    std::string _title;

    int _input_buffer_position;

public:
    Encoder(const AudioFile<double>&);
    ~Encoder();
    void encode(const char *, const char *);
};
