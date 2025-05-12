#ifndef AUDIO_ENGINE_HPP
#define AUDIO_ENGINE_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include "Handler.hpp"
#include "AudioBuffer.hpp"
#include "Source.hpp"

#include <iostream>
#include <vector>

class AudioEngine {
    private:
        std::vector<std::string> devicesRegistered = {};    //Dispostivos registrados
        std::vector<Audio> AudioBuffers={};                 //Buffers de audio
        std::vector<AudioSource> Sources={};                //Buffers de audio
        ALCdevice* device;                                  //Dispositivo predeterminado
        ALCcontext* ccontext;                               //Contexto de OpenAL
        ALCboolean contextMadeCurrent = false;              //Contexto inicializado
        bool getAvailableDevices(std::vector<std::string>& devicesVec, ALCdevice* device);
        void clearElements();
    public:
        AudioEngine();
        //Getters
        std::vector<ALuint> getAllAudios();
        std::vector<ALuint> getAllSources();
        //Methods
        bool init();
        void close();
        ALuint makeAudio(const char* path);
        void registerSource(AudioSource& source);
};

#endif