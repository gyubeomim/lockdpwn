/*
 *	freescale ==> 성현이가 짠 코드. 7세그먼트를 1씩 증가시키면서 Dot Point를 0.1초마다 깜빡거린다
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

vuint32_t Pit0cnt = 0, DPcnt = 0;			
int i=0;
void cntLED(void);
void PIT0ISR(void);
void init_PIT(void);
int map[16][7] = { 0, 0, 0, 0, 0, 0, 1,
                  1, 0, 0, 1, 1, 1, 1,  
	 			  0, 0, 1, 0, 0, 1, 0, 
	 			  0, 0, 0, 0, 1, 1, 0, 
	 			  1, 0, 0, 1, 1, 0, 0, 
	 			  0, 1, 0, 0, 1, 0, 0, 
	 			  0, 1, 0, 0, 0, 0, 0, 
	 			  0, 0, 0, 1, 1, 0, 1, 
	 			  0, 0, 0, 0, 0, 0, 0, 
	 			  0, 0, 0, 0, 1, 0, 0, 
	 			  0, 0, 0, 1, 0, 0, 0, 
	 			  1, 1, 0, 0, 0, 0, 0, 
	 			  1, 1, 1, 0, 0, 1, 0, 
	 			  1, 0, 0, 0, 0, 1, 0, 
	 			  0, 1, 1, 0, 0, 0, 0, 
	 			  0, 1, 1, 1, 0, 0, 0};

void main(void) 
{
    initModesAndClock(); 		
	disableWatchdog();    		
	enableIrq();		   		
	
	init_INTC();				
	init_Linflex0();
	init_PIT();
	
	INTC_InstallINTCInterruptHandler(PIT0ISR, 59, 6);
	
	INTC.CPR.B.PRI = 0;
	
	FMSTR_Init();
	
	PIT.CH[0].TCTRL.B.TIE = 0x1;
	PIT.CH[1].TCTRL.B.TIE = 0x1;
	
	PIT.CH[0].TCTRL.B.TEN = 0x1;
	PIT.CH[1].TCTRL.B.TEN = 0x1;
	
	PIT.CH[0].TCTRL.R = 0x3;
	PIT.CH[1].TCTRL.R = 0x3;
	
	
	SIU.PCR[48].R = 0x0200;
	SIU.PCR[49].R = 0x0200;
	SIU.PCR[50].R = 0x0200;
	SIU.PCR[51].R = 0x0200;
	SIU.PCR[52].R = 0x0200;
	SIU.PCR[53].R = 0x0200;
	SIU.PCR[54].R = 0x0200;
	SIU.PCR[55].R = 0x0200;
	
	
	
	
	/* Loop forever */
	for(;;)
	{
    	FMSTR_Recorder();
    	FMSTR_Poll();
    	i=0;
    	cntLED();
	}
}

void init_PIT(void)
{
	PIT.PITMCR.R = 0x00000001;
	PIT.CH[0].LDVAL.R = 6400000;/*0x0061a800;*/
	PIT.CH[0].TCTRL.R = 0x00000003;
	PIT.PITMCR.R = 0x00000000;
}




void PIT0ISR(void)
{
    DPcnt++;
    SIU.GPDO[55].B.PDO^=1;
	PIT.CH[0].TFLG.B.TIF = 1;
	if(DPcnt==10)
	{
		Pit0cnt++;
		DPcnt=0;
	}
	if(Pit0cnt>=16) Pit0cnt=0;
}

void cntLED(void)
{
	while(1)
	{
		SIU.GPDO[48+i].B.PDO=map[Pit0cnt][i];
		if(i==6) break;
		i=i+1;
	}
}

