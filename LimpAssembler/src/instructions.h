

LSMnemonic lsdb_mnemonics[] = {
    {
        "nop", 0x0, LS_INSTRTYPE_JL,
        0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "halt", 0x1, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "wait", 0x1, LS_INSTRTYPE_SI,
        0x0, 0x1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "waiti", 0x1, LS_INSTRTYPE_SI,
        0x1, 0x1,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "waiti", 0x1, LS_INSTRTYPE_SI,
        0x2, 0x1,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popas", 0x3, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popss", 0x3, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pops", 0x3, LS_INSTRTYPE_IR,
        0x2, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popr", 0x4, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popp", 0x4, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmb", 0x7, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmw", 0x7, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmd", 0x7, LS_INSTRTYPE_AMI,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmq", 0x7, LS_INSTRTYPE_AMI,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "in", 0x8, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "out", 0x8, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0rr", 0x8, LS_INSTRTYPE_SI,
        0x0, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1rr", 0x8, LS_INSTRTYPE_SI,
        0x1, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2rr", 0x8, LS_INSTRTYPE_SI,
        0x2, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3rr", 0x8, LS_INSTRTYPE_SI,
        0x3, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0wr", 0x8, LS_INSTRTYPE_SI,
        0x0, 0x3,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1wr", 0x8, LS_INSTRTYPE_SI,
        0x1, 0x3,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2wr", 0x8, LS_INSTRTYPE_SI,
        0x2, 0x3,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3wr", 0x8, LS_INSTRTYPE_SI,
        0x3, 0x3,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0di", 0x8, LS_INSTRTYPE_SI,
        0x0, 0x4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1di", 0x8, LS_INSTRTYPE_SI,
        0x1, 0x4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2di", 0x8, LS_INSTRTYPE_SI,
        0x2, 0x4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3di", 0x8, LS_INSTRTYPE_SI,
        0x3, 0x4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0en", 0x8, LS_INSTRTYPE_SI,
        0x0, 0x5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1en", 0x8, LS_INSTRTYPE_SI,
        0x1, 0x5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2en", 0x8, LS_INSTRTYPE_SI,
        0x2, 0x5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3en", 0x8, LS_INSTRTYPE_SI,
        0x3, 0x5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0chkst", 0x8, LS_INSTRTYPE_SI,
        0x0, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1chkst", 0x8, LS_INSTRTYPE_SI,
        0x1, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2chkst", 0x8, LS_INSTRTYPE_SI,
        0x2, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3chkst", 0x8, LS_INSTRTYPE_SI,
        0x3, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0cmd", 0x8, LS_INSTRTYPE_SI,
        0x0, 0x7,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1cmd", 0x8, LS_INSTRTYPE_SI,
        0x1, 0x7,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2cmd", 0x8, LS_INSTRTYPE_SI,
        0x2, 0x7,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3cmd", 0x8, LS_INSTRTYPE_SI,
        0x3, 0x7,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "inup", 0x8, LS_INSTRTYPE_SI,
        0, 0x8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshas", 0xB, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshss", 0xB, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshs", 0xB, LS_INSTRTYPE_IR,
        0x2, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshi", 0xC, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshr", 0xC, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshp", 0xC, LS_INSTRTYPE_IR,
        0x2, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stsi", 0xE, LS_INSTRTYPE_CDI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stsd", 0xE, LS_INSTRTYPE_CDI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mmsi", 0xE, LS_INSTRTYPE_CDI,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mmsd", 0xE, LS_INSTRTYPE_CDI,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "strb", 0xF, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strw", 0xF, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strd", 0xF, LS_INSTRTYPE_AMI,
        0x2, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strq", 0xF, LS_INSTRTYPE_AMI,
        0x3, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "add", 0x10, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "adc", 0x10, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "sub", 0x10, LS_INSTRTYPE_AMI,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "sbb", 0x10, LS_INSTRTYPE_AMI,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mul", 0x11, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "hmul", 0x11, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "div", 0x11, LS_INSTRTYPE_AMI,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mod", 0x11, LS_INSTRTYPE_AMI,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "inc", 0x14, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "dec", 0x14, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "neg", 0x14, LS_INSTRTYPE_SI,
        0, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "madd", 0x14, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "msub", 0x14, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "madc", 0x14, LS_INSTRTYPE_SI,
        0, 0x5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "msbb", 0x14, LS_INSTRTYPE_SI,
        0, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "ldiv", 0x14, LS_INSTRTYPE_SI,
        0, 0x7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "baa", 0x14, LS_INSTRTYPE_SI,
        0, 0x8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "aba", 0x14, LS_INSTRTYPE_SI,
        0, 0x9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cmp", 0x15, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cpb", 0x15, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "and", 0x18, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "or", 0x18, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xor", 0x18, LS_INSTRTYPE_AMI,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "nand", 0x18, LS_INSTRTYPE_AMI,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "not", 0x19, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "setb", 0x19, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clrb", 0x19, LS_INSTRTYPE_SI,
        0, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
        },
    },
    {
        "swap", 0x19, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "swapb", 0x19, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "test", 0x1A, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "bit", 0x1A, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "lshf", 0x1B, LS_INSTRTYPE_AMI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "rshf", 0x1B, LS_INSTRTYPE_AMI,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "lrot", 0x1B, LS_INSTRTYPE_AMI,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "rrot", 0x1B, LS_INSTRTYPE_AMI,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fadd", 0x1C, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fadc", 0x1C, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsub", 0x1C, LS_INSTRTYPE_SI,
        0, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsbb", 0x1C, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fmul", 0x1C, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fmadd", 0x1C, LS_INSTRTYPE_SI,
        0, 0x5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmadc", 0x1C, LS_INSTRTYPE_SI,
        0, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmsub", 0x1C, LS_INSTRTYPE_SI,
        0, 0x7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmsbb", 0x1C, LS_INSTRTYPE_SI,
        0, 0x8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fdiv", 0x1C, LS_INSTRTYPE_SI,
        0, 0x9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fmod", 0x1C, LS_INSTRTYPE_SI,
        0, 0x10,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fscale", 0x1C, LS_INSTRTYPE_SI,
        0, 0x11,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fabs", 0x1C, LS_INSTRTYPE_SI,
        0, 0x12,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fneg", 0x1C, LS_INSTRTYPE_SI,
        0, 0x13,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fpow", 0x1C, LS_INSTRTYPE_SI,
        0, 0x14,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsqrt", 0x1C, LS_INSTRTYPE_SI,
        0, 0x15,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcbrt", 0x1C, LS_INSTRTYPE_SI,
        0, 0x16,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fqtrt", 0x1C, LS_INSTRTYPE_SI,
        0, 0x17,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcint", 0x1C, LS_INSTRTYPE_SI,
        0, 0x18,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fxam", 0x1C, LS_INSTRTYPE_SI,
        0, 0x19,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "flog2", 0x1C, LS_INSTRTYPE_SI,
        0, 0x20,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "flog10", 0x1C, LS_INSTRTYPE_SI,
        0, 0x21,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsin", 0x1C, LS_INSTRTYPE_SI,
        0, 0x22,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcos", 0x1C, LS_INSTRTYPE_SI,
        0, 0x23,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ftan", 0x1C, LS_INSTRTYPE_SI,
        0, 0x24,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fasin", 0x1C, LS_INSTRTYPE_SI,
        0, 0x25,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "facos", 0x1C, LS_INSTRTYPE_SI,
        0, 0x26,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fatan", 0x1C, LS_INSTRTYPE_SI,
        0, 0x27,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fatan2", 0x1C, LS_INSTRTYPE_SI,
        0, 0x28,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fflr", 0x1C, LS_INSTRTYPE_SI,
        0, 0x29,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "frnd", 0x1C, LS_INSTRTYPE_SI,
        0, 0x30,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcil", 0x1C, LS_INSTRTYPE_SI,
        0, 0x31,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvub", 0x1C, LS_INSTRTYPE_SI,
        0, 0x56,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvuw", 0x1C, LS_INSTRTYPE_SI,
        0, 0x57,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvud", 0x1C, LS_INSTRTYPE_SI,
        0, 0x58,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvb", 0x1C, LS_INSTRTYPE_SI,
        0, 0x59,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvw", 0x1C, LS_INSTRTYPE_SI,
        0, 0x60,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvd", 0x1C, LS_INSTRTYPE_SI,
        0, 0x61,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fudcv", 0x1C, LS_INSTRTYPE_SI,
        0, 0x62,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fdcv", 0x1C, LS_INSTRTYPE_SI,
        0, 0x63,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsteq", 0x1D, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstne", 0x1D, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstlt", 0x1D, LS_INSTRTYPE_SI,
        0, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstgt", 0x1D, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstle", 0x1D, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstge", 0x1D, LS_INSTRTYPE_SI,
        0, 0x5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstezi", 0x1D, LS_INSTRTYPE_SI,
        0, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstnzi", 0x1D, LS_INSTRTYPE_SI,
        0, 0x7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstltzi", 0x1D, LS_INSTRTYPE_SI,
        0, 0x8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgtzi", 0x1D, LS_INSTRTYPE_SI,
        0, 0x9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstlezi", 0x1D, LS_INSTRTYPE_SI,
        0, 0x10,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgezi", 0x1D, LS_INSTRTYPE_SI,
        0, 0x11,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstez", 0x1D, LS_INSTRTYPE_SI,
        0, 0x12,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstnz", 0x1D, LS_INSTRTYPE_SI,
        0, 0x13,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstltz", 0x1D, LS_INSTRTYPE_SI,
        0, 0x14,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgtz", 0x1D, LS_INSTRTYPE_SI,
        0, 0x15,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstlez", 0x1D, LS_INSTRTYPE_SI,
        0, 0x16,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgez", 0x1D, LS_INSTRTYPE_SI,
        0, 0x17,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "ja", 0x20, LS_INSTRTYPE_ADI,
        0x0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ba", 0x20, LS_INSTRTYPE_ADI,
        0x1, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jr", 0x20, LS_INSTRTYPE_ADI,
        0x2, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "br", 0x20, LS_INSTRTYPE_ADI,
        0x3, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ret", 0x21, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "iret", 0x21, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enter", 0x21, LS_INSTRTYPE_SI,
        0x0, 0x2,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enterv", 0x21, LS_INSTRTYPE_SI,
        0x1, 0x2,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "leave", 0x21, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "int", 0x21, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jra", 0x22, LS_INSTRTYPE_CDI,
        0x0, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "bra", 0x22, LS_INSTRTYPE_CDI,
        0x1, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jrap", 0x22, LS_INSTRTYPE_CDI,
        0x2, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "brap", 0x22, LS_INSTRTYPE_CDI,
        0x3, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jrr", 0x23, LS_INSTRTYPE_CDI,
        0x0, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "brr", 0x23, LS_INSTRTYPE_CDI,
        0x1, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xjp", 0x23, LS_INSTRTYPE_CDI,
        0x2, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xbr", 0x23, LS_INSTRTYPE_CDI,
        0x3, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jl", 0x24, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "bl", 0x25, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jlp", 0x26, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "blp", 0x27, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mov", 0x30, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "movi", 0x30, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvbw", 0x31, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvbd", 0x31, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvwd", 0x31, LS_INSTRTYPE_IR,
        0x2, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvwdi", 0x31, LS_INSTRTYPE_IR,
        0x3, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mv", 0x32, LS_INSTRTYPE_CDI,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xchg", 0x33, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "steq", 0x34, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stne", 0x34, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stlt", 0x34, LS_INSTRTYPE_SI,
        0, 0x2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stgt", 0x34, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stle", 0x34, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stge", 0x34, LS_INSTRTYPE_SI,
        0, 0x5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stbl", 0x34, LS_INSTRTYPE_SI,
        0, 0x6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stab", 0x34, LS_INSTRTYPE_SI,
        0, 0x7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stbe", 0x34, LS_INSTRTYPE_SI,
        0, 0x8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stae", 0x34, LS_INSTRTYPE_SI,
        0, 0x9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stezi", 0x34, LS_INSTRTYPE_SI,
        0, 0x10,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stnzi", 0x34, LS_INSTRTYPE_SI,
        0, 0x11,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stltzi", 0x34, LS_INSTRTYPE_SI,
        0, 0x12,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgtzi", 0x34, LS_INSTRTYPE_SI,
        0, 0x13,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stlezi", 0x34, LS_INSTRTYPE_SI,
        0, 0x14,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgezi", 0x34, LS_INSTRTYPE_SI,
        0, 0x15,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stblzi", 0x34, LS_INSTRTYPE_SI,
        0, 0x16,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stabzi", 0x34, LS_INSTRTYPE_SI,
        0, 0x17,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stbezi", 0x34, LS_INSTRTYPE_SI,
        0, 0x18,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "staezi", 0x34, LS_INSTRTYPE_SI,
        0, 0x19,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stez", 0x34, LS_INSTRTYPE_SI,
        0, 0x20,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stnz", 0x34, LS_INSTRTYPE_SI,
        0, 0x21,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stltz", 0x34, LS_INSTRTYPE_SI,
        0, 0x22,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgtz", 0x34, LS_INSTRTYPE_SI,
        0, 0x23,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stlez", 0x34, LS_INSTRTYPE_SI,
        0, 0x24,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgez", 0x34, LS_INSTRTYPE_SI,
        0, 0x25,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stblz", 0x34, LS_INSTRTYPE_SI,
        0, 0x26,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stabz", 0x34, LS_INSTRTYPE_SI,
        0, 0x27,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stbez", 0x34, LS_INSTRTYPE_SI,
        0, 0x28,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "staez", 0x34, LS_INSTRTYPE_SI,
        0, 0x29,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mvfr", 0x35, LS_INSTRTYPE_IR,
        0x0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvtr", 0x35, LS_INSTRTYPE_IR,
        0x1, 0,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stc", 0x38, LS_INSTRTYPE_SI,
        0, 0x0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clc", 0x38, LS_INSTRTYPE_SI,
        0, 0x1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgc", 0x38, LS_INSTRTYPE_SI,
        0, 0x2,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stb", 0x38, LS_INSTRTYPE_SI,
        0, 0x3,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clb", 0x38, LS_INSTRTYPE_SI,
        0, 0x4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgb", 0x38, LS_INSTRTYPE_SI,
        0, 0x5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stv", 0x38, LS_INSTRTYPE_SI,
        0, 0x6,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clv", 0x38, LS_INSTRTYPE_SI,
        0, 0x7,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgv", 0x38, LS_INSTRTYPE_SI,
        0, 0x8,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stz", 0x38, LS_INSTRTYPE_SI,
        0, 0x9,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clz", 0x38, LS_INSTRTYPE_SI,
        0, 0x10,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgz", 0x38, LS_INSTRTYPE_SI,
        0, 0x11,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stn", 0x38, LS_INSTRTYPE_SI,
        0, 0x12,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cln", 0x38, LS_INSTRTYPE_SI,
        0, 0x13,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgn", 0x38, LS_INSTRTYPE_SI,
        0, 0x14,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "sto", 0x38, LS_INSTRTYPE_SI,
        0, 0x15,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clo", 0x38, LS_INSTRTYPE_SI,
        0, 0x16,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgo", 0x38, LS_INSTRTYPE_SI,
        0, 0x17,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enbi", 0x38, LS_INSTRTYPE_SI,
        0, 0x18,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "dsbi", 0x38, LS_INSTRTYPE_SI,
        0, 0x19,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enbv", 0x38, LS_INSTRTYPE_SI,
        0, 0x20,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "dsbv", 0x38, LS_INSTRTYPE_SI,
        0, 0x21,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
};