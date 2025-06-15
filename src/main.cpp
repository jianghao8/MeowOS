#include <Arduino.h>
#include <M5Cardputer.h>
#include <WiFi.h>
#include <M5GFX.h>

#include "InputManager.h"
#include "CommandDispatcher.h"
#include "PetModule.h"
#include "NetModule.h"
#include "SoundModule.h"
#include "DisplayManager.h"
#include "SettingModule.h"

InputManager input;
PetModule pet;
NetModule net;
SoundModule sound;
DisplayManager display;
SettingModule setting;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  M5Cardputer.begin();

  M5Cardputer.Display.setFont(&fonts::lgfxJapanGothic_8);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setTextColor(WHITE, BLACK);
  M5Cardputer.Display.fillScreen(BLACK);

  Serial.println("=== MeowOS Boot ===");
  Serial.println("Type 'help' to get started.");

  input.begin(Serial);
  sound.begin();
  sound.registerCommands();
  setting.begin();
  setting.registerCommands();

  CommandDispatcher::get().registerCommand("help", [](const String &args) {
    Serial.println("[MeowOS] 可用命令:");
    Serial.println(" - help");
    Serial.println(" - info");
    Serial.println(" - pet status / feed / name");
    Serial.println(" - wifi scan / connect <SSID> <密码> / status");
    Serial.println(" - sound on / off / status");
    Serial.println(" - set theme dark/light/status");
  });

  CommandDispatcher::get().registerCommand("info", [](const String &args) {
    Serial.println("[MeowOS] 设备信息:");
    Serial.println(" - MeowOS v0.1.0");
    Serial.println(" - 板子：M5Stack Cardputer");
  });

  pet.begin();
  pet.registerCommands();
  net.begin();
  net.registerCommands();
  display.begin();
}

void loop() {
  M5Cardputer.update();

  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
      auto status = M5Cardputer.Keyboard.keysState();
      for (auto c : status.word) {
        input.appendChar(c);
      }
      if (status.del) {
        input.backspace();
      }
      if (status.enter) {
        display.toggleCommandBox();
      }
    }
  }

  input.update();
  display.updateInputText(input.getBuffer());

  pet.update();
  net.update();

  display.setStatus(WiFi.isConnected(), 85);
  display.update();

  delay(10);
}
