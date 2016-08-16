/*
  Socket.IO client for the Arduino
  
  Copyright 2011 Kevin Rohling http://kevinrohling.com
  Copyright 2013 Bill Roy
  Copyright 2015 Florent Vidal
  Copyright 2016 AlvinHKH http://alvinhkh.com

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation
  files (the "Software"), to deal in the Software without
  restriction, including without limitation the rights to use,
  copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following
  conditions:
  
  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Ethernet.h>

// Length of static data buffers
#define DATA_BUFFER_LEN 120
#define SID_LEN 24

class SocketIOClient {
public:
  Client *client;         // instance of client class (e.g. EthernetClient)

  SocketIOClient(Client *client_instance);
  typedef void (*DataArrivedDelegate) (SocketIOClient client, String data);
  bool connect(char hostname[], int port = 80);
  bool connected();
  void heartbeat(int select);
  bool monitor();
  void println(String msg);
  bool reconnect(char hostname[], int port = 80);
  void setOnDataArrived(DataArrivedDelegate dataArrivedDelegate);
  void send(String RID, String Rname, String Rcontent);
  void stop();
  
private:
  DataArrivedDelegate dataArrivedDelegate;
  char databuffer[DATA_BUFFER_LEN];
  char *dataptr;
  char sid[SID_LEN];
  char key[28];
  char *hostname;
  int port;

  void eatHeader(void);
  void findColon(char which);
  void parser(int index);
  bool readHandshake();
  void readLine();
  void sendHandshake(char hostname[]);
  void terminateCommand(void);
  bool waitForInput(void);
};
