#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include <Arduino.h>
#include <map>
#include <functional>

class CommandDispatcher
{
public:
  using CommandHandler = std::function<void(const String &args)>;

  static CommandDispatcher &get();
  void registerCommand(const String &name, CommandHandler handler);
  void dispatch(const String &name, const String &args);

private:
  std::map<String, CommandHandler> commands;
};

#endif
