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
  InstFormatRR = 2,
  InstFormatI = 3,
  InstFormatOther = 4,

  InstFormatMask = 7
};

} // namespace BogusII

namespace BogusOp {
enum OperandType : unsigned {
  OPERAND_FIRST_BOGUS_IMM = MCOI::OPERAND_FIRST_TARGET,
  OPERAND_UIMM5 = OPERAND_FIRST_BOGUS_IMM,
  OPERAND_CUSTOM_SIMM12,
  OPERAND_LAST_BOGUS_IMM = OPERAND_CUSTOM_SIMM12
};
} // namespace BogusOp

} // namespace llvm
