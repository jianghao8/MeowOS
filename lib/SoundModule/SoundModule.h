#ifndef SOUND_MODULE_H
#define SOUND_MODULE_H

#include <Arduino.h>

class SoundModule
{
public:
  void begin();
  void registerCommands();

  void playStartup();
  void playFeed();
  void playError();

  bool isMuted() const;

private:
  bool muted = false;

  void tone(int freq, int duration = 100);
};

#endif
