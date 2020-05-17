#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

// Config Firebase
#define FIREBASE_HOST "YOUR_FIREBASE_HOST" // EX. myfirebase.firebaseio.com
#define FIREBASE_AUTH "YOUR_AUTH_KEY" // The key is in your firebase project

// Config connect WiFi
const char* ssid = "username wifi";
const char* password = "password wifi";

// ประกาศ obj ของ firebase
FirebaseData firebaseData;

void setup() {
  
  Serial.begin(9600);
 

  // เชื่อมต่อ wifi
  connectedWifi();

  // เริ่มต้นใช้งาน firebase 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // ตั้งค่า AP reconnect wifi 
  Firebase.reconnectWiFi(true);

  // ตั้งค่าขนาดของ BearSSL เพื่อรับและส่งค่า
  firebaseData.setBSSLBufferSize(1024, 1024);

  // ตั้งค่าขนาดของ HTTP response buffer
  firebaseData.setResponseSize(1024);
    
}

void loop() {

  // รับค่า JSON, firebaseData คือ obj ของ firebase ที่ได้ประกาศไว้ด้านบน, dataPath = path ที่จะเข้าถึงข้อมูลใน firebase 
  
  if (Firebase.getJSON(firebaseData, "dataPath"))
  {
    Serial.println(firebaseData.jsonString());
  }
  
  
  delay(1000);
}

void connectedWifi(){

   WiFi.begin(ssid, password);
   
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
   }

   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
  }
