#include "InputManager.h"
#include "CommandDispatcher.h"

void InputManager::begin(HardwareSerial &serial) {
  _serial = &serial;
  _buffer = "";
}

void InputManager::appendChar(char c) {
  if (_buffer.length() < 64) {
    _buffer += c;
  }
}

void InputManager::backspace() {
  if (_buffer.length() > 0) {
    _buffer.remove(_buffer.length() - 1);
  }
}

String InputManager::getBuffer() const {
  return _buffer;
}

void InputManager::update() {
  if (_serial->available()) {
    char c = _serial->read();
    if (c == '\n' || c == '\r') {
      // 拆分命令与参数
      String cmd, args;
      int spaceIndex = _buffer.indexOf(' ');
      if (spaceIndex >= 0) {
        cmd = _buffer.substring(0, spaceIndex);
        args = _buffer.substring(spaceIndex + 1);
      } else {
        cmd = _buffer;
        args = "";
      }
      CommandDispatcher::get().dispatch(cmd, args);
      _buffer = "";
    } else if (c == 8 || c == 127) {
      backspace();
    } else {
      appendChar(c);
    }
  }
}
