#include "gg.hpp"

GG::GG() {
  Clock = new sf::Clock();
  srand ( Clock->GetElapsedTime() );
}

GG::~GG(){
  delete App;
  delete Clock;
}

void GG::start(int width, int height) {

  this->width = width;
  this->height = height;
  sf::WindowSettings Settings;
  Settings.DepthBits         = 24; // Request a 24 bits depth buffer
  Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
  Settings.AntialiasingLevel = 0;  // Request 2 levels of antialiasing
  App = new sf::Window(sf::VideoMode(width, height, 32), "SFML OpenGL", sf::Style::Close, Settings);


  init();

  

  glClearDepth(1.0f);
  glViewport(0, 0, this->width, this->height);

  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width, this->height, 0, 1, -1);
  
  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

  glEnable(GL_TEXTURE_2D);

  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  float time_now;
  while (App->IsOpened()) {
    sf::Event Event;
    while (App->GetEvent(Event)) {
      if (Event.Type == sf::Event::Closed)
        App->Close();
    }

    time_now = Clock->GetElapsedTime();
    if(time_now > 1.0f/60.0f) {

      loop();

      App->Display();
      Clock->Reset();
    } else {
      sf::Sleep(1.0f/60.0f - time_now);
    }
  }

  time_now = Clock->GetElapsedTime();
}