#ifndef NET_MODULE_H
#define NET_MODULE_H

#include <Arduino.h>

class NetModule
{
public:
  void begin();
  void update(); // 未来可用于保持连接等
  void registerCommands();

private:
  void scanNetworks();
  void connectToNetwork(const String &ssid, const String &password);
  void printStatus();
};

#endif
