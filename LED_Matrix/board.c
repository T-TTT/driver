#include "board.h"

uint8_t Key_scan(void)
{
		uint8_t keyyy = 0;
		hang_1_0;
		hang_2_1;
		hang_3_1;
		hang_4_1;
		if(lie_1==0)		keyyy = 1;	
		if(lie_2==0)		keyyy = 2;		
		if(lie_3==0)		keyyy = 3;
		if(lie_4==0)		keyyy = 4;
		
		hang_1_1;
		hang_2_0;
		hang_3_1;
		hang_4_1;
		if(lie_1==0)		keyyy = 5;	
		if(lie_2==0)		keyyy = 6;		
		if(lie_3==0)		keyyy = 7;
		if(lie_4==0)		keyyy = 8;
		
		hang_1_1;
		hang_2_1;
		hang_3_0;
		hang_4_1;
		if(lie_1==0)		keyyy = 9;	
		if(lie_2==0)		keyyy = 10;		
		if(lie_3==0)		keyyy = 11;
		if(lie_4==0)		keyyy = 12;	

		
		hang_1_1;
		hang_2_1;
		hang_3_1;
		hang_4_0;
		if(lie_1==0)		keyyy = 13;	
		if(lie_2==0)		keyyy = 14;		
		if(lie_3==0)		keyyy = 15;
		if(lie_4==0)		keyyy = 16; 
		
		
		return keyyy;

}
