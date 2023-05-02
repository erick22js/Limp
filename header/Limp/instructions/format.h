#ifndef limp_instructions_format_h
#define limp_instructions_format_h

#include <Limp/api.h>


/**
	INSTRUCTION DECODING FUNCTIONS
*/


#define LIDFmt_baseOpcode(fdt) ((fdt>>26)&0x3F)


/* IR */

#define LIDFmt_IR_selector(fdt) ((fdt>>25)&0x1)
#define LIDFmt_IR_mod(fdt) ((fdt>>24)&0x1)
#define LIDFmt_IR_im(fdt) ((fdt>>22)&0x3)
#define LIDFmt_IR_regd(fdt) ((fdt>>19)&0x7)
#define LIDFmt_IR_regb(fdt) ((fdt>>16)&0x7)
#define LIDFmt_IR_imm(fdt) (fdt&0xFFFF)


/* AMI */

#define LIDFmt_AMI_selector(fdt) ((fdt>>25)&0x1)
#define LIDFmt_AMI_mod(fdt) ((fdt>>24)&0x1)
#define LIDFmt_AMI_adrm(fdt) ((fdt>>20)&0xF)
#define LIDFmt_AMI_dsize(fdt) ((fdt>>18)&0x3)
#define LIDFmt_AMI_f(fdt) ((fdt>>17)&0x1)
#define LIDFmt_AMI_regd(fdt) ((fdt>>14)&0x7)
#define LIDFmt_AMI_regi(fdt) ((fdt>>11)&0x7)
#define LIDFmt_AMI_regb(fdt) ((fdt>>8)&0x7)
#define LIDFmt_AMI_imm(fdt) (fdt&0xFF)


/* SI */

#define LIDFmt_SI_selector(fdt) ((fdt>>25)&0x1)
#define LIDFmt_SI_mod(fdt) ((fdt>>24)&0x1)
#define LIDFmt_SI_func(fdt) ((fdt>>18)&0x3F)
#define LIDFmt_SI_f(fdt) ((fdt>>17)&0x1)
#define LIDFmt_SI_regd(fdt) ((fdt>>14)&0x7)
#define LIDFmt_SI_regp(fdt) ((fdt>>11)&0x7)
#define LIDFmt_SI_regb(fdt) ((fdt>>8)&0x7)
#define LIDFmt_SI_imm(fdt) (fdt&0xFF)


/* ADI */

#define LIDFmt_ADI_selector(fdt) ((fdt>>25)&0x1)
#define LIDFmt_ADI_mod(fdt) ((fdt>>24)&0x1)
#define LIDFmt_ADI_cond(fdt) ((fdt>>19)&0x1F)
#define LIDFmt_ADI_rego(fdt) ((fdt>>16)&0x7)
#define LIDFmt_ADI_imm(fdt) (fdt&0xFFFF)


/* CDI */

#define LIDFmt_CDI_selector(fdt) ((fdt>>25)&0x1)
#define LIDFmt_CDI_mod(fdt) ((fdt>>24)&0x1)
#define LIDFmt_CDI_cond(fdt) ((fdt>>19)&0x1F)
#define LIDFmt_CDI_oselector(fdt) ((fdt>>18)&0x1)
#define LIDFmt_CDI_f(fdt) ((fdt>>17)&0x1)
#define LIDFmt_CDI_regd(fdt) ((fdt>>14)&0x7)
#define LIDFmt_CDI_rego(fdt) ((fdt>>11)&0x7)
#define LIDFmt_CDI_regb(fdt) ((fdt>>8)&0x7)
#define LIDFmt_CDI_imm(fdt) (fdt&0xFF)


/* JL */

#define LIDFmt_JL_imm(fdt) (fdt&0x3FFFFFF)



#endif // limp_instructions_format_h
