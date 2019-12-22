#include <SoftwareSerial.h>

//software serial
SoftwareSerial midiSerial(3, 2); 
volatile int key = 0;
static int k = 24;
#define DEBUG 

void IRAM_ATTR isr18()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200)
  {
    key = 18;
  }
  last_interrupt_time = interrupt_time;

}

void IRAM_ATTR isr19()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200)
  {
    key = 19;
  }
  last_interrupt_time = interrupt_time;
}

void IRAM_ATTR isr23()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200)
  {
    key = 23;
  }
  last_interrupt_time = interrupt_time;
}

void IRAM_ATTR isr27()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 1000)
  {
    key = 27;
  }
  last_interrupt_time = interrupt_time;
}

void IRAM_ATTR isr25()
{ static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 1000)
  {
    key = 25;
  }
  last_interrupt_time = interrupt_time;
}

void IRAM_ATTR isr26()
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200)
  {
    key = 26;
  }

  last_interrupt_time = interrupt_time;
}

void setup ()
{
  Serial.begin(9600);
  midiSerial.begin(31250);

  pinMode(18, INPUT_PULLDOWN);
  pinMode(19, INPUT_PULLDOWN);
  pinMode(23, INPUT_PULLDOWN);
  pinMode(27, INPUT_PULLDOWN);
  pinMode(25, INPUT_PULLDOWN);
  pinMode(26, INPUT_PULLDOWN);

  attachInterrupt(18, isr18, HIGH);
  attachInterrupt(19, isr19, HIGH);
  attachInterrupt(23, isr23, HIGH);
  attachInterrupt(27, isr27, HIGH);
  attachInterrupt(25, isr25, HIGH);
  attachInterrupt(26, isr26, HIGH);

}
// 18 26 19 23 27 25
void loop()
{

  while (1)
  {
    if (key > 0)
    {
     
#ifdef DEBUG
      Serial.println(key);
#endif
      switch (key) {
        case 23:
          midiCC(176, 69, 0);
          break;
        case 19:
          midiCC(176, 69, 1);
          break;
        case 26:
          midiCC(176, 69, 2);
          break;
        case 18:
          midiCC(176, 69, 3);
          break;
        case 27:
          k--;
          midiPC(192, k);
          break;
        case 25:
          k ++;
          midiPC(192, k);
          break;

      }
 
      key = 0;
    }
  }
}


void midiPC(byte cmd, byte data1)
{

  midiSerial.write(cmd);
  midiSerial.write(data1);

#ifdef DEBUG
  Serial.print("cmd: ");
  Serial.print(cmd);
  Serial.print(", data1: ");
  Serial.println(data1);
#endif
  delay (500);
}


void midiCC(byte cmd, byte data1, byte data2)
{
  midiSerial.write(cmd);
  midiSerial.write(data1);
  midiSerial.write(data2);

#ifdef DEBUG
  Serial.print("cmd: ");
  Serial.print(cmd);
  Serial.print(", data1: ");
  Serial.print(data1);
  Serial.print(", data2: ");
  Serial.println(data2);
#endif
  delay (500);
}
