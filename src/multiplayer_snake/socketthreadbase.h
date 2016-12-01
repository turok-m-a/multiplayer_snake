#ifndef SOCKETTHREADBASE_H
#define SOCKETTHREADBASE_H



#include "windows.h"
#include "QMutex"
#include "QThread"
#include "QTcpServer.h"
#include "QTcpSocket"
#include "QVector"
#include "QString"
#include "commands.h"
#include "deque"
#define GAME_PORT 27015
const char LISTEN_ANY[]  = "0.0.0.0";
class SocketThreadBase
{
public:
  SocketThreadBase(const QString &ipAddr, const ushort port ) : mIP( ipAddr ), mPort( port )
  {
    mRunThread = false;
  }
  enum Identity {
    BAD_IDENTITY,
    SERVER,
        CLIENT
  };
  virtual void startThread() = 0;
  virtual void stopThread() = 0;
  virtual Identity getIdentity() = 0;

  void pushCommand(commands);
  commands getCommand();
  bool isConnected();
protected:
  QMutex mMutex;
  const QString mIP;
  const ushort mPort;
  void setRunThread( bool newVal );
  bool getRunThread();
  void run();
  QString readLine(QTcpSocket *socket );
  int waitForInput( QTcpSocket *socket );
  void writeLine( QTcpSocket *client, const QString &line );
  void sendCommand(commands);
  commands receiveCommand();
  QTcpSocket * socket;
  bool disconnected;
  std::deque<commands> commandOut;
  std::deque<commands> commandIn;
private:
  bool mRunThread;

};


#endif // SOCKETTHREADBASE_H
