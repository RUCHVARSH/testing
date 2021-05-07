#include <SD.h>                      // need to include the SD library

#include <TMRpcm.h>                  // library for audio play back

#include <SPI.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define trigPinL  2

#define echoPinL  3

#define trigPinR  6

#define echoPinR  7

#define Buzzer    5

#define SD_ChipSelectPin 4           // using digital pin 4 for SPI chip select

TMRpcm tmrpcm;   // create an object for use in this sketch

bool flag = false;

void setup()

{

// initialize the LCD

lcd.begin();

lcd.backlight();

pinMode( Buzzer,   OUTPUT );

pinMode( trigPinL, OUTPUT );

pinMode( echoPinL, INPUT  );

pinMode( trigPinR, OUTPUT );

pinMode( echoPinR, INPUT  );

digitalWrite(Buzzer, HIGH);

tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

Serial.begin(9600);

if(!SD.begin(SD_ChipSelectPin))

{

flag = false;

}

else

{

flag = true;

}

lcd.clear();

lcd.setCursor(0, 0);

lcd.print(“Object Detection”);

}

void loop()

{

if(flag == true)

{

long  duration, dis_L, dis_R;

digitalWrite(trigPinL, LOW);

delayMicroseconds(2);

digitalWrite(trigPinL, HIGH);

delayMicroseconds(10);

digitalWrite(trigPinL, LOW);

duration = pulseIn(echoPinL, HIGH);

dis_L = microsecondsToCentimeters(duration);

digitalWrite(trigPinR, LOW);

delayMicroseconds(2);

digitalWrite(trigPinR, HIGH);

delayMicroseconds(10);

digitalWrite(trigPinR, LOW);

duration = pulseIn(echoPinR, HIGH);

dis_R = microsecondsToCentimeters(duration);

Serial.print(dis_L);

Serial.print(“ ”);

Serial.print(dis_R);

Serial.println();

if( dis_L < 20 || dis_R < 20)

{

lcd.setCursor(0, 1);

lcd.print(“CAUTION !!!    “);

digitalWrite(Buzzer, LOW);

delay(800);

digitalWrite(Buzzer, HIGH);

lcd.setCursor(0, 1);

lcd.print(“TOO NEAR”);

}

else if(dis_L >= 20 && dis_L < 30)

{

tmrpcm.play(“10.wav”);

lcd.setCursor(0, 1);

lcd.print(“20cm left      “);

delay(3000);

}

else if(dis_R >= 20 && dis_R < 30)

{

tmrpcm.play(“11.wav”);

lcd.setCursor(0, 1);

lcd.print(“20cm right     “);

delay(3000);

}

else if(dis_L >= 30 && dis_L < 40)

{

tmrpcm.play(“20.wav”);

lcd.setCursor(0, 1);

lcd.print(“30cm left      “);

delay(3000);

}

else if(dis_R >= 30 && dis_R < 40)

{

tmrpcm.play(“21.wav”);

lcd.setCursor(0, 1);

lcd.print(“30cm right     “);

delay(3000);

}

else if(dis_L >= 40 && dis_L < 50)

{

tmrpcm.play(“30.wav”);

lcd.setCursor(0, 1);

lcd.print(“40cm left      “);

delay(3000);

}

else if(dis_R >= 40 && dis_R < 50)

{

tmrpcm.play(“31.wav”);

lcd.setCursor(0, 1);

lcd.print(“40cm right     “);

delay(3000);

}

else if(dis_L >= 50 && dis_L < 60)

{

tmrpcm.play(“40.wav”);

lcd.setCursor(0, 1);

lcd.print(“50cm left      “);

delay(3000);

}

else if(dis_R >= 50 && dis_R < 60)

{

tmrpcm.play(“41.wav”);

lcd.setCursor(0, 1);

lcd.print(“50cm right     “);

delay(3000);

}

else if(dis_L >= 60 && dis_L < 70)

{

tmrpcm.play(“50.wav”);

lcd.setCursor(0, 1);

lcd.print(“60cm left      “);

delay(3000);

}

else if(dis_R >= 60 && dis_R < 70)

{

tmrpcm.play(“51.wav”);

lcd.setCursor(0, 1);

lcd.print(“60cm right     “);

delay(3000);

}

else if(dis_L >= 70 && dis_L < 80)

{

tmrpcm.play(“60.wav”);

lcd.setCursor(0, 1);

lcd.print(“70cm left      “);

delay(3000);

}

else if(dis_R >= 70 && dis_R < 80)

{

tmrpcm.play(“61.wav”);

lcd.setCursor(0, 1);

lcd.print(“70cm right     “);

delay(3000);

}

else if(dis_L >= 80 && dis_L < 85)

{

tmrpcm.play(“70.wav”);

lcd.setCursor(0, 1);

lcd.print(“80cm left      “);

delay(3000);

}

else if(dis_R >= 80 && dis_R < 85)

{

tmrpcm.play(“71.wav”);

lcd.setCursor(0, 1);

lcd.print(“80cm right     “);

delay(3000);

}

else

{

lcd.setCursor(0, 1);

lcd.print(“No object near “);

}

}

else

{

lcd.setCursor(0, 0);

lcd.print(“Unsuccess init  “);

lcd.setCursor(0, 1);

lcd.print(“Please check SD “);

}

}

long microseconds To Centimeters(long microseconds)

{

return microseconds / 29 / 2;

}
