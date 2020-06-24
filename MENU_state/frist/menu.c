uint8_t keyvalue=0;
uint8_t Tableindex = 0;
void (*operation)();

typedef struct Table
{
	uint8_t status;
	uint8_t keydown;
	uint8_t keyup;
	uint8_t keyenter;
	uint8_t keyesc;
	void (*operate)();
}TABLE;


const TABLE TAB[]={
	{0,0,0,1,0,(*Mainmenu)},
	{1,2,3,4,0,(*Firstmenu1)},
	{2,3,1,5,0,(*Firstmenu2)},
	{3,1,2,7,0,(*Firstmenu3)},
	{4,4,4,10,1,(*Secondmenu1_1)},
	{5,6,6,10,2,(*Secondmenu2_1)},
	{6,5,5,10,2,(*Secondmenu2_2)},
	{7,8,9,10,3,(*Secondmenu3_1)},
	{8,9,7,10,3,(*Secondmenu3_2)},
	{9,7,8,10,3,(*Secondmenu3_3)},
	{10,10,10,10,4,(*counter)},
	{11,10,10,10,5,(*counter)},
	{12,10,10,10,5,(*counter)},
	{13,10,10,10,6,(*counter)},
	{14,10,10,10,6,(*counter)},
	{15,10,10,10,6,(*counter)},
};





//while中存放的
	Key_Scan();
	if(keyvalue !=0)
	{
	switch(keyvalue)
		{ 
			case 1:
			Tableindex=TAB[Tableindex].keydown;  break;  //向上翻
			case 2:
			Tableindex=TAB[Tableindex].keyup; break;   //向下翻
			case 3:
			Tableindex=TAB[Tableindex].keyenter; break;   //确认
			case 4:
			Tableindex=TAB[Tableindex].keyesc; break;
		default:break;				
	}	   
	LCDClear();    
	}
	operation=TAB[Tableindex].operate;
	(*operation)();//执行当前操作函数