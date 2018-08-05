
//////////////////   LCD   ///////////////////////
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  
    
    return btnNONE;                // when all others fail, return this.
}


// value for storing
int val = 0;
int output_value ;

// set all sensors PIN ID
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;

// background light
int LuzFondo = 10; 

// declare sensors values
int sensor1_value = 0;
int sensor2_value = 0;
int sensor3_value = 0;
int sensor4_value = 0;
int sensor5_value = 0;
int sensor6_value = 0;

// set relays
int relay1 = 3;
int relay2 = 4;
int relay3 = 5;
int relay4 = 6;

// set "water pump" relay
int pump = 2;

char myData[1];



  
void setup() {
  
  // background light
  pinMode(LuzFondo, OUTPUT);
  
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);  

  // LCD
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  
  //LCD first line

  lcd.setCursor(0, 0);
  lcd.print("M"); 
   lcd.setCursor(2, 0);
  lcd.print("EN"); 
  lcd.setCursor(5, 0);
  lcd.print("H%");
  lcd.setCursor(8, 0);
  lcd.print("R%");
  lcd.setCursor(11, 0);
  lcd.print("Tm");
  lcd.setCursor(14, 0);
  lcd.print("Ch");
  
  // background light
  // digitalWrite(LuzFondo, LOW);
  // delay(1000); 
  digitalWrite(LuzFondo, HIGH);
  delay(1000);

  // read the value from the moisture sensors
  sensor1_value = analogRead(sensor1);
  delay(1000);

  //declare sensros as output
  pinMode(sensor1, OUTPUT);
  pinMode(sensor2, OUTPUT);
  pinMode(sensor3, OUTPUT);
  pinMode(sensor4, OUTPUT);
  pinMode(sensor5, OUTPUT);
  pinMode(sensor6, OUTPUT);
  
  // declare relay as output
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  // declare pump as output
  pinMode(pump, OUTPUT); 
  }





  //////////////// CREATE 4 LOOPS (SEPARTED MODULES)  ////////////////
  // void loop(){ 
  //  moduleloop1();
  //  moduleloop2();
  //  moduleloop3();
  //  moduleloop4();
  // }

  
  
  void loop() {
 
 //////////////// MODULE 1  //////////////// 

 //////////////// PRINT MODULE NUMBER //////////////// 
  
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("1");

  //////////////// PRINT TRD TO WATER ////////////////   
  lcd.setCursor(2, 1);
  lcd.print("SI");
 
  //////////////// PRINT TRD ///////////////   
  output_value= analogRead(sensor1); 
  output_value= 300;
  output_value = map(output_value,0,550,0,99); 
  lcd.setCursor(0, 1);
  lcd.setCursor(5, 1);
  lcd.print(output_value);

  //////////////// PRINT TRD TO WATER ////////////////   
  lcd.setCursor(8, 1);
  lcd.print("NU");

  //////////////// PRINT TIME TO WATER//////////////// 
  lcd.setCursor(11, 1);
  lcd.print("NU");

  //////////////// PRINT CICLE TIME //////////////// 
  lcd.setCursor(14, 1);
  lcd.print("NU");

  
 ////////////////  VALVE & PUMP ON ////////////////
 // check which plant need water and open the switch for that specific plant
 // dry soil = 0-300 // humid soil = 300-500 // water = 500-750
 
 if(sensor1_value<=300){
  digitalWrite(relay1, HIGH); // VALVE 1
  digitalWrite(pump, HIGH); // WATER PUMP
 }

 // 6000 milliseconds = 1 minute // 3000 milliseconds = 30 sec.
 delay(6000);
  
 //////////////// VALVES & PUMP OFF  ////////////////
 digitalWrite(relay1, LOW); // VALVE 1
 digitalWrite(pump, LOW); // PUMP
 
 //////////////// SENSORS OFF  ////////////////
 digitalWrite(sensor1, LOW); // SENSOR 1

 
 ////////////////  LOOPING TIME  ////////////////
 // 30000 milliseconds = 30 sec.
 // 1080000 milliseconds = 3 hrs.
 delay(30000);

}



