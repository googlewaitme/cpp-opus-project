#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include "encoder.h"
#include <AudioFile.h>

#include <opus/opusenc.h>


Encoder::Encoder(const AudioFile<double>& file)
{
    _audio_file = file;
    _channels = file.getNumChannels();
    _frame_size = file.getSampleRate(); // file.getNumSamplesPerChannel() > 0xFF ? 0xFF : file.getNumSamplesPerChannel();
    _max_frame_size = 1500;  // Не знаю почему такие числа, будет круто если кто-то поможет.
    _max_data_bytes = _max_frame_size * _channels;
    _application = OPUS_APPLICATION_AUDIO;
    _error=0;
    _inbuf = new opus_int16[_channels * _frame_size];
    _outbuf = new unsigned char[_channels * _frame_size];
    _pcm = std::vector<opus_int16>();
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
    for (int i=_input_buffer_position; i < _input_buffer_position + _frame_size; i++) {
        _inbuf[i] = _audio_file.samples[0][i];
        len += 1;
        if (len == _frame_size)
            break;
    }
    _input_buffer_position += len;
    return len;
}

//
//std::vector<std::vector<unsigned char>> Encoder::encode(
//            const std::vector<opus_int16>& pcm, int frame_size)
//{
//    // размер одного sample в записи
//    constexpr auto sample_size = sizeof(pcm[0]);
//    // frame_size - частота дискретизации, _channels - количество каналов в записи
//    const auto frame_length = frame_size * _channels * sample_size;
//    // pcm - массив, в котором хранятся все sample's записи
//    auto data_length = pcm.size() * sample_size;
//    std::vector<std::vector<unsigned char>> encoded;
//    for (std::size_t i{}; i < data_length; i += frame_length) {
//        encoded.push_back(encode_frame(pcm.begin() + (i / sample_size), frame_size));
//    }
//    return encoded;
//}
//
//
//std::vector<unsigned char> Encoder::encode_frame(
//            const std::vector<opus_16>::const_iterator& frame_start,
//            int frame_size)
//{
//    const int frame_length = (frame_size * _channels * sizeof(*frame_start));
//    std::vector<unsigned char> encoded(frame_length);
//    auto num_bytes = opus_encode(_encoder, &*frame_start, frame_size,
//                                 encoded.data(), encoded.size());
//    return encoded;
//}

void Encoder::encode_by_filename(const char *output_filename)
{
    int len = _set_pcm();
    std::cout << "len-start: " << len << std::endl;
    FILE *fout = std::fopen(output_filename, "wb");
    while (len > 0)
    {
        std::cout << "len: " << len << std::endl;
        opus_int32 result = opus_encode(_encoder, _inbuf, len, _outbuf, _max_data_bytes);

        for (int i=0; i < len * _channels; i++)
        {
            short s = _outbuf[i+(_input_buffer_position-len)*_channels];
            _fbytes[2*i]=s&0xFF;
            _fbytes[2*i+1]=(s>>8)&0xFF;
            std::cout << _fbytes[2*i] << " ";
        }

        std::cout << "fwrite: " << len << std::endl;
        fwrite(_fbytes, sizeof(short)*_channels, len, fout);
        len = _set_pcm();
    }
    std::cout << "len-end: " << len << std::endl;
    std::fclose(fout);
}
