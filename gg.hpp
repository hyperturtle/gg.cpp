#ifndef __GG__HPP__
#define __GG__HPP__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GG {
  private:
    sf::Window * App;
    sf::Clock * Clock;

    int width;
    int height;

    float prev_frame_clock;

  public:
    GG();
    virtual ~GG();

    
    void start(int width=800, int height=600);

    virtual void init() = 0;
    virtual void loop() = 0;

    void addSound();
    void playSound();
};

#endif