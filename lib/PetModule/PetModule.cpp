#include "PetModule.h"
#include "CommandDispatcher.h"
#include "SoundModule.h"

extern SoundModule sound; // 从 main.cpp 获取 sound 模块

void PetModule::begin()
{
  if (!storage.begin())
  {
    Serial.println("[PetModule] ⚠️ 存储未初始化，状态不会保存");
  }
  else
  {
    if (!storage.load(petData))
    {
      petData.name = "mimi";
      petData.hunger = 50;
    }
  }

  Serial.printf("[PetModule] 欢迎回来，%s！\n", petData.name.c_str());
  ui.begin();
}

void PetModule::update()
{
  ui.update(petData.name, petData.hunger);
  // 可在此添加状态逐渐减少等逻辑
}

void PetModule::registerCommands()
{
  CommandDispatcher::get().registerCommand("pet", [this](const String &args)
                                           {
        if (args == "status") {
            showStatus();
        } else if (args == "feed") {
            feed();
        } else if (args.startsWith("name ")) {
            rename(args.substring(5));
        } else {
            Serial.println("[PetModule] 可用命令:");
            Serial.println(" - pet status");
            Serial.println(" - pet feed");
            Serial.println(" - pet name <新名字>");
        } });
}

void PetModule::showStatus()
{
  Serial.println("[PetModule] 当前宠物状态:");
  Serial.printf(" - 名字: %s\n", petData.name.c_str());
  Serial.printf(" - 饱食度: %d/100\n", petData.hunger);
}

void PetModule::feed()
{
  petData.hunger = min(petData.hunger + 20, 100);
  Serial.printf("[PetModule] 你喂了 %s，它发出喵喵叫～ 现在饱食度是 %d\n", petData.name.c_str(), petData.hunger);
  sound.playFeed(); // 播放提示音
  save();
}

void PetModule::rename(const String &newName)
{
  if (newName.length() > 0)
  {
    petData.name = newName;
    Serial.printf("[PetModule] 宠物名字改为：%s\n", petData.name.c_str());
    save();
  }
  else
  {
    Serial.println("[PetModule] 名字不能为空！");
  }
}

void PetModule::save()
{
  if (!storage.save(petData))
  {
    Serial.println("[PetModule] ⚠️ 状态保存失败！");
  }
}
