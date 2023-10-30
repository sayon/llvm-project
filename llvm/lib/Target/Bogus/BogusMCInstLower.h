#pragma once

#include "BogusSubtarget.h"
#include "llvm/Support/Compiler.h"

namespace llvm {

class AsmPrinter;
class MachineInstr;
class MachineOperand;
class MCContext;
class MCInst;
class MCOperand;
class MCSymbol;

/// Lowers `MachineInstr` objects into `MCInst` objects.
class BogusMCInstLower {
public:
  BogusMCInstLower(MCContext &Ctx, AsmPrinter &Printer)
      : Ctx(Ctx), Printer(Printer) {}

  /// Lowers a `MachineInstr` into a `MCInst`.
  void lowerInstruction(const MachineInstr &MI, MCInst &OutMI) const;

private:
  MCContext &Ctx;
  AsmPrinter &Printer;
};

} // end namespace llvm
