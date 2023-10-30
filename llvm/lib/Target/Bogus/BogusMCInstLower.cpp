//===----------------------------------------------------------------------===//
//
// This file contains code to lower Bogus MachineInstrs to their corresponding
// MCInst records.
//
//===----------------------------------------------------------------------===//

#include "BogusMCInstLower.h"
#include "BogusInstrInfo.h"

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/IR/Mangler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {


void BogusMCInstLower::lowerInstruction(const MachineInstr &MI,
                                      MCInst &OutMI) const {
  // auto &Subtarget = MI.getParent()->getParent()->getSubtarget<BogusSubtarget>();
  OutMI.setOpcode(MI.getOpcode());

  // for (MachineOperand const &MO : MI.operands()) {
  //   MCOperand MCOp;

    // switch (MO.getType()) {
    // default:
    //   MI.print(errs());
    //   llvm_unreachable("unknown operand type");
    // case MachineOperand::MO_Register:
    //   // Ignore all implicit register operands.
    //   if (MO.isImplicit())
    //     continue;
    //   MCOp = MCOperand::createReg(MO.getReg());
    //   break;
    // case MachineOperand::MO_Immediate:
    //   MCOp = MCOperand::createImm(MO.getImm());
    //   break;
    // case MachineOperand::MO_GlobalAddress:
    //   MCOp =
    //       lowerSymbolOperand(MO, Printer.getSymbol(MO.getGlobal()), Subtarget);
    //   break;
    // case MachineOperand::MO_ExternalSymbol:
    //   MCOp = lowerSymbolOperand(
    //       MO, Printer.GetExternalSymbolSymbol(MO.getSymbolName()), Subtarget);
    //   break;
    // case MachineOperand::MO_MachineBasicBlock:
    //   MCOp = MCOperand::createExpr(
    //       MCSymbolRefExpr::create(MO.getMBB()->getSymbol(), Ctx));
    //   break;
    // case MachineOperand::MO_RegisterMask:
    //   continue;
    // case MachineOperand::MO_BlockAddress:
    //   MCOp = lowerSymbolOperand(
    //       MO, Printer.GetBlockAddressSymbol(MO.getBlockAddress()), Subtarget);
    //   break;
    // case MachineOperand::MO_JumpTableIndex:
    //   MCOp = lowerSymbolOperand(MO, Printer.GetJTISymbol(MO.getIndex()),
    //                             Subtarget);
    //   break;
    // case MachineOperand::MO_ConstantPoolIndex:
    //   MCOp = lowerSymbolOperand(MO, Printer.GetCPISymbol(MO.getIndex()),
    //                             Subtarget);
    //   break;
    // }

  //   OutMI.addOperand(MCOp);
  // }
}

} // end of namespace llvm
