#include "Ultrasonic.h"
//#include <Adafruit_MLX90614.h>
//#include <Wire.h>

Ultrasonic ultrasonic(7);
//Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
    Serial.begin(9600);
}
void loop() {

    long RangeInCentimeters;
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
    Serial.print(RangeInCentimeters);//0~400cm
    Serial.println(" cm");
    //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
    //Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    delay(2000);
}
