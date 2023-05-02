#include <math.h>

#include <Limp/instructions/opcode2D.h>
#include <Limp/cpu.h>


// FADC
void LIIsaDtb_opcode2D_func00(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd += *(Float32*)m_cpu->args.rb + getBit(m_cpu->sregs.st, LI_CPU_CF);
}

// FSBB
void LIIsaDtb_opcode2D_func01(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd -= *(Float32*)m_cpu->args.rb - getBit(m_cpu->sregs.st, LI_CPU_BF);
}

// FMADD
void LIIsaDtb_opcode2D_func02(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd *= *(Float32*)m_cpu->args.rb;
	*(Float32*)m_cpu->args.rd += *(Float32*)m_cpu->args.ro;
}

// FMADC
void LIIsaDtb_opcode2D_func03(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd *= *(Float32*)m_cpu->args.rb;
	*(Float32*)m_cpu->args.rd += *(Float32*)m_cpu->args.ro + getBit(m_cpu->sregs.st, LI_CPU_CF);
}

// FMSUB
void LIIsaDtb_opcode2D_func04(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd *= *(Float32*)m_cpu->args.rb;
	*(Float32*)m_cpu->args.rd -= *(Float32*)m_cpu->args.ro;
}

// FMSBB
void LIIsaDtb_opcode2D_func05(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd *= *(Float32*)m_cpu->args.rb;
	*(Float32*)m_cpu->args.rd -= *(Float32*)m_cpu->args.ro - getBit(m_cpu->sregs.st, LI_CPU_BF);
}

// FMOD
void LIIsaDtb_opcode2D_func06(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = fmodf(*(Float32*)m_cpu->args.rd, *(Float32*)m_cpu->args.rb);
}

// FSCALE
void LIIsaDtb_opcode2D_func07(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd *= ((Sint32)*m_cpu->args.rb)*2;
}

// FABS
void LIIsaDtb_opcode2D_func08(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = fabsf(*(Float32*)m_cpu->args.rd);
}

// FNEG
void LIIsaDtb_opcode2D_func09(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = -(*(Float32*)m_cpu->args.rd);
}

// FPOW
void LIIsaDtb_opcode2D_func0A(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = powf(*(Float32*)m_cpu->args.rd, *(Float32*)m_cpu->args.rb);
}

// FSQRT
void LIIsaDtb_opcode2D_func0B(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = sqrtf(*(Float32*)m_cpu->args.rb);
}

// FCBRT
void LIIsaDtb_opcode2D_func0C(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = powf(*(Float32*)m_cpu->args.rb, 1.f/3.f);
}

// FQTRT
void LIIsaDtb_opcode2D_func0D(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = powf(*(Float32*)m_cpu->args.rb, 1.f/4.f);
}

// FCINT
void LIIsaDtb_opcode2D_func0E(LCpu *m_cpu){
	*m_cpu->args.rd = *(Float32*)m_cpu->args.rb;
}

// FXAM
void LIIsaDtb_opcode2D_func0F(LCpu *m_cpu){
	switch(fpclassify(*(Float32*)m_cpu->args.rb)){
		case FP_ZERO:{
			*m_cpu->args.rd = 0;
		}
		break;
		case FP_NORMAL:{
			*m_cpu->args.rd = 1;
		}
		break;
		case FP_SUBNORMAL:{
			*m_cpu->args.rd = 2;
		}
		break;
		case FP_NAN:{
			*m_cpu->args.rd = 3;
		}
		break;
		case FP_INFINITE:{
			*m_cpu->args.rd = 4;
		}
		break;
		default:{
			*m_cpu->args.rd = -1;
		}
	}
}

// FLOG2
void LIIsaDtb_opcode2D_func10(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = log2f(*(Float32*)m_cpu->args.rb);
}

// FLOG10
void LIIsaDtb_opcode2D_func11(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = log10f(*(Float32*)m_cpu->args.rb);
}

// FSIN
void LIIsaDtb_opcode2D_func12(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = sinf(*(Float32*)m_cpu->args.rb);
}

// FCOS
void LIIsaDtb_opcode2D_func13(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = cosf(*(Float32*)m_cpu->args.rb);
}

// FTAN
void LIIsaDtb_opcode2D_func14(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = tanf(*(Float32*)m_cpu->args.rb);
}

// FASIN
void LIIsaDtb_opcode2D_func15(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = asinf(*(Float32*)m_cpu->args.rb);
}

// FACOS
void LIIsaDtb_opcode2D_func16(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = acosf(*(Float32*)m_cpu->args.rb);
}

// FATAN
void LIIsaDtb_opcode2D_func17(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = atanf(*(Float32*)m_cpu->args.rb);
}

// FATAN2
void LIIsaDtb_opcode2D_func18(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = atan2f(*(Float32*)m_cpu->args.rb, *(Float32*)m_cpu->args.rp);
}

// FFLR
void LIIsaDtb_opcode2D_func19(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = floorf(*(Float32*)m_cpu->args.rb);
}

// FRND
void LIIsaDtb_opcode2D_func1A(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = roundf(*(Float32*)m_cpu->args.rb);
}

// FCIL
void LIIsaDtb_opcode2D_func1B(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = ceilf(*(Float32*)m_cpu->args.rb);
}


// FCVUB
void LIIsaDtb_opcode2D_func38(LCpu *m_cpu){
	*m_cpu->args.rd = (Uint8)(*(Float32*)m_cpu->args.rd);
}

// FCVUW
void LIIsaDtb_opcode2D_func39(LCpu *m_cpu){
	*m_cpu->args.rd = (Uint16)(*(Float32*)m_cpu->args.rd);
}

// FCVUD
void LIIsaDtb_opcode2D_func3A(LCpu *m_cpu){
	*m_cpu->args.rd = (Uint32)(*(Float32*)m_cpu->args.rd);
}

// FCVB
void LIIsaDtb_opcode2D_func3B(LCpu *m_cpu){
	*m_cpu->args.rd = (Sint8)(*(Float32*)m_cpu->args.rd);
}

// FCVW
void LIIsaDtb_opcode2D_func3C(LCpu *m_cpu){
	*m_cpu->args.rd = (Sint16)(*(Float32*)m_cpu->args.rd);
}

// FCVD
void LIIsaDtb_opcode2D_func3D(LCpu *m_cpu){
	*m_cpu->args.rd = (Sint32)(*(Float32*)m_cpu->args.rd);
}

// FUDCV
void LIIsaDtb_opcode2D_func3E(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = (Uint32)(*m_cpu->args.rd);
}

// FDCV
void LIIsaDtb_opcode2D_func3F(LCpu *m_cpu){
	*(Float32*)m_cpu->args.rd = (Sint32)(*m_cpu->args.rd);
}


extern void (*LIIsaDtb_opcode2D[64])(LCpu *m_cpu) = {
	[0x00] = LIIsaDtb_opcode2D_func00,
	[0x01] = LIIsaDtb_opcode2D_func01,
	[0x02] = LIIsaDtb_opcode2D_func02,
	[0x03] = LIIsaDtb_opcode2D_func03,
	[0x04] = LIIsaDtb_opcode2D_func04,
	[0x05] = LIIsaDtb_opcode2D_func05,
	[0x06] = LIIsaDtb_opcode2D_func06,
	[0x07] = LIIsaDtb_opcode2D_func07,
	[0x08] = LIIsaDtb_opcode2D_func08,
	[0x09] = LIIsaDtb_opcode2D_func09,
	[0x0A] = LIIsaDtb_opcode2D_func0A,
	[0x0B] = LIIsaDtb_opcode2D_func0B,
	[0x0C] = LIIsaDtb_opcode2D_func0C,
	[0x0D] = LIIsaDtb_opcode2D_func0D,
	[0x0E] = LIIsaDtb_opcode2D_func0E,
	[0x0F] = LIIsaDtb_opcode2D_func0F,
	
	[0x10] = LIIsaDtb_opcode2D_func10,
	[0x11] = LIIsaDtb_opcode2D_func11,
	[0x12] = LIIsaDtb_opcode2D_func12,
	[0x13] = LIIsaDtb_opcode2D_func13,
	[0x14] = LIIsaDtb_opcode2D_func14,
	[0x15] = LIIsaDtb_opcode2D_func15,
	[0x16] = LIIsaDtb_opcode2D_func16,
	[0x17] = LIIsaDtb_opcode2D_func17,
	[0x18] = LIIsaDtb_opcode2D_func18,
	[0x19] = LIIsaDtb_opcode2D_func19,
	[0x1A] = LIIsaDtb_opcode2D_func1A,
	[0x1B] = LIIsaDtb_opcode2D_func1B,
	[0x1C] = LIIsaDtb_undefined,
	[0x1D] = LIIsaDtb_undefined,
	[0x1E] = LIIsaDtb_undefined,
	[0x1F] = LIIsaDtb_undefined,
	
	[0x20] = LIIsaDtb_undefined,
	[0x21] = LIIsaDtb_undefined,
	[0x22] = LIIsaDtb_undefined,
	[0x23] = LIIsaDtb_undefined,
	[0x24] = LIIsaDtb_undefined,
	[0x25] = LIIsaDtb_undefined,
	[0x26] = LIIsaDtb_undefined,
	[0x27] = LIIsaDtb_undefined,
	[0x28] = LIIsaDtb_undefined,
	[0x29] = LIIsaDtb_undefined,
	[0x2A] = LIIsaDtb_undefined,
	[0x2B] = LIIsaDtb_undefined,
	[0x2C] = LIIsaDtb_undefined,
	[0x2D] = LIIsaDtb_undefined,
	[0x2E] = LIIsaDtb_undefined,
	[0x2F] = LIIsaDtb_undefined,
	
	[0x30] = LIIsaDtb_undefined,
	[0x31] = LIIsaDtb_undefined,
	[0x32] = LIIsaDtb_undefined,
	[0x33] = LIIsaDtb_undefined,
	[0x34] = LIIsaDtb_undefined,
	[0x35] = LIIsaDtb_undefined,
	[0x36] = LIIsaDtb_undefined,
	[0x37] = LIIsaDtb_undefined,
	[0x38] = LIIsaDtb_opcode2D_func38,
	[0x39] = LIIsaDtb_opcode2D_func39,
	[0x3A] = LIIsaDtb_opcode2D_func3A,
	[0x3B] = LIIsaDtb_opcode2D_func3B,
	[0x3C] = LIIsaDtb_opcode2D_func3C,
	[0x3D] = LIIsaDtb_opcode2D_func3D,
	[0x3E] = LIIsaDtb_opcode2D_func3E,
	[0x3F] = LIIsaDtb_opcode2D_func3F,
};
