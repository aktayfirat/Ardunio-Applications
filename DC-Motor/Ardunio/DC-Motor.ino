#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7
int motorSpeedA = 60;
int motorSpeedB = 60;
String terminal;

void setup() {
  // İlgili pin ayarları yapıldı
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Baslangıc degerleri icin motor hızı ayarlandı
  analogWrite(enA, motorSpeedA);
  analogWrite(enB, motorSpeedB);
  delay(200);
  // Terminalden okuma islemi baslatıldı
  Serial.begin(9600);
  Serial.println("Yapilacak islem icin komutlar : ");
  Serial.println(" 1) Ileri");
  Serial.println(" 2) Geri");
  Serial.println(" 3) Sol");
  Serial.println(" 4) Sag");
  Serial.println(" 5) Hiz");
  Serial.println();
}

void loop() {
  if (Serial.available()) {
    terminal = "" + Serial.readString();
    if (terminal == "ileri") {
      Serial.println("Komut Algilandi Motor Ileri Yone Hareket Ediyor..");
      // Motor A ileri
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      // Motor B geri
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }
    else if (terminal == "geri") {

      Serial.println("Komut Algilandi Motor Geri Yone Hareket Ediyor..");
      // Motor A yönü geriye doğru
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      // Motor B yönü geriye doğru
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    else if (terminal == "sol") {
      Serial.println("Komut Algilandi Motor Sol Yone Hareket Ediyor..");
      // Sola git - sol motor hızını azalt, sag motor hızını arttır seklinde islem gerceklestirildi
      // Sağ ve Sola gitmenin bir diger yolu motorları ters yone ayarlamaktır.
      motorSpeedA = motorSpeedA - 20;
      motorSpeedB = motorSpeedB + 20;
      // Aralığı 0 ile 255 arasında sınırlandırın
      if (motorSpeedA < 0) {
        motorSpeedA = 0;
      }
      if (motorSpeedB > 255) {
        motorSpeedB = 255;
      }
    }
    else if (terminal == "sag") {
      Serial.println("Komut Algilandi Motor Sag Yöne Hareket Ediyor..");
      // Saga git - sag motor hızını azaltılıp, sol motor hızı arttırıldı.
      // Sağ ve Sola gitmenin bir diger yolu motorları ters yone ayarlamaktır.
      motorSpeedA = motorSpeedA + 20;
      motorSpeedB = motorSpeedB - 20;
      // Aralığı 0 ile 255 arasında sınırlandırdım
      if (motorSpeedB < 0) {
        motorSpeedB = 0;
      }
      if (motorSpeedA > 255) {
        motorSpeedA = 255;
      }
    }
    else if (terminal == "hiz") {
      Serial.println("Komut Algilandi Hiz Belirleniyor...");
      Serial.println("Belirlemek istediginiz hiz degerini giriniz : ");
hiz:
      delay(1000);
      if (Serial.available()) {
        int hiz_degeri = Serial.readString().toInt();
        if (hiz_degeri < 255 && hiz_degeri > 0) {
          Serial.print(" Motor hizi belirlendi, yeni hiz degerimiz : ");
          Serial.println(hiz_degeri);
          motorSpeedA = hiz_degeri;
          motorSpeedB = hiz_degeri;
        }
        else
          Serial.println("Hiz Belirlenemedi. Girilen deger 0-255 aralıgında degil.!");
      }
      else goto hiz;

      analogWrite(enA, motorSpeedA); // A motoruna PWM sinyali gönderildi
      analogWrite(enB, motorSpeedB); // B Motoruna PWM sinyali gönderildi
    }
    else {
      Serial.print(terminal);
      Serial.println(" Komutu Algilanmadi, Lutfen Tekrar Deneyiniz..");
    }
  }
}
