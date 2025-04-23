#ifndef SONG_PLAYER_HPP
#define SONG_PLAYER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class SongPlayer {
    public:
        SongPlayer()=default;
        void playSong(std::string SongPath);
        void stopSong();
};

void SongPlayer::playSong(std::string SongPath){    
    std::cout<<"Musica Maistro"<<std::endl;
}
void SongPlayer::stopSong(){
    std::cout<<"Aguafiestas"<<std::endl;
}

#endif