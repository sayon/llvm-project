//===-- BogusRegisterInfo.cpp - Bogus Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Bogus implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "BogusRegisterInfo.h"
#include "BogusSubtarget.h"
#include "llvm/Support/Debug.h"

#define GET_REGINFO_TARGET_DESC
#include "BogusGenRegisterInfo.inc"


using namespace llvm;

BogusRegisterInfo::BogusRegisterInfo(const BogusSubtarget &ST)
  : BogusGenRegisterInfo(Bogus::X1, /*DwarfFlavour*/0, /*EHFlavor*/0,
                         /*PC*/0), Subtarget(ST) {}

const MCPhysReg *
BogusRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return Bogus_CalleeSavedRegs_SaveList;
}

const TargetRegisterClass *BogusRegisterInfo::intRegClass(unsigned Size) const {
  return &Bogus::GPRRegClass;
}

const uint32_t *
BogusRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID) const {
  return Bogus_CalleeSavedRegs_RegMask;
}

BitVector BogusRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  markSuperRegs(Reserved, Bogus::X0); // zero
  markSuperRegs(Reserved, Bogus::X2); // sp
  markSuperRegs(Reserved, Bogus::X3); // gp
  markSuperRegs(Reserved, Bogus::X4); // tp

  return Reserved;
}

bool BogusRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                           int SPAdj,
                                           unsigned FIOperandNum,
                                           RegScavenger *RS) const {
  llvm_unreachable("Unsupported eliminateFrameIndex");
}

bool
BogusRegisterInfo::requiresRegisterScavenging(const MachineFunction &MF) const {
  return true;
}

bool
BogusRegisterInfo::requiresFrameIndexScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
BogusRegisterInfo::requiresFrameIndexReplacementScavenging(
                                            const MachineFunction &MF) const {
  return true;
}

bool
BogusRegisterInfo::trackLivenessAfterRegAlloc(const MachineFunction &MF) const {
  return true;
}

Register BogusRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Register(0);
  //llvm_unreachable("Unsupported getFrameRegister");
}
