#include <SPI.h>
#include <Ethernet.h>
// Dirección MAC de la tarjeta  Galileo (esta legible en el conector  Ethernet de la Galileo).
byte mac[] = { 0x??, 0x??, 0x??, 0x??, 0x??, 0x?? };
//La dirección IP de la tarjeta Galileo, asignara una aleatoria si no tiene DHCP.
byte ip[] = { ??, ??, ??, ?? };
void setup() {
 delay(5000);
Serial.println("Configurando Ethernet usando DHCP");
if (Ethernet.begin(mac) == 0) {
Serial.begin(9600);
Serial.println("Error al configurar Ethernet por DHCP");
Serial.println("configurando Ethernet con la IP estática");
Ethernet.begin(mac, ip);
} else
Serial.println("Muy bien");
system("ifupeth0"); // interface Ethernet  
}
void loop () {}
