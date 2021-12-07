// Odległościomierz
// Autor Jakub Karalus
#include <LiquidCrystal_I2C.h> // include lib according to your lcd type

// Stałe mojego wyświetlacza
#define LCDWIDTH 16
#define LCDHEIGHT 2

// zdefiniowane piny
#define trigPin 9
#define echoPin 10
#define redPin 7
#define greenPin 6
#define bluePin 5

// zdefiniowane zmienne
long duration;
int distanceCm, distanceInch;

// używane lcd: moje jest typu 0x27
LiquidCrystal_I2C lcd(0x27, LCDWIDTH, LCDHEIGHT);

void setup() {
  Serial.begin(9600); // Zaczynam komunikację z arduino poprzez port szeregowy
  lcd.begin(LCDWIDTH,LCDHEIGHT); // Inicjalizuje interfejs do ekranu LCD i określam wymiary (szerokość i wysokość) wyświetlacza
  lcd.init();
  lcd.clear();
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Czas przebycia odległości przez dźwięk
  distanceCm = duration*0.034/2; // Dystans w cm
  distanceInch = duration*0.0133/2; // Dystans w calach
  Serial.print("Odleglosc w cm: "); // Wyświetlam odległość w cm na ekranie do monitorowania portu szeregowego
  Serial.println(distanceCm);
  lcd.setCursor(0,0); // Wybieram miejsce na jakim miejscu ma się wyświetlić napis na LCD
  lcd.print("Odleglosc:"); // Podaję tekst jaki ma się wyświetlić
  lcd.print(distanceCm); // Wypisuje dystans w cm z sensora
  lcd.print(" cm");
  delay(10);
  lcd.setCursor(0,1);
  lcd.print("Odleglosc:");
  lcd.print(distanceInch); // Wypisuje dystans w calach z sensora
  lcd.print(" inch");
  delay(10);
  if (distanceCm < 9){
    setColor(255, 0, 0); // Czerwony kolor
    tone(A5, 3500); //Wygeneruj sygnał o częstotliwości 3500Hz na pinie A5  
    delay(100);  
    tone(A5, 2500); //Wygeneruj sygnał o częstotliwości 2500Hz na pinie A5  
    delay(100);
    } // Jezeli dystans jest mniejszy niz 9 cm to LED zmienia kolor na czerwony oraz buzzer wydaje dźwięki o różnych częstotliwościach

  else if (distanceCm < 13){
    setColor(255, 255, 0); // Żółty kolor
    delay(250);
    noTone(A5); //Wyłącz generowanie sygnału
    delay(250);
    } // Jezeli dystans jest mniejszy niz 13 cm ale większy niż 9 to LED zmienia kolor na żółty

  else if (distanceCm < 18){
    setColor(0, 255, 0); // Zielony kolor
    delay(250);
    noTone(A5); //Wyłącz generowanie sygnału
    delay(250);
    } // Jezeli dystans jest mniejszy niz 18 cm ale większy niż 13 to LED zmienia kolor na zielony

  else if(distanceCm >= 18){
    setColor(0, 0, 0); // Brak koloru
    delay(250);
    noTone(A5); //Wyłącz generowanie sygnału
    delay(250);
    } // Jezeli dystans jest większy bądź równy 18 cm to LED nie świeci 
    
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

// Odległościomierz
// Autor Jakub Karalus
