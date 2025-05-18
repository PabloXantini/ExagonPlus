#ifndef AUDIO_BUFFER_HPP
#define AUDIO_BUFFER_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include "AudioProcessor.h"
#include "Handler.hpp"

#include <cstdint>

class Audio {
    private:
        ALuint ID;
        ALenum format;
        //Methods
        void defineFormat(uint32_t channels, uint16_t bits){
            if(channels==1&&bits==8){
                format=AL_FORMAT_MONO8;   
            }else if(channels==1&&bits==16){
                format=AL_FORMAT_MONO16;
            }else if(channels==2&&bits==8){
                format=AL_FORMAT_STEREO8;
            }else if(channels==2&&bits==16){
                format=AL_FORMAT_STEREO16;
            }else{
                std::cerr
                << "ERROR: unrecognised wave format: "
                << channels << " channels, "
                << bits << " bps" << std::endl;
            }
        }
    public:
        Audio(const char* path){
            //Carga el audio con el recurso
            MP3Data data = readAudio(path);
            defineFormat(data.channels, data.bitsPerSample);
            //Crea el buffer y lo inicializa
            alCall(alGenBuffers, 1, &ID);
            alCall(alBufferData, ID, format, data.samples.data(), data.samples.size()*sizeof(uint16_t), data.sampleRate);
            //Lo elimina de la RAM (lo puedo comentar si lo necesito luego)
            data.samples.clear();   
        }
        //Getters
        const ALuint getID() const {
            return ID;
        }
        void free(){
            alCall(alDeleteBuffers, 1, &ID);
        }
};

#endif