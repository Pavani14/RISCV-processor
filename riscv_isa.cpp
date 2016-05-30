#include "riscv_isa.H"
#include "riscv_isa_init.cpp"
#include "riscv_bhv_macros.H"

#include "ac_debug_model.H"

#define Ra 1 
#define Sp 14

using namespace riscv_parms;

//static int processors_started = ;
//#define DEFAULT_STACK_SIZE(     );

//generic instruction behavior method
void ac_behavior(instruction){
}

//Instruction Format behavior methods
void ac_behavior(Type_R){}
void ac_behavior(Type_I){}
void ac_behavior(Type_S){}
void ac_behavior(Type_SB){}
void ac_behavior(Type_U){}
void ac_behavior(Type_UJ){}

// Behavior called before starting simulation
void ac_behavior(begin)
{
  dbg_printf("@@@ begin behavior @@@\n");
  npc = ac_pc + 4;

  for (int regNum = 0; regNum < 32; regNum ++)
    RB[regNum] = 0;
  hi = 0;
  lo = 0;
}

// Behavior called after finishing simulation
void ac_behavior(end)
{
  dbg_printf("@@@ end behavior @@@\n");
}

void ac_behavior( ADD ){
	dbg_printf();
	RB[rd] = RB[rs1] + RB[rs2];
	dbg_printf("Result = %#x\n", RB[rd]);
	//no check for overflow
}

void ac_behavior( SUB ){
	dbg_printf();
	RB[rd] = RB[rs1] - RB[rs2];
	dbg_printf("Result = %#x\n", RB[rd]);
	//no check for overflow/underflow
}

void ac_behavior( SLL ){
	dbg_printf();
	RB[rd] = RB[rs1] << RB[rs2];
}

void ac_behavior( SLT ){
	dbg_printf();
	if(RB[rs1] < RB[rs2])
		RB[rd] = 1;
	else
		RB[rd] = 0;
}

//check how to compare unsigned numbers
void ac_behavior( SLTU ){
	dbg_printf();
	if( (ac_Uword)RB[rs1] < (ac_Uword)RB[rs2])
		RB[rd] = 1;
	else
		RB[rd] = 0;
}

void ac_behavior( XOR ){
	dbg_printf();
	RB[rd] = RB[rs1] ^ RB[rs2];
	dbg_printf("Result = %#x\n", RB[rd]);
}

void ac_behavior( SRL ){
	dbg_printf();
	RB[rd] = RB[rs1] >> RB[rs2];
}

void ac_behavior( SRA ){
	if((RB[rs1] >> 4) == 1){
		RB[rd] = (RB[rs1]>>RB[rs2]) | (0xFFFFFFFF<<RB[rs2]);
	else
		RB[rd] = RB[rs1]>>RB[rs2];

}

void ac_behavior( OR ){
	dbg_printf();
	RB[rd] = RB[rs1] | RB[rs2];
	dbg_printf("Result = %#x\n", RB[rd]);
}

void ac_behavior( AND ){
	dbg_printf();
	RB[rd] = RB[rs1] & RB[rs2];
	dbg_printf("Result = %#x\n", RB[rd]);
}


void ac_behavior( LB ){
	char byte;
	dbg_printf();
	byte = DATA_PORT->read_byte(RB[rs1] + (imm & 0xFFFFFFFF));
	RB[rd] = (ac_Sword)byte;
}

void ac_behavior( LH ){
	short int half;
	half = DATA_PORT->read_half(RB[rs1] + (imm & 0xFFFFFFFF));
	RB[rd] = (ac_Sword)half;
}

void ac_behavior( LW ){
	dbg_printf();
	RB[rd] = DATA_PORT->read(RB[rs1] + (imm & 0xFFFFFFFF));
	dbg_printf();
}

void ac_behavior( LBU ){
	dbg_printf();
	unsigned char byte;
	byte = DATA_PORT->read_byte(RB[rs1] + (imm & 0xFFFFFFFF));
	RB[rd] = (ac_Uword)byte;
}

void ac_behavior( LHU ){
	unsigned short int half;
	half = DATA_PORT->read_half(RB[rs1] + (imm & 0xFFFFFFFF));
	RB[rd] = (ac_Uword)half;	
}

void ac_behavior( ADDI ){
	dbg_printf();
	int sign_ext;
	if((imm >> 11) == 1){
		sign_ext = imm & 0xFFFFFFFF;
	else
		sign_ext = imm & 0x00000FFF;
	RB[rd] = RB[rs1] + sign_ext;
	dbg_printf("Result = %#x\n", RB[rd]);
}

void ac_behavior( SLTI ){
	dbg_printf();
	int sign_ext;
	if((imm >> 11) == 1){
		sign_ext = imm & 0xFFFFFFFF;
	else
		sign_ext = imm & 0x00000FFF;
	if(RB[rs1] < sign_ext)
		RB[rd] = 1;
	else
		RB[rd] = 0;
}

//REDO
void ac_behavior( SLTIU ){
		dbg_printf();
	int sign_ext;
	if((imm >> 11) == 1){
		sign_ext = imm & 0xFFFFFFFF;
	else
		sign_ext = imm & 0x00000FFF;
//Check how to convert signed number to unsigned number.	
	if( (ac_Uword)RB[rs1] < (ac_Uword)sign_ext)
		RB[rd] = 1;
	else
		RB[rd] = 0;
}


void ac_behavior( XORI ){
	dbg_printf();
	int sign_ext;
	if((imm >> 11) == 1){
		sign_ext = imm & 0xFFFFFFFF;
	else
		sign_ext = imm & 0xFFFFF000;
	RB[rd] = RB[rs1] ^ sign_ext;
	dbg_printf("Result = %#x\n", RB[rd]);
}

void ac_behavior( ORI ){
	dbg_printf();
	int sign_ext;
	if((imm >> 11) == 1){
		sign_ext = imm & 0xFFFFFFFF;
	else
		sign_ext = imm | 0xFFFFF000;
	RB[rd] = RB[rs1] + sign_ext;
	dbg_printf("Result = %#x\n", RB[rd]);
}

void ac_behavior( ANDI ){
	dbg_printf();
	int sign_ext;
	if((imm >> 11) == 1){
		sign_ext = imm & 0xFFFFFFFF;
	else
		sign_ext = imm & 0xFFFFF000;
	RB[rd] = RB[rs1] & sign_ext;
	dbg_printf("Result = %#x\n", RB[rd]);
}

void ac_behavior( JALR ){
	int target_addr;
	target_addr = (imm + RB[rs1]) & 0xD;
	pc = target_addr;
	RB[rd] = pc+4;
}

void ac_behavior( SLLI ){
	RB[rd] = RB[rs1]<<shamt;
}

void ac_behavior( SRLI ){
	RB[rd] = RB[rs1]>>shamt;
}

void ac_behavior( SRAI ){
	if((imm >> 11) == 1){
		RB[rd] = (RB[rs1]>>shamt) | (0xFFFFFFFF<<shamt);
	else
		RB[rd] = RB[rs1]>>shamt;
}

void ac_behavior( SCALL ){

}

void ac_behavior( SBREAK ){

}

void ac_behavior( RDCYCLE ){

}

void ac_behavior( RDCYCLEH ){

}

void ac_behavior( RDTIME ){

}

void ac_behavior( RDTIMEH ){

} 

void ac_behavior( RDINSTRET ){

}

void ac_behavior( RDINSTRETH ){

}

void ac_behavior( SB ){
	unsigned char byte;
	dbg_printf();
	byte = RB[rs2];
	DATA_PORT->write_byte(RB[rs1] + (imm & 0xFFFFFFFF), byte);_
}

void ac_behavior( SH ){
	dbg_printf();
	DATA_PORT->write_half(RB[rs1] + (imm & 0xFFFFFFFF), RB[rs2]);
}

void ac_behavior( SW ){
	dbg_printf();
	DATA_PORT->write(RB[rs1] + (imm & 0xFFFFFFFF), RB[rs2]);
}

void ac_behavior( BEQ ){
	if(RB[rs1] == RB[rs2])
		pc = pc + imm;
}

void ac_behavior( BNE ){
	if(RB[rs1] != RB[rs2])
		pc = pc + imm;
}

void ac_behavior( BLT ){
	if(RB[rs1] < RB[rs2])
		pc = pc + imm;

}

void ac_behavior( BGE ){
	if((RB[rs1] > RB[rs2]) || (RB[rs1] == RB[rs2])) 
		pc = pc + imm;
}

void ac_behavior( BLTU ){
	if((ac_Uword)RB[rs1] < (ac_Uword)RB[rs2])
		pc = pc + imm;
}

void ac_behavior( BGEU ){
	if(((ac_Uword)RB[rs1] > (ac_Uword)RB[rs2]) || ((ac_Uword)RB[rs1] == (ac_Uword)RB[rs2])) 
		pc = pc + imm;
}

void ac_behavior( LUI ){
	RB[rd] = imm<<12; 
}

void ac_behavior( AUIPC ){
	int offset, new_pc;
	offset = imm<<12;
	RB[rd] = pc + offset;
}

void ac_behavior( JAL ){
	RB[rd] = pc + 4;
	pc = (imm & 0xFFFFFFFF) + pc; 
}