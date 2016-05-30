/*
* @file		riscv_gdb_funcs.cpp
* @version	1.0
*
*
* @date
* @brief 	The ArchC RISC-V functional model
*
*/

#include "riscv.H"

using namespace riscv_parms;

int riscv::nRegs(void){
	return //look for the right number to return
}

ac_word riscv::reg_read(){
	if((reg>=0) && (reg<32))
		return RB.read(reg);
	else{
		if(reg == 33)
			return lo;
		else if (reg == 34)
			return hi;
		else
			if(reg == )
				return ac_pc;
	}
}

ac_word riscv::reg_write(){
	if((reg>=0) && (reg<32))
		RB.write(reg-1, value);
	else{
		//conditions for hi and lo
		if ()
		
		else
			if(reg == )
				ac_pc = value;
	}
}


//check these two functions
unsigned char riscv::mem_read(){
	return IM->read_byte(address);
}

void riscv::mem_write(){
	IM->write_byte(adress, byte);
}