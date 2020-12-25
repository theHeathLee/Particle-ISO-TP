
<span style="color:red">
⚠️⚠️⚠️STATUS: Just getting started. Do not expect this to work perfectly just yet.⚠️⚠️⚠️
</span>
<br>
<br>
## ISO-TP Library for Particle devices
___


**This project is a rebuilt version of [lishen2 isotp-c](https://github.com/lishen2/isotp-c), to work out of the box with Particle devices. That code was inspired by [openxc isotp-c](https://github.com/openxc/isotp-c), but the code has been completely re-written.**

This is a platform agnostic C++ library that implements the [ISO 15765-2](https://en.wikipedia.org/wiki/ISO_15765-2) (also known as ISO-TP) protocol, which runs over a CAN bus. Quoting Wikipedia:

>ISO 15765-2, or ISO-TP, is an international standard for sending data packets over a CAN-Bus.
>The protocol allows for the transport of messages that exceed the eight byte maximum payload of CAN frames. 
>ISO-TP segments longer messages into multiple frames, adding metadata that allows the interpretation of individual frames and reassembly 
>into a complete message packet by the recipient. It can carry up to 4095 bytes of payload per message packet.

This library doesn't assume anything about the source of the ISO-TP messages or the underlying interface to CAN. It uses dependency injection to give you complete control.

**The current version supports [ISO-15765-2](https://en.wikipedia.org/wiki/ISO_15765-2) single and multiple frame transmition, and works in Full-duplex mode.**

## Example

```C++
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
