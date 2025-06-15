#include "SoundModule.h"
#include "CommandDispatcher.h"

#ifdef M5UNIFIED_H
#include <M5Unified.h>
#endif

void SoundModule::begin()
{
  Serial.println("[SoundModule] 初始化");
  playStartup();
}

void SoundModule::registerCommands()
{
  CommandDispatcher::get().registerCommand("sound", [this](const String &args)
                                           {
        if (args == "on") {
            muted = false;
            Serial.println("[SoundModule] 音效已开启");
        } else if (args == "off") {
            muted = true;
            Serial.println("[SoundModule] 已进入静音模式");
        } else if (args == "status") {
            Serial.printf("[SoundModule] 当前：%s\n", muted ? "静音" : "有声");
        } else {
            Serial.println("[SoundModule] 可用命令:");
            Serial.println(" - sound on");
            Serial.println(" - sound off");
            Serial.println(" - sound status");
        } });
}

void SoundModule::tone(int freq, int duration)
{
  if (muted)
    return;

  // 如果 M5Speaker 存在
#ifdef M5UNIFIED_H
  if (M5.Speaker.isEnabled())
  {
    M5.Speaker.tone(freq, duration);
  }
#endif
}

void SoundModule::playStartup()
{
  tone(1000, 100);
  delay(100);
  tone(1500, 100);
}

void SoundModule::playFeed()
{
  tone(900, 80);
  delay(40);
  tone(1200, 100);
}

void SoundModule::playError()
{
  tone(500, 300);
}
