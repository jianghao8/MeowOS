#ifndef SETTING_MODULE_H
#define SETTING_MODULE_H

#include <Arduino.h>

class SettingModule
{
public:
  void begin();
  void registerCommands();

  bool isDarkTheme() const;
  void applyTheme();

private:
  String theme = "dark"; // "light" or "dark"
  const char *configPath = "/setting.txt";

  void save();
  void load();
};

#endif
