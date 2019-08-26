#include "Sound.h"

Sound::Sound(string url){
    this->buffer.loadFromFile(url);
    this->sound.setBuffer(buffer);
}

void Sound::play(){
    this->sound.play();
}
