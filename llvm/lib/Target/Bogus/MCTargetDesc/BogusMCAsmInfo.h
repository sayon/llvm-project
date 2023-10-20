//===-- BogusMCAsmInfo.h - Bogus Asm Info ------------------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the BogusMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Bogus_MCTARGETDESC_BogusMCASMINFO_H
#define LLVM_LIB_TARGET_Bogus_MCTARGETDESC_BogusMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

class BogusMCAsmInfo : public MCAsmInfoELF {
  void anchor() override;

public:
  explicit BogusMCAsmInfo(const Triple &TheTriple);
};

} // namespace llvm

#endif // end LLVM_LIB_TARGET_Bogus_MCTARGETDESC_BogusMCASMINFO_H
