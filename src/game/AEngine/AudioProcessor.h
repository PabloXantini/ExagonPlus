#ifndef AUDIO_PROCESSOR_H
#define AUDIO_PROCESSOR_H

#include <Audio/dr_mp3.h>

#include <cstdint>
#include <iostream>
#include <vector>

struct MP3Data {
    bool success=false;
    //Informacion crucial del MP3
    drmp3_uint64 totalFrames;
    std::vector<int16_t> samples;
    uint16_t bitsPerSample;
    uint32_t sampleRate;
    uint32_t channels;
};

MP3Data readAudio(const char* path);

#endif