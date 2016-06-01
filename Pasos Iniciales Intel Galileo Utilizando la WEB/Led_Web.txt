//Librerias
#include <Ethernet.h>

//Direccion MAC de la tarjeta Galileo
byte mac[] = { 0x98, 0x4F, 0xEE, 0x01, 0x46, 0x64 };

//Declaracion del servidor Ethernet, escuchando al puerto 80
EthernetServer server = EthernetServer(80); 
String readString;
EthernetClient client;

void setup() {
  
  pinMode(13, OUTPUT);  
  
  system("ifdown eth0");
  delay(500); 
  system("ifup eth0"); 
  delay(500);
  
  Serial.begin(9600);

  Serial.println("Configurando Ethernet...");
  if(!Ethernet.begin(mac)) {
    Serial.println("Error");
  }
  else {
    Serial.println("ok");
  }
 
  delay(2000);
  Serial.println("Listo");
  server.begin(); 
}

void loop() {
  
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
         if (readString.length() < 100) {readString += c;}

        if (c == '\n' && currentLineIsBlank) {
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML><HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Intel</TITLE></HEAD>");
           client.println("<BODY><H1>Intel</H1><hr/><br/><H2>Controles</H2><br/>"); 
           client.println("<a href=\"/?button1on\"\">Led ON</a>");
           client.println("<a href=\"/?button1off\"\">Led OFF</a>");  
           client.println("<br/><br/><br/>");   
           client.println("<p>Intel</p>");  
           client.println("<br /></BODY></HTML>"); 
     
           delay(1);
           client.stop();
           if (readString.indexOf("?button1on") >0)   {digitalWrite(13, HIGH);}
           if (readString.indexOf("?button1off") >0)  {digitalWrite(13, LOW);}
           readString="";   
        }
        if (c == '\n')      {currentLineIsBlank = true;} 
        else if (c != '\r') {currentLineIsBlank = false;}   
      }
    }
    Serial.println("cliente desconectado");
  }
}
