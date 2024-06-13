#include <WiFi.h>
#include <HTTPClient.h>

// Konfigurasi WiFi
const char* ssid = "Sukses Bersama";
const char* password = "berjuang3";

// Konfigurasi URL server
const char* serverUrl = "http://192.168.1.44:5000/";

// Konfigurasi sensor MQ135
const int mq135Pin = 34; // Pin ADC untuk MQ135

void setup() {
  Serial.begin(115200);

  // Menghubungkan ke WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Membaca data dari sensor MQ135
  int mq135Value = analogRead(mq135Pin);

  // Mempersiapkan data untuk dikirim
  String postData = "{\"mq135\":" + String(mq135Value) + "}";

  // Mengirim data ke server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(6000); // Menunggu 6 detik sebelum mengirim data lagi
}