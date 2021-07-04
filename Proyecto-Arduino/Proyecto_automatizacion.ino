#include <Time.h>
#include <TimeLib.h>
#include <RTClib.h>
#include <TimeAlarms.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>    // Libreria de graficos
#include <Adafruit_TFTLCD.h> // Libreria de LCD 
#include <TouchScreen.h>     // Libreria del panel tactil
MCUFRIEND_kbv tft;
 
 //pines del panel tactil

#define YP A3   
#define XM A2  
#define YM 9       
#define XP 8          


// Definimos la presion máxima y minima que podemos realizar sobre el panel
#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 348); 
//const int TS_LEFT=101,TS_RT=926,TS_TOP=76,TS_BOT=892;
short TS_MINX=173;//173
short TS_MINY=172; //172
short TS_MAXX=966; //966
short TS_MAXY=927; //927
/* NO SE PORQUE MURIO ESTA LIBRERIA
#define LCD_CS A3   // Definimos los pines del LCD
#define LCD_CD A2   // para poder visualizar elementos graficos
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4
*/

#define  BLACK     0x0000  // Definimos los colores 
#define BLUE      0x001F  // que utilizaremos para
#define BLUE2     0x051F 
#define RED       0xF800  // el texto y los elementos graficos
#define GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0
#define WHITE     0xFFFF
#define DARKGREY  0x7BEF
#define ORANGE    0xFD20

//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);       // Instancia LCD
 
//SET RTC
RTC_DS3231 rtc;
#define CLOCK_INTERRUPT_PIN 43

int X; // Variables que almacenaran la coordenada
int Y; // X, Y donde presionemos y la variable Z 
int Z; // almacenara la presion realizada
int  pulsacion = 0;
int decena[] = {0,1,2,3,4,5,6,7,8,9};
int unidad[] = {0,1,2,3,4,5,6,7,8,9};
//Variables set horas luz
int hora[]= {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
int minutos[]={0,10,20,30,40,50};
int dia[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};
int mes[]={1,2,3,4,5,6,7,8,9,10,11,12};
int ano[]={2021,2022,2023,2024,2025,2026,2027,2028,2029,2030,2031}; //obsolencia programada
//SET CRECIMIENTO
int diaInicioC = 0;
int diaFinC=0;
int mesInicioC=0;
int mesFinC=0;
int anoInicioC=0;
int anoFinC=0;

int horaInicioC=0;
int minutosInicioC=0;
int horaFinC=0;
int minutosFinC=0;

//SET VEGETACION
int diaInicioV = 0;
int diaFinV=0;
int mesInicioV=0;
int mesFinV=0;
int anoInicioV=0;
int anoFinV=0;

int horaInicioV=0;
int minutosInicioV=0;
int horaFinV=0;
int minutosFinV=0;

//SET FLORACION
int diaInicioF = 0;
int diaFinF=0;
int mesInicioF=0;
int mesFinF=0;
int anoInicioF=0;
int anoFinF=0;

int horaInicioF=0;
int minutosInicioF=0;
int horaFinF=0;
int minutosFinF=0;

//variables temperatura
int i = 0;//decena temp max
int b = 0;//unidad temp max
int c = 0;//decena temp minima
int d = 0;//unidad temp minima
int temperaturaMaximaEstablecida = 0; // concatenacionm de la decena y unidad de temp maxima --> max temp control
int temperaturaMinimaEstablecida = 0; // concatenacion de la decena y unida de temp minima --> min temp control
//variables humedad suelo
int hd = 0; //decena humedad max
int hu = 0; //unidad humedad max
int hsd = 0; //decena humedad min
int hsu = 0; //unidad humedad min
int humedadMaximaEstablecida = 0; // concatenacion -->max humedad control
int humedadMinimaEstablecida = 0; // concatenacion -->min humedad control
//variables humedad aire
int had = 0;//decena humedad aire max
int hau = 0; //unidad humedad aire max
int hadm = 0; //decena humedad aire min
int haum = 0; //unidad humedad aire min
int humedadAireMaximaEstablecida = 0; // concatenacion --> max humedad aire control
int humedadAireMinimaEstablecida = 0; //concatenacion --> min humedad aire control


int contador = 0;

//VARIABLES DE LOS DIAS DE CRECIMIENTO
int diaInicioCrecimiento = 0;
int diaFinCrecimiento = 0;
int mesInicioCrecimiento = 0;
int mesFinCrecimiento = 0;
int anoInicioCrecimiento = ano[0];
int anoFinCrecimiento= 0;
int diaInicioVegetacion= 0;
int diaFinVegetacion= 0;
int mesInicioVegetacion= 0;
int mesFinVegetacion= 0;
int anoInicioVegetacion= 0;
int anoFinVegetacion= 0;
int diaInicioFloracion= 0;
int diaFinFloracion= 0;
int mesInicioFloracion= 0;
int mesFinFloracion= 0;
int anoInicioFloracion= 0;
int anoFinFloracion= 0;
int anomas = 0;
int anomas1 = 0;
//MENU HORARIO CRECIMIENTO
int horaC = 0;
int horaInicioCrecimiento = 0;
int minInicioCrecimiento;
int horaFinCrecimiento = 0;
int horaCF = 0;
int minutoInicioCrecimiento= 0;
int minutoFinCrecimiento=0;
int minC = 0;
int minCF = 0;
//menu horario vegetacion
int anomasV;
int anomas1V;
int horaV;
int horaVF;
int minV;
int minVF;
int horaInicioVegetacion;
int horaFinVegetacion;
int minutoInicioVegetacion;
int minutoFinVegetacion;
//menu horario floracion
int anomas1F;
int horaF;
int horaFF;
int minF;
int minFF;
int horaInicioFloracion;
int minutoInicioFloracion;
int horaFinFloracion;
int minutoFinFloracion;


// LIBRERIAS Y COSAS DEL SENSOR DE TEMPERATURA AMBIENTE Y HUMEDAD
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 10     // PIN digital al que esta conectado el sensor. No anda en todos del 3 al 14 aprox. 
#define DHTTYPE    DHT11     // Ahora es el DHT 11, pero puede ser el DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int temperaturaMaxima = temperaturaMaximaEstablecida; //PONER LA TEMPERATURA MAXIMA //RELAY 4 PIN 35
int temperaturaMinima = temperaturaMinimaEstablecida;//PONER LA TEMPERATURA MINIMA  //RELAY 3 PIN 33
int humedadMaxima = humedadAireMaximaEstablecida; //PONER LA HUMEDAD MAXIMA //RELAY 6 PIN 39
int humedadMinima = humedadAireMinimaEstablecida;//PONER LA HUMEDAD MINIMA //RELAY 5 PIN 37
int humedadRelativa;
int temperaturaAmbiente;

//COSAS DEL HIGROMETRO
const int higrometro = A5; // PIN del higrometro
int humedadSueloRequerida = 800; // variable para modificar cuan humedo se quiere el suelo
int valorSuelo;
int humedadSueloRequeridaMax;
int humedadSueloRequeridaMin;
int valorHumedad;

//CONVERSION DE FECHAS A TIEMPO UNIX PARA LAS ALARMAS
time_t fechaIC;
int fechaFC;
int fechaIV;
int fechaFV;
int fechaIF;
int fechaFF;
int fechaICV;
DateTime t;
int horaInicioCrecimient = 13;
int minutoInicioCrecimient = 9;




                                //INICIO SETUP
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
tft.begin(0x9341);
tft.setRotation(1);
menuPrincipal();
//Inicio RTC
rtc.begin();
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//inicializa en la fecha de compilacion
rtc.disable32K();
pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN),onAlarm, FALLING);
rtc.writeSqwPinMode(DS3231_OFF);
//SENSOR DE TEMPERATURA Y HUMEDAD AMBIENTE  
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000; // delay obligatorio, minimo 1seg.

}

                                    //FIN SETUP


                                    
void higrometroLectura(){
int valorHumedad = map(analogRead(higrometro), 0, 1023, 100, 0);
//int humedadSuelo = analogRead(higrometro); // lectura del higrometro(1024), <800 suelo seco
Serial.print("Lectura suelo: ");
Serial.println(humedadMinimaEstablecida);
if (valorHumedad < humedadMinimaEstablecida){
  pinMode(31,HIGH); // PIN DEL RELAY 2
  } 
if(valorHumedad >= humedadMaximaEstablecida) {
    pinMode(31,LOW);
  }
if (pulsacion == 0){
tft.fillRect(163,47,115,50,BLACK); // (x,y,ancho,altura,color)//x max= 320, y max =240
tft.setCursor(205,60); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(3);
tft.print(valorHumedad);
tft.println(" %");
  }
  }
void lecturaDHT(){
   //TEMPERATURA AMBIENTE Y HUMEDAD RELATIVA
 delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
 int temperaturaAmbiente = event.temperature;
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
 int humedadRelativa = event.relative_humidity;
 //Serial.println(humedadRelativa);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }


if (temperaturaAmbiente < temperaturaMinimaEstablecida){ //ENCIENDE CALEFACCION RELAY 3
  pinMode(33,HIGH);
}else{pinMode(33,LOW);}
if(temperaturaMaximaEstablecida == 0){pinMode(35,LOW);}else{
if (temperaturaAmbiente > temperaturaMaximaEstablecida){ //ENCIENDE EXTRACTOR o AIREACONDICIONADO RELAY 4
  pinMode(35,HIGH);
}else{pinMode(35,LOW);}
}
if (humedadRelativa < humedadAireMinimaEstablecida){ //ENCIENDE HUMIDIFICADOR RELAY 5
  pinMode(37,HIGH);
}else{pinMode(37,LOW);}
if(humedadAireMaximaEstablecida == 0){pinMode(39,LOW);}else{
if (humedadRelativa > humedadAireMaximaEstablecida){ //ENCIENDE DESHUMIDIFICADOR RELAY 6
  pinMode(39,HIGH);
} else {pinMode(39,LOW);}
}
 
  if (pulsacion == 0) {
tft.fillRect(2,50,156,36,BLACK);
tft.setCursor(45,60); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(3);
tft.print(temperaturaAmbiente);
tft.println(" C");
tft.fillRect(2,131,156,36,BLACK);
tft.setCursor(45,141); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(3);
tft.print(humedadRelativa);
tft.println(" %");

}
  }


                                                                  //MENU PRINCIPAL
void menuPrincipal(){
tft.fillScreen(BLACK);

tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
tft.setCursor(80,3);
tft.setTextColor(WHITE);
tft.setTextSize(1);
tft.print("Super Mega Cultivador 3000");

tft.drawRect(0,17,160,80,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
tft.setCursor(20,30); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.print("Temperatura");
tft.setCursor(45,60); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(3);
tft.print("N/A");

tft.drawRect(0,97,160,80,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
tft.setCursor(10,111); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.print("Humedad Aire");
tft.setCursor(45,141); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(3);
tft.print("N/A");

tft.drawRect(160,17,160,80,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
tft.setCursor(163,30); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.print("Humedad Suelo");
tft.setCursor(205,60); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(3);
tft.print("N/A");

tft.drawRect(160,97,160,80,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
tft.setCursor(168,111); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.print("Ciclo de Luz");
tft.setCursor(180,141); // X, Y
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.print("Creciendo");

tft.drawRect(0,177,320,63, RED);
tft.setCursor(30,200);
tft.setTextColor(WHITE);
tft.setTextSize(2);
tft.print("Todo perfecto por aqui");
//tft.print(now.minute(),DEC);
//tft.print(now.second();DEC);

}
                                                                //COSAS DE LOS MENUES DE TEMPERATURA
void menuTemperatura(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,120,RED);
  tft.drawRect(0,120,320,120,RED);
  tft.setCursor(20,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Temperatura");
  tft.setCursor(30,60);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Maxima");
  tft.setCursor(20,160);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Temperatura");
  tft.setCursor(30,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Minima");

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
}
void menuTemperaturaMaxima(){
tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,170,RED);
  tft.drawRect(0,170,320,240,RED);
  
  tft.fillRect(109,45,109,77,WHITE);
  tft.fillTriangle(60,18,80,75,40,75,RED); //mas temp decena
  tft.fillTriangle(60,152,80,95,40,95,RED); //menos temp decena
  tft.fillTriangle(260,18,280,75,240,75,RED);//mas temp unidad
  tft.fillTriangle(260,152,240,95,280,95,RED);//menos temp unidad
 
  tft.setCursor(120,56);   //TEMPERATURA DECENA
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[i]);

   tft.setCursor(165,56); //TEMPERATURA UNIDAD
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[b]);
  
  tft.setCursor(20,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Introduzca cual sera");
  tft.setCursor(20,205);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("la temperatura maxima");
  
tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
}
void menuTemperaturaMinima(){
  tft.fillScreen(BLACK);

  tft.drawRect(0,0,320,170,RED);
  tft.drawRect(0,170,320,240,RED);
  
  tft.fillRect(109,45,109,77,WHITE);
  tft.fillTriangle(60,18,80,75,40,75,RED); //mas temp decena
  tft.fillTriangle(60,152,80,95,40,95,RED); //menos temp decena
  tft.fillTriangle(260,18,280,75,240,75,RED);//mas temp unidad
  tft.fillTriangle(260,152,240,95,280,95,RED);//menos temp unidad
 
  tft.setCursor(120,56);   //TEMPERATURA DECENA
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[c]);

   tft.setCursor(165,56); //TEMPERATURA UNIDAD
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[d]);
  
  tft.setCursor(20,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Introduzca cual sera");
  tft.setCursor(20,205);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("la temperatura minima");



  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
}

void lecturaMenuTemperatura(){
if (X > 1 && X < 320 && Y > 1 && Y < 80 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuTemperaturaMaxima(); 
    Z=0;
    pulsacion = 2;
  }
if(X > 1 && X < 280 && Y > 81 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
  menuTemperaturaMinima();
  Z=0;
  pulsacion = 3;
}
if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuPrincipal();
  Z=0;
  pulsacion = 0;
}
}

void lecturaMenuTemperaturaMaxima (){
 temperaturaMaximaEstablecida = i*10 + b;
 if (X >0 && X < 109 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR DECENA
  if (i  == 9){
      decena[0];
      i=0;}
  else {decena[i++];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[i]);
//delay(200);
 }

 if (X >0 && X <152 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR DECENA
  if (i  == 0){
      i=9;}
  else {decena[i--];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[i]);
//delay(200);
 }
  if (X >250 && X < 320 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR UNIDAD
  if (b  == 9){
      b=0;}
  else {unidad[b++];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[b]);
//delay(200);
 }

 if (X >250 && X <320 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR UNIDAD
  if (b  == 0){
      b=9;}
  else {unidad[b--];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[b]);
//delay(200);
 }   
 
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuTemperatura();
  Z=0;
  pulsacion = 1;
}

}
void lecturaMenuTemperaturaMinima(){
  temperaturaMinimaEstablecida = c*10 + d;
if (X >0 && X < 109 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR DECENA
  if (c  == 9){
      c=0;}
  else {decena[c++];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[c]);
//delay(200);
 }

 if (X >0 && X <152 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR DECENA
  if (c  == 0){
      c=9;}
  else {decena[c--];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[c]);
//delay(200);
 }
  if (X >250 && X < 320 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR UNIDAD
  if (d  == 9){
      d=0;}
  else {unidad[d++];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[d]);
//delay(200);
 }

 if (X >250 && X <320 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR UNIDAD
  if (d  == 0){
      d=9;}
  else {unidad[d--];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[d]);
//delay(200);
 }   
 
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuTemperatura();
  Z=0;
  pulsacion = 1;
}
}
                                                              //COSAS DE LOS MENUES DE HUMEDAD DE SUELO
void menuHumedadSuelo() {
   tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,120,RED);
  tft.drawRect(0,120,320,120,RED);
  tft.setCursor(20,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Humedad Suelo");
  tft.setCursor(30,60);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Maxima");
  tft.setCursor(20,160);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Humedad Suelo");
  tft.setCursor(30,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Minima");

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  }
void menuHumedadSueloMax() {
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,170,RED);
  tft.drawRect(0,170,320,240,RED);
  
  tft.fillRect(109,45,109,77,WHITE);
  tft.fillTriangle(60,18,80,75,40,75,RED); //mas humedad decena
  tft.fillTriangle(60,152,80,95,40,95,RED); //menos humedad decena
  tft.fillTriangle(260,18,280,75,240,75,RED);//mas humedad unidad
  tft.fillTriangle(260,152,240,95,280,95,RED);//menos humedad unidad
 
  tft.setCursor(120,56);   //HUMEDAD SUELO DECENA
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hd]);

   tft.setCursor(165,56); //HUMEDAD SUELO UNIDAD
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hu]);
  
  tft.setCursor(20,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Cual sera la humedad");
  tft.setCursor(20,205);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("maxima del suelo?");

tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  }

void menuHumedadSueloMin () {
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,170,RED);
  tft.drawRect(0,170,320,240,RED);
  
  tft.fillRect(109,45,109,77,WHITE);
  tft.fillTriangle(60,18,80,75,40,75,RED); //mas humedad decena
  tft.fillTriangle(60,152,80,95,40,95,RED); //menos humedad decena
  tft.fillTriangle(260,18,280,75,240,75,RED);//mas humedad unidad
  tft.fillTriangle(260,152,240,95,280,95,RED);//menos humedad unidad
 
  tft.setCursor(120,56);   //HUMEDAD SUELO DECENA
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hsd]);

   tft.setCursor(165,56); //HUMEDAD SUELO UNIDAD
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hsu]);
  
  tft.setCursor(20,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Cual sera la humedad");
  tft.setCursor(20,205);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("minima del suelo?");
  
tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");


  }

void lecturaMenuHumedadSuelo(){
  if (X > 1 && X < 320 && Y > 1 && Y < 80 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuHumedadSueloMax(); 
    Z=0;
    pulsacion = 5;
  }
if(X > 1 && X < 280 && Y > 81 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
  menuHumedadSueloMin();
  Z=0;
  pulsacion = 6;
}
if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuPrincipal();
  Z=0;
  pulsacion = 0;
}
}
void lecturaMenuHumedadSueloMax(){
humedadMaximaEstablecida = hd*10 + hu;
 if (X >0 && X < 109 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR DECENA
  if (hd  == 9){
      hd=0;}
  else {decena[hd++];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hd]);
//delay(200);
 }

 if (X >0 && X <152 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR DECENA
  if (hd  == 0){
      hd=9;}
  else {decena[hd--];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hd]);
//delay(200);
 }
  if (X >250 && X < 320 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR UNIDAD
  if (hu  == 9){
      hu=0;}
  else {unidad[hu++];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hu]);
//delay(200);
 }

 if (X >250 && X <320 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR UNIDAD
  if (hu  == 0){
      hu=9;}
  else {unidad[hu--];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hu]);
//delay(200);
 }   
 
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuHumedadSuelo();
  Z=0;
  pulsacion = 4;
}
}
void lecturaMenuHumedadSueloMin(){
humedadMinimaEstablecida = hsd*10 + hsu;
 if (X >0 && X < 109 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR DECENA
  if (hsd  == 9){
      hsd=0;}
  else {decena[hsd++];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hsd]);
//delay(200);
 }

 if (X >0 && X <152 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR DECENA
  if (hsd  == 0){
      hsd=9;}
  else {decena[hsd--];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hsd]);
//delay(200);
 }
  if (X >250 && X < 320 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR UNIDAD
  if (hsu  == 9){
      hsu=0;}
  else {unidad[hsu++];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hsu]);
//delay(200);
 }

 if (X >250 && X <320 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR UNIDAD
  if (hsu  == 0){
      hsu=9;}
  else {unidad[hsu--];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hsu]);
//delay(200);
 }   
 
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuHumedadSuelo();
  Z=0;
  pulsacion = 4;
}
}
                                                                                      //COSAS DE LOS MENUES DE HUMEDAD DEL AIRE
void menuHumedadAire(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,120,RED);
  tft.drawRect(0,120,320,120,RED);
  tft.setCursor(20,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Humedad Aire");
  tft.setCursor(30,60);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Maxima");
  tft.setCursor(20,160);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Humedad Aire");
  tft.setCursor(30,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Minima");

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
}
void menuHumedadAireMax(){
 tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,170,RED);
  tft.drawRect(0,170,320,240,RED);
  
  tft.fillRect(109,45,109,77,WHITE);
  tft.fillTriangle(60,18,80,75,40,75,RED); //mas humedad decena
  tft.fillTriangle(60,152,80,95,40,95,RED); //menos humedad decena
  tft.fillTriangle(260,18,280,75,240,75,RED);//mas humedad unidad
  tft.fillTriangle(260,152,240,95,280,95,RED);//menos humedad unidad
 
  tft.setCursor(120,56);   //HUMEDAD AIRE DECENA
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[had]);

   tft.setCursor(165,56); //HUMEDAD AIRE UNIDAD
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hau]);
  
  tft.setCursor(20,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Cual sera la humedad");
  tft.setCursor(20,205);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("maxima del aire?");
  
tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
}
void menuHumedadAireMin(){
tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,170,RED);
  tft.drawRect(0,170,320,240,RED);
  
  tft.fillRect(109,45,109,77,WHITE);
  tft.fillTriangle(60,18,80,75,40,75,RED); //mas humedad decena
  tft.fillTriangle(60,152,80,95,40,95,RED); //menos humedad decena
  tft.fillTriangle(260,18,280,75,240,75,RED);//mas humedad unidad
  tft.fillTriangle(260,152,240,95,280,95,RED);//menos humedad unidad
 
  tft.setCursor(120,56);   //HUMEDAD AIRE DECENA
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hadm]);

   tft.setCursor(165,56); //HUMEDAD AIRE UNIDAD
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[haum]);
  
  tft.setCursor(20,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Cual sera la humedad");
  tft.setCursor(20,205);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("minima del aire?");
  
tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
}
void lecturaMenuHumedadAire(){
  if (X > 1 && X < 320 && Y > 1 && Y < 80 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuHumedadAireMax(); 
    Z=0;
    pulsacion = 8;
  }
if(X > 1 && X < 280 && Y > 81 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
  menuHumedadAireMin();
  Z=0;
  pulsacion = 9;
}
if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuPrincipal();
  Z=0;
  pulsacion = 0;
}
}
void lecturaMenuHumedadAireMax(){
  humedadAireMaximaEstablecida = had*10 + hau;
 if (X >0 && X < 109 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR DECENA
  if (had  == 9){
      had=0;}
  else {decena[had++];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[had]);
//delay(200);
 }

 if (X >0 && X <152 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR DECENA
  if (had  == 0){
      had=9;}
  else {decena[had--];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[had]);
//delay(200);
 }
  if (X >250 && X < 320 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR UNIDAD
  if (hau  == 9){
      hau=0;}
  else {unidad[hau++];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hau]);
//delay(200);
 }

 if (X >250 && X <320 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR UNIDAD
  if (hau  == 0){
      hau=9;}
  else {unidad[hau--];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[hau]);
//delay(200);
 }   
 
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuHumedadAire();
  Z=0;
  pulsacion = 7;
}
}
void lecturaMenuHumedadAireMin(){
    humedadAireMinimaEstablecida = hadm*10 + haum;
 if (X >0 && X < 109 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR DECENA
  if (hadm  == 9){
      hadm=0;}
  else {decena[hadm++];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hadm]);
//delay(200);
 }

 if (X >0 && X <152 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR DECENA
  if (hadm  == 0){
      hadm=9;}
  else {decena[hadm--];
  Z=0;
  }
  tft.fillRect(110,50,50,70, WHITE);
  tft.setCursor(120,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(decena[hadm]);
//delay(200);
 }
  if (X >250 && X < 320 && Y > 0 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE) { //SUBIR UNIDAD
  if (haum  == 9){
      haum=0;}
  else {unidad[haum++];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[haum]);
//delay(200);
 }

 if (X >250 && X <320 && Y > 80 && Y < 150 && Z > MINPRESSURE && Z < MAXPRESSURE) { //BAJAR UNIDAD
  if (haum  == 0){
      haum=9;}
  else {unidad[haum--];
  Z=0;
  }
  tft.fillRect(160,50,50,70, WHITE);
  tft.setCursor(170,56);
  tft.setTextColor(BLACK);
  tft.setTextSize(8);
  tft.print(unidad[haum]);
//delay(200);
 }   
 
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuHumedadAire();
  Z=0;
  pulsacion = 7;
}
} 

                                                                      //LOS MIL Y UN MENUES DEL CICLO DE LUCES
void menuLuz(){
  if (diaInicioC == 0 && diaInicioV == 0 && diaInicioF == 0){
    menuConfiguracion();
    pulsacion = 11;
    Z= 0;
  }else{
    menuParametros();
    pulsacion = 12;
    Z=0;
    }
}
void menuParametros(){
  tft.fillScreen(BLACK);

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  }
void menuConfiguracion(){
  tft.fillScreen(BLACK);

  tft.setCursor(90,2);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Configuracion");

  tft.drawRect(0,20,320,73,RED);//set germinacion
  tft.setCursor(60,45);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Germinacion");
  tft.drawRect(0,94,320,73,RED);//set vegetacion
  tft.setCursor(60,119);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Vegetacion");
  tft.drawRect(0,168,320,70,RED);//set floracion
  tft.setCursor(60,193);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Floracion");

tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  
}
void menuCrecimiento(){
  tft.fillScreen(BLACK);
  
  tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
  tft.setCursor(80,3);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Configuracion de Germinacion"); 
  
  tft.drawRect(0,0,320,120,RED);
  tft.drawRect(0,120,320,120,RED);
  tft.setCursor(20,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Fechas");
  tft.setCursor(30,70);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Inicio y fin de la germinacion");
  tft.setCursor(20,150);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Horario");
  tft.setCursor(30,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Periodo en el que tendra luz");

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  }
void menuVegetacion(){
  tft.fillScreen(BLACK);
  
  tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
  tft.setCursor(80,3);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Configuracion de Vegetacion"); 
  
  tft.drawRect(0,0,320,120,RED);
  tft.drawRect(0,120,320,120,RED);
  tft.setCursor(20,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Fechas");
  tft.setCursor(30,70);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Inicio y fin de la vegetacion");
  tft.setCursor(20,150);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Horario");
  tft.setCursor(30,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Periodo en el que tendra luz");

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  }
void menuFloracion(){
  tft.fillScreen(BLACK);
  
  tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
  tft.setCursor(80,3);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Configuracion de Floracion"); 
  
  tft.drawRect(0,0,320,120,RED);
  tft.drawRect(0,120,320,120,RED);
  tft.setCursor(20,40);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Fechas");
  tft.setCursor(30,70);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Inicio y fin de la floracion");
  tft.setCursor(20,150);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Horario");
  tft.setCursor(30,180);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Periodo en el que tendra luz");

  tft.fillRect(280,200,40,40,RED); //escape
  tft.setCursor(288,205);
  tft.setTextSize(4);
  tft.setTextColor(WHITE);
  tft.print("X");
  }

void menuFechaCrecimiento(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
  tft.setCursor(90,3);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Periodo de Germinacion");

  tft.drawRect(0,0,320,240,RED);
  tft.setCursor(10,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Germinar desde:");

  tft.fillRect(25,55,60,52,WHITE); //dia inicio
  tft.fillRect(105,55,60,52,WHITE);//mes inicio
  tft.fillRect(185,55,120,52,WHITE);// año inicio
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioCrecimiento); //año incio germinacion

  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioCrecimiento);    //mes inicio germinacion

   tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioCrecimiento);    //dia inicio germinacion

  
  
  tft.fillTriangle(55,40,25,50,85,50, RED);//SUBE FECHA
  tft.fillTriangle(55,120,25,110,85,110, RED);//BAJA FECHA
  tft.fillTriangle(135,40,105,50,165,50, RED);//SUBE MES
  tft.fillTriangle(135,120,105,110,165,110, RED);//BAJA MES
  tft.fillTriangle(245,40,185,50,305,50, RED);//SUBE AÑO
  tft.fillTriangle(245,120,185,110,305,110, RED);//BAJA AÑO

  tft.setCursor(10,125);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Germinar hasta:");
  
  tft.fillRect(25,160,60,52,WHITE);//dia fin
  tft.fillRect(105,160,60,52,WHITE);//mes fin
  tft.fillRect(185,160,120,52,WHITE);//año fin
  
  tft.fillTriangle(55,145,25,155,85,155, RED);//SUBE FECHA
  tft.fillTriangle(55,225,25,215,85,215, RED);//BAJA FECHA
  tft.fillTriangle(135,145,105,155,165,155, RED);//SUBE MES
  tft.fillTriangle(135,225,105,215,165,215, RED);//BAJA MES
  tft.fillTriangle(245,145,185,155,305,155, RED);//SUBE AÑO
  tft.fillTriangle(245,225,185,215,305,215, RED);//BAJA AÑO

   tft.setCursor(187,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinCrecimiento);    //año fin germinacion

   tft.setCursor(107,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinCrecimiento);      //mes fin germinacion

 
   tft.setCursor(27,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinCrecimiento);    //dia fin germinacion

  tft.fillRect(290,0,30,30,RED); //escape
  tft.setCursor(298,5);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("X");
  }
void menuHorarioCrecimiento(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,240,RED);
  tft.drawRect(0,0,320,15, RED);
  tft.setCursor(90,3);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print("Fotoperiodo en Germinacion");
                                            //FRONT DEL ENCENDIDO DE LUCES EN GERMINACION
  tft.setCursor(5,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Encender luz: ");

  
  
  tft.fillRect(80,45,70,70,WHITE);
  tft.fillRect(170,45,70,70,WHITE);
  tft.fillTriangle(37,45,10,65,65,65,RED);
  tft.fillTriangle(37,115,10,95,65,95,RED);
  tft.fillTriangle(283,45,310,65,255,65,RED);
  tft.fillTriangle(283,115,310,95,255,95,RED);

  //tft.setCursor(95,95);
  //tft.setTextSize(2);
  //tft.setTextColor(BLACK);
  //tft.print("A.M");
if(horaInicioCrecimiento < 11){ 
  tft.setCursor(95,95);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("A.M");}else{ 
  tft.setCursor(95,95);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("P.M");};
 
  tft.setCursor(15,73);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Hora");
  
  tft.setCursor(86,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(horaInicioCrecimiento);

  //tft.setCursor(185,95);
  //tft.setTextSize(2);
  //tft.setTextColor(BLACK);
  //tft.print("A.M");

if(horaInicioCrecimiento > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
    }
 tft.setCursor(260,73);
 tft.setTextSize(2);
 tft.setTextColor(WHITE);
 tft.print("Min.");



  
  tft.setCursor(176,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoInicioCrecimiento);
                                        //FRONT DEL APAGADO DE LUCES EN GERMINACION
  tft.setCursor(5,120);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Apagar luz: ");
                                    
  tft.fillRect(80,145,70,70,WHITE);
  tft.fillRect(170,145,70,70,WHITE);
  tft.fillTriangle(37,145,10,165,65,165,RED);
  tft.fillTriangle(37,215,10,195,65,195,RED);
  tft.fillTriangle(283,145,310,165,255,165,RED);
  tft.fillTriangle(283,215,310,195,255,195,RED);

  
 if(horaFinCrecimiento < 11){ 
  tft.setCursor(95,195);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("A.M");}else{ 
  tft.setCursor(95,195);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("P.M");};
 
  tft.setCursor(15,173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Hora");
  
  tft.setCursor(86,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(horaFinCrecimiento);

 // tft.setCursor(185,195);
  //tft.setTextSize(2);
 // tft.setTextColor(BLACK);
  //tft.print("A.M");

  if(horaFinCrecimiento > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
 
  tft.setCursor(260,173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Min.");
  
  tft.setCursor(176,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoFinCrecimiento);

  tft.fillRect(290,0,30,30,RED); //escape
  tft.setCursor(298,5);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("X");
  }


void menuFechaVegetacion(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
  tft.setCursor(90,3);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Periodo de Vegetacion");

  tft.drawRect(0,0,320,240,RED);
  tft.setCursor(10,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Inicio de la Vegetacion:");

  tft.fillRect(25,55,60,52,WHITE); //dia inicio
  tft.fillRect(105,55,60,52,WHITE);//mes inicio
  tft.fillRect(185,55,120,52,WHITE);// año inicio
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinCrecimiento); //año incio germinacion

  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinCrecimiento);    //mes inicio germinacion

   tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinCrecimiento);    //dia inicio germinacion

  
  
 /* tft.fillTriangle(55,40,25,50,85,50, RED);//SUBE FECHA
  tft.fillTriangle(55,120,25,110,85,110, RED);//BAJA FECHA
  tft.fillTriangle(135,40,105,50,165,50, RED);//SUBE MES
  tft.fillTriangle(135,120,105,110,165,110, RED);//BAJA MES
  tft.fillTriangle(245,40,185,50,305,50, RED);//SUBE AÑO
  tft.fillTriangle(245,120,185,110,305,110, RED);//BAJA AÑO */

  tft.setCursor(10,125);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Vegetar hasta:");
  
  tft.fillRect(25,160,60,52,WHITE);//dia fin
  tft.fillRect(105,160,60,52,WHITE);//mes fin
  tft.fillRect(185,160,120,52,WHITE);//año fin
  
  tft.fillTriangle(55,145,25,155,85,155, RED);//SUBE FECHA
  tft.fillTriangle(55,225,25,215,85,215, RED);//BAJA FECHA
  tft.fillTriangle(135,145,105,155,165,155, RED);//SUBE MES
  tft.fillTriangle(135,225,105,215,165,215, RED);//BAJA MES
  tft.fillTriangle(245,145,185,155,305,155, RED);//SUBE AÑO
  tft.fillTriangle(245,225,185,215,305,215, RED);//BAJA AÑO

   tft.setCursor(187,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinVegetacion);    //año fin germinacion

   tft.setCursor(107,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinVegetacion);      //mes fin germinacion

 
   tft.setCursor(27,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinVegetacion);    //dia fin germinacion

  tft.fillRect(290,0,30,30,RED); //escape
  tft.setCursor(298,5);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("X");
  }
  

void menuHorarioVegetacion(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,240,RED);
  tft.drawRect(0,0,320,15, RED);
  tft.setCursor(90,3);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print("Fotoperiodo en Vegetacion");
                                            //FRONT DEL ENCENDIDO DE LUCES EN GERMINACION
  tft.setCursor(5,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Encender luz: ");

  
  
  tft.fillRect(80,45,70,70,WHITE);
  tft.fillRect(170,45,70,70,WHITE);
  tft.fillTriangle(37,45,10,65,65,65,RED);
  tft.fillTriangle(37,115,10,95,65,95,RED);
  tft.fillTriangle(283,45,310,65,255,65,RED);
  tft.fillTriangle(283,115,310,95,255,95,RED);

  //tft.setCursor(95,95);
  //tft.setTextSize(2);
  //tft.setTextColor(BLACK);
  //tft.print("A.M");
if(horaInicioVegetacion < 11){ 
  tft.setCursor(95,95);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("A.M");}else{ 
  tft.setCursor(95,95);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("P.M");};
 
  tft.setCursor(15,73);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Hora");
  
  tft.setCursor(86,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(horaInicioVegetacion);

  //tft.setCursor(185,95);
  //tft.setTextSize(2);
  //tft.setTextColor(BLACK);
  //tft.print("A.M");

if(horaInicioVegetacion > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
    }
 tft.setCursor(260,73);
 tft.setTextSize(2);
 tft.setTextColor(WHITE);
 tft.print("Min.");



  
  tft.setCursor(176,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoInicioVegetacion);
                                        //FRONT DEL APAGADO DE LUCES EN GERMINACION
  tft.setCursor(5,120);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Apagar luz: ");
                                    
  tft.fillRect(80,145,70,70,WHITE);
  tft.fillRect(170,145,70,70,WHITE);
  tft.fillTriangle(37,145,10,165,65,165,RED);
  tft.fillTriangle(37,215,10,195,65,195,RED);
  tft.fillTriangle(283,145,310,165,255,165,RED);
  tft.fillTriangle(283,215,310,195,255,195,RED);

  
 if(horaFinVegetacion < 11){ 
  tft.setCursor(95,195);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("A.M");}else{ 
  tft.setCursor(95,195);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("P.M");};
 
  tft.setCursor(15,173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Hora");
  
  tft.setCursor(86,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(horaFinVegetacion);

 // tft.setCursor(185,195);
  //tft.setTextSize(2);
 // tft.setTextColor(BLACK);
  //tft.print("A.M");

  if(horaFinVegetacion > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
 
  tft.setCursor(260,173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Min.");
  
  tft.setCursor(176,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoFinVegetacion);

  tft.fillRect(290,0,30,30,RED); //escape
  tft.setCursor(298,5);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("X");
  }

void menuFechaFloracion(){
tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,15,RED); // (x,y,ancho,altura,color)//x max= 320, y max =240
  tft.setCursor(90,3);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print("Periodo de Floracion");

  tft.drawRect(0,0,320,240,RED);
  tft.setCursor(10,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Inicio de la Floracion:");

  tft.fillRect(25,55,60,52,WHITE); //dia inicio
  tft.fillRect(105,55,60,52,WHITE);//mes inicio
  tft.fillRect(185,55,120,52,WHITE);// año inicio
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinVegetacion); //año incio floracion

  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinVegetacion);    //mes inicio floracion

   tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinVegetacion);    //dia inicio floracion

  
  
 /* tft.fillTriangle(55,40,25,50,85,50, RED);//SUBE FECHA
  tft.fillTriangle(55,120,25,110,85,110, RED);//BAJA FECHA
  tft.fillTriangle(135,40,105,50,165,50, RED);//SUBE MES
  tft.fillTriangle(135,120,105,110,165,110, RED);//BAJA MES
  tft.fillTriangle(245,40,185,50,305,50, RED);//SUBE AÑO
  tft.fillTriangle(245,120,185,110,305,110, RED);//BAJA AÑO */

  tft.setCursor(10,125);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Florar hasta:");
  
  tft.fillRect(25,160,60,52,WHITE);//dia fin
  tft.fillRect(105,160,60,52,WHITE);//mes fin
  tft.fillRect(185,160,120,52,WHITE);//año fin
  
  tft.fillTriangle(55,145,25,155,85,155, RED);//SUBE FECHA
  tft.fillTriangle(55,225,25,215,85,215, RED);//BAJA FECHA
  tft.fillTriangle(135,145,105,155,165,155, RED);//SUBE MES
  tft.fillTriangle(135,225,105,215,165,215, RED);//BAJA MES
  tft.fillTriangle(245,145,185,155,305,155, RED);//SUBE AÑO
  tft.fillTriangle(245,225,185,215,305,215, RED);//BAJA AÑO

   tft.setCursor(187,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinFloracion);    //año fin germinacion

   tft.setCursor(107,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinFloracion);      //mes fin germinacion

 
   tft.setCursor(27,168);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinFloracion);    //dia fin germinacion

  tft.fillRect(290,0,30,30,RED); //escape
  tft.setCursor(298,5);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("X");
  
  }



void menuHorarioFloracion(){
  tft.fillScreen(BLACK);
  tft.drawRect(0,0,320,240,RED);
  tft.drawRect(0,0,320,15, RED);
  tft.setCursor(90,3);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print("Fotoperiodo en Floracion");
                                            //FRONT DEL ENCENDIDO DE LUCES EN GERMINACION
  tft.setCursor(5,20);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Encender luz: ");

  
  
  tft.fillRect(80,45,70,70,WHITE);
  tft.fillRect(170,45,70,70,WHITE);
  tft.fillTriangle(37,45,10,65,65,65,RED);
  tft.fillTriangle(37,115,10,95,65,95,RED);
  tft.fillTriangle(283,45,310,65,255,65,RED);
  tft.fillTriangle(283,115,310,95,255,95,RED);

  //tft.setCursor(95,95);
  //tft.setTextSize(2);
  //tft.setTextColor(BLACK);
  //tft.print("A.M");
if(horaInicioFloracion < 11){ 
  tft.setCursor(95,95);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("A.M");}else{ 
  tft.setCursor(95,95);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("P.M");};
 
  tft.setCursor(15,73);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Hora");
  
  tft.setCursor(86,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(horaInicioFloracion);

  //tft.setCursor(185,95);
  //tft.setTextSize(2);
  //tft.setTextColor(BLACK);
  //tft.print("A.M");

if(horaInicioFloracion > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
    }
 tft.setCursor(260,73);
 tft.setTextSize(2);
 tft.setTextColor(WHITE);
 tft.print("Min.");



  
  tft.setCursor(176,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoInicioFloracion);
                                        //FRONT DEL APAGADO DE LUCES EN GERMINACION
  tft.setCursor(5,120);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Apagar luz: ");
                                    
  tft.fillRect(80,145,70,70,WHITE);
  tft.fillRect(170,145,70,70,WHITE);
  tft.fillTriangle(37,145,10,165,65,165,RED);
  tft.fillTriangle(37,215,10,195,65,195,RED);
  tft.fillTriangle(283,145,310,165,255,165,RED);
  tft.fillTriangle(283,215,310,195,255,195,RED);

  
 if(horaFinFloracion < 11){ 
  tft.setCursor(95,195);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("A.M");}else{ 
  tft.setCursor(95,195);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.print("P.M");};
 
  tft.setCursor(15,173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Hora");
  
  tft.setCursor(86,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(horaFinFloracion);

 // tft.setCursor(185,195);
  //tft.setTextSize(2);
 // tft.setTextColor(BLACK);
  //tft.print("A.M");

  if(horaFinFloracion > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
 
  tft.setCursor(260,173);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.print("Min.");
  
  tft.setCursor(176,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoFinFloracion);

  tft.fillRect(290,0,30,30,RED); //escape
  tft.setCursor(298,5);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.print("X");
  }


  
void lecturaMenuLuz(){}
void lecturaMenuConfiguracion(){
  if (X> 0 && X < 320 && Y > 20 && Y < 93 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuCrecimiento();
    pulsacion = 13;
    Z=0;
    }
  if (X>0 && X < 320 && Y>94 && Y< 166 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuVegetacion();
    pulsacion = 14;
    Z=0;
    }
  if (X>0 && X<270 && Y>167 && Y<240 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuFloracion();
    pulsacion = 15;
    Z=0;
    }
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuParametros();
  Z=0;
  pulsacion = 12;
  }


}
void lecturaMenuParametros(){

  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuPrincipal();
  Z=0;
  pulsacion = 0;
  }
  }
void lecturaMenuCrecimiento(){
  if(X>0 && X< 320 && Y > 0 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuFechaCrecimiento();
    pulsacion = 16;
    Z = 0;
    }
  if (X > 0 && X< 270 && Y > 121 && Y < 200 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuHorarioCrecimiento();
    pulsacion= 17;
    Z=0;
    }
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuConfiguracion();
  Z=0;
  pulsacion = 11;
  }
} 
void lecturaMenuVegetacion(){
  if(X>0 && X< 320 && Y > 0 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuFechaVegetacion();
    pulsacion = 18;
    Z = 0;
    }
  if (X > 0 && X< 270 && Y > 121 && Y < 200 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuHorarioVegetacion();
    pulsacion= 19;
    Z=0;
    }
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuConfiguracion();
  Z=0;
  pulsacion = 11;
  }
  }
void lecturaMenuFloracion(){

  if(X>0 && X< 320 && Y > 0 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuFechaFloracion();
    pulsacion = 20;
    Z = 0;
    }
  if (X > 0 && X< 270 && Y > 121 && Y < 200 && Z > MINPRESSURE && Z < MAXPRESSURE){
    menuHorarioFloracion();
    pulsacion= 21;
    Z=0;
    }
  
  if (X > 280 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuConfiguracion();
  Z=0;
  pulsacion = 11;
  }
  }

void lecturaMenuFechaCrecimiento(){                                     //TACTIL PANTALLA FOTOPERIODO (GERMINACION)
                                                                        //CONTROL DE FECHA DE INICIO GERMINACION
  if(X > 0 && X < 85 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir dia
    if (diaInicioCrecimiento == 31){diaInicioCrecimiento = 1;}
    else {dia[diaInicioCrecimiento++];}
     Z=0;
  tft.fillRect(25,55,60,52,WHITE);
  tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioCrecimiento);
//  delay(200);  
    }
  if(X > 0 && X < 85 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar dia
    if (diaInicioCrecimiento < 1){diaInicioCrecimiento = 31;}
    else {dia[diaInicioCrecimiento--];}
     Z=0;
  tft.fillRect(25,55,60,52,WHITE);
  tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioCrecimiento);
//  delay(200);  
  }

  if(X > 90 && X < 150 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir mes
    if (mesInicioCrecimiento == 12){mesInicioCrecimiento = 1;}
    else {mes[mesInicioCrecimiento++];}
     Z=0;
  tft.fillRect(105,55,60,52,WHITE);
  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioCrecimiento);
//  delay(200);  
    }
  if(X > 90 && X < 150 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar mes
    if (mesInicioCrecimiento < 1){mesInicioCrecimiento = 12;}
    else {mes[mesInicioCrecimiento--];}
     Z=0;
  tft.fillRect(105,55,60,52,WHITE);
  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioCrecimiento);
//  delay(200);  
  }
  
  if(X > 160 && X < 280 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir año
     anomas = anomas + 1;
    if (anomas > 10){anomas = 0;}
   //else {ano[anoInicioCrecimiento++];}
    
      {anoInicioCrecimiento = ano[anomas];}
     Z=0;
  tft.fillRect(185,55,120,52,WHITE);
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioCrecimiento);
 // delay(200);  
    }
  if(X > 160 && X < 320 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar año
    anomas = anomas-1;
    if (anomas < 0){anomas = 11;}
    //else {ano[anoInicioCrecimiento--];}
     else anoInicioCrecimiento = ano[anomas];
     Z=0;
  tft.fillRect(185,55,120,52,WHITE);
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioCrecimiento);
 // delay(200);  
  }

                                                //CONTROL FECHA FIN DE GERMINACION
 
 
 if(X > 0 && X < 85 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir dia
    if (diaFinCrecimiento == 31){diaFinCrecimiento = 1;}
    else {dia[diaFinCrecimiento++];}
     Z=0;
  tft.fillRect(25,160,60,52,WHITE);
  tft.setCursor(27,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinCrecimiento);
//  delay(200);  
    }
  if(X > 0 && X < 85 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar dia
    if (diaFinCrecimiento < 1){diaFinCrecimiento = 31;}
    else {dia[diaFinCrecimiento--];}
     Z=0;
  tft.fillRect(25,160,60,52,WHITE);
  tft.setCursor(27,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinCrecimiento);
 // delay(200);  
  }

  if(X > 90 && X < 150 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir mes
    if (mesFinCrecimiento == 12){mesFinCrecimiento = 1;}
    else {mes[mesFinCrecimiento++];}
     Z=0;
  tft.fillRect(105,160,60,52,WHITE);
  tft.setCursor(107,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinCrecimiento);
//  delay(200);  
    }
  if(X > 90 && X < 150 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar mes
    if (mesFinCrecimiento < 1){mesFinCrecimiento = 12;}
    else {mes[mesFinCrecimiento--];}
     Z=0;
  tft.fillRect(105,160,60,52,WHITE);
  tft.setCursor(107,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinCrecimiento);
//  delay(200);  
  }
  
  if(X > 160 && X < 280 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir año
     anomas1 = anomas1 + 1;
    if (anomas1 > 10){anomas1 = 0;}
   //else {ano[anoInicioCrecimiento++];}
    
      {anoFinCrecimiento = ano[anomas1];}
     Z=0;
  tft.fillRect(185,160,120,52,WHITE);
  tft.setCursor(187,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinCrecimiento);
//  delay(200);  
    }
  if(X > 160 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar año
    anomas1 = anomas1-1;
    if (anomas1 < 0){anomas1 = 11;}
    //else {ano[anoInicioCrecimiento--];}
     else anoFinCrecimiento = ano[anomas1];
     Z=0;
  tft.fillRect(185,160,120,52,WHITE);
  tft.setCursor(187,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinCrecimiento);
//  delay(200);  
  }
  if (X > 280 && X < 320 && Y > 0 && Y < 30 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuCrecimiento();
  Z=0;
  pulsacion = 13;
  }
  }

void lecturaMenuHorarioCrecimiento(){
  if (X > 0 && X < 80 && Y > 0 && Y < 50 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaC = horaC + 1; 
    if(horaC == 23){horaC = 0;}
    horaInicioCrecimiento = hora[horaC];
    Z=0;
 tft.fillRect(80,45,70,70,WHITE);
 tft.setCursor(86,53);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaInicioCrecimiento);
      
 if(horaInicioCrecimiento > 11){
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
//    delay(200);
    }
if (X > 0 && X < 80 && Y > 60 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaC = horaC - 1; 
    if(horaC < 1){horaC = 23;}
    horaInicioCrecimiento = hora[horaC];
    Z=0;
 tft.fillRect(80,45,70,50,WHITE);
 tft.setCursor(86,53);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaInicioCrecimiento);
      
 if(horaInicioCrecimiento > 11){
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //  delay(200);
    }


if (X > 0 && X < 80 && Y > 130 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaCF = horaCF + 1; 
    if(horaCF == 23){horaCF = 0;}
    horaFinCrecimiento = hora[horaCF];
    Z=0;
 tft.fillRect(80,145,70,70,WHITE);
 tft.setCursor(86,153);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaFinCrecimiento);
      
 if(horaFinCrecimiento > 11){
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //  delay(200);
    }
if (X > 0 && X < 80 && Y > 180 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaCF = horaCF - 1; 
    if(horaCF < 1){horaCF = 23;}
    horaFinCrecimiento = hora[horaCF];
    Z=0;
 tft.fillRect(80,145,70,50,WHITE);
 tft.setCursor(86,153);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaFinCrecimiento);
      
 if(horaFinCrecimiento > 11){
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
   // delay(200);
    }

if (X > 200 && X < 320 && Y > 35 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE){
  minC = minC + 1;
   if(minC == 6){minC = 0;}
    minutoInicioCrecimiento = minutos[minC];
    Z= 0;
 tft.fillRect(170,45,70,50, WHITE);
 tft.setCursor(176,53);
 tft.setTextSize(5);
 tft.setTextColor(BLACK);
 tft.print(minutoInicioCrecimiento);
   
 if(horaInicioCrecimiento > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
   //   delay(200);
}
  if (X > 200 && X < 320 && Y > 76 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
   minC = minC - 1;
    if(minC < 1){minC = 6;}
      minutoInicioCrecimiento = minutos[minC];
      Z=0;
  tft.fillRect(170,45,70,50, WHITE);
  tft.setCursor(176,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoInicioCrecimiento);
  
 if(horaInicioCrecimiento > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //   delay(200);
} 

if (X > 200 && X < 320 && Y > 120 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE){
  minCF = minCF + 1;
   if(minCF == 6){minCF = 0;}
    minutoFinCrecimiento = minutos[minCF];
    Z= 0;
 tft.fillRect(170,145,70,50, WHITE);
 tft.setCursor(176,153);
 tft.setTextSize(5);
 tft.setTextColor(BLACK);
 tft.print(minutoFinCrecimiento);
   
 if(horaFinCrecimiento > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //    delay(200);
}
  if (X > 200 && X < 320 && Y > 180 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
   minCF = minCF - 1;
    if(minCF < 1){minCF = 6;}
      minutoFinCrecimiento = minutos[minCF];
      Z=0;
  tft.fillRect(170,145,70,50, WHITE);
  tft.setCursor(176,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoFinCrecimiento);
  
 if(horaFinCrecimiento > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
 //    delay(200);
} 

  
if (X > 280 && X < 320 && Y > 0 && Y < 30 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuCrecimiento();
  Z=0;
  pulsacion = 13;
  }
}

void lecturaMenuFechaVegetacion(){
  /*                                                                       //CONTROL DE FECHA DE INICIO GERMINACION
  if(X > 0 && X < 85 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir dia
    if (diaInicioVegetacion == 31){diaInicioVegetacion = 1;}
    else {dia[diaInicioVegetacion++];}
     Z=0;
  tft.fillRect(25,55,60,52,WHITE);
  tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioVegetacion);
  delay(200);  
    }
  if(X > 0 && X < 85 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar dia
    if (diaInicioVegetacion < 1){diaInicioVegetacion = 31;}
    else {dia[diaInicioVegetacion--];}
     Z=0;
  tft.fillRect(25,55,60,52,WHITE);
  tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioVegetacion);
  delay(200);  
  }

  if(X > 90 && X < 150 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir mes
    if (mesInicioVegetacion == 12){mesInicioVegetacion = 1;}
    else {mes[mesInicioVegetacion++];}
     Z=0;
  tft.fillRect(105,55,60,52,WHITE);
  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioVegetacion);
  delay(200);  
    }
  if(X > 90 && X < 150 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar mes
    if (mesInicioVegetacion < 1){mesInicioVegetacion = 12;}
    else {mes[mesInicioVegetacion--];}
     Z=0;
  tft.fillRect(105,55,60,52,WHITE);
  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioVegetacion);
  delay(200);  
  }
  
  if(X > 160 && X < 280 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir año
     anomasV = anomasV + 1;
    if (anomasV > 10){anomasV = 0;}
   //else {ano[anoInicioCrecimiento++];}
    
      {anoInicioVegetacion = ano[anomasV];}
     Z=0;
  tft.fillRect(185,55,120,52,WHITE);
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioVegetacion);
  delay(200);  
    }
  if(X > 160 && X < 320 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar año
    anomasV = anomasV-1;
    if (anomasV < 0){anomasV = 11;}
    //else {ano[anoInicioCrecimiento--];}
     else anoInicioVegetacion = ano[anomasV];
     Z=0;
  tft.fillRect(185,55,120,52,WHITE);
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioVegetacion);
  delay(200);  
  }
*/
                                                //CONTROL FECHA FIN DE VEGETACION
 
 
 if(X > 0 && X < 85 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir dia
    if (diaFinVegetacion == 31){diaFinVegetacion = 1;}
    else {dia[diaFinVegetacion++];}
     Z=0;
  tft.fillRect(25,160,60,52,WHITE);
  tft.setCursor(27,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinVegetacion);
//  delay(200);  
    }
  if(X > 0 && X < 85 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar dia
    if (diaFinVegetacion < 1){diaFinVegetacion = 31;}
    else {dia[diaFinVegetacion--];}
     Z=0;
  tft.fillRect(25,160,60,52,WHITE);
  tft.setCursor(27,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinVegetacion);
  //delay(200);  
  }

  if(X > 90 && X < 150 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir mes
    if (mesFinVegetacion == 12){mesFinVegetacion = 1;}
    else {mes[mesFinVegetacion++];}
     Z=0;
  tft.fillRect(105,160,60,52,WHITE);
  tft.setCursor(107,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinVegetacion);
 // delay(200);  
    }
  if(X > 90 && X < 150 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar mes
    if (mesFinVegetacion < 1){mesFinVegetacion = 12;}
    else {mes[mesFinVegetacion--];}
     Z=0;
  tft.fillRect(105,160,60,52,WHITE);
  tft.setCursor(107,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinVegetacion);
 // delay(200);  
  }
  
  if(X > 160 && X < 280 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir año
     anomas1V = anomas1V + 1;
    if (anomas1V > 10){anomas1V = 0;}
   //else {ano[anoInicioCrecimiento++];}
    
      {anoFinVegetacion = ano[anomas1V];}
     Z=0;
  tft.fillRect(185,160,120,52,WHITE);
  tft.setCursor(187,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinVegetacion);
//  delay(200);  
    }
  if(X > 160 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar año
    anomas1V = anomas1V-1;
    if (anomas1V < 0){anomas1V = 11;}
    //else {ano[anoInicioCrecimiento--];}
     else anoFinVegetacion = ano[anomas1V];
     Z=0;
  tft.fillRect(185,160,120,52,WHITE);
  tft.setCursor(187,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinVegetacion);
//  delay(200);  
  }
  if (X > 280 && X < 320 && Y > 0 && Y < 30 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuVegetacion();
  Z=0;
  pulsacion = 14;
  }
  }


void lecturaMenuHorarioVegetacion(){
  if (X > 0 && X < 80 && Y > 0 && Y < 50 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaV = horaV + 1; 
    if(horaV == 24){horaV = 0;}
    horaInicioVegetacion = hora[horaV];
    Z=0;
 tft.fillRect(80,45,70,70,WHITE);
 tft.setCursor(86,53);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaInicioVegetacion);
      
 if(horaInicioVegetacion > 11){
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
//    delay(200);
    }
if (X > 0 && X < 80 && Y > 60 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaV= horaV - 1; 
    if(horaC < 0){horaC = 24;}
    horaInicioVegetacion = hora[horaV];
    Z=0;
 tft.fillRect(80,45,70,50,WHITE);
 tft.setCursor(86,53);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaInicioVegetacion);
      
 if(horaInicioVegetacion > 11){
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
 //   delay(200);
    }


if (X > 0 && X < 80 && Y > 130 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaVF = horaVF + 1; 
    if(horaVF == 23){horaVF = 0;}
    horaFinVegetacion = hora[horaVF];
    Z=0;
 tft.fillRect(80,145,70,70,WHITE);
 tft.setCursor(86,153);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaFinVegetacion);
      
 if(horaFinVegetacion > 11){
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //  delay(200);
    }
if (X > 0 && X < 80 && Y > 180 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaVF = horaVF - 1; 
    if(horaVF < 0){horaVF = 24;}
    horaFinVegetacion = hora[horaVF];
    Z=0;
 tft.fillRect(80,145,70,50,WHITE);
 tft.setCursor(86,153);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaFinVegetacion);
      
 if(horaFinVegetacion > 11){
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //  delay(200);
    }

if (X > 200 && X < 320 && Y > 35 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE){
  minV = minV + 1;
   if(minV == 6){minV = 0;}
    minutoInicioVegetacion = minutos[minV];
    Z= 0;
 tft.fillRect(170,45,70,50, WHITE);
 tft.setCursor(176,53);
 tft.setTextSize(5);
 tft.setTextColor(BLACK);
 tft.print(minutoInicioVegetacion);
   
 if(horaInicioVegetacion > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //    delay(200);
}
  if (X > 200 && X < 320 && Y > 76 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
   minV = minV - 1;
    if(minV < 1){minV = 6;}
      minutoInicioVegetacion = minutos[minV];
      Z=0;
  tft.fillRect(170,45,70,50, WHITE);
  tft.setCursor(176,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoInicioVegetacion);
  
 if(horaInicioVegetacion > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
   //  delay(200);
} 

if (X > 200 && X < 320 && Y > 120 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE){
  minVF = minVF + 1;
   if(minVF == 6){minVF = 0;}
    minutoFinVegetacion = minutos[minVF];
    Z= 0;
 tft.fillRect(170,145,70,50, WHITE);
 tft.setCursor(176,153);
 tft.setTextSize(5);
 tft.setTextColor(BLACK);
 tft.print(minutoFinVegetacion);
   
 if(horaFinVegetacion > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
  //    delay(200);
}
  if (X > 200 && X < 320 && Y > 180 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
   minVF = minVF - 1;
    if(minVF < 1){minVF = 6;}
      minutoFinVegetacion = minutos[minVF];
      Z=0;
  tft.fillRect(170,145,70,50, WHITE);
  tft.setCursor(176,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoFinVegetacion);
  
 if(horaFinVegetacion > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
   //  delay(200);
} 

  
if (X > 280 && X < 320 && Y > 0 && Y < 30 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuVegetacion();
  Z=0;
  pulsacion = 14;
  }
  }

void lecturaMenuFechaFloracion(){
    /*         NO TIENE ESTABLECIDO NINGUNA VARIABLE, ESTA COPIADO Y PEGADO POR LAS DUDAS SE PRECISE EN ALGUN MOMENTO                                                              //CONTROL DE FECHA DE INICIO GERMINACION
  if(X > 0 && X < 85 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir dia
    if (diaInicioVegetacion == 31){diaInicioVegetacion = 1;}
    else {dia[diaInicioVegetacion++];}
     Z=0;
  tft.fillRect(25,55,60,52,WHITE);
  tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioVegetacion);
  delay(200);  
    }
  if(X > 0 && X < 85 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar dia
    if (diaInicioVegetacion < 1){diaInicioVegetacion = 31;}
    else {dia[diaInicioVegetacion--];}
     Z=0;
  tft.fillRect(25,55,60,52,WHITE);
  tft.setCursor(27,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaInicioVegetacion);
  delay(200);  
  }

  if(X > 90 && X < 150 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir mes
    if (mesInicioVegetacion == 12){mesInicioVegetacion = 1;}
    else {mes[mesInicioVegetacion++];}
     Z=0;
  tft.fillRect(105,55,60,52,WHITE);
  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioVegetacion);
  delay(200);  
    }
  if(X > 90 && X < 150 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar mes
    if (mesInicioVegetacion < 1){mesInicioVegetacion = 12;}
    else {mes[mesInicioVegetacion--];}
     Z=0;
  tft.fillRect(105,55,60,52,WHITE);
  tft.setCursor(107,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesInicioVegetacion);
  delay(200);  
  }
  
  if(X > 160 && X < 280 && Y > 0 && Y < 40 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir año
     anomasV = anomasV + 1;
    if (anomasV > 10){anomasV = 0;}
   //else {ano[anoInicioCrecimiento++];}
    
      {anoInicioVegetacion = ano[anomasV];}
     Z=0;
  tft.fillRect(185,55,120,52,WHITE);
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioVegetacion);
  delay(200);  
    }
  if(X > 160 && X < 320 && Y > 50 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar año
    anomasV = anomasV-1;
    if (anomasV < 0){anomasV = 11;}
    //else {ano[anoInicioCrecimiento--];}
     else anoInicioVegetacion = ano[anomasV];
     Z=0;
  tft.fillRect(185,55,120,52,WHITE);
  tft.setCursor(187,63);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoInicioVegetacion);
  delay(200);  
  }
*/
                                                //CONTROL FECHA FIN DE VEGETACION
 
 
 if(X > 0 && X < 85 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir dia
    if (diaFinFloracion == 31){diaFinFloracion = 1;}
    else {dia[diaFinFloracion++];}
     Z=0;
  tft.fillRect(25,160,60,52,WHITE);
  tft.setCursor(27,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinFloracion);
//  delay(200);  
    }
  if(X > 0 && X < 85 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar dia
    if (diaFinFloracion < 1){diaFinFloracion = 31;}
    else {dia[diaFinFloracion--];}
     Z=0;
  tft.fillRect(25,160,60,52,WHITE);
  tft.setCursor(27,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(diaFinFloracion);
  //delay(200);  
  }

  if(X > 90 && X < 150 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir mes
    if (mesFinFloracion == 12){mesFinFloracion = 1;}
    else {mes[mesFinFloracion++];}
     Z=0;
  tft.fillRect(105,160,60,52,WHITE);
  tft.setCursor(107,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinFloracion);
 // delay(200);  
    }
  if(X > 90 && X < 150 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar mes
    if (mesFinFloracion < 1){mesFinFloracion = 12;}
    else {mes[mesFinFloracion--];}
     Z=0;
  tft.fillRect(105,160,60,52,WHITE);
  tft.setCursor(107,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(mesFinFloracion);
 // delay(200);  
  }
  
  if(X > 160 && X < 280 && Y > 145 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // subir año
     anomas1F = anomas1F + 1;
    if (anomas1F > 10){anomas1F = 0;}
   //else {ano[anoInicioCrecimiento++];}
    
      {anoFinFloracion = ano[anomas1F];}
     Z=0;
  tft.fillRect(185,160,120,52,WHITE);
  tft.setCursor(187,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinFloracion);
 // delay(200);  
    }
  if(X > 160 && X < 320 && Y > 200 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE ){ // bajar año
    anomas1F = anomas1F-1;
    if (anomas1F < 0){anomas1F = 11;}
    //else {ano[anoInicioCrecimiento--];}
     else anoFinFloracion = ano[anomas1F];
     Z=0;
  tft.fillRect(185,160,120,52,WHITE);
  tft.setCursor(187,163);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(anoFinFloracion);
 // delay(200);  
  }
  if (X > 280 && X < 320 && Y > 0 && Y < 30 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuFloracion();
  Z=0;
  pulsacion = 15;
  }
  }



void lecturaMenuHorarioFloracion(){
  if (X > 0 && X < 80 && Y > 0 && Y < 50 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaF = horaF + 1; 
    if(horaF == 24){horaF = 0;}
    horaInicioFloracion = hora[horaF];
    Z=0;
 tft.fillRect(80,45,70,70,WHITE);
 tft.setCursor(86,53);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaInicioFloracion);
      
 if(horaInicioFloracion > 11){
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
    //delay(50);
    }
if (X > 0 && X < 80 && Y > 60 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaF= horaF - 1; 
    if(horaF < 0){horaF = 24;}
    horaInicioFloracion = hora[horaF];
    Z=0;
 tft.fillRect(80,45,70,50,WHITE);
 tft.setCursor(86,53);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaInicioFloracion);
      
 if(horaInicioFloracion > 11){
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,94,70,21,WHITE);
 tft.setCursor(95,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
    //delay(50);
    }


if (X > 0 && X < 80 && Y > 130 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaFF = horaFF + 1; 
    if(horaFF == 23){horaFF = 0;}
    horaFinFloracion = hora[horaFF];
    Z=0;
 tft.fillRect(80,145,70,70,WHITE);
 tft.setCursor(86,153);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaFinFloracion);
      
 if(horaFinFloracion > 11){
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
    //delay(50);
    }
if (X > 0 && X < 80 && Y > 180 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
   horaFF = horaFF - 1; 
    if(horaFF < 0){horaFF = 24;}
    horaFinFloracion = hora[horaFF];
    Z=0;
 tft.fillRect(80,145,70,50,WHITE);
 tft.setCursor(86,153);
 tft.setTextColor(BLACK);
 tft.setTextSize(5);
 tft.print(horaFinFloracion);
      
 if(horaFinFloracion > 11){
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(80,194,70,21,WHITE);
 tft.setCursor(95,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
    //delay(50);
    }

if (X > 200 && X < 320 && Y > 35 && Y < 75 && Z > MINPRESSURE && Z < MAXPRESSURE){
  minF = minF + 1;
   if(minF == 6){minF = 0;}
    minutoInicioFloracion = minutos[minF];
    Z= 0;
 tft.fillRect(170,45,70,50, WHITE);
 tft.setCursor(176,53);
 tft.setTextSize(5);
 tft.setTextColor(BLACK);
 tft.print(minutoInicioFloracion);
   
 if(horaInicioFloracion > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
      //delay(50);
}
  if (X > 200 && X < 320 && Y > 76 && Y < 120 && Z > MINPRESSURE && Z < MAXPRESSURE){
   minF = minF - 1;
    if(minF < 1){minF = 6;}
      minutoInicioFloracion = minutos[minF];
      Z=0;
  tft.fillRect(170,45,70,50, WHITE);
  tft.setCursor(176,53);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoInicioFloracion);
  
 if(horaInicioFloracion > 11){
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,94,70,21,WHITE);
 tft.setCursor(185,95);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
     //delay(50);
} 

if (X > 200 && X < 320 && Y > 120 && Y < 170 && Z > MINPRESSURE && Z < MAXPRESSURE){
  minFF = minFF + 1;
   if(minFF == 6){minFF = 0;}
    minutoFinFloracion = minutos[minFF];
    Z= 0;
 tft.fillRect(170,145,70,50, WHITE);
 tft.setCursor(176,153);
 tft.setTextSize(5);
 tft.setTextColor(BLACK);
 tft.print(minutoFinFloracion);
   
 if(horaFinFloracion > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
      //delay(50);
}
  if (X > 200 && X < 320 && Y > 180 && Y < 240 && Z > MINPRESSURE && Z < MAXPRESSURE){
   minFF = minFF - 1;
    if(minFF < 1){minFF = 6;}
      minutoFinFloracion = minutos[minFF];
      Z=0;
  tft.fillRect(170,145,70,50, WHITE);
  tft.setCursor(176,153);
  tft.setTextSize(5);
  tft.setTextColor(BLACK);
  tft.print(minutoFinFloracion);
  
 if(horaFinFloracion > 11){
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("P.M");
    }else{
 tft.fillRect(170,194,70,21,WHITE);
 tft.setCursor(185,195);
 tft.setTextColor(BLACK);
 tft.setTextSize(2);
 tft.print("A.M");
      }
     //delay(50);
} 

  
if (X > 280 && X < 320 && Y > 0 && Y < 30 && Z > MINPRESSURE && Z < MAXPRESSURE){ //escape
  menuFloracion();
  Z=0;
  pulsacion = 15;
  }
  }






void lecturaPanel()                                                  // Realizamos lectura del panel para detectar presion y coordenadas
{
     
    TSPoint p = ts.getPoint(); // Realizamos lectura de las coordenadas

  
    pinMode(XM, OUTPUT); // La librería utiliza estos pines como entrada y salida
    pinMode(YP, OUTPUT); // por lo que es necesario declararlos como salida justo
                         // despues de realizar una lectura de coordenadas.    

  //  X = map(p.y,TS_MAXX  ,TS_MINX, 0, tft.width());
    //Y = map(p.x, TS_MAXY ,TS_MINY, 0, tft.height());
  //  X = map(p.y, TS_LEFT, TS_RT, 0, 320);
   // Y = map(p.x, TS_TOP, TS_BOT, 0, 240);
const int TS_LEFT =110;
const int TS_RT=929;
const int TS_TOP=83;
const int TS_BOT=907;
    X = map(p.y, 83, 907, 0, 320);
    Y = map(p.x, 929, 110, 0, 240);
    Z = p.z;  
}



void lecturaMenuPrincipal (){
  if (X > 1 && X < 160 && Y >1 && Y < 80 &&  Z > MINPRESSURE && Z < MAXPRESSURE){
    pulsacion = 1;
    menuTemperatura();
    Z=0;
  }
  if (X > 161 && X < 320 && Y > 1 && Y < 80 && Z > MINPRESSURE && Z < MAXPRESSURE){
  pulsacion = 4;
  menuHumedadSuelo();
  Z=0;
  }  
  if (X > 0 && X < 160 && Y >98 && Y < 177 && Z > MINPRESSURE && Z < MAXPRESSURE){
  pulsacion = 7;
  menuHumedadAire();
  Z=0;  
  }
  if (X>161 && X < 320 && Y > 98 && Y<177 && Z > MINPRESSURE && Z < MAXPRESSURE){
    pulsacion=10;
    menuLuz();
    Z=0;
    }
}

  





void cicloLuminico(){


tmElements_t inicioC;
inicioC.Minute = minutoInicioCrecimiento;
inicioC.Hour = horaInicioCrecimiento;
inicioC.Day = diaInicioCrecimiento;
inicioC.Month= mesInicioCrecimiento;
inicioC.Year = anoInicioCrecimiento - 1970;
time_t fechaIC = makeTime(inicioC);
//fecha fin CRECIMIENTO
tmElements_t finC;
finC.Minute = minutoFinCrecimiento;
finC.Hour = horaFinCrecimiento;
finC.Day = diaFinCrecimiento;
finC.Month= mesFinCrecimiento;
finC.Year = anoFinCrecimiento - 1970;
time_t fechaFC = makeTime(finC);
//Fecha inicio VEGETACION
tmElements_t inicioV;
inicioV.Minute = minutoFinCrecimiento;
inicioV.Hour = horaFinCrecimiento;
inicioV.Day = diaFinCrecimiento;
inicioV.Month= mesFinCrecimiento;
inicioV.Year = anoFinCrecimiento - 1970;
time_t fechaIV = makeTime(inicioV);
//fecha fin VEGETACION
tmElements_t finV;
finV.Minute = minutoFinVegetacion;
finV.Hour = horaFinVegetacion;
finV.Day = diaFinVegetacion;
finV.Month= mesFinVegetacion;
finV.Year = anoFinVegetacion - 1970;
time_t fechaFV = makeTime(finV);
//fecha inicio FLORACION
tmElements_t inicioF;
inicioF.Minute = minutoFinVegetacion;
inicioF.Hour = horaFinVegetacion;
inicioF.Day = diaFinVegetacion;
inicioF.Month= mesFinVegetacion;
inicioF.Year = anoFinVegetacion - 1970;
time_t fechaIF = makeTime(inicioF);
//fecha fin FLORACION
tmElements_t finF;
finF.Minute = minutoFinFloracion;
finF.Hour = horaFinFloracion;
finF.Day = diaFinFloracion;
finF.Month= mesFinFloracion;
finF.Year = anoFinFloracion - 1970;
time_t fechaFF = makeTime(finF);




  DateTime t = rtc.now();
  uint32_t UX = t.unixtime();
int horasLuzC;
DateTime dt0 (t.year(),t.month(),t.day(),/*horaInicioCrecimiento,minutoInicioCrecimiento*/11,04,t.second());
DateTime dt1 (t.year(),t.month(),t.day(),/*horaFinCrecimiento,minutoFinCrecimiento*/11,05,t.second());
/*DateTime dt3 = dt0 - dt1;
if (dt3 < 0){
  horasLuzC = dt3*-1;
  }else {horasLuzC = dt3}
*/
uint32_t DT0 = dt0;
uint32_t DT1 = dt1;
Serial.print("hora ");
Serial.println(t.hour());
Serial.print("minutos ");
Serial.println(t.minute());
Serial.print("fecha inicio ");
Serial.println(horaInicioCrecimiento,minutoInicioCrecimiento);
Serial.print("fecha fin: ");
Serial.println(horaFinCrecimiento,minutoInicioCrecimiento);
Serial.print("ALARMA 1 ");
Serial.println(rtc.alarmFired(1));
Serial.print("Alarma 2 ");
Serial.println(rtc.alarmFired(2));
Serial.print("SQW: ");
Serial.println(digitalRead(CLOCK_INTERRUPT_PIN)); 
rtc.clearAlarm(1);
rtc.clearAlarm(2);
// INCIO Y FIN DE CICLO DE CRECIMIENTO
if (UX > fechaIC && UX < fechaFC ){
 if(UX > DT0 && UX < DT1){
  pinMode(41,HIGH);
  }
 if(UX > DT1 && UX < DT0){
  pinMode(41,LOW);
  }
} 
// INICIO Y FIN DE CICLO DE VEGETACION
if (UX > fechaIV && UX < fechaFV ){
//1609486200 2021 1 1 16 30 0

  
}      

//INICIO Y FIN DE CICLO DE FLORACION
  if (UX > fechaIF && UX < fechaFF ){
    }


}


void alarmCrecimiento(){
  rtc.setAlarm1((0,0,0,22,15,0),DS3231_A1_Hour);
  if(rtc.alarmFired(1)){
    pinMode(41,HIGH);
    }
  }
void alarmCrecimientoOff(){
  rtc.setAlarm2((0,0,0,22,16,0),DS3231_A2_Hour);
  if(rtc.alarmFired(2)){
    pinMode(41,LOW);
    rtc.clearAlarm(1);
    
    }
  }


void loop() {
  // put your main code here, to run repeatedly:

lecturaPanel();
if (pulsacion == 0){lecturaMenuPrincipal();}
if (pulsacion == 1){lecturaMenuTemperatura();}
if (pulsacion == 2){lecturaMenuTemperaturaMaxima();}
if (pulsacion == 3){lecturaMenuTemperaturaMinima();}
if (pulsacion == 4){lecturaMenuHumedadSuelo();}
if (pulsacion == 5){lecturaMenuHumedadSueloMax();}
if (pulsacion == 6){lecturaMenuHumedadSueloMin();}
if (pulsacion == 7){lecturaMenuHumedadAire();}
if (pulsacion == 8){lecturaMenuHumedadAireMax();}
if (pulsacion == 9){lecturaMenuHumedadAireMin();}
if (pulsacion == 10){lecturaMenuLuz();}
if (pulsacion == 11){lecturaMenuConfiguracion();}
if (pulsacion == 12){lecturaMenuParametros();}
if (pulsacion == 13){lecturaMenuCrecimiento();}
if (pulsacion == 14){lecturaMenuVegetacion();}
if (pulsacion == 15){lecturaMenuFloracion();}
if (pulsacion == 16){lecturaMenuFechaCrecimiento();}
if (pulsacion == 17){lecturaMenuHorarioCrecimiento();}
if (pulsacion == 18){lecturaMenuFechaVegetacion();}
if (pulsacion == 19){lecturaMenuHorarioVegetacion();}
if (pulsacion == 20){lecturaMenuFechaFloracion();}
if (pulsacion == 21){lecturaMenuHorarioFloracion();}
lecturaDHT();
higrometroLectura();
cicloLuminico();

}
void onAlarm() {
    Serial.println("Alarm occured!");
}
