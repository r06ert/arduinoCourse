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

funkcja Arduino pinMode(pin, mode)
https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
https://www.arduino.cc/en/Tutorial/DigitalPins

funkcja Arduino digitalRead(pin)
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/

funkcja Arduino digitalWrite(pin, value)
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/

funkcja Arduino analogWrite(pin, value)
https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/

funkcja Arduino milis();
https://www.arduino.cc/reference/en/language/functions/time/millis/

funkcje Arduino: Serial.begin(), Serial.print(), Serial.println()
https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/
https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
https://www.arduino.cc/reference/en/language/functions/communication/serial/println/

tryby pracy PWM - teoria
https://www.arduino.cc/en/Tutorial/PWM

--------------------------------------------------------

wszystkie typy zmiennych uzywanych w Arduino
https://www.arduino.cc/reference/en/#variables

slowo kluczowe static jezyka c++
https://www.arduino.cc/reference/en/language/variables/variable-scope--qualifiers/static/

struktura if else jezyka c++
https://www.arduino.cc/reference/en/language/structure/control-structure/if/
https://www.arduino.cc/reference/en/language/structure/control-structure/else/

*/

#define LED  3 //przypisz do slowa LED liczbe 3
#define BUTTON 4 //przypisz do slowa BUTTON liczbe 4

void Blink(void);
void BlinkSmoothly(void);


int przycisk = 0;

unsigned long aktualnyCzas10 = 0;
unsigned long zapamietanyCzas10 = 0;
unsigned long roznicaCzasu10 = 0;

unsigned long aktualnyCzas100 = 0;
unsigned long zapamietanyCzas100 = 0;
unsigned long roznicaCzasu100 = 0;

//funkcja arduino setup() - wywolywana tylko jeden raz na poczatku programu
void setup() {

  Serial.begin(115200); //zainicjuj UART do debugoania kodu
  
  pinMode(LED, OUTPUT); //zainicuj pin portu o numerze LED jak wyjście
  
  pinMode(BUTTON, INPUT_PULLUP); //zainicuj pin portu o numerze BUTTON jako wejście z "podciąganiem"

  Serial.println("Start programu!"); //wyslij wiadomosc przez UART - port do debugowania kodu
}


//funkcja arduino loop() - wywolywana cyklicznie
void loop() {

  przycisk = digitalRead(BUTTON); //odczytaj stan przycisku i zapisz do zmiennej button

  //oblicz roznice czasu, odmierzenie 10ms 
  aktualnyCzas10 = millis(); //Pobierz liczbe milisekund od startu programu
  roznicaCzasu10 = aktualnyCzas10 - zapamietanyCzas10;

  //oblicz roznice czasu, odmierzenie 10ms 
  aktualnyCzas100 = millis(); //Pobierz liczbe milisekund od startu programu
  roznicaCzasu100 = aktualnyCzas100 - zapamietanyCzas100;


  if (roznicaCzasu10 >= 10) {
    zapamietanyCzas10 = aktualnyCzas10; //Zapamietaj aktualny czas

    //kod tutaj bedzie sie wykonywac co 10ms

    //migiaj dioda plynnie lub nie, w zaleznosci od stanu przycisku
    if (przycisk == HIGH) {
      Blink();
    } else {
      BlinkSmoothly();
    }

  }

  if (roznicaCzasu100 >= 100) {
    //Zapamietaj aktualny czas
    zapamietanyCzas100 = aktualnyCzas100;
    
    //kod tutaj bedzie sie wykonywac co 100ms

    //wyslij na UART dane debugowe
    Serial.print("zmienna przycisk ma wartosc: ");
    Serial.println(przycisk);
  }
}


void Blink(void){
    //zainicjuj zmienne statyczne
    static int blinkCnt = 0;
    static int blinkDir = 0;

    //odmierzaj liczba powtorzen i kiedy wiecej lub rowne 100 to inkeremntuj zmienna blinkDir
    blinkCnt++;
    if (blinkCnt>=100) {
      blinkCnt=0;
      blinkDir++;
    }
    
    if (blinkDir%2) {
      //kod tutaj wykona sie za kazdym razem kiedy operacja blinkDir%2 da reszte rozna od 0

      //ustaw pin LED na wartość HIGH i odczekaj 1000ms
      digitalWrite(LED, HIGH);

    } else {
      //kod tutaj wykona sie za kazdym razem kiedy operacja blinkDir%2 da rowna 0

      //ustaw pin LED na wartość LOW i odczekaj 1000ms
      digitalWrite(LED, LOW);
      
    }
}


//funkcja realizuje procedure jednego okresu plynnego migania dioda LED
void BlinkSmoothly(void) {

  //zainicjuj zmienne statyczne
  static int blinkCnt = 0;
  static int blinkDir = 1;
  static int brightnrss = 0;
  
  if (blinkDir%2) {
    //kod tutaj wykona sie za kazdym razem kiedy operacja blinkDir%2 da reszte rozna od 0
    
    //ustaw PWM na wartosc odpowiadajacej wartosci blinkCnt
    analogWrite(LED, blinkCnt);

    //odmierzaj liczba powtorzen i kiedy wiecej lub rowne 100 to inkeremntuj zmienna blinkDir
    blinkCnt++;
    if ( blinkCnt >= 100 ) {
      blinkDir++;
    }

  } else {
    //kod tutaj wykona sie za kazdym razem kiedy operacja blinkDir%2 da rowna 0
    
    //ustaw PWM na wartosc odpowiadajacej wartosci blinkCnt
    analogWrite(LED, blinkCnt);

    //odmierzaj liczba powtorzen i kiedy wiecej lub rowne 100 to inkeremntuj zmienna blinkDir
    blinkCnt--;
    if ( blinkCnt <= 0 ) {
      blinkDir++;
    }
  }
}
