#ifndef SERVER_H
#define SERVER_H
#include "socketthreadbase.h"
//#include "gamefield.h"
class Server : public SocketThreadBase, QThread
{
public:
  Server(const QString &ipAddr, const ushort port) : SocketThreadBase( ipAddr, port ) {}
  void startThread();
  void stopThread();
  Identity getIdentity() { return SERVER; }
  ~Server();
protected:
  void run();
  void serverRoutine( QTcpSocket *client );
};



#endif // SERVER_H
