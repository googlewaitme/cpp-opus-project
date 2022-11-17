//
// Created by bulat on 16.11.22.
//

#include <string>
#include "encoder.h"
#include "AudioFile.h"


Encoder::Encoder(AudioFile<double> file)
{
    OpusEncoder *_encoder;
    int _channels = file.getNumChannels();
    opus_int16 _frame_size = file.getNumSamplesPerChannel();
    int _application = OPUS_APPLICATION_AUDIO;
    int error;

    _encoder = opus_encoder_create(_frame_size, _channels, _application,&error);
}


Encoder::~Encoder()
{
    opus_encoder_destroy(_encoder);

}

std::string Encoder::encode_by_filenames(std::string input_filename, std::string output_filename)
{
    // get data from file with name input_filename
    // return encoded .opus file in name output_filename
    OpusEncoder *encoder;

    // opus_encode(encoder, frame_size*channels*sizeof(opus_int16));
    return output_filename;
}
