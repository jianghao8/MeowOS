#include "PetUI.h"
#include <M5Cardputer.h>
#include <M5GFX.h>

// 建议统一写法：避免 fonts 不明确错误
using namespace m5gfx;

void PetUI::begin()
{
  // 显式指定命名空间，避免 IntelliSense 报错
  M5Cardputer.Display.setFont(&m5gfx::fonts::lgfxJapanGothic_8);
  M5Cardputer.Display.fillRect(0, 16, 240, 104, BLACK);
}

void PetUI::update(const String &name, int hunger)
{
  drawFace(hunger);
  drawInfo(name, hunger);
}

void PetUI::drawFace(int hunger)
{
  String face;
  if (hunger > 80)
    face = "(=^.^=)";
  else if (hunger > 50)
    face = "(=^_^=)";
  else if (hunger > 30)
    face = "(=._.=)";
  else
    face = "(T_T)";

  M5Cardputer.Display.setTextSize(2);
  M5Cardputer.Display.fillRect(0, 40, 240, 30, BLACK); // 清除区域
  M5Cardputer.Display.setCursor(60, 40);
  M5Cardputer.Display.println(face);
}

void PetUI::drawInfo(const String &name, int hunger)
{
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.fillRect(0, 70, 240, 30, BLACK); // 清除旧文字
  M5Cardputer.Display.setCursor(10, 75);
  M5Cardputer.Display.printf("名字: %s\n", name.c_str());
  M5Cardputer.Display.printf("饱食度: %d/100\n", hunger);
}
