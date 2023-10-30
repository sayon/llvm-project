#pragma once

#include "BogusBaseInfo.h"
#include "llvm/MC/MCTargetOptions.h"

// Defines symbolic names for Bogus registers. This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "BogusGenRegisterInfo.inc"

// Defines symbolic names for the Bogus instructions.
#define GET_INSTRINFO_ENUM
#include "BogusGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "BogusGenSubtargetInfo.inc"

namespace llvm {
class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class Target;

MCCodeEmitter *createBogusMCCodeEmitter(const MCInstrInfo &MCII,
                                        MCContext &Ctx);

MCAsmBackend *createBogusAsmBackend(const Target &T,
                                          const MCSubtargetInfo &STI,
                                          const MCRegisterInfo &MRI,
                                    const MCTargetOptions &Options) ;

  std::unique_ptr<MCObjectTargetWriter> createBogusELFObjectWriter(uint8_t OSABI, bool Is64Bit);
} // namespace llvm
