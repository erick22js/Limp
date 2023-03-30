#include <Limp/alu.h>
#include <Limp/cpu.h>



/**
	ARITHMETIC FUNCTIONS
*/


Uint32 LIAlu_add(LCpu *m_cpu, Uint32 v1, Uint32 v2, Bool wcarry){
	Uint32 st = m_cpu->sregs.est;
	Bool g_cf = getBit(st, LI_CPU_CF);
	
	// Do the sum between values
	// If "wcarry", carry will sums
	Uint32 res = v1+v2 + (g_cf&wcarry); /* TODO: Carry may cause difference in some flags */
	
	// Define the flags
	// Carry Flag
	st = setVBit(st, LI_CPU_CF,
		res<v1);
	// Overflow Flag
	st = setVBit(st, LI_CPU_VF,
		(getSign(v1)==getSign(v2))&&(getSign(v1)!=getSign(res)));
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_sub(LCpu *m_cpu, Uint32 v1, Uint32 v2, Bool wborrow){
	Uint32 st = m_cpu->sregs.est;
	Bool g_bf = getBit(st, LI_CPU_BF);
	
	// Do the subtraction between values
	// If "wborrow", borrow will subtracts
	Uint32 res = v1-v2 - (g_bf&wborrow); /* TODO: Borrow may cause difference in some flags */
	
	// Define the flags
	// Borrow Flag
	st = setVBit(st, LI_CPU_BF,
		res>v1);
	// Overflow Flag
	st = setVBit(st, LI_CPU_VF,
		(getSign(v1)!=getSign(v2))&&(getSign(v2)==getSign(res)));
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_mul(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the multiplication between values
	Uint32 res = v1*v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_hmul(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the quad multiplication between values
	// Test and returns only the high dword
	Uint64 qres = (Uint64)v1*(Uint64)v2;
	Uint32 res = qres>>32;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_div(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the division between values
	Uint32 res = v1/v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_mod(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the modulation between values
	Uint32 res = v1%v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_ldiv(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the quad division between values
	// Test and returns only the lower dword
	Uint64 qv1 = ((Uint64)v1)<<32;
	qv1 /= v2;
	Uint32 res = qv1;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}


Uint32 LIAlu_and(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the and bitwise between values
	Uint32 res = v1&v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_nand(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the nand bitwise between values
	Uint32 res = ~(v1&v2);
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_or(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the and bitwise between values
	Uint32 res = v1|v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_xor(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the xor bitwise between values
	Uint32 res = v1^v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_not(LCpu *m_cpu, Uint32 v){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the negation between values
	Uint32 res = ~v;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

void LIAlu_test(LCpu *m_cpu, Uint32 v){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the negation between values
	Uint32 res = v;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
}



Uint32 LIAlu_lshf(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the left shift between values
	Uint32 res = v1<<v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_rshf(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the right shift between values
	Uint32 res = v1>>v2;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_lrot(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the left rotation between values
	Uint32 exc = v1>>(32-v2);
	Uint32 res = v1<<v2;
	res |= exc;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}

Uint32 LIAlu_rrot(LCpu *m_cpu, Uint32 v1, Uint32 v2){
	Uint32 st = m_cpu->sregs.est;
	
	// Do the right rotation between values
	Uint32 exc = v1<<(32-v2);
	Uint32 res = v1>>v2;
	res |= exc;
	
	// Define the flags
	// Zero FLag
	st = setVBit(st, LI_CPU_ZF, res==0);
	// Negative Flag
	st = setVBit(st, LI_CPU_NF, getSign(res));
	// Odd Flag
	st = setVBit(st, LI_CPU_OF, getBit(res, 0));
	
	m_cpu->sregs.est = st;
	
	return res;
}


