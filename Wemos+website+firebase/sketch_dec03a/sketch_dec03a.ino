#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>
//#include <FirebaseArduino.h>
//time taking library
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pk.pool.ntp.org", 18000, 60000);  //here you have to write zone value taken from  https://www.epochconverter.com/timezones
Servo myservo;
#define FIREBASE_HOST "https://wemostesting-41ab1-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "Ejh2eQkVhd75Y2s7Ld8OHL1o4Cehc1U2AcsPjgsx"
//#define WIFI_SSID "TP-LINK_NBB"
#define WIFI_SSID "laptop"
#define WIFI_PASSWORD "99551100"

#define btn D5
#define btn2 D6
#define led D0
#define led2 D1
#define led3 D8

FirebaseData firebaseData;

FirebaseJson json;

//void printResult(FirebaseData &data);
long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void setup() {
  // put your setup code here, to run once:
    
 
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
    myservo.attach(D4);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  // Udp.begin(localPort);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(".");
    delay(300);
  }

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  timeClient.begin();
  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");


}

void loop() {
  // put your main code here, to run repeatedly:
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    while (WiFi.status() != WL_CONNECTED)
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print(".");
      delay(300);
    }

  }
  else
  {
    digitalWrite(LED_BUILTIN, 1);
  }
  String path = "wemos";
  //   int data=firebaseData.intData();
  if (Firebase.getInt(firebaseData, "/wemos/led")) {

    if (firebaseData.dataType() == "int") {
      int data = firebaseData.intData();
      Serial.println(firebaseData.intData());
      //      Serial.println(data);
      if (firebaseData.intData() == 1)
      {
        Serial.println("PASSED On he");
        digitalWrite(led3, HIGH);
      }
      else
      {
        Serial.println("NOT PASSED off he");
        digitalWrite(led3, LOW);

      }
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }

  if (Firebase.getInt(firebaseData, "/wemos/servo")) {

    if (firebaseData.dataType() == "int") {
      int data = firebaseData.intData();
      Serial.print("Servo:");
      Serial.println(firebaseData.intData());
      int value=firebaseData.intData();
      if(firebaseData.intData()){
        Serial.println("starting SERVO:");
  int val=map(value,0,value,0,255);
         myservo.write(val); 
        
    
      //      Serial.println(data);
//      if (firebaseData.intData() == 1)
//      {
//        Serial.println("PASSED On he");
//        digitalWrite(led3, HIGH);
//      }
//      else
//      {
//        Serial.println("NOT PASSED off he");
//        digitalWrite(led3, LOW);
//
      }
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
  if (digitalRead(btn) == HIGH) {
    digitalWrite(led, HIGH);
    String path = "wemos";
    //    Firebase.pushInt(firebaseData, path + randNum,inches );
    //    Firebase.pushString(firebaseData, path + randNum,dates );  //sending time to firebase
    //    Firebase.pushStringByMe("Time", path + randNum,dates );  //sending time to firebase

    //    Serial.println(firebaseData);
    //    Firebase.pushInt(firebaseData, path + randNum,inches );
    //   Firebase.pushInt("logs", 123);

    // Firebase.setInt(firebaseData, path+"/distance", inches);
    Firebase.setInt(firebaseData, path + "/led", 1);


  }
  else
  {
    digitalWrite(led, LOW);

  }
  if (digitalRead(btn2) == HIGH) {
    String path = "wemos";
    Firebase.setInt(firebaseData, path + "/led", 0);
    digitalWrite(led2, HIGH);

  }
  else
  {
    digitalWrite(led2, LOW);

  }

}
