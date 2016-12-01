#include "socketthreadbase.h"


void SocketThreadBase::setRunThread(bool newVal )
{
  QMutexLocker lock( &mMutex );
  mRunThread = newVal;
}

bool SocketThreadBase::getRunThread()
{
  QMutexLocker lock( &mMutex );
  return mRunThread;
}


int SocketThreadBase::waitForInput( QTcpSocket *socket )
{
  int bytesAvail = -1;
  while (socket->state() == QAbstractSocket::ConnectedState && getRunThread() && bytesAvail < 0) {
    if (socket->waitForReadyRead( 100 )) {
      bytesAvail = socket->bytesAvailable();
    }
    else {
      Sleep( 50 );
      return 0;
    }
  }
  return bytesAvail;
}

QString SocketThreadBase::readLine(QTcpSocket *socket )
{
  QString line = "";
  int bytesAvail = waitForInput( socket );
  if (bytesAvail > 0) {
    int cnt = 0;
    bool endOfLine = false;
    bool endOfStream = false;
    while (cnt < bytesAvail && (!endOfLine) && (!endOfStream)) {
      char ch;
      int bytesRead = socket->read(&ch, sizeof(ch));
      if (bytesRead == sizeof(ch)) {
    cnt++;
    line.append( ch );
    if (ch == '\r') {
      endOfLine = true;
    }
      }
      else {
    endOfStream = true;
      }
    }
  }
  return line;
}

void SocketThreadBase::sendCommand(commands cmd)
{
      socket->write(QByteArray((char*)&cmd,sizeof(commands)));
      if (! socket->waitForBytesWritten())
      {
           printf("sendCommand failed\n");
      }
}
commands SocketThreadBase::receiveCommand()
{
    int bytesAvail = waitForInput( socket );
    //int bytesAvail = socket->bytesAvailable();
    commands cmd;
    if (bytesAvail >= sizeof(commands)) {
        int bytesRead = socket->read((char*)&cmd, sizeof(commands));
    } else {
        cmd = NO_CMD;
    }
    return cmd;
}

void SocketThreadBase::pushCommand(commands cmd){
    puts("server push command\n");
    fflush(stdout);
    commandOut.push_back(cmd);
}

commands SocketThreadBase::getCommand(){
    commands cmd;
    if (commandIn.size()>0){
        cmd = commandIn.front();
        commandIn.pop_front();
    } else {
        cmd = NO_CMD;
    }

    return cmd;
}

void SocketThreadBase::writeLine(QTcpSocket *socket, const QString &line)
{
  if (line.length() > 0) {
    socket->write( line.toStdString().c_str() );
    if (! socket->waitForBytesWritten()) {
      if (getIdentity() == SERVER) {
    printf("Server - ");
      }
      else if (getIdentity() == CLIENT) {
    printf("Client - ");
      }
      else {
    printf("Unknown identity - ");
      }
      printf("writeLine: the write to the socket failed\n");
    }
  }
}
 bool SocketThreadBase::isConnected(){
     return (!disconnected);
 }
