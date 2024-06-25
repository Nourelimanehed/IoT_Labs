#include <WiFiNINA.h>
#include <PubSubClient.h>

const char* ssid = "Me";  // WiFi information
const char* password = "36044871";
//const char* mqtt_server = "test.mosquitto.org";  // MQTT information
const char* mqtt_server = "192.168.132.204";  // MQTT information
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

int ldr_pin = A0;
int force_pin = A1;

void setup_wifi() {
  delay(10);
  // Start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  pinMode(ldr_pin, INPUT);
  pinMode(force_pin, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ArduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement and resubscribe
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  // Read the light value
  int ldr_value = analogRead(ldr_pin);
  // Read the Force value
  int force_value = analogRead(force_pin);
  // Publish the Light reading to the MQTT server
 client.publish("Light", String(ldr_value).c_str());
  // Publish the Force reading to the MQTT server
 client.publish("Force", String(force_value).c_str());
  delay(1000);
}
