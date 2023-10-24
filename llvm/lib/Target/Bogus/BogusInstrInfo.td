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
  let RenderMethod = "addImmOperands";
  let DiagnosticType = !strconcat("Invalid", Name);
}

class SImmAsmOperand<int width, string suffix = "">
    : ImmAsmOperand<"S", width, suffix> {
}

class UImmAsmOperand<int width, string suffix = "">
    : ImmAsmOperand<"U", width, suffix> {
}

def UImmLog2WSizeAsmOperand : AsmOperandClass {
  let Name = "UImmLog2WSize";
  let RenderMethod = "addImmOperands";
  let DiagnosticType = "InvalidUImmLog2WSize";
}

def uimmlog2wsize : Operand<i32>, ImmLeaf<i32, [{
  return isUInt<5>(Imm);
}]> {
  let ParserMatchClass = UImmLog2WSizeAsmOperand;
  // TODO: should ensure invalid shamt is rejected when decoding.
  let DecoderMethod = "decodeUImmOperand<5>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (!MCOp.evaluateAsConstantImm(Imm))
      return false;
    return isUInt<5>(Imm);
  }];
  let OperandType = "OPERAND_UIMMLOG2WSIZE";
  let OperandNamespace = "BogusOp";
}

def simm12 : Operand<i32>, ImmLeaf<i32, [{return isInt<12>(Imm);}]> {
  let ParserMatchClass = SImmAsmOperand<12>;
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeSImmOperand<12>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isInt<12>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_SIMM12";
  let OperandNamespace = "BogusOp";
}

class UImm20Operand : Operand<i32> {
  let EncoderMethod = "getImmOpValue";
  let DecoderMethod = "decodeUImmOperand<20>";
  let MCOperandPredicate = [{
    int64_t Imm;
    if (MCOp.evaluateAsConstantImm(Imm))
      return isUInt<20>(Imm);
    return MCOp.isBareSymbolRef();
  }];
  let OperandType = "OPERAND_UIMM20";
  let OperandNamespace = "BogusOp";
}

def uimm20_lui : UImm20Operand {
  let ParserMatchClass = UImmAsmOperand<20, "LUI">;
}
def uimm20_auipc : UImm20Operand {
  let ParserMatchClass = UImmAsmOperand<20, "AUIPC">;
}

// Standalone (codegen-only) immleaf patterns.
def simm32     : ImmLeaf<i32, [{return isInt<32>(Imm);}]>;
def simm32hi20 : ImmLeaf<i32, [{return isShiftedInt<20, 12>(Imm);}]>;
// A mask value that won't affect significant shift bits.
def immbottomwsizeset : ImmLeaf<i32, [{
  return maskTrailingOnes<uint64_t>(Imm) >= 5;
}]>;

// Extract least significant 12 bits from an immediate value and sign extend
// them.
def LO12Sext : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant(SignExtend64<12>(N->getZExtValue()),
                                   SDLoc(N), N->getValueType(0));
}]>;

// Extract the most significant 20 bits from an immediate value. Add 1 if bit
// 11 is 1, to compensate for the low 12 bits in the matching immediate addi
// or ld/st being negative.
def HI20 : SDNodeXForm<imm, [{
  return CurDAG->getTargetConstant(((N->getZExtValue()+0x800) >> 12) & 0xfffff,
                                   SDLoc(N), N->getValueType(0));
}]>;

//===----------------------------------------------------------------------===//
// Instruction Formats
//===----------------------------------------------------------------------===//

include "BogusInstrFormats.td"

//===----------------------------------------------------------------------===//
// Instruction Class Templates
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class ALU_ri<bits<3> funct3, string opcodestr>
    : RWInstI<funct3, OPC_OP_IMM, (outs GPR:$rd), (ins GPR:$rs1, simm12:$imm12),
              opcodestr, "$rd, $rs1, $imm12">,
      Sched<[WriteIALU, ReadIALU]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class Shift_ri<bit arithshift, bits<3> funct3, string opcodestr>
    : RWInstIShift<arithshift, funct3, OPC_OP_IMM, (outs GPR:$rd),
                   (ins GPR:$rs1, uimmlog2wsize:$shamt), opcodestr,
                   "$rd, $rs1, $shamt">,
      Sched<[WriteShift, ReadShift]>;

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in
class ALU_rr<bits<7> funct7, bits<3> funct3, string opcodestr>
    : RWInstR<funct7, funct3, OPC_OP, (outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
              opcodestr, "$rd, $rs1, $rs2">;

//===----------------------------------------------------------------------===//
// Instructions
//===----------------------------------------------------------------------===//

let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {
let isReMaterializable = 1, isAsCheapAsAMove = 1 in
def LUI : RWInstU<OPC_LUI, (outs GPR:$rd), (ins uimm20_lui:$imm20),
                  "lui", "$rd, $imm20">, Sched<[WriteIALU]>;

def AUIPC : RWInstU<OPC_AUIPC, (outs GPR:$rd), (ins uimm20_auipc:$imm20),
                    "auipc", "$rd, $imm20">, Sched<[WriteIALU]>;
} // hasSideEffects = 0, mayLoad = 0, mayStore = 0

def ADDI  : ALU_ri<0b000, "addi">;

def ANDI  : ALU_ri<0b111, "andi">;

def ADD  : ALU_rr<0b0000000, 0b000, "add">, Sched<[WriteIALU, ReadIALU, ReadIALU]>;

/* Procedure calling instructions */
let hasSideEffects = 0, mayLoad = 0, mayStore = 0 in {
let isCall = 1 in
def JALR : RWInstI<0b000, OPC_JALR, (outs GPR:$rd),
                   (ins GPR:$rs1, i32imm:$imm12),
                   "jalr", "$rd, ${imm12}(${rs1})">,
           Sched<[WriteJalr, ReadJalr]>;
}

//===----------------------------------------------------------------------===//
// Assembler Pseudo Instructions (User-Level ISA, Version 2.2, Chapter 20)
//===----------------------------------------------------------------------===//

let isReturn = 1, isBarrier = 1, isTerminator = 1 in
def PseudoRET : Pseudo<(outs), (ins), [(bogus_ret)]>,
                PseudoInstExpansion<(JALR X0, X1, 0)>;
// def : InstAlias<"ret",                   (JALR      X0,      X1, 0), 4>;

// def : MnemonicAlias<"move", "mv">;

//===----------------------------------------------------------------------===//
// Pseudo-instructions and codegen patterns
//
// Naming convention: For 'generic' pattern classes, we use the naming
// convention PatTy1Ty2. For pattern classes which offer a more complex
// expension, prefix the class name, e.g. BccPat.
//===----------------------------------------------------------------------===//

/// Generic pattern classes

class PatGprGpr<SDPatternOperator OpNode, RWInst Inst>
    : Pat<(OpNode GPR:$rs1, GPR:$rs2), (Inst GPR:$rs1, GPR:$rs2)>;
class PatGprSimm12<SDPatternOperator OpNode, RWInstI Inst>
    : Pat<(OpNode GPR:$rs1, simm12:$imm12), (Inst GPR:$rs1, simm12:$imm12)>;

/// Immediates

def : Pat<(simm12:$imm), (ADDI X0, simm12:$imm)>;
def : Pat<(simm32:$imm), (ADDI (LUI (HI20 imm:$imm)), (LO12Sext imm:$imm))>;

/// Simple arithmetic operations

def : PatGprGpr<add, ADD>;
def : PatGprSimm12<add, ADDI>;
