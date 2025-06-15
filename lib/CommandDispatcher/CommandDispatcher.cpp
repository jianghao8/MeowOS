#include "CommandDispatcher.h"

CommandDispatcher &CommandDispatcher::get()
{
  static CommandDispatcher instance;
  return instance;
}

void CommandDispatcher::registerCommand(const String &name, CommandHandler handler)
{
  commands[name] = handler;
}

void CommandDispatcher::dispatch(const String &name, const String &args)
{
  if (commands.count(name))
  {
    commands[name](args);
  }
  else
  {
    Serial.print("[Error] Unknown command: ");
    Serial.println(name);
  }
}
