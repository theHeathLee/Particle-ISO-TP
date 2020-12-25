# Particle-ISO-TP
ISO-TP Library for Particle devices


This project is a rebuilt version of [lishen2 isotp-c](https://github.com/lishen2/isotp-c), to work out of the box with Particle devices. That code was inspired by [openxc isotp-c](https://github.com/openxc/isotp-c), but the code has been completely re-written.


## Example

```C
#include "../lib/Particle-ISO-TP/src/isotp.h"

static IsoTpLink g_link;
#define ISOTP_BUFSIZE 100
static uint8_t g_isotpRecvBuf[ISOTP_BUFSIZE];
static uint8_t g_isotpSendBuf[ISOTP_BUFSIZE];

void setup() {

  can.begin(250000); // initialize can at 250 kbs 
  Serial.begin(9600); //usb debugging

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

canSendIsoTP();
delay(5000);

}

void canSendIsoTP()
{
  isotp_init_link(&g_link, 0x700,
						g_isotpSendBuf, sizeof(g_isotpSendBuf), 
						g_isotpRecvBuf, sizeof(g_isotpRecvBuf));
  /*create a message array to send that is 10 bytes long, 2 bigger than a maximum can frame size*/
  uint8_t txData[] = {0x02,0x01,0x00,0x55,0x55,0x55,0x55,0x55,0x66,0x77};
  /*make a pointer for the above array*/
  uint8_t *txDataPtr = txData;
  //send via iso-tp
  isotp_send(&g_link , txDataPtr, sizeof(txData));
}
```