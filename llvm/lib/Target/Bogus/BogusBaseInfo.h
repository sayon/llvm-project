#pragma once

#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

// This namespace holds all of the target specific flags that
// instruction info tracks. All definitions must match BogusInstrFormats.td.
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
  OPERAND_SIMM12,
  OPERAND_LAST_BOGUS_IMM = OPERAND_SIMM12
};
} // namespace BogusOp

} // namespace llvm
