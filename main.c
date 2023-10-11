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
    uint32_t i; //Variable para el ciclo for

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    *p2_sel0 &= ~0x0F;
    *p2_sel1 &= ~0x0F;  //P2 configurado en GPIO

    *p2_dir |= 0x03;    //Se habilitan dos bits de entrada (G,R / P2.1,P2.0)
    *p2_dir &= ~0x10;   //Habilita P2.4 como entrada
    *p2_ren |= 0x10;    //Se habilita la resistencia de pull-up/down en P2.4

    *p2_out &= ~0xFF;   //Limpiar salida
    *p2_out |= 0x02;    //Se selecciona pull-down para P2.4 y se asigna Verde a las salidas

    while(1){
        if (*p2_in & 0x10){         //Si se pulsa el botón
            if (*p2_out == 0x03)    //Y el color es Amarillo (3)
                *p2_out ^= 0x01;    //Se cambia a Rojo (1)
            else                                //Si el color NO es Amarillo (3).
                *p2_out ^= (*p2_out + 0x01);    //Se cambia de color (Rojo o Verde)
        }
        for(i=RETARDO ; i>0 ; i--);                 //for para crear delay
    }
}
