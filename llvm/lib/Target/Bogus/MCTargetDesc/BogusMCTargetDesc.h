//===-- BogusMCTargetDesc.h - Bogus Target Descriptions ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Bogus specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_Bogus_MCTARGETDESC_BogusMCTARGETDESC_H
#define LLVM_LIB_TARGET_Bogus_MCTARGETDESC_BogusMCTARGETDESC_H

// Defines symbolic names for Bogus registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "BogusGenRegisterInfo.inc"

// Defines symbolic names for the Bogus instructions.
#define GET_INSTRINFO_ENUM
#include "BogusGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "BogusGenSubtargetInfo.inc"

#endif // end LLVM_LIB_TARGET_Bogus_MCTARGETDESC_BogusMCTARGETDESC_H
