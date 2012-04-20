#include "gg.hpp"
#include <iostream>
#include <string>

using namespace std;

float x = 400.0f;
float y = 300.0f;
float vx = 0.0f;
float vy = 0.0f;

char words1[] = "ABCDEFGHIJKLOPQRSTUVWXYZ";
char words2[] = "0123456789";
char words3[] = "HELLO!";
char words4[] = "WORLD?";

void drawstring(const char *word, float x, float y, float s){
  //float offset = s*0.8f;
  float letter_x;
  float letter_y;
  float offset_x;
  float offset_y;
  for(unsigned int i = 0; i < strlen(word); i ++){
    letter_x = (((int)word[i] - 32)%32) * 0.03125f;
    letter_y = (((int)word[i] - 32)/32) * 0.03125f;
    offset_x = x + i*s*1.142857143f;
    offset_y = y;
    glTexCoord2f(letter_x           , letter_y           ); glVertex3f(offset_x, offset_y, 0);
    glTexCoord2f(letter_x + 0.03125f - 0.00390625f, letter_y           ); glVertex3f(offset_x+s, offset_y, 0);
    glTexCoord2f(letter_x + 0.03125f - 0.00390625f, letter_y + 0.03125f - 0.00390625f); glVertex3f(offset_x+s, offset_y+s, 0);
    glTexCoord2f(letter_x           , letter_y + 0.03125f - 0.00390625f); glVertex3f(offset_x, offset_y+s, 0);
  }
}

class gg: public GG {
  void init() {
    sf::Image Image;
    if (!Image.LoadFromFile("assets/sprite.png"))
    {
      return;
    }

    sf::SoundBuffer Buffer;
    if (!Buffer.LoadFromFile("assets/test.wav"))
    {
      return;
    }

    sf::Sound Sound;
    Sound.SetBuffer(Buffer);

    //Sound.Play();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, Image.GetWidth(),
        Image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
        Image.GetPixelsPtr());
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glClearColor(0.9f, 0.9f, 0.9f, 1);
  }
  void loop() {
    vx *= 0.999f;
    vx += float(rand()) / float(RAND_MAX) - 0.5f;
    x += vx;
    vy *= 0.999f;
    vy += float(rand()) / float(RAND_MAX) - 0.5f;
    y += vy;
    if (x < 0.0f || x > 800.0f || y < 0.0f || y > 600.0f) {
      x = 400.0f;
      y = 300.0f;
      vx = 0.0f;
      vy = 0.0f;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);

    glColor4f(0.1f,0.1f,0.1f,1);
    drawstring(words1, x, y, 21);
    drawstring(words2, y, x, 28);
    drawstring(words3, 800-x, 600-y, 63);
    drawstring(words4, 800-y, 600-x, 126);

    drawstring(words3, 0, 0, 63);
    drawstring(words4, 0, 70, 63);
    drawstring(words1, 0, 140, 21);
    drawstring(words2, 0, 168, 28);

    glEnd();
  }
};

int main(int argc, char* argv[]) {
  gg mygame;
  mygame.start();
  return 0;
}