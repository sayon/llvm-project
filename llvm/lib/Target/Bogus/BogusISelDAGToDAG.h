//===---- BogusISelDAGToDAG.h - A Dag to Dag Inst Selector for Bogus ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines an instruction selector for the Bogus target.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Bogus_BogusISELDAGTODAG_H
#define LLVM_LIB_TARGET_Bogus_BogusISELDAGTODAG_H

#include "BogusSubtarget.h"
#include "BogusTargetMachine.h"
#include "llvm/CodeGen/MachineFunction.h"

namespace {
char ID;
}

namespace llvm {
class BogusDAGToDAGISel : public SelectionDAGISel {
public:
  explicit BogusDAGToDAGISel(BogusTargetMachine &TM, CodeGenOptLevel OL)
      : SelectionDAGISel(ID, TM, OL), Subtarget(nullptr) {}

  // Pass Name
  StringRef getPassName() const override {
    return "CPU0 DAG->DAG Pattern Instruction Selection";
  }

  bool runOnMachineFunction(MachineFunction &MF) override;

  void Select(SDNode *Node) override;

#include "BogusGenDAGISel.inc"

private:
  const BogusSubtarget *Subtarget;
};
} // namespace llvm

#endif // end LLVM_LIB_TARGET_Bogus_BogusISELDAGTODAG_H
