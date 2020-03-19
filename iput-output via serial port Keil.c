#include <stdio.h>
#include <REG52.h>
 void putstr (unsigned char *x)
 {
     while (*x)
     {
         SBUF = *x;
         while (!TI)
         TI = 0;
         x++;
     }
 }
 unsigned char * getstr(void)
 {
     unsigned char buf[32];
     unsigned char *pbuf = buf;
     while(1)
     {
         while(!RI)
         RI = 0;
         *pbuf = SBUF;
         if (*pbuf==0x0D)
         {
             *pbuf = '\0';
             break;
         }
         return buf;
     }
     void main(void)
     {
         unsigned char *pdat;
         SCON =0x50;
         TH1=0xFD;
         TMOD |=0x20;
         TR1=1;
         TI=0;
         RI=0;
         while(1)
         {
             pdat=getstr();
             putstr(pdat);
         }
     }