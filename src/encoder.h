//
// Created by bulat on 16.11.22.
//

#ifndef CPP_OPUS_ENCODER_H
#define CPP_OPUS_ENCODER_H

#include <opus/opus.h>
#include <string>

#include <AudioFile.h>

class Encoder
{
private:
    OpusEncoder *_encoder;
    AudioFile<double> _audio_file;
    int _channels;
    opus_int32 _frame_size;
    int _max_frame_size;
    opus_int32 _max_data_bytes;
    int _error;
    int _application;
    opus_int16 *_inbuf;
    unsigned char *_outbuf;
    unsigned char *_fbytes;

    std::vector<opus_int16> _pcm;


    int _input_buffer_position;

    int _set_pcm();


public:
    Encoder(const AudioFile<double>&);
    ~Encoder();
    void encode_by_filename(const char *);
};

#endif //CPP_OPUS_ENCODER_H
