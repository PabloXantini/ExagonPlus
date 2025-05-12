#ifndef SONG_PLAYER_HPP
#define SONG_PLAYER_HPP

#include "AEngine/Engine.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class SongPlayer {
    private:
        //bool firstTime = true;
        std::vector<ALuint> SongID;
        float volume = 1.0f;
        float pitch = 1.0f;
        ALboolean loopEnabled = false;
        //Objetos de referencia
        AudioSource* src;
        AudioEngine* engine;
    public:
        SongPlayer(AudioEngine* engine);
        void loadSong(const char* SongPath);
        void setupSong(unsigned int index, float volume, float pitch, ALboolean loopEnabled);
        void changeSong(unsigned int index);
        void playSong();
        void stopSong();
};

SongPlayer::SongPlayer(AudioEngine* engine):
    engine(engine)
{
    std::cout<<"Oooo me creo, Musica Maistro"<<std::endl;
}
void SongPlayer::loadSong(const char* SongPath){
    SongID.push_back(engine->makeAudio(SongPath));
    //firstTime = false;
}
void SongPlayer::setupSong(unsigned int index, float volume, float pitch, ALboolean loopEnabled){
    if(index<SongID.size()){
        src = new AudioSource(SongID.at(index), volume, pitch, loopEnabled);
    } else {
        std::cout<<"Error: no se pudo configurar la musica: Fuera de rango"<<std::endl;
    }
}
void SongPlayer::changeSong(unsigned int index){
    if(index<SongID.size()){
       src->setAudio(SongID.at(index)); 
    } else {
        std::cout<<"Error: no se pudo cambiar la musica: Fuera de rango"<<std::endl;
    }    
}
void SongPlayer::playSong(){    
    std::cout<<"Musica Maistro"<<std::endl;
    src->playSound();
}
void SongPlayer::stopSong(){
    std::cout<<"Aguafiestas"<<std::endl;
    src->stopSound();
}

#endif