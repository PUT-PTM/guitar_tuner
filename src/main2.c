#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_adc.h"
#include "misc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_spi.h"
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "math.h"
#include "stm32f4xx_i2c.h"
uint16_t ADC_Result;
int main(void)
{
	SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE); // zegar dla portu GPIO z kt�rego wykorzystany zostanie pin jako wej�cie ADC (PA1)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // zegar dla modu�u ADC1

	GPIO_InitTypeDef GPIO_InitStructure;
	//inicjalizacja wej�cia ADC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	// niezale�ny tryb pracy przetwornik�w
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	// zegar g��wny podzielony przez 2
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	// opcja istotna tylko dla trybu multi ADC
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	// czas przerwy pomi�dzy kolejnymi konwersjami
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitTypeDef ADC_InitStructure;
	//ustawienie rozdzielczo�ci przetwornika na maksymaln� (12 bit�w)
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	//wy��czenie trybu skanowania (odczytywa� b�dziemy jedno wej�cie ADC
	//w trybie skanowania automatycznie wykonywana jest konwersja na wielu //wej�ciach/kana�ach)
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	//w��czenie ci�g�ego trybu pracy
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	//wy��czenie zewn�trznego wyzwalania
	//konwersja mo�e by� wyzwalana timerem, stanem wej�cia itd. (szczeg�y w //dokumentacji)
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//warto�� binarna wyniku b�dzie podawana z wyr�wnaniem do prawej
	//funkcja do odczytu stanu przetwornika ADC zwraca warto�� 16-bitow�
	//dla przyk�adu, warto�� 0xFF wyr�wnana w prawo to 0x00FF, w lewo 0x0FF0
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//liczba konwersji r�wna 1, bo 1 kana�
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	// zapisz wype�nion� struktur� do rejestr�w przetwornika numer 1
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_84Cycles);

	ADC_Cmd(ADC1, ENABLE);

	ADC_SoftwareStartConv(ADC1);


	while(1){
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
		ADC_Result = ADC_GetConversionValue(ADC1);
	}
}
