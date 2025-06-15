#include "SettingModule.h"
#include "CommandDispatcher.h"
#include <FS.h>
#include <SD.h>
#include <M5Unified.h>

void SettingModule::begin()
{
  load();
  applyTheme();
}

void SettingModule::registerCommands()
{
  CommandDispatcher::get().registerCommand("set", [this](const String &args)
                                           {
        if (args == "theme light") {
            theme = "light";
            save();
            applyTheme();
            Serial.println("[Setting] 已切换为浅色主题");
        } else if (args == "theme dark") {
            theme = "dark";
            save();
            applyTheme();
            Serial.println("[Setting] 已切换为深色主题");
        } else if (args == "theme status") {
            Serial.printf("[Setting] 当前主题：%s\n", theme.c_str());
        } else {
            Serial.println("[Setting] 可用命令:");
            Serial.println(" - set theme light");
            Serial.println(" - set theme dark");
            Serial.println(" - set theme status");
        } });
}

void SettingModule::save()
{
  File f = SD.open(configPath, FILE_WRITE);
  if (f)
  {
    f.print(theme);
    f.close();
  }
}

void SettingModule::load()
{
  if (!SD.exists(configPath))
    return;
  File f = SD.open(configPath);
  if (f)
  {
    theme = f.readStringUntil('\n');
    theme.trim();
    f.close();
  }
}

void SettingModule::applyTheme()
{
  if (theme == "light")
  {
    M5.Display.setTextColor(BLACK, WHITE);
    M5.Display.fillScreen(WHITE);
  }
  else
  {
    M5.Display.setTextColor(WHITE, BLACK);
    M5.Display.fillScreen(BLACK);
  }
}

bool SettingModule::isDarkTheme() const
{
  return theme == "dark";
}
