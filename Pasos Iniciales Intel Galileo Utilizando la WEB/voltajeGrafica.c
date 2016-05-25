//Librerias
#include <Ethernet.h>

const int analogInPin = A0;
const int analogOutPin = 9;
int sensorValue = 0; 
int outputValue = 0; 
char SensorVoltaje[100];

int Puntos[100];
int Npuntos=20;
/*
int S0=0;
int S1=0;
int S2=0;
int S3=0;
int S4=0;
int S5=0;
*/
//Direccion MAC de la tarjeta Galileo
byte mac[] = { 0x98, 0x4F, 0xEE, 0x01, 0x46, 0x64 };

//Declaracion del servidor Ethernet, escuchando al puerto 80
EthernetServer server = EthernetServer(80); 
String readString;
EthernetClient client;

void setup() {
  
  pinMode(12, OUTPUT);  
  
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
  
  sensorValue = analogRead(analogInPin);             
  outputValue = map(sensorValue, 0, 1023, 0, 500);  
  analogWrite(analogOutPin, outputValue);
  
  
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
        client.println("<html><head><title>Intel</title>");
        client.println("<meta http-equiv='refresh' content='1' />");
        client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
        client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
        client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
        client.println("<script>");
        client.println("function drawPicture(){");
        client.println("var canvas = document.getElementById('example');");
        client.println("var context = canvas.getContext('2d');");
        
        client.println("context.moveTo(0, 100);");
        client.println("context.lineTo(500, 100);");
        client.println("context.moveTo(0, 200);");
        client.println("context.lineTo(500, 200);");
        client.println("context.moveTo(0, 300);");
        client.println("context.lineTo(500, 300);");
        client.println("context.moveTo(0, 400);");
        client.println("context.lineTo(500, 400);");
        client.println("context.font = '15px Arial';");
        client.println("context.strokeText('5V',5,15);");
        client.println("context.strokeText('4V',5,100);");
        client.println("context.strokeText('3V',5,200);");
        client.println("context.strokeText('2V',5,300);");
        client.println("context.strokeText('1V',5,400);");		
        client.println("context.strokeStyle = 'hsla(444, 0%, 0%, 1)';");
       client.println(" context.stroke();");
        
        client.println("context.stroke();");
        client.println("context.lineWidth = 1;");
        client.println("context.beginPath();");

        for(int n=0; n<Npuntos; n++) {Puntos[n]=Puntos[n+1];}
        Puntos[Npuntos]=outputValue;
        int y=0;
        for(int n=0; n<=Npuntos; n++) {
          sprintf(SensorVoltaje,"context.lineTo(%d,%d);",y,500-(Puntos[n]));//100 ,outputValue%100);
          client.println(SensorVoltaje);
          y=y+25;
        }

        client.println("context.strokeStyle = 'hsla(120, 100%, 50%, 1)';");
        client.println("context.stroke();");
        client.println("}");
        client.println("</script>");
        client.println("<style type='text/css'>");
         client.println(" canvas { border: 2px solid black; }");
        client.println("</style>");
        client.println("</head>");
        client.println("<body onload='drawPicture();'>");
        client.println("<H1>Intel</H1><hr/><br/><H2>Voltaje</H2><br/>"); 
        client.println("<canvas id='example' width='500' height='500'>");
        client.println("There is supposed ");
        client.println("</canvas>");
        sprintf(SensorVoltaje, "<H1>%d,%d V  </H1>",outputValue/100 ,outputValue%100);
        client.println(SensorVoltaje);
        
        client.println("<br/><br/><br/>");   
        client.println("<p>Intel</p>");  
        
        client.println("</body>");
        client.println("</html>");

           delay(1);
           client.stop();
           readString="";   
       }
        if (c == '\n')      {currentLineIsBlank = true;} 
        else if (c != '\r') {currentLineIsBlank = false;}   
      }
    }
    Serial.println("cliente desconectado");
  }
}

