#include "stdafx.h"

#include <iostream>
#include <Windows.h>

enum { ACT_TYPE_CALLBACK = 1000 };

struct StartResult
{
  enum { CALLBACK_TYPE = ACT_TYPE_CALLBACK + 1 };
  int errorCode;
};

////////////////////////////////////////////////////
class CallbackBase
{
public:
  virtual ~CallbackBase() {};
  
  virtual void Invoke( void* param ) const = 0;
  const int GetType() { return _callbackType; }
  
protected:
  int _callbackType;
};
