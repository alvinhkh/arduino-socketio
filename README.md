# Socket.IO Library for Arduino

This library is based on multiple people's work (Kevin Rohling, Bill Roy and Florent Vidal). 
The main changes is easier to use with wider variety of shields and modules.
You can pass any Client class (e.g. WifiClient, EthernetClient, ESP8266Client in SparkFunESP8266WiFi) as long as the class is adheres to the Ethernet.Client primitive.


```
char* ssid = ""; // wifi ssid
char* pass = ""; // wifi password
char* io_host = "";
int io_port = 3000;
WiFiClient client;
SocketIOClient io((Client *)&client);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  io.setOnDataArrived(ondata);
  if (!io.connect(io_host, io_port)) {
    Serial.println("connection failed");
  }
  io.send("message", "content", "Hello World!"); // {"content": "Hello World!"}
}

void loop() {
  client.monitor();
}

void ondata(SocketIOClient io, String data) {
  String id = data.substring(data.indexOf("42[") + 4, data.indexOf("\","));
  String content = data.substring(data.indexOf("\",") + 2, data.indexOf("]"));
  // id=message, content={"content": "Hello World!"}
  Serial.print(F("id="));
  Serial.println(id);
  Serial.print(F(", content="));
  Serial.println(content);
}
```