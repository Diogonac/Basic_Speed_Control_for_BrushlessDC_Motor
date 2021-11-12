#include "mbed.h"

// I/O to PWM signals 
PwmOut IN_1(PA_8);
PwmOut IN_2(PA_9);
PwmOut IN_3(PA_10);

// I/O to enable pins of H-Bridge
DigitalOut EN_1(PC_10); 
DigitalOut EN_2(PC_11);
DigitalOut EN_3(PC_12);

// Potentiometer to speed control
AnalogIn POT(PB_1); 

// Interrupt pin for user turn on the motor  
InterruptIn BT(PC_13); 

// Variable to get phases delay 
float dt; 

// Function to logic enable 
void toggle(void);
bool flag;

int main() {

  // Initial conditions
  IN_1.period_ms(1); 
  IN_2.period_ms(1); // PWM period = 1 ms
  IN_3.period_ms(1); 

  IN_1.write(0); 
  IN_2.write(0); // PWM = 0% of duty cicle
  IN_3.write(0);

  EN_1 = 2; // arm 1 --> phase W
  EN_2 = 2; // arm 2 --> phase V
  EN_3 = 2; // arm 3 --> phase U

  flag = false;

  BT.fall(&toggle);

  while (true) {

    if (flag == true) {

      /* Potentiometer value into a calibrate value of phase delay */
      dt = -0.0185 * POT.read() + 0.02  ; 

      /* Step 1 */
      IN_1 = 0; // phase W
      IN_2 = 0; // phase V
      IN_3 = 1; // phase U

      EN_1 = 0; // arm 1 --> phase W
      EN_2 = 1; // arm 2 --> phase V
      EN_3 = 1; // arm 3 --> phase U
      wait(dt);

      /* Step 2 */
      IN_1 = 0; // phase W
      IN_2 = 0; // phase V
      IN_3 = 1; // phase U

      EN_1 = 1; // arm 1 --> phase W
      EN_2 = 0; // arm 2 --> phase V
      EN_3 = 1; // arm 3 --> phase U
      wait(dt);

      /* Step 3 */
      IN_1 = 0; // phase W
      IN_2 = 1; // phase V
      IN_3 = 0; // phase U

      EN_1 = 1; // arm 1 --> phase W
      EN_2 = 1; // arm 2 --> phase V
      EN_3 = 0; // arm 3 --> phase U
      wait(dt);

      /* Step 4 */
      IN_1 = 0; // phase W
      IN_2 = 1; // phase V
      IN_3 = 0; // phase U

      EN_1 = 0; // arm 1 --> phase W
      EN_2 = 1; // arm 2 --> phase V
      EN_3 = 1; // arm 3 --> phase U
      wait(dt);

      /* Step 5 */
      IN_1 = 1; // phase W
      IN_2 = 0; // phase V
      IN_3 = 0; // phase U

      EN_1 = 1; // arm 1 --> phase W
      EN_2 = 0; // arm 2 --> phase V
      EN_3 = 1; // arm 3 --> phase U
      wait(dt);

      /* Step 6 */
      IN_1 = 1; // phase W
      IN_2 = 0; // phase V
      IN_3 = 0; // phase U

      EN_1 = 1; // arm 1 --> phase W
      EN_2 = 1; // arm 2 --> phase V
      EN_3 = 0; // arm 3 --> phase U
      wait(dt);

    } else {

      IN_1 = 0; // phase W
      IN_2 = 0; // phase V
      IN_3 = 0; // phase U

      EN_1 = 2; // arm 1 --> phase W
      EN_2 = 2; // arm 2 --> phase V
      EN_3 = 2; // arm 3 --> phase U
    }
  }
}

void toggle(void) { flag = !flag; }
