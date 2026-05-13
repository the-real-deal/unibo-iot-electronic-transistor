#include "Arduino.h"
#include "MsgService.h"

String content;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable()
{
  return msgAvailable;
}

Msg *MsgServiceClass::receiveMsg()
{
  if (msgAvailable)
  {
    Msg *msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = "";
    return msg;
  }
  else
  {
    return NULL;
  }
}

void MsgServiceClass::init()
{
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println(F("Begin"));
  content.reserve(64);
  content = F("");
  currentMsg = NULL;
  msgAvailable = false;
}

void MsgServiceClass::sendMsg(const String &msg)
{
  Serial.println(msg);
  Serial.flush();
}

void serialEvent()
{
  /* reading the content */
  while (Serial.available())
  {
    char ch = (char)Serial.read();
    if (ch == '\n')
    {
      MsgService.currentMsg = new Msg(content);
      MsgService.msgAvailable = true;
    }
    else
    {
      content += ch;
    }
  }
}

bool MsgServiceClass::isMsgAvailable(Pattern &pattern)
{
  return (msgAvailable && pattern.match(*currentMsg));
}

Msg *MsgServiceClass::receiveMsg(Pattern &pattern)
{
  if (msgAvailable && pattern.match(*currentMsg))
  {
    Msg *msg = currentMsg;
    msgAvailable = false;
    currentMsg = NULL;
    content = F("");
    return msg;
  }
  else
  {
    return NULL;
  }
}
