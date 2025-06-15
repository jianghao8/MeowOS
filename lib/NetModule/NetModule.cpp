#include "NetModule.h"
#include "CommandDispatcher.h"
#include <WiFi.h>

void NetModule::begin()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // 清除残留
  delay(100);
  Serial.println("[NetModule] WiFi 初始化完成");
}

void NetModule::update()
{
  // 可扩展：断线自动重连等
}

void NetModule::registerCommands()
{
  CommandDispatcher::get().registerCommand("wifi", [this](const String &args)
                                           {
        if (args == "scan") {
            scanNetworks();
        } else if (args.startsWith("connect ")) {
            int space1 = args.indexOf(' ');
            int space2 = args.indexOf(' ', space1 + 1);
            if (space2 != -1) {
                String ssid = args.substring(space1 + 1, space2);
                String pass = args.substring(space2 + 1);
                connectToNetwork(ssid, pass);
            } else {
                Serial.println("[NetModule] 格式错误：wifi connect <SSID> <密码>");
            }
        } else if (args == "status") {
            printStatus();
        } else {
            Serial.println("[NetModule] 可用命令:");
            Serial.println(" - wifi scan");
            Serial.println(" - wifi connect <SSID> <密码>");
            Serial.println(" - wifi status");
        } });
}

void NetModule::scanNetworks()
{
  Serial.println("[NetModule] 正在扫描 WiFi...");

  int n = WiFi.scanNetworks();
  if (n == 0)
  {
    Serial.println("未发现任何网络");
  }
  else
  {
    Serial.printf("共发现 %d 个网络：\n", n);
    for (int i = 0; i < n; ++i)
    {
      Serial.printf(" - %s (%ddBm)%s\n",
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i),
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? " [开放]" : ""));
    }
  }
}

void NetModule::connectToNetwork(const String &ssid, const String &password)
{
  Serial.printf("[NetModule] 正在连接到 %s...\n", ssid.c_str());
  WiFi.begin(ssid.c_str(), password.c_str());

  int retries = 15;
  while (WiFi.status() != WL_CONNECTED && retries-- > 0)
  {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n[NetModule] 连接成功！");
    Serial.print("IP 地址: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\n[NetModule] 连接失败！");
  }
}

void NetModule::printStatus()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("[NetModule] 当前已连接");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("[NetModule] 未连接");
  }
}
