
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

void setup()
{
  
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
 // while (!Serial) continue;
    WiFi.disconnect();
   WiFi.begin("Username","Password");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(500);

  }
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output


}


void loop()
{

    
 StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
  { Serial.println("ERROR"); 
    return;
  }
  
  int data1=root["data1"];
  int data2=root["data2"];
  int tempB =data2/10;
  int tempA=(data2%10);  //Serial.print(tempB+"."+tempA);
 
  String stringOne = String(tempB);                        // using a constant integer  
  String stringTwo = String(tempA);                        // using a constant integer
  String stringThree = stringOne+"."+stringTwo;                        // using a constant integer
  float temp = (stringThree.toFloat());
  
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("   Data 1 ");
  Serial.println("");

  
  Serial.println(data1);
  Serial.println("   Data 2 ");

  Serial.print(temp);
 /* Serial.print(".");
  Serial.print(tempA);
  Serial.println("");*/
  Serial.println("---------------------xxxxx--------------------");


  
    if (client.connect("api.thingspeak.com",80)) {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "Y2J6TJFLGL2KSM94";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += data1;
      request_string += "&field2";
      request_string += "=";
      request_string += temp;
      http.begin(request_string);
      http.GET();
      http.end();
      digitalWrite(LED_BUILTIN, LOW);
      }
      delay(1000);
    
      digitalWrite(LED_BUILTIN, HIGH);
    //delay(14000);



}
