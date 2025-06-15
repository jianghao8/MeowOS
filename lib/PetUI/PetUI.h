#ifndef PET_UI_H
#define PET_UI_H

#include <Arduino.h>

class PetUI
{
public:
  void begin();
  void update(const String &name, int hunger);

private:
  void drawFace(int hunger);
  void drawInfo(const String &name, int hunger);
};

#endif
