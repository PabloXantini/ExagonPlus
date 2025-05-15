#include "Engine.hpp"

AudioEngine::AudioEngine(){
    std::cout<<"Oh me creooo, dice AEngine o AMotor"<<std::endl;
}
//Getters
std::vector<ALuint> AudioEngine::getAllAudios(){
    std::vector<ALuint> audiosID;
    audiosID.reserve(AudioBuffers.size());
    for (auto& audio : AudioBuffers){
        audiosID.push_back(audio.getID());
    }
    return audiosID;
}
std::vector<ALuint> AudioEngine::getAllSources(){
    std::vector<ALuint> sourcesID;
    sourcesID.reserve(Sources.size());
    for (auto& source : Sources){
        sourcesID.push_back(source.getID());
    }
    return sourcesID;
}
//Publics
bool AudioEngine::init(){
    //Abrir un dispositivo de audio
    device = alcOpenDevice(NULL);
    if (!device) {
        std::cerr << "ERROR: No audio device found" << std::endl;
        return false;
    }
    //Crear el contexto y hacerlo existente
    if(!alcCall(alcCreateContext, ccontext, device, device, nullptr)||!ccontext){
        std::cerr << "ERROR: Could not create audio context" << std::endl;
        return false;
    }
    if(!alcCall(alcMakeContextCurrent, contextMadeCurrent, device, ccontext)||contextMadeCurrent!=ALC_TRUE){
        std::cerr << "ERROR: Could not make audio context current" << std::endl;
        return false;
    }
    return true;
}
ALuint AudioEngine::makeAudio(const char* path){
    Audio newSound(path);
    AudioBuffers.push_back(std::move(newSound));
    return newSound.getID();
}
void AudioEngine::registerSource(AudioSource& source){
    Sources.push_back(source);
}
void AudioEngine::close(){
    ALCboolean closed;
    clearElements();
    alcCall(alcMakeContextCurrent, contextMadeCurrent, device, nullptr);
    alcCall(alcDestroyContext, device, ccontext);
    alcCall(alcCloseDevice, closed, device, device);
}
//Privates
/*
    Obtiene todos los dispositivos de audio disponibles
*/
bool AudioEngine::getAvailableDevices(std::vector<std::string>& devicesVec, ALCdevice* device){
    const ALCchar* devices;
    if(!alcCall(alcGetString, devices, device, nullptr, ALC_DEVICE_SPECIFIER))
        return false;
    const char* ptr = devices;
    devicesVec.clear();
    do{
        devicesVec.push_back(std::string(ptr));
        ptr += devicesVec.back().size() + 1;
    }while(*(ptr + 1) != '\0');
    return true;
}
/*
    Elimina todo
*/
void AudioEngine::clearElements(){
    auto audios = getAllAudios();
    auto sources = getAllSources();
    alCall(alDeleteSources, sources.size(), sources.data());
    alCall(alDeleteBuffers, audios.size(), audios.data());
    AudioBuffers.clear();
    Sources.clear();
}