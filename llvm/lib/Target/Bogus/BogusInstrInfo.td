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

//===----------------------------------------------------------------------===//
// Instruction Formats
//===----------------------------------------------------------------------===//

include "BogusInstrFormats.td"

//===----------------------------------------------------------------------===//
// Instructions
//===----------------------------------------------------------------------===//

def IMM :
BogusInstI<OPC_OP_IMM, (outs GPR:$src0), (ins simm12:$imm12), "bogus-imm">,
      Sched<[WriteIALU, ReadIALU]>  ;

def ADD  :  BogusInstRR<OPC_OP_ADD, (outs GPR:$dst0), (ins GPR:$src0, GPR:$src1),
              "bogus-add"> , Sched<[WriteIALU, ReadIALU, ReadIALU]>;

/* Procedure calling instructions */
def RET : BogusInstR<OPC_OP_RET, (outs), (ins GPR:$src0),  "bogus-ret">,
           Sched<[]>;

//===----------------------------------------------------------------------===//
// Assembler Pseudo Instructions (User-Level ISA)
//===----------------------------------------------------------------------===//

let isReturn = 1, isBarrier = 1, isTerminator = 1 in
def PseudoRET : Pseudo<(outs), (ins GPR:$src0), [(bogus_ret)]>,
                PseudoInstExpansion<(RET $src0)>;

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
