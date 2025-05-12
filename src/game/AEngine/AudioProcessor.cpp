#define DR_MP3_IMPLEMENTATION
#include "AudioProcessor.h"

MP3Data readAudio(const char* path){
    drmp3 mp3;
    MP3Data output;
    if(!drmp3_init_file(&mp3, path, NULL)){
        std::cout<<"Error: Unable to read file"<<std::endl;
        return;  
    }else{
        output.success=true;
    }
    output.totalFrames = drmp3_get_pcm_frame_count(&mp3);
    output.samples.resize(output.totalFrames * mp3.channels);
    drmp3_read_pcm_frames_s16(&mp3, output.totalFrames, output.samples.data());
    //Lleno la informacion
    output.bitsPerSample=sizeof(uint16_t)*8;
    output.sampleRate=mp3.sampleRate;
    output.channels=mp3.channels;
    
    drmp3_uninit(&mp3);
}