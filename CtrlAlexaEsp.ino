#include <IRremote.h>
#include <ESP8266WiFi.h>
#include <Espalexa.h>

//////////////// Datos de la red ///////////

const char* ssid = "Nombre de la red";
const char* pass  ="Contraseña de la red";

boolean conexionWifi = false;

Espalexa espalexa;      

EspalexaDevice* prueba;

////decode_results resultado;

int RECV_PIN = 4;

IRsend irsend(RECV_PIN);

void setup() {
  
 Serial.begin(115200);

 ////IRsend.enableIRIn();
 
  conexionWifi = setupWifi();
  delay(10);

  if(conexionWifi) {

    espalexa.addDevice("Nombre del dispositivo",encender);
   
    espalexa.begin();
  
  }else

    {
      while (1) {

        Serial.print("No fue posible conectar a la red wifi, revise los datos de conexion y reinicie ");
        delay(2500);
        
      }
    }
  }
  

void loop() {

  espalexa.loop();
  delay(1);
  

}

 //////////////////////////// Funcion de Encendido del dispositivo ////////////

void encender(uint8_t ON) {
    Serial.print("Dispositivo encendido ");
    
   
    if (ON) {

        irsend.sendNEC(0x20DF10EF,32);
        delay(1000);
      
    }
    else  {
        irsend.sendNEC(0x20DF10EF,32);
        delay(1000);
    }
}

////////////////// Configuracion de la red /////////////////////

boolean setupWifi()
{

boolean estado = true;
  int i = 0;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("");
  Serial.println("Conectando a la red...");

  
  Serial.print("Esperando conexion.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20){
      estado = false; break;
    }
    i++;
  }
  Serial.println("");
  if (estado){
    Serial.print("Conectado a ");
    Serial.println(ssid);
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Fallo la conexion.");
  }
  return estado;
}
