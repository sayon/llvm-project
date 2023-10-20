//===-- BogusTargetInfo.cpp - Bogus Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/BogusTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheBogusTarget() {
  static Target TheBogusTarget;
  return TheBogusTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeBogusTargetInfo() {
  RegisterTarget<Triple::bogus, false> X(getTheBogusTarget(), "bogus", "bogus descr", "Bogus");
}
