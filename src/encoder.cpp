#include <cstdio>
#include <iostream>
#include <vector>
#include "encoder.h"
#include <AudioFile.h>
#include <opus/opus.h>
#include <opus/opusenc.h>


Encoder::Encoder(const AudioFile<double>& file)
{
    _channels = file.getNumChannels();
    _frame_size = file.getSampleRate();
    _rate = file.getSampleRate();
    _application = OPUS_APPLICATION_AUDIO;
    _error=0;

    _READ_SIZE_FROM_FILE = 480;
    _buf = new short [_READ_SIZE_FROM_FILE];
    _encoder = opus_encoder_create(_frame_size, _channels, _application,&_error);
}


Encoder::~Encoder()
{
    opus_encoder_destroy(_encoder);
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
    ope_comments_add(comments, "ARTIST", "ARTIST");
    ope_comments_add(comments, "TITLE", "TITLE");

    OggOpusEnc *enc = ope_encoder_create_file(filename_out, comments, _rate, _channels, 0, &_error);

    while (true) {
        int ret = fread(_buf, sizeof(short), _READ_SIZE_FROM_FILE, fin);
        if (ret > 0) {
            // div 2 because one number is two 2 byte.
            ope_encoder_write(enc, _buf, ret / 2);
        } else
            break;
    }
    ope_encoder_drain(enc);
    ope_encoder_destroy(enc);
    ope_comments_destroy(comments);
    fclose(fin);
}
