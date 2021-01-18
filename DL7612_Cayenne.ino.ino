#include <CayenneLPP.h>

#include <stdio.h>

#include <string.h>

CayenneLPP lpp(51);
void loop() {
  int dlen;
  sendCommand("AT+CGATT");
  lpp.reset(); // clear the buffer
  lpp.addTemperature(2, 31.1);
  lpp.addRelativeHumidity(3, 51.2);
  dlen = lpp.getSize();
  Serial.println(lpp.getSize());
  char hex_str[(dlen * 2) + 1];
  Serial.println("+++++++++++Show Data++++++++++++");
  //Convert STRING Data to HEX
  string2hexString((char * ) lpp.getBuffer(), hex_str, dlen); //ascii_str, hex_str
  Serial.println(hex_str);
  Serial.println("+++++++++++SEND Data++++++++++++");
  sendHexData(dlen, hex_str);
  delay(10000);
}
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  sendCommand("AT");
  sendCommand("AT+INFO");
  sendCommand("AT+NCONFIG");
  sendCommand("AT+DEVEUI");
  sendCommand("AT+APPKEY");
  sendCommand("AT+APPEUI");
  sendCommand("AT+NRB");
  delay(40000);
}
void sendCommand(String atComm) {
  String response;
  Serial2.print(atComm + "\r\n");
  Serial.println("*******AT Command Sent");
  Serial.print(atComm + "\r\n");
  delay(300);
  while (Serial2.available()) {
    char ch = Serial2.read();
    response += ch;
  }
  Serial.println(response);
}
void sendData(int type, String data) {
  Serial.println("*******TEXT Build");
  String command = (String)
  "AT+NCMGS=" + type + "," + data + (String)
  "\r\n";
  sendCommand(command);
}
void sendHexData(int type, String data) {
  Serial.println("*******HEX Build");
  String command = (String)
  "AT+NMGS=" + type + "," + data + (String)
  "\r\n";
  sendCommand(command);
}
void string2hexString(char * input, char * output, int dlen) {
  int loop = 0;
  int i = 0;
  //int count = strlen(input);
  int count = dlen;
  Serial.println("count");
  Serial.println(count);
  while (loop < count) {
    sprintf((char * )(output + i), "%02X", input[loop]);
    loop += 1;
    i += 2;
  }
  //insert NULL at the end of the output string
  output[i++] = '\0';
}
