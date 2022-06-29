#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MSG_BUFFER_SIZE (64)

const char* WIFI_SSID = "Red Wifi A_2";
const char* PASSWORD = "Turing0906";
const char* MQTT_SERVER_ADDRESS = "192.168.0.15";
const unsigned short int MQTT_SERVER_PORT = 1883;

/*
 * Este código que sigue a continuación es boilerplate.
 * No necesita prestarse atención ni alterarse. Saltar directamente al siguiente comentario.
 */

void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  randomSeed(micros());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  callbackAction(topic, payload, length);
}

void mqttReconnect(PubSubClient& client) {
  while (!client.connected()) {
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      mqttSubscribeClient(client);
    } else {
      Serial.print("failed to connect to MQTT Server");
      delay(5000);
    }
  }
}

void mqttStart(PubSubClient& client) {
  if(!client.connected()) {
    mqttReconnect(client);
  }
  client.loop();
}

WiFiClient espClient;
PubSubClient MQTTCLIENT(espClient);


/*
 * Estas son las únicas dos funciones necesarias para cada programa.
 * Se encargan de suscribirse a los tópicos y de ejecutar las sentencias deseadas cuando se recibe el callback
 */

void mqttSubscribeClient(PubSubClient& client) {
  client.subscribe("oficina/nodered");
}


void callbackAction(char* topic, byte* payload, unsigned int length) {
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
  MQTTCLIENT.publish("oficina/esp", "mi mensaje de prueba");
}


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  MQTTCLIENT.setServer(MQTT_SERVER_ADDRESS, MQTT_SERVER_PORT);
  MQTTCLIENT.setCallback(callback);
}


void loop() {
  mqttStart(MQTTCLIENT);
}
