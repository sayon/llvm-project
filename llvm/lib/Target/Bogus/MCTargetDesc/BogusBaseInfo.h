#pragma once
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/TargetParser/SubtargetFeature.h"

namespace llvm {

// BOGUSII - This namespace holds all of the target specific flags that
// instruction info tracks. All definitions must match BOGUSInstrFormats.td.
namespace BogusII {
enum {
  InstFormatPseudo = 0,
  InstFormatR = 1,
  InstFormatI = 2,
  InstFormatU = 3,
  InstFormatOther = 4,

  InstFormatMask = 31
};

} // namespace BogusII

namespace BogusOp {
enum OperandType : unsigned {
  OPERAND_FIRST_BOGUS_IMM = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM4 = OPERAND_FIRST_BOGUS_IMM,
  OPERAND_UIMM5,
  OPERAND_UIMM12,
  OPERAND_SIMM12,
  OPERAND_SIMM13_LSB0,
  OPERAND_UIMM20,
  OPERAND_SIMM21_LSB0,
  OPERAND_UIMMLOG2WSIZE,
  OPERAND_LAST_BOGUS_IMM = OPERAND_UIMMLOG2WSIZE
};
} // namespace BogusOp

} // namespace llvm
