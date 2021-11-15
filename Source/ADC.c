#include "stm32f10x.h"
#include "MyGPIO.h"


void configure_adc_in( char voie){
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // validation horloge ADC1
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // passage de l'horloge ADC1 de 72 � 12MHz (div pas 6)
    ADC1->CR2|= ADC_CR2_ADON; // d�marrage ADC1
    ADC1->SQR1&= ADC_SQR1_L; // fixe le nombre de conversion � 1
    ADC1->SQR3|= voie; // indique la voie � convertir
    ADC1->CR2 |= ADC_CR2_CAL; // d�but de la calibration
    while ((ADC1->CR2 & ADC_CR2_CAL)); // attente de la fin de la calibration
}

int convert_single(){
    ADC1->CR2 |= ADC_CR2_ADON; // lancement de la conversion
    while(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
			ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
    return ADC1->DR & ~((0x0F) << 12); // retour de la conversion avec les bits apr�s les 12 premiers pouss�s � 0 pour pas perturber notre valeur
}

