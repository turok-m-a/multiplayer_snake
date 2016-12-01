#include "client.h"

Client::Client(const QString &ipAddr, const ushort port ): SocketThreadBase( ipAddr, port ){
    mDone = false;
}

void Client::setDone(const bool newVal)
{
  QMutexLocker lock( &mMutex );
  mDone = newVal;
}

bool Client::isDone()
{
  QMutexLocker lock( &mMutex );
  return mDone;
}

/**
    Note that the QTcpSocket object must be in the run thread.  It cannot
    be a class variable.
*/
void Client::run()
{
  socket = new QTcpSocket();
  disconnected = false;
  QHostAddress hostAddr( mIP );
  socket->connectToHost( hostAddr, mPort );
  if (socket->waitForConnected( CONNECT_TIME_OUT )) {
    QHostAddress hostAddr = socket->localAddress();
    QString addr = "";
    if (hostAddr != QHostAddress::Null) {
      addr = hostAddr.toString();
    }
    printf("Client connected");
    if (addr.length() > 0) {
      printf(" on address %s:%04d", addr.toStdString().c_str(), socket->localPort() );
    }
    printf("\n");
    //int ix = 0;
    while (socket->state() == QAbstractSocket::ConnectedState && (!disconnected)) {
        //sleep(100000);
        if (commandOut.size() > 0) {
            sendCommand(commandOut.front());
            commandOut.pop_front();
        }
        commands cmd = receiveCommand();
        if (cmd != NO_CMD) {
            commandIn.push_back(cmd);
        }
      //QString line( mStrings[ix] );
     // writeLine(&socket, line);
     // QString echoedLine = readLine( &socket );
     // if (echoedLine.length() > 0) {

    //else {
    //  printf("%s\n", line.toStdString().c_str() );
   // }
     // }
     // ix++;
    } // while
  }
  else {
    printf("Client socket failed to connect\n");
  }
  setDone( true );
}

void Client::dropConnection()
{
    socket->disconnectFromHost();
    disconnected = true;
}

void Client::startThread()
{
  setRunThread( true );
  start();
}

void Client::stopThread()
{
}


const char *Client::mStrings[] = {
  "",""

};

const uint Client::mNumStrings = sizeof Client::mStrings / sizeof( *Client::mStrings );
