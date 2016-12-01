#include "server.h"

void Server::serverRoutine(QTcpSocket *client )
{


    while (socket->state() == QAbstractSocket::ConnectedState && (!disconnected)) {
        if (commandOut.size() > 0) {
            sendCommand(commandOut.front());
            puts("server sends command\n");
            fflush(stdout);
            commandOut.pop_front();
        }
        commands cmd = receiveCommand();
        if (cmd != NO_CMD) {
            commandIn.push_back(cmd);
        }
   }
}


/**
  Note that Qt requires that the QTcpServer be in the same thread it is used in.
  So it cannot be declared as a class variable.  It must be in the run thread.
*/
void Server::run()
{
   disconnected = false;
  QHostAddress serverAddr( mIP );
  QTcpServer * server = new QTcpServer();
  if (server->listen(QHostAddress::Any, mPort)) {
    printf("Server::run: listen() succeeded\n");
    while (server->isListening() && getRunThread()) {
      if (server->waitForNewConnection(10000)) {
    printf("Server::run: got a TCP connection\n");
    socket = server->nextPendingConnection();
    serverRoutine( socket );
    }
      else {
    Sleep( 100 );
      }
    } // while
  }
  else {
    printf("Server::run: listen operation failed\n");
  }
  delete server;
}

Server::~Server(){
}

void Server::startThread()
{
  setRunThread( true );
  start();
}

void Server::stopThread()
{
  setRunThread( false );
}
