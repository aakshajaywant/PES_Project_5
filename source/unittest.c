/******************************************************************************
 *  					PES PROJECT 5
 *   AAKSHA JAYWANT (AAJA1276) & RUCHA BORWANKAR (RUBO1268)
 * 				Cross Platform IDE: MCUXpresso IDE v11
 * 					Cross-Compiler: ARM GCC
 * 						unittest.c
 ********************************************************************************/
 /**************References******************************************************
http://cache.freescale.com/files/32bit/doc/quick_ref_guide/KLQRUG.pdf
http://cunit.sourceforge.net/screenshots.html
http://www.ucunit.org/
*********************************************************************************/
#include <unittest.h>

ring_buffer *buffer;
uint8_t *p;


uint8_t init_uctest(void)
{

	p = (ring_buffer*)malloc(sizeof(ring_buffer));
	uint8_t test=buff_initialize(p,8);
	UCUNIT_CheckIsNotNull(p);
	UCUNIT_CheckIsEqual(test,6);
	return 0;
}

uint8_t uctest_fill(){
	uint8_t test=buff_add_item(p,5);
	UCUNIT_CheckIsEqual(test,12);
	putstr("\n \r SUCCESSFUL ADDITION TO BUFFER");
	return 0;

}
uint8_t uctest_clear(void)
{
	free(p);
	putstr("\n \r CLEAR UCUNIT TEST BUFFER \n \r");
	return 0;
}


uint8_t uctest_overfill(){
	uint8_t test=buff_check_full(p);
	UCUNIT_CheckIsEqual(test,2);
	return 0;
}

uint8_t uctest_empty(){
	uint8_t test=buff_check_empty(p);
	UCUNIT_CheckIsEqual(test,4);
}

uint8_t uctest_resize(){
	uint8_t test=buff_resize(p);
	UCUNIT_CheckIsEqual(test,17);
	return 0;
}

void unit_test(void)
{

	UCUNIT_Init();
	init_uctest();
	uctest_fill();
	uctest_overfill();
	uctest_empty();
	uctest_resize();
	UCUNIT_WriteSummary();
	UCUNIT_TestcaseEnd();
	uctest_clear();

}


