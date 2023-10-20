//===-- BogusInstrInfo.h - Bogus Instruction Information ----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Bogus implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Bogus_BogusINSTRINFO_H
#define LLVM_LIB_TARGET_Bogus_BogusINSTRINFO_H

#include "Bogus.h"
#include "BogusRegisterInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "BogusGenInstrInfo.inc"

namespace llvm {

class BogusInstrInfo : public BogusGenInstrInfo {
public:
  explicit BogusInstrInfo(const BogusSubtarget &STI);

protected:
  const BogusSubtarget &Subtarget;
};
}

#endif // end LLVM_LIB_TARGET_Bogus_BogusINSTRINFO_H
