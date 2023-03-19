var fs = require("fs");

const raw = fs.readFileSync("docs.json", {encoding:'utf8', flag:'r'});
var obj = JSON.parse(raw);

var src = "\n\nLSMnemonic lsdb_mnemonics[] = {\n";
var mnes = "";


function type_by_ta(ta){
	switch(ta){
		case "regd":
			return "LS_ARGNAME_REGD";
		case "regb":
			return "LS_ARGNAME_REGB";
		case "regi":
			return "LS_ARGNAME_REGI";
		case "regp":
			return "LS_ARGNAME_REGP";
		case "rego":
			return "LS_ARGNAME_REGO";
		case "$amd":
			return "LS_ARGNAME_AMD";
		default:
			return "LS_ARGNAME_IMM"+(ta.substr(-2)=="<2"?"|LS_ARGNAME_SHIFT2R":"");
	}
}

function value_by_ta(ta){
	switch(ta){
		case "regd":
		case "regb":
		case "regi":
		case "regp":
		case "rego":
			return "LS_ARGVALUE_REG";
		case "$amd":
			return "LS_ARGVALUE_AMD";
		default:
			ta = ta.substr(0, 4);
			if(ta=="imm8"){
				return "LS_ARGVALUE_IMM8";
			}
			else if(ta=="imm16"){
				return "LS_ARGVALUE_IMM16";
			}
			else if(ta=="imm32"){
				return "LS_ARGVALUE_IMM32";
			}
			return "LS_ARGVALUE_IMM";
	}
}


for(var opcode in obj){
	var opc = obj[opcode];
	
	if(opc["varyants"]!=null){
		for(var mi=0; mi<opc["varyants"].length; mi++){
			var mne = opc["varyants"][mi];
			mnes += mne["mnemonic"].toLowerCase()+"\n";
			src +=
`    {
        "`+mne["mnemonic"].toLowerCase()+`", 0x`+opcode.substr(2, 3).toUpperCase()+`, LS_INSTRTYPE_`+opc["format"]+`,
        `+(mne["mode"]!=null?"0x"+mne["mode"]:"0")+`, `+(mne["func"]!=null?"0x"+mne["func"]:"0")+`,
        {`
			for(var ai=0; ai<4; ai++){
				var arg = mne["args"]&&mne["args"][ai]?mne["args"][ai]:null;
				src += `
            {`+(arg?type_by_ta(arg):0)+`, `+(arg?value_by_ta(arg):0)+`},`;
			}
			src +=
`
        },
    },\n`;
			//opc["varyants"][mi]["mnemonic"]+"\n";
		}
	}
	
};

src += "};";


fs.writeFileSync("LimpAssembler/src/instructions.h", src);
fs.writeFileSync("mnemonics.h", mnes);