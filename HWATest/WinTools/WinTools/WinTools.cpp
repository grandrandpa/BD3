// WinTools.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinTools.h"


////////////////////////////////////////////////
int ItemToMode(int index)
{
	int mode = 0;
	switch (index)
	{
	case 0:
		mode = MOD_B1I;
		break;
	case 1:
		mode = MOD_B1Q;
		break;
	case 2:
		mode = MOD_B1C;
		break;
	case 3:
		mode = MOD_B1A;
		break;
	case 4:
		mode = MOD_B2a;
		break;
	case 5:
		mode = MOD_B2b;
		break;
	case 6:
		mode = MOD_B2;
		break;
	case 7:
		mode = MOD_B3I;
		break;
	case 8:
		mode = MOD_B3Q;
		break;
	case 9:
		mode = MOD_B3C;
		break;
	case 10:
		mode = MOD_B3A;
		break;
	case 11:
		mode = MOD_B3AE;
		break;
	case 12:
		mode = MOD_Bs;
		break;
	case 13:
		mode = MOD_B1CB3C;
		break;
	case 14:
		mode = MOD_B1QB3Q;
		break;
	case 15:
		mode = MOD_B1AB3A;
		break;
	case 16:
		mode = MOD_B1AB3AE;
		break;
	case 17:
		mode = MOD_BsB3A;
		break;
	case 18:
		mode = MOD_BsB3AE;
		break;
	case 19:
		mode = MOD_B1CB2a;
		break;
	case 20:
		mode = MOD_B1CB2B3C;
		break;
	case 21:
		mode = MOD_USER;
		break;
	default:
		mode = -1;
		break;
	}
	return mode;
}
int ModeToItem(int mode)
{
	int index = 0;
	switch (mode)
	{
	case MOD_B1I:
		index = 0;
		break;
	case MOD_B1Q:
		index = 1;
		break;
	case MOD_B1C:
		index = 2;
		break;
	case MOD_B1A:
		index = 3;
		break;
	case MOD_B2a:
		index = 4;
		break;
	case MOD_B2b:
		index = 5;
		break;
	case MOD_B2:
		index = 6;
		break;
	case MOD_B3I:
		index = 7;
		break;
	case MOD_B3Q:
		index = 8;
		break;
	case MOD_B3C:
		index = 9;
		break;
	case MOD_B3A:
		index = 10;
		break;
	case MOD_B3AE:
		index = 11;
		break;
	case MOD_Bs:
		index = 12;
		break;
	case MOD_B1CB3C:
		index = 13;
		break;
	case MOD_B1QB3Q:
		index = 14;
		break;
	case MOD_B1AB3A:
		index = 15;
		break;
	case MOD_B1AB3AE:
		index = 16;
		break;
	case MOD_BsB3A:
		index = 17;
		break;
	case MOD_BsB3AE:
		index = 18;
		break;
	case MOD_B1CB2a:
		index = 19;
		break;
	case MOD_B1CB2B3C:
		index = 20;
		break;
	case MOD_USER:
		index = 21;
		break;
	case MOD_NONE:
		index = 100;
		break;
	default:
		index = 100;
		break;
	}
	return index;
}
int ItemToBranch(int index)
{
	int branch = 0;
	switch (index)
	{
	case 0:
		branch = CH_B1I;
		break;
	case 1:
		branch = CH_B1Q;
		break;
	case 2:
		branch = CH_B1C;
		break;
	case 3:
		branch = CH_B1A;
		break;
	case 4:
		branch = CH_B2a;
		break;
	case 5:
		branch = CH_B2b;
		break;
	case 6:
		branch = CH_B2;
		break;
	case 7:
		branch = CH_B3I;
		break;
	case 8:
		branch = CH_B3Q;
		break;
	case 9:
		branch = CH_B3C;
		break;
	case 10:
		branch = CH_B3A;
		break;
	case  11:
		branch = CH_B3AE;
		break;
	case  12:
		branch = CH_Bs;
		break;
	default:
		branch = -1;
		break;
	}
	return branch;
}
int BranchToitem(int branch)
{
	int ch = 0;
	switch (branch)
	{
	case CH_B1I:
		ch = 0;
		break;
	case CH_B1Q:
		ch = 1;
		break;
	case CH_B1C:
	case CH_B1C_data:
	case CH_B1C_pilot:
		ch = 2;
		break;
	case CH_B1A:
	case CH_B1A_data:
	case CH_B1A_pilot:
		ch = 3;
		break;
	case CH_B2a:
	case CH_B2a_data:
	case CH_B2a_pilot:
		ch = 4;
		break;
	case CH_B2b:
	case CH_B2b_data:
	case CH_B2b_pilot:
		ch = 5;
		break;
	case CH_B2:
		ch = 6;
		break;
	case CH_B3I:
		ch = 7;
		break;
	case CH_B3Q:
		ch = 8;
		break;
	case CH_B3C:
	case CH_B3C_data:
	case CH_B3C_pilot:
		ch = 9;
		break;
	case CH_B3A:
	case CH_B3A_data:
	case CH_B3A_pilot:
		ch = 10;
		break;
	case  CH_B3AE:
	case  CH_B3AE_data:
	case  CH_B3AE_pilot:
		ch = 11;
		break;
	case CH_Bs:
	case  CH_Bs_data:
	case  CH_Bs_pilot:
		ch = 12;
		break;
	default:
		ch = -1;
		break;
	}
	return ch;
}
int BranchToIndex(int branch)
{
	int ch = 0;
	switch (branch)
	{
	case CH_B1I:
		ch = 0;
		break;
	case CH_B1Q:
		ch = 1;
		break;
	case CH_B1C:
		ch = 2;
		break;
	case CH_B1A:
		ch = 3;
		break;
	case CH_B1C_data:
		ch = 4;
		break;
	case CH_B1C_pilot:
		ch = 5;
		break;
	case CH_B1A_data:
		ch = 6;
		break;
	case CH_B1A_pilot:
		ch = 7;
		break;
	case CH_B2I:
		ch = 8;
		break;
	case CH_B2Q:
		ch = 9;
		break;
	case CH_B2a:
		ch = 10;
		break;
	case CH_B2b:
		ch = 11;
		break;
	case CH_B2:
		ch = 12;
		break;
	case CH_B2a_data:
		ch = 13;
		break;
	case CH_B2a_pilot:
		ch = 14;
		break;
	case CH_B2b_data:
		ch = 15;
		break;
	case CH_B2b_pilot:
		ch = 16;
		break;
	case CH_B3I:
		ch = 17;
		break;
	case CH_B3Q:
		ch = 18;
		break;
	case CH_B3C:
		ch = 19;
		break;
	case CH_B3A:
		ch = 20;
		break;
	case  CH_B3AE:
		ch = 21;
		break;
	case CH_B3C_data:
		ch = 22;
		break;
	case CH_B3C_pilot:
		ch = 23;
		break;
	case CH_B3A_data:
		ch = 24;
		break;
	case CH_B3A_pilot:
		ch = 25;
		break;
	case CH_Bs:
		ch = 26;
		break;
	case  CH_Bs_data:
		ch = 27;
		break;
	case  CH_Bs_pilot:
		ch = 28;
		break;
	case  CH_B3AE_data:
		ch = 29;
		break;
	case  CH_B3AE_pilot:
		ch = 30;
		break;
	default:
		ch = -1;
		break;
	}
	return ch;
}
int IndexToBranch(int index)
{
	int branch = 0;
	switch (index)
	{
	case 0:
		branch = CH_B1I;
		break;
	case 1:
		branch = CH_B1Q;
		break;
	case 2:
		branch = CH_B1C;
		break;
	case 3:
		branch = CH_B1A;
		break;
	case 4:
		branch = CH_B1C_data;
		break;
	case 5:
		branch = CH_B1C_pilot;
		break;
	case 6:
		branch = CH_B1A_data;
		break;
	case 7:
		branch = CH_B1A_pilot;
		break;
	case 8:
		branch = CH_B2I;
		break;
	case 9:
		branch = CH_B2Q;
		break;
	case 10:
		branch = CH_B2a;
		break;
	case 11:
		branch = CH_B2b;
		break;
	case 12:
		branch = CH_B2;
		break;
	case 13:
		branch = CH_B2a_data;
		break;
	case 14:
		branch = CH_B2a_pilot;
		break;
	case 15:
		branch = CH_B2b_data;
		break;
	case 16:
		branch = CH_B2b_pilot;
		break;
	case 17:
		branch = CH_B3I;
		break;
	case 18:
		branch = CH_B3Q;
		break;
	case 19:
		branch = CH_B3C;
		break;
	case 20:
		branch = CH_B3A;
		break;
	case 21:
		branch = CH_B3AE;
		break;
	case 22:
		branch = CH_B3C_data;
		break;
	case 23:
		branch = CH_B3C_pilot;
		break;
	case 24:
		branch = CH_B3A_data;
		break;
	case 25:
		branch = CH_B3A_pilot;
		break;
	case 26:
		branch = CH_Bs;
		break;
	case 27:
		branch = CH_Bs_data;
		break;
	case 28:
		branch = CH_Bs_pilot;
		break;
	case 29:
		branch = CH_B3AE_data;
		break;
	case 30:
		branch = CH_B3AE_pilot;
		break;
	default:
		branch = -1;
		break;
	}
	return branch;
}
////////////////////////////////////////////////////////
