#include "MCTargetDesc/BogusMCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class BogusELFObjectWriter : public MCELFObjectTargetWriter {
public:
  BogusELFObjectWriter(uint8_t OSABI, bool Is64Bit)
      : MCELFObjectTargetWriter(Is64Bit, OSABI, ELF::EM_BOGUS,
                                /*HasRelocationAddend*/ true) {}

  ~BogusELFObjectWriter() override;

  // Return true if the given relocation must be with a symbol rather than
  // section plus offset.
  bool needsRelocateWithSymbol(const MCValue &Val, const MCSymbol &Sym,
                               unsigned Type) const override {
    return true;
  }

protected:
  unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                        const MCFixup &Fixup, bool IsPCRel) const override {
    return ELF::R_BOGUS_NONE;
  }
};
} // namespace

BogusELFObjectWriter::~BogusELFObjectWriter() = default;
std::unique_ptr<MCObjectTargetWriter>
llvm::createBogusELFObjectWriter(uint8_t OSABI, bool Is64Bit) {
  return std::make_unique<BogusELFObjectWriter>(OSABI, Is64Bit);
}
