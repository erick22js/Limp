

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
        0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "wait", 0x1, LS_INSTRTYPE_SI,
        0, 1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "waiti", 0x1, LS_INSTRTYPE_SI,
        1, 1,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "waiti", 0x1, LS_INSTRTYPE_SI,
        2, 1,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "in", 0x1, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "out", 0x1, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "outi", 0x1, LS_INSTRTYPE_SI,
        1, 3,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0rr", 0x1, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1rr", 0x1, LS_INSTRTYPE_SI,
        0, 5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2rr", 0x1, LS_INSTRTYPE_SI,
        0, 6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3rr", 0x1, LS_INSTRTYPE_SI,
        0, 7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0wr", 0x1, LS_INSTRTYPE_SI,
        0, 8,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1wr", 0x1, LS_INSTRTYPE_SI,
        0, 9,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2wr", 0x1, LS_INSTRTYPE_SI,
        0, 10,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3wr", 0x1, LS_INSTRTYPE_SI,
        0, 11,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0di", 0x1, LS_INSTRTYPE_SI,
        0, 12,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1di", 0x1, LS_INSTRTYPE_SI,
        0, 13,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2di", 0x1, LS_INSTRTYPE_SI,
        2, 14,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3di", 0x1, LS_INSTRTYPE_SI,
        0, 15,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0en", 0x1, LS_INSTRTYPE_SI,
        0, 16,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1en", 0x1, LS_INSTRTYPE_SI,
        0, 17,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2en", 0x1, LS_INSTRTYPE_SI,
        0, 18,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3en", 0x1, LS_INSTRTYPE_SI,
        0, 19,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0chkst", 0x1, LS_INSTRTYPE_SI,
        0, 20,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1chkst", 0x1, LS_INSTRTYPE_SI,
        0, 21,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2chkst", 0x1, LS_INSTRTYPE_SI,
        0, 22,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3chkst", 0x1, LS_INSTRTYPE_SI,
        0, 23,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp0cmd", 0x1, LS_INSTRTYPE_SI,
        0, 24,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp1cmd", 0x1, LS_INSTRTYPE_SI,
        0, 25,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp2cmd", 0x1, LS_INSTRTYPE_SI,
        0, 26,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cp3cmd", 0x1, LS_INSTRTYPE_SI,
        0, 27,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "inup", 0x1, LS_INSTRTYPE_SI,
        0, 28,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "inus", 0x1, LS_INSTRTYPE_SI,
        1, 28,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvtit", 0x1, LS_INSTRTYPE_SI,
        0, 29,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvfit", 0x1, LS_INSTRTYPE_SI,
        1, 29,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvtst", 0x1, LS_INSTRTYPE_SI,
        0, 30,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvfst", 0x1, LS_INSTRTYPE_SI,
        1, 30,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvtsiv", 0x1, LS_INSTRTYPE_SI,
        0, 31,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvfsiv", 0x1, LS_INSTRTYPE_SI,
        1, 31,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stc", 0x2, LS_INSTRTYPE_SI,
        0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clc", 0x2, LS_INSTRTYPE_SI,
        0, 1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgc", 0x2, LS_INSTRTYPE_SI,
        0, 2,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stb", 0x2, LS_INSTRTYPE_SI,
        0, 3,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clb", 0x2, LS_INSTRTYPE_SI,
        0, 4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgb", 0x2, LS_INSTRTYPE_SI,
        0, 5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stv", 0x2, LS_INSTRTYPE_SI,
        0, 6,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clv", 0x2, LS_INSTRTYPE_SI,
        0, 7,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgv", 0x2, LS_INSTRTYPE_SI,
        0, 8,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stz", 0x2, LS_INSTRTYPE_SI,
        0, 9,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clz", 0x2, LS_INSTRTYPE_SI,
        0, 10,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgz", 0x2, LS_INSTRTYPE_SI,
        0, 11,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stn", 0x2, LS_INSTRTYPE_SI,
        0, 12,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cln", 0x2, LS_INSTRTYPE_SI,
        0, 13,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgn", 0x2, LS_INSTRTYPE_SI,
        0, 14,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "sto", 0x2, LS_INSTRTYPE_SI,
        0, 15,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clo", 0x2, LS_INSTRTYPE_SI,
        0, 16,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "tgo", 0x2, LS_INSTRTYPE_SI,
        0, 17,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enbi", 0x2, LS_INSTRTYPE_SI,
        0, 18,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "dsbi", 0x2, LS_INSTRTYPE_SI,
        0, 19,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enbv", 0x2, LS_INSTRTYPE_SI,
        0, 20,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "dsbv", 0x2, LS_INSTRTYPE_SI,
        0, 21,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popas", 0x3, LS_INSTRTYPE_SI,
        0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popss", 0x3, LS_INSTRTYPE_SI,
        0, 1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pops", 0x3, LS_INSTRTYPE_SI,
        0, 2,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshas", 0x3, LS_INSTRTYPE_SI,
        0, 3,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshss", 0x3, LS_INSTRTYPE_SI,
        0, 4,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshs", 0x3, LS_INSTRTYPE_SI,
        0, 5,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "popr", 0x4, LS_INSTRTYPE_IR,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmb", 0x6, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmw", 0x6, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmd", 0x7, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ldmq", 0x7, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "psh", 0x8, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "pshr", 0x8, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cmpeqst", 0x9, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cmpnest", 0x9, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strb", 0xA, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strw", 0xA, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strd", 0xB, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "strq", 0xB, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "stsi", 0xC, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stsd", 0xC, LS_INSTRTYPE_CDI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mmsi", 0xD, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mmsd", 0xD, LS_INSTRTYPE_CDI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGO, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "add", 0x10, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "adc", 0x10, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "sub", 0x11, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "sbb", 0x11, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mul", 0x12, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "hmul", 0x12, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "div", 0x13, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mod", 0x13, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "inc", 0x14, LS_INSTRTYPE_SI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "dec", 0x14, LS_INSTRTYPE_SI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "neg", 0x14, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "madd", 0x14, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "msub", 0x14, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "madc", 0x14, LS_INSTRTYPE_SI,
        0, 5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "msbb", 0x14, LS_INSTRTYPE_SI,
        0, 6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "ldiv", 0x14, LS_INSTRTYPE_SI,
        0, 7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "baa", 0x14, LS_INSTRTYPE_SI,
        0, 8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "aba", 0x14, LS_INSTRTYPE_SI,
        0, 9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cmp", 0x15, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cpb", 0x15, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "and", 0x18, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "or", 0x18, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "not", 0x19, LS_INSTRTYPE_SI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "setb", 0x19, LS_INSTRTYPE_SI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
        },
    },
    {
        "clrb", 0x19, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
        },
    },
    {
        "swap", 0x19, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "swapb", 0x19, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "test", 0x1A, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "bit", 0x1A, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "lshf", 0x1B, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "rshf", 0x1B, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fadd", 0x1C, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsub", 0x1C, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsteq", 0x1D, LS_INSTRTYPE_SI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstne", 0x1D, LS_INSTRTYPE_SI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstlt", 0x1D, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstgt", 0x1D, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstle", 0x1D, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstge", 0x1D, LS_INSTRTYPE_SI,
        0, 5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "fstezi", 0x1D, LS_INSTRTYPE_SI,
        0, 6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstnzi", 0x1D, LS_INSTRTYPE_SI,
        0, 7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstltzi", 0x1D, LS_INSTRTYPE_SI,
        0, 8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgtzi", 0x1D, LS_INSTRTYPE_SI,
        0, 9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstlezi", 0x1D, LS_INSTRTYPE_SI,
        0, 10,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgezi", 0x1D, LS_INSTRTYPE_SI,
        0, 11,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstez", 0x1D, LS_INSTRTYPE_SI,
        0, 12,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstnz", 0x1D, LS_INSTRTYPE_SI,
        0, 13,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstltz", 0x1D, LS_INSTRTYPE_SI,
        0, 14,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgtz", 0x1D, LS_INSTRTYPE_SI,
        0, 15,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstlez", 0x1D, LS_INSTRTYPE_SI,
        0, 16,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fstgez", 0x1D, LS_INSTRTYPE_SI,
        0, 17,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mov", 0x20, LS_INSTRTYPE_IR,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "movi", 0x20, LS_INSTRTYPE_IR,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvbw", 0x21, LS_INSTRTYPE_IR,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvbd", 0x21, LS_INSTRTYPE_IR,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvwd", 0x22, LS_INSTRTYPE_IR,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "cvwdi", 0x22, LS_INSTRTYPE_IR,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mv", 0x23, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xchg", 0x23, LS_INSTRTYPE_CDI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvrse", 0x24, LS_INSTRTYPE_SI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REGE},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REGS},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvres", 0x24, LS_INSTRTYPE_SI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REGS},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REGE},
            {0, 0},
            {0, 0},
        },
    },
    {
        "steq", 0x25, LS_INSTRTYPE_SI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stne", 0x25, LS_INSTRTYPE_SI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stlt", 0x25, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stgt", 0x25, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stle", 0x25, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stge", 0x25, LS_INSTRTYPE_SI,
        0, 5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stbl", 0x25, LS_INSTRTYPE_SI,
        0, 6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stab", 0x25, LS_INSTRTYPE_SI,
        0, 7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stbe", 0x25, LS_INSTRTYPE_SI,
        0, 8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stae", 0x25, LS_INSTRTYPE_SI,
        0, 9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
        },
    },
    {
        "stezi", 0x25, LS_INSTRTYPE_SI,
        0, 10,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stnzi", 0x25, LS_INSTRTYPE_SI,
        0, 11,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stltzi", 0x25, LS_INSTRTYPE_SI,
        0, 12,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgtzi", 0x25, LS_INSTRTYPE_SI,
        0, 13,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stlezi", 0x25, LS_INSTRTYPE_SI,
        0, 14,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgezi", 0x25, LS_INSTRTYPE_SI,
        0, 15,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stblzi", 0x25, LS_INSTRTYPE_SI,
        0, 16,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stabzi", 0x25, LS_INSTRTYPE_SI,
        0, 17,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stbezi", 0x25, LS_INSTRTYPE_SI,
        0, 18,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "staezi", 0x25, LS_INSTRTYPE_SI,
        0, 19,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stez", 0x25, LS_INSTRTYPE_SI,
        0, 20,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stnz", 0x25, LS_INSTRTYPE_SI,
        0, 21,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stltz", 0x25, LS_INSTRTYPE_SI,
        0, 22,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgtz", 0x25, LS_INSTRTYPE_SI,
        0, 23,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stlez", 0x25, LS_INSTRTYPE_SI,
        0, 24,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stgez", 0x25, LS_INSTRTYPE_SI,
        0, 25,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stblz", 0x25, LS_INSTRTYPE_SI,
        0, 26,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stabz", 0x25, LS_INSTRTYPE_SI,
        0, 27,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "stbez", 0x25, LS_INSTRTYPE_SI,
        0, 28,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "staez", 0x25, LS_INSTRTYPE_SI,
        0, 29,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "mvfc", 0x26, LS_INSTRTYPE_IR,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "mvtc", 0x26, LS_INSTRTYPE_IR,
        1, 0,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xor", 0x28, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "nand", 0x28, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "lrot", 0x2B, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "rrot", 0x2B, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_AMD, LS_ARGVALUE_AMD},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fmul", 0x2C, LS_INSTRTYPE_AMI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fdiv", 0x2C, LS_INSTRTYPE_AMI,
        1, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fadc", 0x2D, LS_INSTRTYPE_SI,
        0, 0,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsbb", 0x2D, LS_INSTRTYPE_SI,
        0, 1,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fmadd", 0x2D, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmadc", 0x2D, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmsub", 0x2D, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmsbb", 0x2D, LS_INSTRTYPE_SI,
        0, 5,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fmod", 0x2D, LS_INSTRTYPE_SI,
        0, 6,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fscale", 0x2D, LS_INSTRTYPE_SI,
        0, 7,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fabs", 0x2D, LS_INSTRTYPE_SI,
        0, 8,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fneg", 0x2D, LS_INSTRTYPE_SI,
        0, 9,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fpow", 0x2D, LS_INSTRTYPE_SI,
        0, 10,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsqrt", 0x2D, LS_INSTRTYPE_SI,
        0, 11,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcbrt", 0x2D, LS_INSTRTYPE_SI,
        0, 12,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fqtrt", 0x2D, LS_INSTRTYPE_SI,
        0, 13,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcint", 0x2D, LS_INSTRTYPE_SI,
        0, 14,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fxam", 0x2D, LS_INSTRTYPE_SI,
        0, 15,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "flog2", 0x2D, LS_INSTRTYPE_SI,
        0, 16,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "flog10", 0x2D, LS_INSTRTYPE_SI,
        0, 17,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fsin", 0x2D, LS_INSTRTYPE_SI,
        0, 18,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcos", 0x2D, LS_INSTRTYPE_SI,
        0, 19,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ftan", 0x2D, LS_INSTRTYPE_SI,
        0, 20,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fasin", 0x2D, LS_INSTRTYPE_SI,
        0, 21,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "facos", 0x2D, LS_INSTRTYPE_SI,
        0, 22,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fatan", 0x2D, LS_INSTRTYPE_SI,
        0, 23,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fatan2", 0x2D, LS_INSTRTYPE_SI,
        0, 24,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
        },
    },
    {
        "fflr", 0x2D, LS_INSTRTYPE_SI,
        0, 25,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "frnd", 0x2D, LS_INSTRTYPE_SI,
        0, 26,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcil", 0x2D, LS_INSTRTYPE_SI,
        0, 27,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvub", 0x2D, LS_INSTRTYPE_SI,
        0, 56,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvuw", 0x2D, LS_INSTRTYPE_SI,
        0, 57,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvud", 0x2D, LS_INSTRTYPE_SI,
        0, 58,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvb", 0x2D, LS_INSTRTYPE_SI,
        0, 59,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvw", 0x2D, LS_INSTRTYPE_SI,
        0, 60,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fcvd", 0x2D, LS_INSTRTYPE_SI,
        0, 61,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fudcv", 0x2D, LS_INSTRTYPE_SI,
        0, 62,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "fdcv", 0x2D, LS_INSTRTYPE_SI,
        0, 63,
        {
            {LS_ARGNAME_REGD, LS_ARGVALUE_REG},
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ja", 0x30, LS_INSTRTYPE_ADI,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ba", 0x30, LS_INSTRTYPE_ADI,
        1, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "ret", 0x31, LS_INSTRTYPE_SI,
        0, 0,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "iret", 0x31, LS_INSTRTYPE_SI,
        0, 1,
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enter", 0x31, LS_INSTRTYPE_SI,
        0, 2,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "enterv", 0x31, LS_INSTRTYPE_SI,
        1, 2,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "leave", 0x31, LS_INSTRTYPE_SI,
        0, 3,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "int", 0x31, LS_INSTRTYPE_SI,
        0, 4,
        {
            {LS_ARGNAME_IMM, LS_ARGVALUE_IMM8},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jra", 0x32, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "bra", 0x32, LS_INSTRTYPE_CDI,
        1, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jrr", 0x33, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "brr", 0x33, LS_INSTRTYPE_CDI,
        1, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jl", 0x34, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "bl", 0x35, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jlp", 0x36, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "blp", 0x37, LS_INSTRTYPE_JL,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jr", 0x38, LS_INSTRTYPE_ADI,
        0, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "br", 0x38, LS_INSTRTYPE_ADI,
        1, 0,
        {
            {LS_ARGNAME_IMM|LS_ARGNAME_SHIFT2R, LS_ARGVALUE_IMM},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "jrap", 0x3A, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "brap", 0x3A, LS_INSTRTYPE_CDI,
        1, 0,
        {
            {LS_ARGNAME_REGP, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xjp", 0x3B, LS_INSTRTYPE_CDI,
        0, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
    {
        "xbr", 0x3B, LS_INSTRTYPE_CDI,
        1, 0,
        {
            {LS_ARGNAME_REGB, LS_ARGVALUE_REG},
            {0, 0},
            {0, 0},
            {0, 0},
        },
    },
};