#ifndef CLIENT_H
#define CLIENT_H
#include "socketthreadbase.h"

class Client : public SocketThreadBase, QThread
{
public:
  Client(const QString &ipAddr, const ushort port );
  void startThread();
  void stopThread();
  bool isDone();
  Identity getIdentity() { return CLIENT; }
  void dropConnection();
protected:
  void run();
  void setDone( const bool newVal );

private:
  static const unsigned int CONNECT_TIME_OUT = 5 * 1000; // 5 seconds
  static const char *mStrings[];
  static const uint mNumStrings;
  bool mDone;

};

#endif // CLIENT_H
