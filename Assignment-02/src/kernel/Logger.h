#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"

/**
 * Singleton Pattern
 */
class LoggerService
{
private:
  LoggerService() {}

public:
  // static LoggerService &instance()
  // {
  //   static LoggerService logger;
  //   return logger;
  // }

  // Delete copy constructor and assignment to enforce singleton
  LoggerService(const LoggerService &) = delete;
  LoggerService &operator=(const LoggerService &) = delete;

  void log(const String &msg);
};

extern LoggerService Logger;

#endif