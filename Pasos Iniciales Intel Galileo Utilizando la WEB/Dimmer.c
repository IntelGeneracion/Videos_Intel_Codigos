//Librerias
#include <Ethernet.h>

const int analogInPin = A0;
const int analogOutPin = 9;
const int analogOutPin2 = 10;
int sensorValue = 0; 
int outputValue = 0; 
char SensorVoltaje[100];
int estado=0;

int Puntos[100];
int Npuntos=20;
int Intencidad=0;
int Intencidad2=0;
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
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
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
        client.println("<meta http-equiv='refresh' content='1; url=http:/'/>");
        client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
        client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
        client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
        client.println("<script>");
        client.println("function drawPicture(){");
        client.println("var canvas = document.getElementById('example');");
        client.println("var context = canvas.getContext('2d');");
        
        sprintf(SensorVoltaje," context.fillStyle = 'rgba(%d,%d,0, 1)';",outputValue,outputValue);//100 ,outputValue%100);
        client.println(SensorVoltaje);
        client.println("context.beginPath();");
        client.println("context.arc(125,100,50,0,Math.PI*2,true);");
        client.println("context.fill();");
        sprintf(SensorVoltaje," context.fillStyle = 'rgba(%d,%d,0, 1)';",outputValue,outputValue);//100 ,outputValue%100);
        client.println(SensorVoltaje);
        client.println("context.beginPath();");
        client.println("context.moveTo(75,100);");
        client.println("context.lineTo(175,100);");
        client.println("context.lineTo(125,200);");
        client.println("context.fill();");
	client.println("context.fillStyle = 'rgb(200,200,200)';");
	client.println("context.fillRect (100, 150, 50, 50);");
	client.println("context.lineWidth = 1;");
	client.println("context.beginPath();");
	client.println("context.moveTo(100,150);");
	client.println("context.lineTo(150,150);");
	client.println("context.moveTo(100,170);");
	client.println("context.lineTo(150,160);");	
	client.println("context.moveTo(100,180);");
	client.println("context.lineTo(150,170);");
	client.println("context.moveTo(100,190);");
	client.println("context.lineTo(150,180);");
        
        
        
        sprintf(SensorVoltaje," context.fillStyle = 'rgba(%d,%d,0, 1)';",Intencidad2,Intencidad2);//100 ,outputValue%100);
        client.println(SensorVoltaje);
        client.println("context.beginPath();");
        client.println("context.arc(425,100,50,0,Math.PI*2,true);");
        client.println("context.fill();");
        sprintf(SensorVoltaje," context.fillStyle = 'rgba(%d,%d,0, 1)';",Intencidad2,Intencidad2);//100 ,outputValue%100);
        client.println(SensorVoltaje);
        client.println("context.beginPath();");
        client.println("context.moveTo(375,100);");
        client.println("context.lineTo(475,100);");
        client.println("context.lineTo(425,200);");
        client.println("context.fill();");
	client.println("context.fillStyle = 'rgb(200,200,200)';");
	client.println("context.fillRect (400, 150, 50, 50);");
	client.println("context.lineWidth = 1;");
	client.println("context.beginPath();");
	client.println("context.moveTo(400,150);");
	client.println("context.lineTo(450,150);");
	client.println("context.moveTo(400,170);");
	client.println("context.lineTo(450,160);");	
	client.println("context.moveTo(400,180);");
	client.println("context.lineTo(450,170);");
	client.println("context.moveTo(400,190);");
	client.println("context.lineTo(450,180);");
        
       
        
        client.println("context.stroke();");
        client.println("context.lineWidth = 1;");
        client.println("context.beginPath();");

        client.println("}");
        client.println("</script>");
        client.println("<style type='text/css'>");
         client.println(" canvas { border: 2px solid black; }");
        client.println("</style>");
        client.println("</head>");
        client.println("<body onload='drawPicture();'>");
        client.println("<H1>Intel</H1><hr/><br/>"); 
        client.println("<canvas id='example' width='500' height='200'>");
        client.println("There is supposed ");
        client.println("</canvas>");
        sprintf(SensorVoltaje, "<H1>bombillo izquierdo: %d,%d V </H1><H1>bombillo derecho: %d Intencidad </H1>"
		,outputValue/100 ,outputValue%100,Intencidad2);
        client.println(SensorVoltaje);
       
        client.println("<a href=\"/?button1on\"\">Mas</a>");
        client.println("<a href=\"/?button1off\"\">Menos</a>"); 
        
        client.println("<br/><br/><br/>");   
        client.println("<p>Intel</p>");  
        
        client.println("</body>");
        client.println("</html>");

           delay(1);
           client.stop();
            if (readString.indexOf("?button1on") >0)   {
              Intencidad++;
              if(Intencidad>8)  Intencidad=8;
              analogWrite(analogOutPin2, Intencidad*5);
              Intencidad2=Intencidad*31;
              
          }
           if (readString.indexOf("?button1off") >0)  {
              Intencidad--;
             if(Intencidad<0)  Intencidad=0;
              analogWrite(analogOutPin2, Intencidad*5);
              Intencidad2=Intencidad*31;
         }
           readString="";   
       }
        if (c == '\n')      {currentLineIsBlank = true;} 
        else if (c != '\r') {currentLineIsBlank = false;}   
      }
    }
    Serial.println("cliente desconectado");
  }
}
