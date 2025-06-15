#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h>

class InputManager
{
public:
  void begin(HardwareSerial &serial);
  void update();
  void appendChar(char c);
  void backspace();
  String getBuffer() const;

private:
  HardwareSerial *_serial;
  String _buffer;
};

#endif
