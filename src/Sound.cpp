#include "Sound.h"

Sound::Sound(string url) : sound(buffer){
    this->buffer.loadFromFile(url);
}

void Sound::play(){
    this->sound.play();
}
