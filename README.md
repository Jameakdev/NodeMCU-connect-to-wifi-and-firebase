### NodeMCU เชื่อมต่อ Wi-Fi
 > ใช้ library ของ NodeMCU เพื่อทำการเชื่อมต่อ wifi  **<ESP8266WiFi.h>** แหล่งที่มา [อ่านเพิ่มเติม](https://netpie.gitbooks.io/nodemcu-esp8266-on-netpie/content/lab-6.html)

#### คำสั่งการเชื่อมต่อ Wi-Fi

เรียกใช้ Library:
```
#include <ESP8266WiFi.h>
```

กำหนด username และ password Wi-Fi เพื่อทำเชื่อมต่อโดยตัวแปรประกาศไว้เป็น Global variable:
```
// Config connect Wi-Fi
const char* ssid = "username Wi-Fi";
const char* password = "password Wi-Fi";

```

ประกาศฟังชันของการเชื่อมต่อ Wi-Fi:
```
void connectedWifi(){

   WiFi.begin(ssid, password);
   
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
   }

   Serial.println("Wi-Fi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
  }

```
การเรียกใช้ฟังก์ชันงานใน setup:
```
// เชื่อมต่อ Wi-Fi
  connectedWifi();
```
### Node เชื่อมต่อ Firebase 
> การเชื่อมต่อและดึงค่าจาก Firebase ด้วย **"FirebaseESP8266.h"** แหล่งที่มา [อ่านเพิ่มเติม](https://github.com/mobizt/Firebase-ESP8266/blob/master/README.md?fbclid=IwAR0Hs8vYTkr_rOeDoeaDegefeu5BZAjdR7alp9-wD-fp85kRTltZGDW7yMU) และศึกษาฟังก์ชันต่าง ๆ ได้ [ที่นี่](https://github.com/mobizt/Firebase-ESP8266/tree/master/src)

#### Code การเชื่อมต่อกับ Firebase

เรียกใช้ Library ดาวน์โหลดได้ [ที่นี่](https://github.com/mobizt/Firebase-ESP8266/blob/master/README.md?fbclid=IwAR0Hs8vYTkr_rOeDoeaDegefeu5BZAjdR7alp9-wD-fp85kRTltZGDW7yMU):
```
#include "FirebaseESP8266.h"
```
ประกาศ Firebase Data ให้เป็น global variable:
```
// ประกาศ obj ของ firebase
FirebaseData firebaseData;
```

ตั้งค่า Firebase ใน setup เพื่อเริ่มต้นการใช้งาน:
```
// เริ่มต้นใช้งาน firebase 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // ตั้งค่า AP reconnect wifi 
  Firebase.reconnectWiFi(true);

  // ตั้งค่าขนาดของ BearSSL เพื่อรับและส่งค่า
  firebaseData.setBSSLBufferSize(1024, 1024);

  // ตั้งค่าขนาดของ HTTP response buffer
  firebaseData.setResponseSize(1024);
```
การดึงค่าจาก Firebase ใน loop:
```
// รับค่า JSON, firebaseData คือ obj ของ firebase ที่ได้ประกาศไว้ด้านบน, dataPath = path ที่จะเข้าถึงข้อมูลใน firebase 
  
  if (Firebase.getJSON(firebaseData, "dataPath"))
  {
    Serial.println(firebaseData.jsonString());
  }
  ```
 ### คำสั่งทั้งหมด
 คำสั่ง:
 ```
 #include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"

// Config Firebase
#define FIREBASE_HOST "YOUR_FIREBASE_HOST" // EX. myfirebase.firebaseio.com
#define FIREBASE_AUTH "YOUR_AUTH_KEY" // The key is in your firebase project

// Config connect Wi-Fi
const char* ssid = "username Wi-Fi";
const char* password = "password Wi-Fi";

// ประกาศ obj ของ firebase
FirebaseData firebaseData;

void setup() {
  
  Serial.begin(9600);
 

  // เชื่อมต่อ Wi-Fi
  connectedWifi();

  // เริ่มต้นใช้งาน firebase 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // ตั้งค่า AP reconnect Wi-Fi 
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

   Serial.println("Wi-Fi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
  }

 ```
 ## อ้างอิง
 *************************************************************************************************************************
 [https://netpie.gitbooks.io/nodemcu-esp8266-on-netpie/content/lab-6.html](https://netpie.gitbooks.io/nodemcu-esp8266-on-netpie/content/lab-6.html)
 
 [https://github.com/mobizt/Firebase-ESP8266/blob/master/README.md?fbclid=IwAR0Hs8vYTkr_rOeDoeaDegefeu5BZAjdR7alp9-wD-fp85kRTltZGDW7yMU](https://github.com/mobizt/Firebase-ESP8266/blob/master/README.md?fbclid=IwAR0Hs8vYTkr_rOeDoeaDegefeu5BZAjdR7alp9-wD-fp85kRTltZGDW7yMU)
 
 [https://github.com/mobizt/Firebase-ESP8266/tree/master/src](https://github.com/mobizt/Firebase-ESP8266/tree/master/src)
 
 ## จากใจผู้เขียน
 *บทความนี้คือบทความแรกในชีวิตครับถ้าผิดพลาดประการใดทางผู้เขียนต้องขออภัยในที่นี่ด้วยครับถ้ามีคำแนะนำเพิ่มเติมสามารถแนะนำได้นะครับแล้วจะนำไปปรับปรุงเพื่อพัฒนาตัวเองต่อไปครับ 😄😍*
