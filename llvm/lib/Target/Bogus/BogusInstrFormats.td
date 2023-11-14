class InstFormat<bits<3> val> {
  bits<3> Value = val;
}
def InstFormatPseudo : InstFormat<0>;
def InstFormatR      : InstFormat<1>;
def InstFormatRR      : InstFormat<2>;
def InstFormatI      : InstFormat<3>;

class BogusOpcode<bits<3> val> {bits<3> Value = val;}

def OPC_OP_IMM    : BogusOpcode<0b001>;
def OPC_OP_ADD    : BogusOpcode<0b010>;
def OPC_OP_RET : BogusOpcode< !add(0b101, !shl(0b1, 1)) >;

class BogusInstBase : Instruction {

  let Namespace = "Bogus";
  bits<32> Inst;
}
class BogusInst<InstFormat format, dag outs, dag ins> : BogusInstBase
{
  dag OutOperandList = outs;
  dag InOperandList = ins;

  let TSFlags{2-0} =  format.Value;

}

// Pseudo instructions
class Pseudo<dag outs, dag ins, list<dag> pattern>
    : BogusInst<InstFormatPseudo, outs, ins>,
      Sched<[]> {
  let Pattern = pattern;
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}

class NonPseudo<BogusOpcode opcode, InstFormat format, dag outs,
              dag ins, string opcodestr, string argstr>
    : BogusInst<format, outs, ins>{
  field bits<32> Inst;
  field bits<32> SoftFail = 0;
  let Size = 4;
  field BogusOpcode Opcode = opcode;
  let Inst{2-0} = Opcode.Value;

  let AsmString = "bogus-" # opcodestr # "\t" # argstr;
}

// Formats
class BogusInstR<BogusOpcode opcode, dag outs,
              dag ins, string opcodestr>
    : NonPseudo<opcode, InstFormatR, outs, ins, opcodestr, "${src0}">
{
field bits<5> src0;
let Inst{3-7} = src0;
}

class BogusInstRR<BogusOpcode opcode, dag outs,
              dag ins, string opcodestr>
    : NonPseudo<opcode, InstFormatR, outs, ins, opcodestr, "${src0}, ${src1}, ${dst0}">
{
field bits<5> src0;
field bits<5> src1;
field bits<5> dst0;
let Inst{3-7} = src0;
let Inst{8-12} = src1;
let Inst{13-17} = dst0;
}
class BogusInstI<BogusOpcode opcode, dag outs,
              dag ins, string opcodestr>
    : NonPseudo<opcode, InstFormatI, outs, ins, opcodestr, "${imm12}">
{
field bits<12> imm12;
let Inst{3-14} = imm12;
}
