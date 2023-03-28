int t1[7]= { //Timer do motor de 3cv
0,0,0,0,0,0,0};
int dd=1000; // used for delay in show timer data

#include <LiquidCrystal.h> 
#include <Wire.h>
#include <EEPROM.h>
#include "RTClib.h"
RTC_DS1307 RTC;

// Definição dos pinos dos botões
#define bMenu A2 // Os pinos analógicos podem ser
#define bChange A3 // usados como digitais, bastando
#define bUp A0 // referenciá-los por A0, A1..
#define bDown A1
#define benter 8
#define bMenu0 90 // Valor de referência que a 
#define bChange0 91 // função CheckButton() passa
#define bUp0 92 // indicando que um botão foi
#define bDown0 93 // solto
#define benter0 94
boolean aMenu, aChange, aUp, aDown, aenter; // Grava o ultimo valor lidos nos botões.
// Utilizado pela função Checkbutton p/ identificar quando há uma alteração no estado do pino dos botões
int horini=EEPROM.read(0); // variavel a ser alterada pelo menu
int minini=EEPROM.read(1);
int horfim=EEPROM.read(2);
int minfim=EEPROM.read(3);
char state=1; // variável que guarda posição atual do menu
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Declaração do objeto tipo lcd
String ArrumaZero(int i)
{
String ret;
if (i < 10) ret += "0";
ret += i;
return ret;
}
//============================================== SETUP
void setup()
{
Wire.begin();
lcd.begin(16, 2); // Iniciando a biblioteca do LCD
RTC.begin();

pinMode(bMenu, INPUT); // Botões
pinMode(bChange,INPUT);
pinMode(bUp, INPUT);
pinMode(bDown, INPUT);
pinMode(benter, INPUT);
pinMode(6, OUTPUT); // USADO PARA VALVULA 2
pinMode(7, OUTPUT); // USADO PARA VALVULA 1
pinMode(9, OUTPUT); // USADO PARA CONTROLAR A BOMBA

digitalWrite(bMenu, HIGH); // Aciona o pull-up interno
digitalWrite(bChange,HIGH); // dos botões
digitalWrite(bUp, HIGH);
digitalWrite(bDown, HIGH);
digitalWrite(benter, HIGH);


if (!RTC.isrunning())
{
RTC.adjust(DateTime(__DATE__, __TIME__));
}

t1[0]= EEPROM.read(0);
t1[1]= EEPROM.read(1);
t1[2]= EEPROM.read(2);
t1[3]= EEPROM.read(3);
t1[4]= 8;
t1[5]= 1;
}
//==============================================
//============================================== LOOP
void loop()
{
switch (state) { // Define checa qual tela atual
case 1: // executado quando na TELA 1
switch (CheckButton()) {
case bUp:
lcd.clear(); Set_state(7); // antes de mudar de tela, é necessário limpar o 
break; // display com a função lcd.clear()
case bDown:
lcd.clear(); Set_state(2);
break;
default: // Caso nenhum botão tenha sido apertado, ela executa a set_state
Set_state(1); // mesmo assim para atualizar o display.
}
break;

case 2: // executado quando na TELA 2
switch (CheckButton()) {
case bMenu:
lcd.clear(); horini--;
break;
case bChange:
lcd.clear(); horini++;
break;
case bUp: 
lcd.clear(); Set_state(1);
break;
case bDown:
lcd.clear(); Set_state(3);
break;
case benter:
EEPROM.write(0, horini);
default: 
Set_state(2);
}
break;

case 3: // executado quando na TELA 3
switch (CheckButton()) {
case bMenu:
lcd.clear(); minini--;
break;
case bChange:
lcd.clear(); minini++;
break;
case bUp: 
lcd.clear(); Set_state(2);
break;
case bDown:
lcd.clear(); Set_state(4);
break;
case benter:
EEPROM.write(1, minini);
default: 
Set_state(3);
}
break;

case 4: // executado quando na TELA 4
switch (CheckButton()) {
case bMenu:
lcd.clear(); horfim--;
break;
case bChange:
lcd.clear(); horfim++;
break;
case bUp: 
lcd.clear(); Set_state(3);
break;
case bDown:
lcd.clear(); Set_state(5);
break;
case benter:
EEPROM.write(2, horfim);
default: 
Set_state(4);
}
break;

case 5: // executado quando na TELA 5
switch (CheckButton()) {
case bMenu:
lcd.clear(); minfim--;
break;
case bChange:
lcd.clear(); minfim++;
break;
case bUp: 
lcd.clear(); Set_state(4);
break;
case bDown:
lcd.clear(); Set_state(6);
break;
case benter:
EEPROM.write(3, minfim);
default: 
Set_state(5);
}
break;

case 6: // executado quando na TELA 6
switch (CheckButton()) {
case bUp: 
lcd.clear(); Set_state(5);
break;
case bDown:
lcd.clear(); Set_state(7);
break;
default: 
Set_state(6);
}
break;

case 7: // executado quando na TELA 7
switch (CheckButton()) {
case bUp:
lcd.clear(); Set_state(6);
break;
case bDown:
lcd.clear(); Set_state(1);
break;
default: 
Set_state(7);
}
break;

default: ;
}
checktimer1();
delay(200); // to stop screen flicker
}
//============================================== FIM da função LOOP

void checktimer1()
// checa o horário para saber se irá ligar o motor
{
DateTime agora = RTC.now();

int hora = agora.hour();
int minuto = agora.minute();
int segundo = agora.second();


if (t1[4]==8);
{
if (hora==t1[0] && minuto==t1[1])
{
digitalWrite(7, HIGH);
delay(5000);
digitalWrite(9,HIGH);
delay(3600000);
digitalWrite(6,HIGH);
delay(5000);
digitalWrite(7,LOW);
delay(3600000);
digitalWrite(9,LOW);
digitalWrite(6,LOW);
t1[6]=1;
}
if (hora==t1[2] && minuto==t1[3])
{
digitalWrite(9, LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
t1[6]=0;
}
}
}

//============================================== CheckButton
char CheckButton() {
if (aMenu!=digitalRead(bMenu)) {
aMenu=!aMenu;
if (aMenu) return bMenu0; else return bMenu;
} else
if (aChange!=digitalRead(bChange)) {
aChange=!aChange;
if (aChange) return bChange0; else return bChange;
} else
if (aUp!=digitalRead(bUp)) {
aUp=!aUp;
if (aUp) return bUp0; else return bUp;
} else
if (aDown!=digitalRead(bDown)) {
aDown=!aDown;
if (aDown) return bDown0; else return bDown;
} else
if (aenter!=digitalRead(benter)) {
aenter=!aenter;
if (aenter) return benter0; else return benter;
} else
return 0;
}
//========================================================
//============================================== Set_state
void Set_state(char index) {
state = index; // Atualiza a variável state para a nova tela

DateTime agora = RTC.now();

String relogio_data = "DT: ";
String relogio_hora = "HR: ";

int dia = agora.day();
int mes = agora.month();
int ano = agora.year();


relogio_data += ArrumaZero(dia);
relogio_data += "/";
relogio_data += ArrumaZero(mes);
relogio_data += "/";
relogio_data += ano;

int hora = agora.hour();
int minuto = agora.minute();
int segundo = agora.second();

relogio_hora += ArrumaZero(hora);
relogio_hora += ":";
relogio_hora += ArrumaZero(minuto);
relogio_hora += ":";
relogio_hora += ArrumaZero(segundo);
switch (state) { // verifica qual a tela atual e exibe o conteúdo correspondente
case 1: //==================== state 1
lcd.setCursor(0, 0);
lcd.print(relogio_data);
lcd.setCursor(0, 1);
lcd.print(relogio_hora);
break;
case 2: //==================== state 2
lcd.setCursor(0,0);
lcd.print("Hor. Inicio");
lcd.setCursor(0,1);
lcd.print(horini);
break;
case 3: //==================== state 3
lcd.setCursor(0,0);
lcd.print("Min. Inicio");
lcd.setCursor(0,1);
lcd.print(minini);
break;
case 4: //==================== state 4
lcd.setCursor(0,0);
lcd.print("Hor. Fim");
lcd.setCursor(0,1);
lcd.print(horfim);
break;
case 5: //==================== state 5
lcd.setCursor(0,0);
lcd.print("Min. Fim");
lcd.setCursor(0,1);
lcd.print(minfim);
break;
case 6: //==================== state 6
lcd.setCursor(0,0);
lcd.print("Alarme:");
break;
case 7: //==================== state 7
lcd.setCursor(0,0);
lcd.print("Segundos:");
lcd.setCursor(0,1);
lcd.print( millis()/1000 , DEC); // mostra os segundos na tela
lcd.print(" s");
lcd.print(" ");
lcd.print(millis()/86400000, DEC); // mostra os dias na tela
lcd.print(" dias");

break;
default: ;
}
}
