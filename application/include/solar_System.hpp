#ifndef SOLAR_SYSTEM_HPP
#define SOLAR_SYSTEM_HPP
#include "application_solar.hpp"

class solar_System : public ApplicationSolar {
  public:
    ApplicationSolar();
    ~ApplicationSolar();
    //create sun and other planets, including name, position and size
    void init(); 
    //update is based on the orientation and position
    void update();
    //display sun and other planets
    void render();
};
#ENDIF
