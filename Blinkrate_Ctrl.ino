#include "Blinkrate_Ctrl.h"

static int BlinkRate = 500;
static const uint8_t buf_len = 20;
static uint8_t buffer[buf_len], index = 0;

// Our task: blink an LED
void toggleLED(void *parameter) {
  while(1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(BlinkRate/portTICK_PERIOD_MS); // tick period (can be scaled)
    digitalWrite(led_pin, LOW);
    vTaskDelay(BlinkRate/portTICK_PERIOD_MS); // Both lines do delay for 500ms
  }
}

void BlinkRateCtrl(void *parameter) {
  for (;;)
  {
    while(Serial.available()>0)
    {
      char c = Serial.read();
      if(c =='\n')
      {
        BlinkRate = atoi(buffer);
        Serial.println(BlinkRate);
        memset(buffer,0,buf_len);  // set the block of memory to zero
        index = 0;
      }
      else if (index < buf_len-1)
      {
        buffer[index] = c;
        index ++;
      }
    }
    //vTaskDelay(1);
  }
}

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  memset(buffer,0,buf_len);  // set the block of memory to zero
  Serial.begin(9600);
  while(!Serial){
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  xTaskCreate(
    toggleLED,  // Function to be called
    "Toggle LED",  // Name of task for humans
    128,  // Stack size
    &BlinkRate,  // Parameter to pass to the task
    2, // Task priority ( 0~24, 0 is the lowest priority)
    NULL  // Task handler
  );  // More arguments like core number in other MCs

   xTaskCreate(
    BlinkRateCtrl
    ,  "Serial"
    ,  128  // Stack size
    ,  NULL //Parameters passed to the task function
    ,  1  // Priority
    ,  NULL);  //Task handle
}

// the loop function runs over and over again forever
void loop() 
{

}

