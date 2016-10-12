/*
 * WiiChuckDemo -- 
 *
 * 2008 Tod E. Kurt, http://thingm.com/
 *
 */

#include <Wire.h>
#include "nunchuck_funcs.h"
#include <Servo.h>


int loop_cnt=0;

byte accx,accy,accz,zbut,cbut,joyx,joyy;
int ledPin = 13;

Servo eyepan;
Servo eyetilt;
Servo jaw;
void setup()
{
    Serial.begin(19200);


    nunchuck_setpowerpins();
    nunchuck_init(); // send the initilization handshake
    eyepan.attach(D6);
    eyetilt.attach(D5);
    jaw.attach(D3);
    Serial.print("WiiChuckDemo ready\n");
}
// 130 50

void loop()
{
   
    if( loop_cnt > 20 ) { // every 20 msecs get new data
        loop_cnt = 0;
        nunchuck_get_data();

        accx  = nunchuck_accelx(); // ranges from approx 70 - 182
        accy  = nunchuck_accely(); // ranges from approx 65 - 173
        accz  = nunchuck_accelz(); // ranges from approx 65 - 173
        zbut = nunchuck_zbutton();
        cbut = nunchuck_cbutton(); 
        joyx = nunchuck_joyx();
        joyy = nunchuck_joyy();
        if(joyx>160)
          joyx=160;
        if(joyy>160)
          joyy=160;
          
        if(joyx<25)
          joyx=24;
        if(joyy<25)
          joyy=24;  
          
        eyetilt.write(joyx);
        eyepan.write(joyy);  
        jaw.write(zbut?160:20); 
        //Serial.print("accx: "); Serial.print((byte)accx,DEC);
        //Serial.print("\taccy: "); Serial.print((byte)accy,DEC);
        //Serial.print("\taccy: "); Serial.print((byte)accz,DEC);
        //Serial.print("\tzbut: "); Serial.print((byte)zbut,DEC);
        //Serial.print("\tcbut: "); Serial.println((byte)cbut,DEC);
    }
    loop_cnt++;
    delay(1);
}
