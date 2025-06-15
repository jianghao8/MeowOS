#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>

class DisplayManager
{
public:
  void begin();
  void update();
  void updateInputText(const String &text);
  void toggleCommandBox();
  void setStatus(bool wifiConnected, int batteryLevel);

private:
  bool _showCommandBox = true;
  bool _wifiConnected = false;
  int _batteryLevel = 100;
};

#endif
