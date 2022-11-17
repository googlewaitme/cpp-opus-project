//
// Created by bulat on 16.11.22.
//

#include <string>
#include <cstdio>
#include <iostream>
#include "encoder.h"
#include "AudioFile.h"


Encoder::Encoder(const AudioFile<double>& file)
{
    _audio_file = file;
    _channels = file.getNumChannels();
    _frame_size = file.getNumSamplesPerChannel() > 0xFF ? 0xFF : file.getNumSamplesPerChannel();
    _max_frame_size = 48000 * 2;  // Не знаю почему такие числа, будет круто если кто-то поможет.
    _max_data_bytes = _max_frame_size * _channels;
    _application = OPUS_APPLICATION_AUDIO;
    _error=0;
    _inbuf = new opus_int16[_channels * _frame_size];
    _outbuf = new unsigned char[_channels * _frame_size];
    _fbytes = new unsigned char[_channels * _max_frame_size];
    _input_buffer_position = 0;

    _encoder = opus_encoder_create(_frame_size, _channels, _application,&_error);
}


Encoder::~Encoder()
{
    opus_encoder_destroy(_encoder);
    delete [] _inbuf;
    delete [] _outbuf;
    delete [] _fbytes;
}


int Encoder::_set_pcm()
{
    int len = 0;
    for (int i=_input_buffer_position; i < _frame_size; i++) {
        _inbuf[i] = _audio_file.samples[0][i];
        len += 1;
        if (len == _frame_size)
            break;
    }
    _input_buffer_position += len;
    return len;
}


void Encoder::encode_by_filename(const char *output_filename)
{
    int len = _set_pcm();
    FILE *fout = std::fopen(output_filename, "wb");
    while (len > 0)
    {
        opus_int32 result = opus_encode(_encoder, _inbuf, len, _outbuf, _max_data_bytes);

        for (int i=0; i < len * _channels; i++)
        {
            short s = _outbuf[i+(_input_buffer_position-len)*_channels];
            _fbytes[2*i]=s&0xFF;
            _fbytes[2*i+1]=(s>>8)&0xFF;
            std::cout << _fbytes[2*i] << " ";
        }

        fwrite(_fbytes, sizeof(short)*_channels, len, fout);
        len = _set_pcm();
    }
    std::fclose(fout);
}
