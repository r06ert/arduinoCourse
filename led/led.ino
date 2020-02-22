/*
http://wrzesnia.freelab.edu.pl/
led

--------------------------------------------------------

struktura szkicu Arduino - funkcja setup()
https://www.arduino.cc/reference/en/language/structure/sketch/setup/

struktura szkicu Arduino - funkcja loop()
https://www.arduino.cc/reference/en/language/structure/sketch/loop/

--------------------------------------------------------

wszystkie natywne funkcje wbudowane w Arduino
https://www.arduino.cc/reference/en/#functions

funkcja Arduino milis();
https://www.arduino.cc/reference/en/language/functions/time/millis/

funkcje Arduino: Serial.begin(), Serial.print(), Serial.println()
https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/
https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
https://www.arduino.cc/reference/en/language/functions/communication/serial/println/

--------------------------------------------------------

wszystkie typy zmiennych uzywanych w Arduino
https://www.arduino.cc/reference/en/#variables


struktura if else jezyka c++
https://www.arduino.cc/reference/en/language/structure/control-structure/if/
https://www.arduino.cc/reference/en/language/structure/control-structure/else/


---------------------------------------------------------

wyświetlacz tekstowy LCD z konwerterem I2C
http://www.arduino.idsl.pl/index.php/biblioteki-arduino-ide/13-liquidcrystal-i2c-h

*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

unsigned long aktualnyCzas500 = 0;
unsigned long zapamietanyCzas500 = 0;
unsigned long roznicaCzasu500 = 0;

unsigned int kierunek = 0;
unsigned int krok = 0;

String wiadomosc = "Arduino :)";

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//funkcja arduino setup() - wywolywana tylko jeden raz na poczatku programu
void setup() {

  Serial.begin(115200); //zainicjuj UART do debugoania kodu
  
  //inicjalizacja wysweitlacza
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(wiadomosc);

  Serial.println("Start programu!"); //wyslij wiadomosc przez UART - port do debugowania kodu
}


//funkcja arduino loop() - wywolywana cyklicznie
void loop() {

  //oblicz roznice czasu, odmierzenie 10ms 
  aktualnyCzas500 = millis(); //Pobierz liczbe milisekund od startu programu
  roznicaCzasu500 = aktualnyCzas500 - zapamietanyCzas500;

  if (roznicaCzasu500 >= 500) {
    //Zapamietaj aktualny czas
    zapamietanyCzas500 = aktualnyCzas500;
    
    //kod tutaj bedzie sie wykonywac co 500ms
    
    if (krok >= (16 - wiadomosc.length()) ) {
      krok = 0; //zeruj liczbe krokow
      kierunek++; //zmien kierunek przesuwania tekstu

      //debug
      Serial.println("zmieniono kierunek przesuwania tekstu");
    }

    if ( kierunek % 2 == 0) {
      //przesuwaj wiadomosc na wyswietlaczu w prawo
      
      lcd.scrollDisplayRight(); //komenda do wyswietlacza - przesun wiadomosc w prawo
      krok++; //inkrementuj licznik krokow
      
      //debug
      Serial.println("przesunieto wiadomosc w prawo");
      
    } else {
      //przesuwaj wiadomosc na wyswietlaczu w lewo
      
      lcd.scrollDisplayLeft(); //komenda do wyswietlacza - przesun wiadomosc w lewo
      krok++; //inkrementuj licznik krokow

      //debug
      Serial.println("przesunieto wiadomosc w lewo");
      
    }

  }
}
