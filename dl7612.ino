String response = ""; 
void loop() { 
 sendCommand("AT+INFO\r\n");
 sendCommand("AT+CGATT\r\n"); 
 sendData(5,"HELLO"); 
 delay(10000);  
}
void setup() { 
Serial.begin(115200); 
Serial2.begin(115200); 
sendCommand("AT\r\n");
sendCommand("AT+INFO\r\n");
sendCommand("AT+NCONFIG\r\n");
sendCommand("AT+DEVEUI\r\n");
sendCommand("AT+APPKEY\r\n");
sendCommand("AT+APPEUI\r\n");
sendCommand("AT+NRB\r\n");
delay(40000); 
}
void sendCommand(String atComm){
response = "";
Serial2.print(atComm);
Serial.println("*******AT Command Sent");
Serial.print(atComm);
delay(300);
while(Serial2.available()){
     char ch = Serial2.read();
     //delay(500);
     response += ch;
     }
     Serial.println(response);
}
void sendData(int type, String data){
  String command = (String)"AT+NCMGS=" + type + "," +data + (String)"\r\n";
  sendCommand(command);
}
