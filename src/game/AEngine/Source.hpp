#ifndef AUDIO_SOURCE_HPP
#define AUDIO_SOURCE_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include "../utils/Position.h"
#include "Handler.hpp"

class AudioSource {
    private:
        ALuint ID;
        ALuint audioID;
        ALint state;
        Coor3D position = {0.0f, 0.0f, 0.0f};
        Coor3D velocity = {0.0f, 0.0f, 0.0f};
        float volume = 1.0f;
        float pitch = 1.0f;
        ALboolean loopEnabled = false;
        //Methods
        void makeSource(){
            alCall(alGenSources, 1, &ID);
            alCall(alSourcef, ID, AL_PITCH, pitch);
            alCall(alSourcef, ID, AL_GAIN, volume);
            alCall(alSource3f, ID, AL_POSITION, position.x, position.y, position.z);
            alCall(alSource3f, ID, AL_VELOCITY, velocity.x, velocity.y, velocity.z);
            alCall(alSourcei, ID, AL_LOOPING, loopEnabled);
            //Por ultimo vinculo la fuente con el audio a usar
            alCall(alSourcei, ID, AL_BUFFER, audioID);
        }
    public:
        AudioSource(ALuint audioID, float volume, float pitch, ALboolean loopEnabled){
            this->audioID=audioID;
            this->volume=volume;
            this->pitch=pitch;
            this->loopEnabled=loopEnabled;
            makeSource();
        }
        AudioSource(ALuint audioID, Coor3D position, Coor3D velocity, float volume, float pitch, ALboolean loopEnabled){
            this->audioID=audioID;
            this->position=position;
            this->velocity=velocity;
            this->volume=volume;
            this->pitch=pitch;
            this->loopEnabled=loopEnabled;
            makeSource();
        }
        /*
        ~AudioSource(){
            alCall(alDeleteSources, 1, &ID);
        }
        */
        //Getters
        const ALuint getID() const {
            return ID;
        }
        //Setters
        void setAudio(ALuint newID){
            audioID=newID;
            alCall(alSourcei, ID, AL_BUFFER, audioID);
        }
        void playSound(){
            alCall(alSourcePlay, ID);
            alCall(alGetSourcei, ID, AL_SOURCE_STATE, &state);
        }
        void pauseSound(){
            alCall(alSourcePause, ID);
        }
        void stopSound(){
            alCall(alSourceStop, ID);
        }
        void quitAudio(){
            alCall(alSourceStop, ID);
            alCall(alSourcei, ID, AL_BUFFER, 0);
        }
        void adminAudio(){
            alCall(alGetSourcei, ID, AL_SOURCE_STATE, &state);
            if(state==AL_PLAYING){

            }
        }
};

#endif