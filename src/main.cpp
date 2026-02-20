#include <Arduino.h>

const int pinLed = 9;
const int poten = A0;
const int boton = 2; // cambios de modo
const int fotoR = A1;
const int indicador = 13;
const int botonCalibrador = 6;

int valorSensor = 0;
int sensorMax = 0;
int sensorMin = 1023;

bool estadoActual;
bool estadoAnterior = HIGH; //porque uso pull-up
int modo = 0;

int brilloActual = 0; //todos los modos trabajan sobre la misma variable

const unsigned long intervalo = 30; //debounce

void setup()
{
    pinMode(pinLed, OUTPUT);
    pinMode(boton, INPUT_PULLUP);
    pinMode(indicador, OUTPUT);
    pinMode(botonCalibrador, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop()
{
    static unsigned long tiempoAnterior = 0;
    unsigned long tiempoActual = millis();
    /*
    CAMBIOS DE MODOS
    */
    estadoActual = digitalRead(boton);

    if (estadoAnterior == HIGH && estadoActual == LOW && (tiempoActual - tiempoAnterior > intervalo)) //Flanco para leer el boton. estadoActual se vuelve LOW al presionar el pulsador por usar pull-up
    {
        modo++;
        if (modo > 2)
        {
            modo = 0;
        }
        tiempoAnterior = tiempoActual; //actualizacion de tiempo

        Serial.print("Cambiado a modo: ");
        Serial.println(modo);
    }
    
    estadoAnterior = estadoActual;



    switch (modo)
    {
    case 0:
        manual();
        break;
    
    case 1:
        automatico();
        break;

    case 2:
    progresivo();
        break;
    }

    analogWrite(pinLed, brilloActual);
}


void automatico()
{
    static unsigned long tiempoAnteriorCalib = 0; 
    unsigned long tiempoActual = millis();
    
    /*
    CALIBRACION DE FOTORRESISTENCIA
    */
    if (digitalRead(botonCalibrador) == LOW && (tiempoActual - tiempoAnteriorCalib) > intervalo)
    {
        calibrar();
    }

    digitalWrite(indicador, LOW);   //apagar el led del arduino una vez calibrado

    valorSensor = analogRead(fotoR);

    /*constain: aunque el ldr puede estar calibrado si valorSensor se pasa del rango (por ruido o mala calibracion)
            el resultado puede ser menor que 0 y mayor que 255 y map NO limita el resultado
            entonces constrain es un limitador de seguridad:
            si el valor < 0  ->  devuelve 0
            si el valor > 255  ->  devuelve 255
            si está dentro del rango  ->  lo deja igual
    */

    int temporal = map(valorSensor, sensorMin, sensorMax, 255, 0);
    temporal = constrain(temporal, 0, 255);
    brilloActual = temporal;
}

void manual()
{
    int potenValue = analogRead(poten);
    brilloActual = map(potenValue, 0, 1023, 0, 255);
}

void calibrar()
{
    digitalWrite(indicador, HIGH);  //prender el led del arduino para saber que estamos calibrando
    valorSensor = analogRead(fotoR);
    
    if (valorSensor > sensorMax)
    {
        sensorMax = valorSensor;
    }

    if (valorSensor < sensorMin)
    {
        sensorMin = valorSensor;
    }
}

void progresivo(){
    static unsigned long ultimoUpdate= 0;
    const unsigned long intervaloProgresivo = 10;
    unsigned long tiempoActual = millis();

    int brilloObjetivo = map(analogRead(poten), 0, 1023, 0, 255);

    if (tiempoActual - ultimoUpdate >= intervaloProgresivo) {
        ultimoUpdate = tiempoActual;

        //cambiar brillo progresivamente
        if (brilloActual < brilloObjetivo) {
            brilloActual++;
        } 
        else if (brilloActual > brilloObjetivo) {
            brilloActual--;
        }
        analogWrite(pinLed, brilloActual);
    }
}