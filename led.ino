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

funkcja Arduino delay(ms)
https://www.arduino.cc/reference/en/language/functions/time/delay/

tryby pracy PWM - teoria
https://www.arduino.cc/en/Tutorial/PWM

--------------------------------------------------------

wszystkie typy zmiennych uzywanych w Arduino
https://www.arduino.cc/reference/en/#variables

zmienna typu int
https://www.arduino.cc/reference/en/language/variables/data-types/int/

struktura "for" jezyka c++
https://www.arduino.cc/reference/en/language/structure/control-structure/for/

struktura if else jezyka c++
https://www.arduino.cc/reference/en/language/structure/control-structure/if/
https://www.arduino.cc/reference/en/language/structure/control-structure/else/

*/

#define LED  3 //przypisz do slowa LED liczbe 3
#define BUTTON 4 //przypisz do slowa BUTTON liczbe 4

void Blink(void);
void BlinkSmoothly(void);


int button = 0; //stworz zmienna button i nadaj jej wartosc poczatkowa 0

//funkcja arduino setup() - wywolywana tylko jeden raz na poczatku programu
void setup() {
  
  pinMode(LED, OUTPUT); //zainicuj pin portu o numerze LED jak wyjście
  
  pinMode(BUTTON, INPUT_PULLUP); //zainicuj pin portu o numerze BUTTON jako wejście z "podciąganiem"
}


//funkcja arduino loop() - wywolywana cyklicznie
void loop() {

  button = digitalRead(BUTTON); //odczytaj stan przycisku i zapisz do zmiennej button

  //struktura "if else" - tworzenie warunków w kodzie
  if (button == HIGH ) {
    //jeżeli zmienna button ma wartość HIGH to wykonaj kod w tych nawiasach klamrowych
    
    Blink(); //wywolaj funkcje Blink()
    
  } else {
    //jeżeli zmienna button ma wartość inna niz HIGH (czyli ma wartosc LOW) to wykonaj kod w tych nawiasach klamrowych
    
    BlinkSmoothly(); //wywolaj funkcje BlinkSmoothly()
    
  }
  
}


//funkcja realizuje procedure jdnego okresu migania dioda LED
void Blink(void){
    //ustaw pin LED na wartość HIGH i odczekaj 1000ms
    digitalWrite(LED, HIGH);
    delay(1000);
    
    //ustaw pin LED na wartość LOW i odczekaj 1000ms
    digitalWrite(LED, LOW);
    delay(1000);
}


//funkcja realizuje procedure jednego okresu plynnego migania dioda LED
void BlinkSmoothly(void) {

  //struktura "for" - zainicjuj zmienna brightness wartością zerą i inkrementuj ją o wartość 10 tak długo jak długo jej wartość nie przekracza 100
  for (int brightness = 0; brightness <= 100; brightness = brightness+1) {
    //kod w tym nawiasie klamrowym bedze sie tak dlugo wykonywac jak dlugo spelniony bedzie warunek (brightness <= 100)

    //ustaw PWM na wartosc odpowiadajacej wartosci brightness i odczekaj 10 milisekund
    analogWrite(LED, brightness);
    delay(10);
  }
  
  //struktura "for" - zainicjuj zmienna brightness wartością 100 i dekrementuj ją o wartość 10 tak długo jak długo jej wartość jest dodatnia lub rowna zero
  for (int brightness = 100; brightness >= 0; brightness = brightness-1) {
    //kod w tym nawiasie klamrowym bedze sie tak dlugo wykonywac jak dlugo spelniony bedzie warunek (brightness >= 0)

    //ustaw PWM na wartosc odpowiadajacej wartosci brightness i odczekaj 10 milisekund
    analogWrite(LED, brightness);
    delay(10);
  }
  
}
