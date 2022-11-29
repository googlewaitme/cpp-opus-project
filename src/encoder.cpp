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
    _rate = file.getSampleRate();
    _max_frame_size = 1500;  // Не знаю почему такие числа, будет круто если кто-то поможет.
    _application = OPUS_APPLICATION_AUDIO;
    _error=0;
    _inbuf = new opus_int16[_channels * _frame_size];
    _outbuf = new unsigned char[_channels * _frame_size];
    _fbytes = new unsigned char[_channels * _max_frame_size];
    _input_buffer_position = 0;

    _encoder = opus_encoder_create(_frame_size, _channels, _application,&_error);

    _artist = "some_artist";
    _title = "some_title";
}


Encoder::~Encoder()
{
    opus_encoder_destroy(_encoder);
    delete [] _inbuf;
    delete [] _outbuf;
    delete [] _fbytes;
}


void Encoder::encode(const char * filename_in, const char * filename_out)
{
    FILE *fin;
    fin = fopen(filename_in, "rb");
    if (!fin) {
        std::cout << "THIS FILE IS NOT EXISTS" << std::endl;
        return;
    }

    OggOpusComments* comments = ope_comments_create();
    ope_comments_add(comments, "ARTIST", _artist);
    ope_comments_add(comments, "TITLE", _title);

    OggOpusEnc *enc = ope_encoder_create_file(filename_out, comments, _rate, _channels, 0, &_error);

    std::size_t READ_SIZE_FROM_FILE = 480;
    while (true) {
        fprintf(stdout, "read next chunk\n");
        short buf[READ_SIZE_FROM_FILE];
        int ret = fread(buf, sizeof(short), READ_SIZE_FROM_FILE, fin);
        if (ret > 0) {
            ope_encoder_write(enc, buf, ret / 2);
        } else
            break;
    }
    ope_encoder_drain(enc);
    ope_encoder_destroy(enc);
    ope_comments_destroy(comments);
    fclose(fin);
}
