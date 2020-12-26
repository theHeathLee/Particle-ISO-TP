/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/workspace/Particle-ISO-TP/example/src/example.ino"
/*
 * Project example
 * Description: Shows how to use ISO-TP library
 * Author: Heath Lee
 * Date: 25.12.2020
 */
#include "../Particle-ISO-TP/src/isotp.h"

void setup();
void loop();
void canSendIsoTP();
#line 9 "c:/workspace/Particle-ISO-TP/example/src/example.ino"
static IsoTpLink g_link;
#define ISOTP_BUFSIZE 100
static uint8_t g_isotpRecvBuf[ISOTP_BUFSIZE];
static uint8_t g_isotpSendBuf[ISOTP_BUFSIZE];

void setup() {
  // Put initialization like pinMode and begin functions here.

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

canSendIsoTP();
delay(5000);

}

void canSendIsoTP()
{
  isotp_init_link(&g_link, 0x703,
						g_isotpSendBuf, sizeof(g_isotpSendBuf), 
						g_isotpRecvBuf, sizeof(g_isotpRecvBuf));
  uint8_t txData[] = {0x02,0x01,0x00,0x55,0x55,0x55,0x55,0x55,0x66,0x77};
  uint8_t *txDataPtr = txData;
  //send via iso-tp
  isotp_send(&g_link , txDataPtr, sizeof(txData));
}