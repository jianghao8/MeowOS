#ifndef STORAGE_MODULE_H
#define STORAGE_MODULE_H

#include <Arduino.h>

struct PetData
{
  String name;
  int hunger;
};

class StorageModule
{
public:
  bool begin();
  bool load(PetData &data);
  bool save(const PetData &data);

private:
  const char *filePath = "/pet.json";
};

#endif
