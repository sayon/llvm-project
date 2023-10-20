//=== BogusMachineFunctionInfo.h - Private data used for Bogus ----*- C++ -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Bogus specific subclass of MachineFunctionInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Bogus_BogusMACHINEFUNCTION_H
#define LLVM_LIB_TARGET_Bogus_BogusMACHINEFUNCTION_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// BogusFunctionInfo - This class is derived from MachineFunction private
/// Bogus target-specific information for each MachineFunction.
class BogusFunctionInfo : public MachineFunctionInfo {
private:
  MachineFunction &MF;

public:
  BogusFunctionInfo(MachineFunction &MF) : MF(MF) {}
};

} // end of namespace llvm

#endif // end LLVM_LIB_TARGET_Bogus_BogusMACHINEFUNCTION_H
