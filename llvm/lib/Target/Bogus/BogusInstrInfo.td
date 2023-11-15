// Procedure return
def bogus_ret : SDNode<"BogusISD::Ret", SDTNone,
                       [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

// Procedure calling
def SDT_CallSeqStart : SDCallSeqStart<[SDTCisVT<0, i32>,
                                       SDTCisVT<1, i32>]>;
def SDT_CallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i32>,
                                    SDTCisVT<1, i32>]>;

// These are target-independent nodes, but have target-specific formats.
def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_CallSeqStart,
                           [SDNPHasChain, SDNPOutGlue]>;
def callseq_end   : SDNode<"ISD::CALLSEQ_END", SDT_CallSeqEnd,
                           [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

//===----------------------------------------------------------------------===//
// Operand and SDNode transformation definitions.
//===----------------------------------------------------------------------===//

class ImmAsmOperand<string prefix, int width, string suffix> : AsmOperandClass {
  let Name = prefix # "Imm" # width # suffix;
  //let RenderMethod = "addImmOperands";
  //let DiagnosticType = !strconcat("Invalid", Name);
}

// selection graph operand
def simm12 : Operand<i32>, ImmLeaf<i32, [{return isInt<12>(Imm);}]> {
  let ParserMatchClass = ImmAsmOperand<"S", 12, "">;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "DecodeSImmOperand";
  // let MCOperandPredicate = [{
  //   int64_t Imm;
  //   if (MCOp.evaluateAsConstantImm(Imm))
  //     return isInt<12>(Imm);
  //   return MCOp.isBareSymbolRef();
  // }];
  let OperandType = "OPERAND_CUSTOM_SIMM12";
  let OperandNamespace = "BogusOp";
}

//------------------------------------------------------===//
// Instruction Formats
//===----------------------------------------------------------------------===//

include "BogusInstrFormats.td"

//===----------------------------------------------------------------------===//
// Instructions
//===----------------------------------------------------------------------===//
class BogusInstNoOp<BogusOpcode opcode, string opcodestr>
    : NonPseudo<opcode, InstFormatR,  (outs), (ins), opcodestr, ""> {
  let Inst{31-0} = 1;
}

class BogusInstR<BogusOpcode opcode, string opcodestr>
    : NonPseudo<opcode, InstFormatR,  (outs), (ins GPR:$src0), opcodestr, "$src0"> {
  bits<5> src0;
  let Inst{7-3} = src0;
}

class BogusInstRR<BogusOpcode opcode, string opcodestr>
    : NonPseudo<opcode, InstFormatI, (outs GPR:$dst0), (ins GPR:$src0, GPR:$src1),
                opcodestr, "$src0, $src1, $dst0"> {
  bits<5> dst0;
  bits<5> src0;
  bits<5> src1;
  let Inst{17-13} = dst0;
  let Inst{12-8} = src1;
  let Inst{7-3} = src0;
  let Inst{31-18} = 0;
}

class BogusInstI<BogusOpcode opcode, string opcodestr>
    : NonPseudo<opcode, InstFormatI, (outs GPR:$src0), (ins simm12:$imm12),
                opcodestr, "$src0, $imm12"> {
  bits<5> src0;
  bits<12> imm12;
  let Inst{14-3} = imm12;
  let Inst{19-15} = src0;
}

def IMM : BogusInstI<OPC_OP_IMM, "imm">;

def ADD : BogusInstRR<OPC_OP_ADD, "add">;

/* Procedure calling instructions */
def RET : BogusInstNoOp<OPC_OP_RET, "ret">;

//===----------------------------------------------------------------------===//
// Assembler Pseudo Instructions (User-Level ISA)
//===----------------------------------------------------------------------===//

let isReturn = 1, isBarrier = 1, isTerminator = 1 in
def PseudoRET : Pseudo<(outs), (ins variable_ops), [(bogus_ret)]>,
                PseudoInstExpansion<(RET)>;

//===----------------------------------------------------------------------===//
// Pseudo-instructions and codegen patterns
//
//===----------------------------------------------------------------------===//

/// Generic pattern classes

// class PatGprGpr<SDPatternOperator OpNode, RWInst Inst>
//     : Pat<(OpNode GPR:$rs1, GPR:$rs2), (Inst GPR:$rs1, GPR:$rs2)>;
// class PatGprSimm12<SDPatternOperator OpNode, RWInstI Inst>
//     : Pat<(OpNode GPR:$rs1, simm12:$imm12), (Inst GPR:$rs1, simm12:$imm12)>;

// class PatGprGpr<SDPatternOperator OpNode, BogusInstR Inst>
//     : Pat<(OpNode GPR:$rs1, GPR:$rs2), (Inst GPR:$rs1, GPR:$rs2)>;
/// Immediates

def : Pat<(simm12:$imm), (IMM $imm)>;
/// Simple arithmetic operations

def : Pat<(add GPR:$rs1, GPR:$rs2), (ADD GPR:$rs1, GPR:$rs2)>;
