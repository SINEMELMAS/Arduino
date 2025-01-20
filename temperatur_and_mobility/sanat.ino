#include <SoftwareSerial.h>

// Bluetooth ve Ultrasonik Pin Tanımları
SoftwareSerial bluetooth(2, 3); // HC-05: RX ve TX
const int trigPin = 9;
const int echoPin = 8;
const int buzzer = 10;
const int redLED = 11;
const int greenLED = 12;
const int blueLED = 13; // Mavi LED
const int lm35Pin = A0; // Sıcaklık sensörü (LM35)

// Mesafe için değişkenler
long duration;
int distance;

// Sıcaklık için değişkenler
int okunan_deger = 0;
float sicaklik_gerilim = 0;
float sicaklik = 0;
const float sicaklik_esik = 20.0; // Sıcaklık alarm eşiği

// Başlangıç ayarları
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);

  // Seri iletişim
  bluetooth.begin(9600); // Bluetooth modülü için
  Serial.begin(9600);    // Seri monitör için

  // Başlangıç durumu
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Mesafe ölçümü
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Mesafeyi cm olarak hesapla

  // Sıcaklık ölçümü
  okunan_deger = analogRead(lm35Pin);
  sicaklik_gerilim = (okunan_deger / 1023.0) * 5000; // mV cinsine çevir
  sicaklik = sicaklik_gerilim / 100.0; // Sıcaklık değeri (°C)

  // Mesafe değerini seri monitörde göster
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.print(" cm, Sicaklik: ");
  Serial.print(sicaklik);
  Serial.println(" °C");

  // Hareket algılandığında
  if (distance > 0 && distance < 50) { // 50 cm içinde bir hareket algılanırsa
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, HIGH);
    bluetooth.println("Hareket algilandi!");
    delay(2000); // Alarm 2 saniye çalar
  } else {
    // Normal durum
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(buzzer, LOW);
  }

  // Sıcaklık kontrolü
  if (sicaklik >= sicaklik_esik) { // Sıcaklık eşiği aşıldıysa
    digitalWrite(blueLED, HIGH);
    bluetooth.print("Sicaklik: ");
    bluetooth.print(sicaklik);
    bluetooth.println(" C");
  } else {
    digitalWrite(blueLED, LOW);
  }

  // Bluetooth üzerinden komut kontrolü
  if (bluetooth.available()) {
    char command = bluetooth.read();
    if (command == 'A') { // A: Sistemi aktif et
      bluetooth.println("Sistem aktif!");
      digitalWrite(redLED,LOW );
      digitalWrite(greenLED, HIGH);
    } else if (command == 'D') { // D: Sistemi devre dışı bırak
      bluetooth.println("Sistem devre disi!");
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
      digitalWrite(blueLED, LOW);
      digitalWrite(buzzer, LOW);
    }
  }

  delay(500); // 500ms bekle
}


