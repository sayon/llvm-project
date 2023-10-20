//===-- BogusISelDAGToDAG.cpp - A Dag to Dag Inst Selector for Bogus ------===//
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

#include "BogusISelDAGToDAG.h"
#include "BogusSubtarget.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

#define DEBUG_TYPE "bogus"


bool BogusDAGToDAGISel::runOnMachineFunction(MachineFunction &MF) {
  Subtarget = &static_cast<const BogusSubtarget &>(MF.getSubtarget());
  return SelectionDAGISel::runOnMachineFunction(MF);
}

void BogusDAGToDAGISel::Select(SDNode *Node) {
  // If we have a custom node, we already have selected!
  if (Node->isMachineOpcode()) {
    LLVM_DEBUG(errs() << "== "; Node->dump(CurDAG); errs() << "\n");
    Node->setNodeId(-1);
    return;
  }

  unsigned Opcode = Node->getOpcode();
  SDLoc DL(Node);

  switch (Opcode) {
  case ISD::Constant: {
    auto* ConstNode = cast<ConstantSDNode>(Node);
    if (ConstNode) {
      SDValue New = CurDAG->getCopyFromReg(CurDAG->getEntryNode(), SDLoc(Node),
                                           Bogus::X0, MVT::i32);
      ReplaceNode(Node, New.getNode());
      return;
    }
    break;
  }
  default:
    break;
  }
  // Select the default instruction
  SelectCode(Node);
}
