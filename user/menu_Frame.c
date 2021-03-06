#include "menu_frame.h"
#include "ddl.h"
#include "lcd_drive.h"
#include "user_sever.h"
#include "user_flash.h"
#include "misc.h"
#include "uart_sever.h"
#include "lcd12864.h"
static void WillBlockBack_Frame(int data);
static void Sitchange_Frame(int data);
static void BlockCheck_Frame(int data);
static void Version_Frame(int data);
void Resetset_Frame(int data);
static void Unitset_Frame(int data);
static void MinHightset_Frame(int data);
static void MaxHightset_Frame(int data);
static void CheckBlence_Frame(int data);
static void AutoBlence_Frame(int data);
static void KnockGoDown_Frame(int data);
static void BlockBack_Frame(int data);

Focus_Srtuct_Typdef Menu_Frame_Foucus;
const char * Menufont[]=
{
	"坐站交替",
	"将阻自检",
	"将阻回退",
	"遇阻回退",
	"敲击升降",
	"智能调平",
	"调平自检",
	"最高限位",
	"最低限位",
	"单位切换",
	"自动复位",
	"软件信息",
	"返回"
};
extern uint8_t Back_To;
void Menu_Frame_Init(void)
{	
	Menu_Frame_Foucus.Now_Focus=0;
	Menu_Frame_Foucus.Max_Focus_Num=12;
}
extern uint8_t RunTo_Slect;
extern const char Page_ARROW_UP[];
extern const char Page_ARROW_DOWN[];
void Menu_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
				  Set_Focus(&Menu_Frame_Foucus);
					GetLang(&Menu_Frame_Foucus,Menufont);
					GRAM_ShowString(MenuX,MenuY,Menu_Frame_Foucus.Focus_Data[Menu_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					GRAM_ShowLattice(17,17,16,6,(const uint8_t *)Page_ARROW_UP,1);
					GRAM_ShowLattice(17,57,16,6,(const uint8_t *)Page_ARROW_DOWN,1);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Main_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				ClearFrame();
				GRAM_ShowLattice(17,17,16,6,(const uint8_t *)Page_ARROW_UP,1);
				GRAM_ShowLattice(17,57,16,6,(const uint8_t *)Page_ARROW_DOWN,1);
				Menu_Frame_Foucus.Now_Focus--;
				if(Menu_Frame_Foucus.Now_Focus<0)
				{
					Menu_Frame_Foucus.Now_Focus=12;
				}
        GRAM_ShowString(MenuX,MenuY,Menu_Frame_Foucus.Focus_Data[Menu_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				ClearFrame();
				GRAM_ShowLattice(17,17,16,6,(const uint8_t *)Page_ARROW_UP,1);
				GRAM_ShowLattice(17,57,16,6,(const uint8_t *)Page_ARROW_DOWN,1);
				Menu_Frame_Foucus.Now_Focus++;
				if(Menu_Frame_Foucus.Now_Focus>Menu_Frame_Foucus.Max_Focus_Num)
				{
					Menu_Frame_Foucus.Now_Focus=0;
				}
        GRAM_ShowString(MenuX,MenuY,Menu_Frame_Foucus.Focus_Data[Menu_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
				break;
			case WM_DWONLONG:
			case WM_UPLONG:
				Lcd_Write_Time(REAL_T,0,10);//5s
				Lcd_Write_Time(READ_BK,0,0);//5s
				Creat_Frame(Run_Frame);
				break;
			case WM_1:
			case WM_2:
			case WM_3:
			case WM_4:
				RunTo_Slect=data-3;
				if(Para_read((enum PARA_ENUM)data)==0)break;//如果没设置不跳转
				Lcd_Write_Time(REAL_T,0,10);//5s
				Lcd_Write_Time(READ_BK,0,0);//5s
				Creat_Frame(RunisSet_Frame);
				break;
			case WM_M:
				Lcd_Write_Time(REAL_T,0,10);//5s
				Lcd_Write_Time(READ_BK,0,0);//5s
				switch(Menu_Frame_Foucus.Now_Focus)
				{
					case 0:
						Creat_Frame(Sitchange_Frame);
						break;
					case 1:
						Creat_Frame(BlockCheck_Frame);
						break;
					case 2:
						Creat_Frame(WillBlockBack_Frame);
						break;
					case 3:
						Creat_Frame(BlockBack_Frame);
						break;
					case 4:
						Creat_Frame(KnockGoDown_Frame);
						break;
					case 5:
						Creat_Frame(AutoBlence_Frame);
						break;
					case 6:
						Creat_Frame(CheckBlence_Frame);
						break;
					case 7:
						Creat_Frame(MaxHightset_Frame);
						break;
					case 8:
						Creat_Frame(MinHightset_Frame);
						break;
					case 9:
						Creat_Frame(Unitset_Frame);
						break;
					case 10:
						Creat_Frame(Resetset_Frame);
						break;
					case 11:
						Creat_Frame(Version_Frame);
						break;
					case 12:
						Creat_Frame(Main_Frame);
						break;
					default:
						break;
				}
				break;
				
    }
}

Focus_Srtuct_Typdef Sitchage_Frame_Foucus;

const char * Sitchagefont[]=
{
	"45分钟",
	"1小时",
	"2小时",
	"关闭",
	"返回",
};
const uint16_t RemindList[5]={45,60,120,0,9999};
extern const char Page_SETOK[];
void Sitchage_Frame_Init(void)
{	
	Sitchage_Frame_Foucus.Now_Focus=0;
	Sitchage_Frame_Foucus.Max_Focus_Num=4;
}

static void Sitchange_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					Sitchage_Frame_Init();
				  Set_Focus(&Sitchage_Frame_Foucus);
					GetLang(&Sitchage_Frame_Foucus,Sitchagefont);
					GRAM_ShowString(MenuX,MenuY,Sitchage_Frame_Foucus.Focus_Data[Sitchage_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					if(Para_read(TIME_SETREMINDER)==RemindList[Sitchage_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
					Lcd_Write_Time(READ_BK,1,3);//5s
					Decrease_Focus(&Sitchage_Frame_Foucus);
					if(Para_read(TIME_SETREMINDER)==RemindList[Sitchage_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					break;
			case WM_DOWN:
					Lcd_Write_Time(READ_BK,1,3);//5s
					Increase_Focus(&Sitchage_Frame_Foucus);
					if(Para_read(TIME_SETREMINDER)==RemindList[Sitchage_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					break;
			case WM_M:
					switch(Sitchage_Frame_Foucus.Now_Focus)
					{
						case 0:
						case 1:
						case 2:
						case 3:
							Para_write(TIME_SETREMINDER,RemindList[Sitchage_Frame_Foucus.Now_Focus],0);
							break;
						case 4:
							Lcd_Write_Time(READ_BK,0,3);//5s
							Creat_Frame(Menu_Frame);
							break;
						default:
							break;
					}
					break;
				case WM_ARRIVE:
					Para_write(TIME_SETREMINDER,RemindList[Sitchage_Frame_Foucus.Now_Focus],1);
					Back_To=1;
					Lcd_Write_Time(READ_BK,0,3);//5s
					Creat_Frame(OK_Frame);
					break;
   }
}




static void BlockCheck_Frame(int data)
{
	static uint8_t SLH;
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					GRAM_ShowString(MenuX+16,MenuY,"自检中",FONT22_DEFAULT);
					Uart_Send_CheckBlock();
					Lcd_Write_Time(READ_BK,1,20);//5s
					Lcd_Write_Time(REAL_T,1,5);//5s
					break;
			case WM_REALTIME:
					switch(SLH)
					{
						case 0:
							GRAM_Clear(MenuX+5*16+5,MenuY+13,MenuX+5*16+5*3+2,MenuY+15);
							SLH++;
							break;
						case 1:
							GRAM_Fill(MenuX+5*16+5,MenuY+13,MenuX+5*16+7,MenuY+15);
							SLH++;
							break;
						case 2:
							GRAM_Fill(MenuX+5*16+5*2,MenuY+13,MenuX+5*16+12,MenuY+15);
							SLH++;
							break;
						case 3:
							GRAM_Fill(MenuX+5*16+5*3,MenuY+13,MenuX+5*16+17,MenuY+15);
							SLH=0;
							break;
						default:
							SLH=0;
							break;
					}
					break;
			case WM_ARRIVE:
					Back_To=1;
					switch(Para_read(ACTIVE_SULT))
					{
						case 0:
							Lcd_Write_Time(READ_BK,0,0);//5s
							Lcd_Write_Time(REAL_T,0,5);//5s
							Creat_Frame(ERROR_Frame);
							break;
						case 1:
							Lcd_Write_Time(READ_BK,0,0);//5s
							Lcd_Write_Time(REAL_T,0,5);//5s
							Creat_Frame(OK_Frame);
							break;
					}
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Lcd_Write_Time(REAL_T,0,5);//5s
					Creat_Frame(retry_Frame);
					break;
    }
}

Focus_Srtuct_Typdef BlockBack_Frame_Foucus;
const uint8_t BlockBackList[4]={1,3,0,254};
void BlockBack_Frame_Init(void)
{	
	BlockBack_Frame_Foucus.Now_Focus=0;
	BlockBack_Frame_Foucus.Max_Focus_Num=3;
}

const char * BlockBackfont[]=
{
	"低灵敏度",
	"高灵敏度",
	"关闭",
	"返回",
};


static void BlockBack_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					BlockBack_Frame_Init();
				  Set_Focus(&BlockBack_Frame_Foucus);
					GetLang(&BlockBack_Frame_Foucus,BlockBackfont);
					GRAM_ShowString(MenuX,MenuY,BlockBack_Frame_Foucus.Focus_Data[BlockBack_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					if(Para_read(MODE_BLOCK)==BlockBackList[BlockBack_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&BlockBack_Frame_Foucus);
				if(Para_read(MODE_BLOCK)==BlockBackList[BlockBack_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&BlockBack_Frame_Foucus);
				if(Para_read(MODE_BLOCK)==BlockBackList[BlockBack_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_M:
				switch(BlockBack_Frame_Foucus.Now_Focus)
				{
					case 0:
					case 1:
					case 2:
						Para_write(MODE_BLOCK,BlockBackList[BlockBack_Frame_Foucus.Now_Focus],0);
						break;
					case 3:
						Lcd_Write_Time(READ_BK,0,0);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
			case WM_ARRIVE:
					Para_write(MODE_BLOCK,BlockBackList[BlockBack_Frame_Foucus.Now_Focus],1);
					Back_To=1;
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(OK_Frame);
					break;
   }
}
Focus_Srtuct_Typdef WillBlockBack_Frame_Foucus;
const uint8_t WillBlockBackList[3]={4,0,22};
void WillBlockBack_Frame_Init(void)
{	
	WillBlockBack_Frame_Foucus.Now_Focus=0;
	WillBlockBack_Frame_Foucus.Max_Focus_Num=2;
}
const char * WillBlockBackfont[]=
{
	"开启",
	"关闭",
	"返回",
};


static void WillBlockBack_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					WillBlockBack_Frame_Init();
				  Set_Focus(&WillBlockBack_Frame_Foucus);
					GetLang(&WillBlockBack_Frame_Foucus,WillBlockBackfont);
					GRAM_ShowString(MenuX,MenuY,WillBlockBack_Frame_Foucus.Focus_Data[WillBlockBack_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					if(Para_read(MODE_WILLBLOCK)==WillBlockBackList[WillBlockBack_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&WillBlockBack_Frame_Foucus);
				if(Para_read(MODE_WILLBLOCK)==WillBlockBackList[WillBlockBack_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&WillBlockBack_Frame_Foucus);
				if(Para_read(MODE_WILLBLOCK)==WillBlockBackList[WillBlockBack_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_M:
				switch(WillBlockBack_Frame_Foucus.Now_Focus)
				{
					case 0:
					case 1:
						Para_write(MODE_WILLBLOCK,WillBlockBackList[WillBlockBack_Frame_Foucus.Now_Focus],0);
						break;
					case 2:
						Lcd_Write_Time(READ_BK,0,3);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
			case WM_ARRIVE:
					Para_write(MODE_WILLBLOCK,WillBlockBackList[WillBlockBack_Frame_Foucus.Now_Focus],1);
					Back_To=1;
					Lcd_Write_Time(READ_BK,0,3);//5s
					Creat_Frame(OK_Frame);
					break;
   }
}


Focus_Srtuct_Typdef KnockGoDown_Frame_Foucus;
const uint8_t BlockGoDownList[3]={1,0,254};
void KnockGoDown_Frame_Init(void)
{	
	KnockGoDown_Frame_Foucus.Now_Focus=0;
	KnockGoDown_Frame_Foucus.Max_Focus_Num=2;
}


const char * BlockGoDownfont[]=
{
	"开启",
	"关闭",
	"返回",
};


static void KnockGoDown_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					KnockGoDown_Frame_Init();
				  Set_Focus(&KnockGoDown_Frame_Foucus);
					GetLang(&KnockGoDown_Frame_Foucus,BlockGoDownfont);
					GRAM_ShowString(MenuX,MenuY,KnockGoDown_Frame_Foucus.Focus_Data[KnockGoDown_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					if(Para_read(MODE_KNOCK)==BlockGoDownList[KnockGoDown_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&KnockGoDown_Frame_Foucus);
				if(Para_read(MODE_KNOCK)==BlockGoDownList[KnockGoDown_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&KnockGoDown_Frame_Foucus);
				if(Para_read(MODE_KNOCK)==BlockGoDownList[KnockGoDown_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_M:
				switch(KnockGoDown_Frame_Foucus.Now_Focus)
				{
					case 0:
					case 1:
						Para_write(MODE_KNOCK,BlockGoDownList[KnockGoDown_Frame_Foucus.Now_Focus],0);
						break;
					case 2:
						Lcd_Write_Time(READ_BK,0,3);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
			case WM_ARRIVE:
					Para_write(MODE_KNOCK,BlockGoDownList[KnockGoDown_Frame_Foucus.Now_Focus],1);
					Back_To=1;		
					Lcd_Write_Time(READ_BK,0,3);//5s
					Creat_Frame(OK_Frame);
					break;
   }
}


static void AutoBlence_Frame(int data)
{
		static uint8_t SLH;
		switch (data)
    {
			case WM_CREATE: 
					Uart_Send_AutoBalence();
					clear_screen();	
					GRAM_ShowString(MenuX+16,MenuY,"调平中",FONT22_DEFAULT);
					Lcd_Write_Time(READ_BK,1,60);//5s
					Lcd_Write_Time(REAL_T,1,5);//5s
					break;
			case WM_REALTIME:
					switch(SLH)
					{
						case 0:
							GRAM_Clear(MenuX+5*16+5,MenuY+13,MenuX+5*16+5*3+2,MenuY+15);
							SLH++;
							break;
						case 1:
							GRAM_Fill(MenuX+5*16+5,MenuY+13,MenuX+5*16+7,MenuY+15);
							SLH++;
							break;
						case 2:
							GRAM_Fill(MenuX+5*16+5*2,MenuY+13,MenuX+5*16+12,MenuY+15);
							SLH++;
							break;
						case 3:
							GRAM_Fill(MenuX+5*16+5*3,MenuY+13,MenuX+5*16+17,MenuY+15);
							SLH=0;
							break;
						default:
							SLH=0;
							break;
					}
					break;
			case WM_ARRIVE:
					Back_To=1;
					switch(Para_read(ACTIVE_SULT))
					{
						case 0:
							Lcd_Write_Time(READ_BK,0,60);//5s
							Lcd_Write_Time(REAL_T,0,5);//5s
							Creat_Frame(ERROR_Frame);
							break;
						case 1:
							Lcd_Write_Time(READ_BK,0,60);//5s
							Lcd_Write_Time(REAL_T,0,5);//5s
							Creat_Frame(OK_Frame);
							break;
					}
					break;
			case WM_M:
					Lcd_Write_Time(READ_BK,0,0);//5s
					Lcd_Write_Time(REAL_T,0,5);//5s
					Back_To=1;
					Creat_Frame(retry_Frame);
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Lcd_Write_Time(REAL_T,0,5);//5s
					Creat_Frame(ERROR_Frame);
					break;
			
    }
}


static void CheckBlence_Frame(int data)
{
		static uint8_t SLH;
		switch (data)
    {
			case WM_CREATE: 
					Uart_Send_CheckBalence();
					clear_screen();	
					GRAM_ShowString(MenuX+16,MenuY,"自检中",FONT22_DEFAULT);
					Lcd_Write_Time(READ_BK,1,10);//5s
					Lcd_Write_Time(REAL_T,1,5);//5s
					break;
			case WM_REALTIME:
					switch(SLH)
					{
						case 0:
							GRAM_Clear(MenuX+5*16+5,MenuY+13,MenuX+5*16+5*3+2,MenuY+15);
							SLH++;
							break;
						case 1:
							GRAM_Fill(MenuX+5*16+5,MenuY+13,MenuX+5*16+7,MenuY+15);
							SLH++;
							break;
						case 2:
							GRAM_Fill(MenuX+5*16+5*2,MenuY+13,MenuX+5*16+12,MenuY+15);
							SLH++;
							break;
						case 3:
							GRAM_Fill(MenuX+5*16+5*3,MenuY+13,MenuX+5*16+17,MenuY+15);
							SLH=0;
							break;
						default:
							SLH=0;
							break;
					}
					break;
			case WM_ARRIVE:
					Back_To=1;
					switch(Para_read(ACTIVE_SULT))
						{
							case 0:
								Lcd_Write_Time(READ_BK,0,60);//5s
								Lcd_Write_Time(REAL_T,0,5);//5s
								Creat_Frame(ERROR_Frame);
								break;
							case 1:
								Lcd_Write_Time(READ_BK,0,60);//5s
								Lcd_Write_Time(REAL_T,0,5);//5s
								Creat_Frame(OK_Frame);
								break;
						}
					break;
			case WM_TIMEOUT:
					Lcd_Write_Time(REAL_T,0,5);//5s
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(retry_Frame);
					break;
    }
}



const char * MaxHightsetfont[]=
{
	"设为最高",
	"关闭",
	"返回",
};

Focus_Srtuct_Typdef MaxHightset_Frame_Foucus;

static void MaxHightset_Frame_Init(void)
{	
	MaxHightset_Frame_Foucus.Now_Focus=0;
	MaxHightset_Frame_Foucus.Max_Focus_Num=2;
}

static void MaxHightset_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					MaxHightset_Frame_Init();
				  Set_Focus(&MaxHightset_Frame_Foucus);
					GetLang(&MaxHightset_Frame_Foucus,MaxHightsetfont);
					GRAM_ShowString(MenuX,MenuY,MaxHightset_Frame_Foucus.Focus_Data[MaxHightset_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&MaxHightset_Frame_Foucus);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&MaxHightset_Frame_Foucus);
				break;
			case WM_M:
				switch(MaxHightset_Frame_Foucus.Now_Focus)
				{
					case 0:
						if(Para_read(HIGHT_NOW)<=(Para_read(HIGHT_DWON)+((Para_str.mode_str.unit_mode)?4:10)))
						{
							Lcd_Write_Time(READ_BK,0,3);//5s
							Creat_Frame(ERROR_Frame);
						}
						else
						{
							Para_write(HIGHT_TOP,Para_read(HIGHT_NOW),0);
						}
						break;
					case 1:
						Para_write(HIGHT_TOP,MAX_HIGHT,0);
						break;
					case 2:
						Lcd_Write_Time(READ_BK,0,3);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
			case WM_ARRIVE:		
					Back_To=1;
					if(MaxHightset_Frame_Foucus.Now_Focus==0)Para_write(HIGHT_TOP,Para_read(HIGHT_NOW),1);		
					else	Para_write(HIGHT_TOP,MAX_HIGHT,1);	
					Lcd_Write_Time(READ_BK,0,3);//5s			
					Creat_Frame(OK_Frame);
				break;
   }
}


const char * MinHightsetfont[]=
{
	"设为最低",
	"关闭",
	"返回",
};

Focus_Srtuct_Typdef MinHightset_Frame_Foucus;
static void MinHightset_Frame_Init(void)
{	
	MinHightset_Frame_Foucus.Now_Focus=0;
	MinHightset_Frame_Foucus.Max_Focus_Num=2;
}

static void MinHightset_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					MinHightset_Frame_Init();
				  Set_Focus(&MinHightset_Frame_Foucus);
					GetLang(&MinHightset_Frame_Foucus,MinHightsetfont);
					GRAM_ShowString(MenuX,MenuY,MinHightset_Frame_Foucus.Focus_Data[MinHightset_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&MinHightset_Frame_Foucus);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&MinHightset_Frame_Foucus);
				break;
			case WM_M:
				switch(MinHightset_Frame_Foucus.Now_Focus)
				{
					case 0:
						if(Para_read(HIGHT_NOW)>=(Para_read(HIGHT_TOP)-((Para_str.mode_str.unit_mode)?4:10)))
						{
							Lcd_Write_Time(READ_BK,0,3);//5s
							Creat_Frame(ERROR_Frame);
						}
						else
						{
							Para_write(HIGHT_DWON,Para_read(HIGHT_NOW),0);
						}
						break;
					case 1:
						Para_write(HIGHT_DWON,MIN_HIGHT,0);
						Para_str.hight_str.DownSetFlag=false;
						break;
					case 2:
						Lcd_Write_Time(READ_BK,0,3);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
			break;
		case WM_ARRIVE:			
					Back_To=1;			
					if(MinHightset_Frame_Foucus.Now_Focus==0)Para_write(HIGHT_DWON,Para_read(HIGHT_NOW),1);		
					else	Para_write(HIGHT_DWON,MIN_HIGHT,1);			
					Lcd_Write_Time(READ_BK,0,3);//5s		
					Creat_Frame(OK_Frame);
				break;
   }
}


const char * Unitsetfont[]=
{
	"厘米",
	"英寸",
	"返回",
};

Focus_Srtuct_Typdef Unitset_Frame_Foucus;
const uint8_t UnitsetList[3]={0,1,254};
static void Unitset_Frame_Init(void)
{	
	Unitset_Frame_Foucus.Now_Focus=0;
	Unitset_Frame_Foucus.Max_Focus_Num=2;
}



static void Unitset_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					Unitset_Frame_Init();
				  Set_Focus(&Unitset_Frame_Foucus);
					GetLang(&Unitset_Frame_Foucus,Unitsetfont);
					GRAM_ShowString(MenuX,MenuY,Unitset_Frame_Foucus.Focus_Data[Unitset_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					if(Para_read(MODE_UNIT)==UnitsetList[Unitset_Frame_Foucus.Now_Focus])
					{
						GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
					}
					else
						GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&Unitset_Frame_Foucus);
				if(Para_read(MODE_UNIT)==UnitsetList[Unitset_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&Unitset_Frame_Foucus);
				if(Para_read(MODE_UNIT)==UnitsetList[Unitset_Frame_Foucus.Now_Focus])
				{
					GRAM_ShowLattice(CheckX,CheckY,16,12,(const uint8_t *)Page_SETOK,1);
				}
				else
					GRAM_Clear(CheckX,CheckY,CheckX+16,CheckY+12);
				break;
			case WM_M:
				switch(Unitset_Frame_Foucus.Now_Focus)
				{
					case 0:
					case 1:
						Para_write(MODE_UNIT,UnitsetList[Unitset_Frame_Foucus.Now_Focus],0);
						break;
					case 2:
						Lcd_Write_Time(READ_BK,0,3);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
			case WM_ARRIVE:			
					Back_To=1;
					Para_write(MODE_UNIT,UnitsetList[Unitset_Frame_Foucus.Now_Focus],1);
					Lcd_Write_Time(READ_BK,0,3);//5s
					Creat_Frame(OK_Frame);
				break;
   }
}


const char * Resetsetfont[]=
{
	"请长按",
	"返回",
};

Focus_Srtuct_Typdef Resetset_Frame_Foucus;
extern const char Page_DOWN[];
static void Resetset_Frame_Init(void)
{	
	Resetset_Frame_Foucus.Now_Focus=0;
	Resetset_Frame_Foucus.Max_Focus_Num=1;
}

void Resetset_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					Resetset_Frame_Init();
				  Set_Focus(&Resetset_Frame_Foucus);
					GetLang(&Resetset_Frame_Foucus,Resetsetfont);
					GRAM_ShowString(MenuX,MenuY,Resetset_Frame_Foucus.Focus_Data[Resetset_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					GRAM_ShowLattice(CheckX,CheckY-2,16,16,(const uint8_t *)Page_DOWN,0);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&Resetset_Frame_Foucus);
				if(Resetset_Frame_Foucus.Now_Focus==0)
					GRAM_ShowLattice(CheckX,CheckY-2,16,16,(const uint8_t *)Page_DOWN,0);
				else
					GRAM_Clear(CheckX,CheckY-2,CheckX+16,CheckY+14);
				break;
			case WM_DWONLONG:
					Lcd_Write_Time(READ_BK,0,3);//5s
					Creat_Frame(Reseting_Frame);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&Resetset_Frame_Foucus);
				if(Resetset_Frame_Foucus.Now_Focus==0)
					GRAM_ShowLattice(CheckX,CheckY-2,16,16,(const uint8_t *)Page_DOWN,0);
				else
					GRAM_Clear(CheckX,CheckY-2,CheckX+16,CheckY+14);
				break;
			case WM_M:
				switch(Resetset_Frame_Foucus.Now_Focus)
				{
					case 1:
						Lcd_Write_Time(READ_BK,0,3);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
   }
}


const char * Versionfont[]=
{
	"LGC_V1.2",
	"返回",
};

Focus_Srtuct_Typdef Version_Frame_Foucus;

static void Version_Frame_Init(void)
{	
	Version_Frame_Foucus.Now_Focus=0;
	Version_Frame_Foucus.Max_Focus_Num=1;
}
static void Version_Frame(int data)
{
		switch (data)
    {
			case WM_CREATE: 
					clear_screen();	
					Version_Frame_Init();
				  Set_Focus(&Version_Frame_Foucus);
					GetLang(&Version_Frame_Foucus,Versionfont);
					GRAM_ShowString(MenuX,MenuY,Version_Frame_Foucus.Focus_Data[Version_Frame_Foucus.Now_Focus],FONT22_DEFAULT);
					Lcd_Write_Time(READ_BK,1,3);//5s
					break;
			case WM_TIMEOUT:
					//Beep_SetNum(1,2,0);
					Lcd_Write_Time(READ_BK,0,0);//5s
					Creat_Frame(Menu_Frame);
					break;
			case WM_UP:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Decrease_Focus(&Version_Frame_Foucus);
				break;
			case WM_DOWN:
				Lcd_Write_Time(READ_BK,1,3);//5s
				Increase_Focus(&Version_Frame_Foucus);
			  break;
			case WM_M:
				switch(Version_Frame_Foucus.Now_Focus)
				{
					case 1:
						Lcd_Write_Time(READ_BK,0,0);//5s
						Creat_Frame(Menu_Frame);
						break;
					default:
						break;
				}
				break;
   }
}

void Reseting_Frame(int data)
{
	static uint8_t SLH;
	static uint8_t senddelay;
		switch (data)
    {
			case WM_CREATE: 
					if(Para_str.FirstPower==0xbb)senddelay=1;else senddelay=0;
					Para_str.FirstPower=0;
					clear_screen();	
					GRAM_ShowString(MenuX,MenuY,"请保持",FONT22_DEFAULT);
					GRAM_ShowLattice(CheckX,CheckY-2,16,16,(const uint8_t *)Page_DOWN,0);
					break;
			case WM_TIMEOUT:
				Uart_Start();
				Uart_Start();
				Uart_Start();
				Uart_Start();
				Uart_Start();
				senddelay=1;
				Lcd_Write_Time(READ_BK,0,0);//5s
				break;
			case WM_ARRIVE:	
					switch(senddelay)
					{
						case 0:
							Lcd_Write_Time(READ_BK,1,2);//5s
							break;
						case 1:
							Back_To=0;
							Para_write(HIGHT_TOP,MAX_HIGHT,0);
							Para_write(HIGHT_DWON,MIN_HIGHT,0);
							Lcd_Write_Time(REAL_T,0,0);//5s
							Creat_Frame(OK_Frame);
							break;
					}
					break;
			case WM_DWONLONG:
					if(senddelay)
					Uart_Send_Forward(1); 
					else
					Uart_Send_Reset();
					SLH++;
					Lcd_Write_Time(REAL_T,1,2);//5s
					if(SLH<5)
					{
						GRAM_Clear(CheckX,CheckY-2,CheckX+16,CheckY+14);
					}
					else if(SLH>=5&&SLH<10)
					{
						GRAM_ShowLattice(CheckX,CheckY-2,16,16,(const uint8_t *)Page_DOWN,0);
					}
					else
					{
						SLH=0;
					}
					break;
			case WM_REALTIME:
					SLH++;
					if(SLH<5)
					{
						GRAM_Clear(CheckX,CheckY-2,CheckX+16,CheckY+14);
					}
					else if(SLH>=5&&SLH<10)
					{
						GRAM_ShowLattice(CheckX,CheckY-2,16,16,(const uint8_t *)Page_DOWN,0);
					}
					else
					{
						SLH=0;
					}
					break;
    }
}
