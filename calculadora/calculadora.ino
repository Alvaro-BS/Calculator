/*
 Code of the arduino calculator.  
 Version: 1.0

  This code convert the Arduino Uno in a simple calculator  which can add, subtract, multiply and divide 
  two different numbers.

 made by: Álvaro Borges Suárez
 github: https://github.com/Alvaro-BS 
 */


//libraries
#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 19, en = 18, d4 = 17, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'=', '0', '/', '.'}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 11, 12, 13}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//variables
String numero = ""; //actual number
char operacion = '+'; //operation
float numero1, numero2; //number 1 and 2 of the operation
float sol; //solucion
bool solucion = HIGH; //boolean variable, LOW the calculator is bloked, HIGH the calculator is no bloked  
bool operacionpuesta = LOW; //boolean variable, mean if the operation is already put

void setup() {
  //initialize display aand serial comunicacion
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  
  //get a key for the keypad
  char teclapulsada = customKeypad.getKey();

  //if a key is pressed
  if (teclapulsada) {

    //if the key is an operacion
    if (teclapulsada == '+' || teclapulsada == '-' || teclapulsada == '*' || teclapulsada == '/') {
      //if the calculator is not bloked, and the operation hasn't been put yet
      if (solucion && !operacionpuesta) {
        operacionpuesta = HIGH; 
        operacion = teclapulsada;  
        numero1 = numero.toFloat(); //convert the actual number in a float and store it in "numero1"
        numero = "";
        //print the operation in the lcd and serial monitor
        lcd.print(operacion);
        Serial.print(" ");
        Serial.print(operacion);
        Serial.print(" ");
      }
    
    }

    //if the key is the equal symbol
    else if (teclapulsada == '=' ) {
      
      if (solucion) {
        //if the calculator is not bloked, block.
        solucion = LOW;
        operacionpuesta = LOW;
        numero2 = numero.toFloat(); //convert the actual number in a float and store it in "numero2"
        numero = "";
        sol = operaciones( numero1, numero2, operacion); //calculate the result
        //reset the variables to the next operation
        numero2 = 0;
        numero1 = 0;
        operacion = '+';
        //show the results in the lcd and serial monitor
        lcd.setCursor(0, 1);
        lcd.print("=");
        lcd.print(sol);
        Serial.print(" = ");
        Serial.println(sol);
      }
      else {
        //if the calculator is bloked, unblock and clear the lcd display
        solucion = HIGH;
        lcd.clear();
      }
    }

    //is the key is a number
    else {
      if (solucion) {
        //add the digit to the actual number
        numero += teclapulsada;
        //print the new character in the lcd and in the serial monitor
        lcd.print(teclapulsada); 
        Serial.print(teclapulsada);
      }
    }
  }
}

//function, given two numbers an operacion, calculate the result
float operaciones(float a, float b, char operacion) {
  switch (operacion) {
    case '+':
      sol = a + b;
      break;
    case '-':
      sol = a - b;
      break;
    case '*':
      sol = a * b;
      break;
    case '/':
      sol = (float)a / (float)b;
      break;
  }
  return sol;
}
