
#include "WPILib.h"

/*
#include <KCrsl.h>
#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Servo.h>
#include <EEPROM.h>
#include <RobotOpen.h>
*/

/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1
ROPWM pwm0(0);
ROPWM pwm1(1);
ROPWM pwm2(2);
ROPWM pwm3(3);





void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
 /*RSl setup  values*/
 rsl.setup(0); // chooses a DIO input to use
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // get desired translation and rotation, scaled to [-127..128] (0 neutral)
  float x = usb1.leftX() - 127.0;
  float y = (255.0 - usb1.leftY()) - 127.0;
  float rotate = usb1.rightX() - 127.0;

  // calculate wheel throttles
  float lf = x + y + rotate;
  float rf = x - y + rotate;
  float lr = -x + y + rotate;
  float rr = -x - y + rotate;

  // normalize wheel throttles
  float maximum = max(max(abs(lf), abs(rf)), max(abs(lr), abs(rr)));
  if (maximum > 127.0) {
    lf = (lf / maximum) * 127.0;
    rf = (rf / maximum) * 127.0;
    lr = (lr / maximum) * 127.0;
    rr = (rr / maximum) * 127.0;
  }

  // Set PWMs, shifted back to [0..255]
  pwm0.write(lf + 127);
  pwm1.write(rf + 127);
  pwm2.write(lr + 127);
  pwm3.write(rr + 127);


}


/* This is called while the robot is disabled
 * All outputs are automatically disabled (PWM, Solenoid, Digital Outs)
 */
void disabled() {
  // safety code

}



/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */

 void timedtasks() {
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());

 rsl.update();
}
// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
