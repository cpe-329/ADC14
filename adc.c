/*
* adc.c
* 
* Danica Fujiwara & Spencer Shaw
*
* CPE 329-17/18 Spring 2019
*
*/

static unsigned int adc_value = 0;

void store_adc(unsigned int val){
    adc_value = val;
}

unsigned int get_adc(){
    return adc_value;
}
