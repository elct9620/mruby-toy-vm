#ifndef OP_CODE_H_
#define OP_CODE_H_

/**
 * From mruby-L1VM
 *
 * @source https://github.com/taisukef/mruby-L1VM/blob/master/mruby_l1vm.h
 */
enum {
	OP_NOP,
	OP_MOVE,
	OP_LOADL,
	OP_LOADI,
	OP_LOADINEG,
	OP_LOADI__1,
	OP_LOADI_0,
	OP_LOADI_1,
	OP_LOADI_2,
	OP_LOADI_3,
	OP_LOADI_4,
	OP_LOADI_5,
	OP_LOADI_6,
	OP_LOADI_7,
	OP_LOADSYM,
	OP_LOADNIL,
	OP_LOADSELF,
	OP_LOADT,
	OP_LOADF,
	OP_GETIV = 23,
	OP_SETIV,
	OP_GETCONST = 27,
	OP_SETCONST,
	OP_GETUPVAR = 31,
	OP_SETUPVAR,
	OP_JMP,
	OP_JMPIF,
	OP_JMPNOT,
	OP_SENDV = 44,
	OP_SENDVB,
	OP_SEND,
	OP_SENDB,
	OP_ENTER = 51,
	OP_RETURN = 55,
	OP_RETURN_BLK,
	OP_BREAK,
	OP_ADD = 59,
	OP_ADDI,
	OP_SUB,
	OP_SUBI,
	OP_MUL,
	OP_DIV,
	OP_EQ,
	OP_LT,
	OP_LE,
	OP_GT,
	OP_GE,
	OP_ARRAY = 70,
	OP_ARRAY2,
	OP_ARYCAT,
	OP_ARYPUSH = 73,
	OP_AREF = 75,
	OP_ASET, // unused?
	OP_APOST,
	OP_STRING = 79,
	OP_STRCAT,
	OP_HASH,
	OP_HASHADD,
	OP_HASHCAT,
	OP_BLOCK = 85,
	OP_METHOD,
	OP_RANGE_INC,
	OP_RANGE_EXC,
	OP_CLASS = 90,
	OP_EXEC = 92,
	OP_DEF,
	OP_TCLASS = 97,
	OP_EXT1 = 100,
	OP_EXT2,
	OP_EXT3,
	OP_STOP,
};

#endif
