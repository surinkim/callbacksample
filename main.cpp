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

template < typename T, typename P >
class Callback : public CallbackBase
{
public:
  typedef void ( T::*Func ) ( P* );
  
  Callback( T* object, Func func ) : _object( object ), _func( func ) { _callbackType = P::CALLBACK_TYPE; };
  void Invoke( void* param ) const { ( _object->*_func )( ( P* ) param ); }
  
private:
  T* _object;
  Func _func;
};

class Library
{
public:
  void Start()
  {
    std::cout << "Start Lib." << std::endl;  
  }
  
  void Stop()
  {
    std::cout << "Stop Lib." << std::endl;
  }
  
  void SetCallback( CallbackBase& callback )
  {
    if ( callback.GetType() == ACT_TYPE_CALLBACK + 1 )  
    {
      _onStart = &callback;
    }
  }
  
  
private:
  CallbackBase* _onStart;
  CallbackBase* _onStop;
};
