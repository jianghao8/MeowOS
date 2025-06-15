#ifndef PET_MODULE_H
#define PET_MODULE_H

#include <Arduino.h>
#include "StorageModule.h"
#include "PetUI.h"

class PetModule
{
public:
  void begin();
  void update();
  void registerCommands();

private:
  PetData petData;
  StorageModule storage;
  PetUI ui;

  void showStatus();
  void feed();
  void rename(const String &newName);
  void save(); // 保存状态
};

#endif
