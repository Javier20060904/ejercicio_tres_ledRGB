#include "msp.h"

#define RETARDO (100000)
/************************************************
 DECLARACION DE APUNTADORES PARA ACCESO A MEMORIA
 ************************************************/
uint8_t *p2_in  = (uint8_t*)0x040004c01;
uint8_t *p2_sel0 = (uint8_t*)0x040004c0B;
uint8_t *p2_sel1 = (uint8_t*)0x040004c0d;
uint8_t *p2_out = (uint8_t*)0x040004c03;
uint8_t *p2_dir = (uint8_t*)0x040004c05;
uint8_t *p2_ren = (uint8_t*)0x040004c07;

//Codigo de colores
/*
 01 - Rojo
 10 - Verde
 11 - Amarillo
 */

void main(void){
    uint32_t i; //Para el ciclo for
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    *p2_sel0 &= ~0x0F;
    *p2_sel1 &= ~0x0F; //P2 en GPIO

    *p2_dir ^= 0x03; //Se habilita dos bits de entradas (G,R)
    *p2_ren |= 0x08; //Se habilita el pullup en P2.4

    *p2_out ^= 0x03; //Se asigna un 2 (Verde)
    while(1){
        if (*p2_out == 0x03)
            *p2_out ^= 0x01;
        else
            *p2_out ^= ((*p2_out) + 1);

        for(i=RETARDO ; i>0 ; i--);
    }
}

