#include "DisplayManager.h"
#include <M5Cardputer.h>
#include <M5GFX.h>

void DisplayManager::begin()
{
  M5Cardputer.Display.setFont(&fonts::lgfxJapanGothic_8);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setTextColor(WHITE, BLACK);
  M5Cardputer.Display.fillScreen(BLACK);
}

void DisplayManager::update()
{
  // 可以在此添加其他更新逻辑
}

void DisplayManager::updateInputText(const String &text)
{
  if (_showCommandBox)
  {
    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 20, M5Cardputer.Display.width(), 20, BLACK);
    M5Cardputer.Display.setCursor(0, M5Cardputer.Display.height() - 18);
    M5Cardputer.Display.print("> " + text);
  }
}

void DisplayManager::toggleCommandBox()
{
  _showCommandBox = !_showCommandBox;
  if (!_showCommandBox)
  {
    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 20, M5Cardputer.Display.width(), 20, BLACK);
  }
}

void DisplayManager::setStatus(bool wifiConnected, int batteryLevel)
{
  _wifiConnected = wifiConnected;
  _batteryLevel = batteryLevel;
  M5Cardputer.Display.fillRect(0, 0, M5Cardputer.Display.width(), 10, BLACK);
  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.printf("WiFi: %s | Battery: %d%%", _wifiConnected ? "Connected" : "Disconnected", _batteryLevel);
}
