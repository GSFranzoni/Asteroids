#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <SFML/Audio.hpp>

using namespace std;

class Sound{
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
public:
    Sound(string);
    void play();
};

#endif
