#include "StorageModule.h"
#include <ArduinoJson.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

bool StorageModule::begin()
{
  if (!SD.begin(GPIO_NUM_4))
  { // 默认 TF 卡 CS 为 GPIO4
    Serial.println("[StorageModule] ❌ SD 卡初始化失败");
    return false;
  }
  Serial.println("[StorageModule] ✅ SD 卡已初始化");
  return true;
}

bool StorageModule::load(PetData &data)
{
  if (!SD.exists(filePath))
  {
    Serial.println("[StorageModule] 未找到保存文件");
    return false;
  }

  File file = SD.open(filePath, FILE_READ);
  if (!file)
  {
    Serial.println("[StorageModule] 无法读取文件");
    return false;
  }

  StaticJsonDocument<256> doc;
  DeserializationError err = deserializeJson(doc, file);
  file.close();

  if (err)
  {
    Serial.println("[StorageModule] JSON 解析失败");
    return false;
  }

  data.name = doc["name"] | "mimi";
  data.hunger = doc["hunger"] | 50;

  Serial.println("[StorageModule] 宠物状态已加载");
  return true;
}

bool StorageModule::save(const PetData &data)
{
  File file = SD.open(filePath, FILE_WRITE);
  if (!file)
  {
    Serial.println("[StorageModule] 无法写入文件");
    return false;
  }

  StaticJsonDocument<256> doc;
  doc["name"] = data.name;
  doc["hunger"] = data.hunger;

  if (serializeJson(doc, file) == 0)
  {
    Serial.println("[StorageModule] 写入失败");
    file.close();
    return false;
  }

  file.close();
  Serial.println("[StorageModule] 宠物状态已保存");
  return true;
}
