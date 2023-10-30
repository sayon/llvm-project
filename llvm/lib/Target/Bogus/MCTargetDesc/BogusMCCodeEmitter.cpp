#include "BogusMCCodeEmitter.h"
#include "BogusMCTargetDesc.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <cstdint>

using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

#define GET_INSTRMAP_INFO
#include "BogusGenInstrInfo.inc"
#undef GET_INSTRMAP_INFO


void BogusMCCodeEmitter::EmitByte(unsigned char C, raw_ostream &OS) const {
  OS << (char)C;
}

/// encodeInstruction - Emit the instruction.
/// Size the instruction with Desc.getSize().
void BogusMCCodeEmitter::encodeInstruction(const MCInst &MI,
                                          SmallVectorImpl<char> &CB,
                                          SmallVectorImpl<MCFixup> &Fixups,
                                          const MCSubtargetInfo &STI) const {
  // Non-pseudo instructions that get changed for direct object
  // only based on operand values.
  // If this list of instructions get much longer we will move
  // the check to a function call. Until then, this is more efficient.
  MCInst TmpInst = MI;

  uint32_t Binary = getBinaryCodeForInstr(TmpInst, Fixups, STI);
  //  const MCInstrDesc &Desc = MCII.get(TmpInst.getOpcode());
  support::endian::write<uint32_t>(CB, Binary, llvm::endianness::big);
}

MCCodeEmitter *llvm::createBogusMCCodeEmitter(const MCInstrInfo &MCII,
                                              MCContext &Ctx) {
  return new BogusMCCodeEmitter(MCII, Ctx);
}

unsigned
BogusMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                      SmallVectorImpl<MCFixup> &Fixups,
                                      const MCSubtargetInfo &STI) const {

  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());

  llvm_unreachable("Unhandled expression!");
  return 0;
}
namespace llvm {
#include "BogusGenCodeEmitter.inc"
} // namespace llvm
