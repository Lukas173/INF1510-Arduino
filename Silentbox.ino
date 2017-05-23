
/* vi har importert SoftwareSerial fra Arduino biblioteket,
med dette er det mulig aa opprette et object faar  aa faa sende data
mellom to Arduino*/
#include <SoftwareSerial.h>
SoftwareSerial kommunikasjon(10, 11); /*software serial objekt,
for aa faa sende data maa de to arduino kobles slik:
fra pin 10 (TX transmit data) paa en arduino til 11 (RX receive data) på andre arduino
fra pin 11 (RX) til 10 (TX) på andre arduino i 10 pin er det RX(receive data), og 11 er TX(transmit data)
man trenger ogsaa en kobling fra gnd til andre arduino gnd for aa stabilisere strom gjennom de to arduino
*/
int lysAlarm = 2; // lys som blinker når den andre trykker på en knapp
int knapp1Strom = 3; // + til gul knapp
int knapp2Strom = 4; // + til rod knapp
int knapp1Lytt = 5; // - og lytt til gul knapp
int knapp2Lytt = 6; // - og lytt til rod knapp
int piezo = 8; // lyd til alarmen ved piezo hoyttaler
int lys1 = 12; // feedback lys for naar du trykker gul knapp
int lys2 = 13; // feedback lys for naar du trykker rod knapp
int mld; //her lagres data for aa sende til andre arduino
int i; // helt vanlig teller

void setup()  
{
  
  pinMode(lysAlarm, OUTPUT);
  pinMode(knapp1Lytt, INPUT);
  pinMode(knapp1Strom, OUTPUT);
  pinMode(knapp2Lytt, INPUT);
  pinMode(knapp2Strom, OUTPUT);
  pinMode(lys1, OUTPUT);
  pinMode(lys2, OUTPUT); 
  digitalWrite(knapp1Strom, HIGH);
  digitalWrite(knapp2Strom, HIGH);

  kommunikasjon.begin(9600); // her starter Serialsoftware objekt aa fungerer
  delay(1500); // bedre aa ha litt delay for aa stabilisere de to arduino
}

void loop() {
  faaklage();
  klage();
}
/*//med metoden sjekker man om noen sender data. Hvis noen gjor det aktiverer man alarmen pa
  arduino. hvis en trykker gul knapp (kommer '1' paa serial) har vi mindre lyd på alarm,
  ellers hvis rod knapp blir trukket kommer '2' og  vi har mer lyd på alarm*/
 void faaklage() { 
  if (kommunikasjon.available()){
    mld = kommunikasjon.read();

    if (mld =='1') {
      beep(1);
      blinking();
      
    } else if (mld == '2') {
      Serial.write("knapp2");
      beep(3);
      blinking();
    }
   }
  }
  /*her er det klaging metode. hvis man trykker gul knapp,
  sender man char '1' ved Software serial objekt
  hvis rod knapp blir trukket sender man char '2'*/

 void klage() {
    if (digitalRead(knapp1Lytt) == HIGH) {
    digitalWrite(lys1, HIGH);
    delay(1000);
    digitalWrite(lys1, LOW);
    kommunikasjon.write('1');
    delay(1000);
    } else if (digitalRead(knapp2Lytt) == HIGH) {
      digitalWrite(lys2, HIGH);
    delay(1000);
    digitalWrite(lys2, LOW);
      kommunikasjon.write('2');
      delay(1000);
      }
 }
 void blinking() { // metode som styrer alarmen lys-dioder
  for(i = 0; i < 25; i ++) {
        digitalWrite(lysAlarm, HIGH);
      delay(100);
      digitalWrite(lysAlarm, LOW);
      delay(100);
      }
  }
 void beep(int ganger) { //metode som styrer lyd alarm ved piezo
  for (i = 0; i < ganger; i ++) {
    tone(8, 500);
    delay(1000);
    noTone(8);
    delay(1000);
    }
  }
