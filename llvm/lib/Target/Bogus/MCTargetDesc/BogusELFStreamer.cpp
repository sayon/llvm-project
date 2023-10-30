#include "BogusELFStreamer.h"
#include "BogusAsmBackend.h"
#include "BogusBaseInfo.h"
#include "BogusMCTargetDesc.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/LEB128.h"

using namespace llvm;

// This part is for ELF object output.
BogusTargetELFStreamer::BogusTargetELFStreamer(MCStreamer &S,
                                               const MCSubtargetInfo &STI)
    : BogusTargetStreamer(S), CurrentVendor("bogus-vendor"), STI(STI) {
  MCAssembler &MCA = getStreamer().getAssembler();
  // const FeatureBitset &Features = STI.getFeatureBits();
  // auto &MAB = static_cast<BogusAsmBackend &>(MCA.getBackend());
  // setTargetABI(BogusABI::computeTargetABI(STI.getTargetTriple(), Features,
  //                                         MAB.getTargetOptions().getABIName()));
}

BogusELFStreamer &BogusTargetELFStreamer::getStreamer() {
  return static_cast<BogusELFStreamer &>(Streamer);
}

// void BogusTargetELFStreamer::emitDirectiveOptionPush() {}
// void BogusTargetELFStreamer::emitDirectiveOptionPop() {}
// void BogusTargetELFStreamer::emitDirectiveOptionPIC() {}
// void BogusTargetELFStreamer::emitDirectiveOptionNoPIC() {}
// void BogusTargetELFStreamer::emitDirectiveOptionRVC() {}
// void BogusTargetELFStreamer::emitDirectiveOptionNoRVC() {}
// void BogusTargetELFStreamer::emitDirectiveOptionRelax() {}
// void BogusTargetELFStreamer::emitDirectiveOptionNoRelax() {}

// void BogusTargetELFStreamer::emitAttribute(unsigned Attribute, unsigned Value) {
//   getStreamer().setAttributeItem(Attribute, Value, /*OverwriteExisting=*/true);
// }

// void BogusTargetELFStreamer::emitTextAttribute(unsigned Attribute,
//                                                StringRef String) {
//   getStreamer().setAttributeItem(Attribute, String, /*OverwriteExisting=*/true);
// }

// void BogusTargetELFStreamer::emitIntTextAttribute(unsigned Attribute,
//                                                   unsigned IntValue,
//                                                   StringRef StringValue) {
//   getStreamer().setAttributeItems(Attribute, IntValue, StringValue,
//                                   /*OverwriteExisting=*/true);
// }

// void BogusTargetELFStreamer::finishAttributeSection() {
//   // BogusELFStreamer &S = getStreamer();
//   // if (S.Contents.empty())
//   //   return;

//   // S.emitAttributesSection(CurrentVendor, ".riscv.attributes",
//   //                         ELF::SHT_Bogus_ATTRIBUTES, AttributeSection);
// }

// void BogusTargetELFStreamer::finish() {
//   BogusTargetStreamer::finish();
//   MCAssembler &MCA = getStreamer().getAssembler();
//   const FeatureBitset &Features = STI.getFeatureBits();
//   BogusABI::ABI ABI = getTargetABI();

//   unsigned EFlags = MCA.getELFHeaderEFlags();

//   if (Features[Bogus::FeatureStdExtC])
//     EFlags |= ELF::EF_Bogus_RVC;
//   if (Features[Bogus::FeatureStdExtZtso])
//     EFlags |= ELF::EF_Bogus_TSO;

//   switch (ABI) {
//   case BogusABI::ABI_ILP32:
//   case BogusABI::ABI_LP64:
//     break;
//   case BogusABI::ABI_ILP32F:
//   case BogusABI::ABI_LP64F:
//     EFlags |= ELF::EF_Bogus_FLOAT_ABI_SINGLE;
//     break;
//   case BogusABI::ABI_ILP32D:
//   case BogusABI::ABI_LP64D:
//     EFlags |= ELF::EF_Bogus_FLOAT_ABI_DOUBLE;
//     break;
//   case BogusABI::ABI_ILP32E:
//   case BogusABI::ABI_LP64E:
//     EFlags |= ELF::EF_Bogus_RVE;
//     break;
//   case BogusABI::ABI_Unknown:
//     llvm_unreachable("Improperly initialised target ABI");
//   }

//   MCA.setELFHeaderEFlags(EFlags);
// }

// void BogusTargetELFStreamer::reset() {
//   AttributeSection = nullptr;
// }

// void BogusTargetELFStreamer::emitDirectiveVariantCC(MCSymbol &Symbol) {
//   getStreamer().getAssembler().registerSymbol(Symbol);
//   cast<MCSymbolELF>(Symbol).setOther(ELF::STO_Bogus_VARIANT_CC);
// }

// void BogusELFStreamer::reset() {
//   static_cast<BogusTargetStreamer *>(getTargetStreamer())->reset();
//   MCELFStreamer::reset();
//   MappingSymbolCounter = 0;
//   LastMappingSymbols.clear();
//   LastEMS = EMS_None;
// }

// void BogusELFStreamer::emitDataMappingSymbol() {
//   if (LastEMS == EMS_Data)
//     return;
//   emitMappingSymbol("$d");
//   LastEMS = EMS_Data;
// }

// void BogusELFStreamer::emitInstructionsMappingSymbol() {
//   if (LastEMS == EMS_Instructions)
//     return;
//   emitMappingSymbol("$x");
//   LastEMS = EMS_Instructions;
// }

// void BogusELFStreamer::emitMappingSymbol(StringRef Name) {
//   auto *Symbol = cast<MCSymbolELF>(getContext().getOrCreateSymbol(
//       Name + "." + Twine(MappingSymbolCounter++)));
//   emitLabel(Symbol);
//   Symbol->setType(ELF::STT_NOTYPE);
//   Symbol->setBinding(ELF::STB_LOCAL);
// }

// void BogusELFStreamer::changeSection(MCSection *Section,
//                                      const MCExpr *Subsection) {
//   // We have to keep track of the mapping symbol state of any sections we
//   // use. Each one should start off as EMS_None, which is provided as the
//   // default constructor by DenseMap::lookup.
//   LastMappingSymbols[getPreviousSection().first] = LastEMS;
//   LastEMS = LastMappingSymbols.lookup(Section);

//   MCELFStreamer::changeSection(Section, Subsection);
// }

// void BogusELFStreamer::emitInstruction(const MCInst &Inst,
//                                        const MCSubtargetInfo &STI) {
//   emitInstructionsMappingSymbol();
//   MCELFStreamer::emitInstruction(Inst, STI);
// }

// void BogusELFStreamer::emitBytes(StringRef Data) {
//   emitDataMappingSymbol();
//   MCELFStreamer::emitBytes(Data);
// }

// void BogusELFStreamer::emitFill(const MCExpr &NumBytes, uint64_t FillValue,
//                                 SMLoc Loc) {
//   emitDataMappingSymbol();
//   MCELFStreamer::emitFill(NumBytes, FillValue, Loc);
// }

// void BogusELFStreamer::emitValueImpl(const MCExpr *Value, unsigned Size,
//                                      SMLoc Loc) {
//   emitDataMappingSymbol();
//   MCELFStreamer::emitValueImpl(Value, Size, Loc);
// }

namespace llvm {
MCELFStreamer *createBogusELFStreamer(MCContext &C,
                                      std::unique_ptr<MCAsmBackend> MAB,
                                      std::unique_ptr<MCObjectWriter> MOW,
                                      std::unique_ptr<MCCodeEmitter> MCE,
                                      bool RelaxAll) {
  BogusELFStreamer *S =
      new BogusELFStreamer(C, std::move(MAB), std::move(MOW), std::move(MCE));
  S->getAssembler().setRelaxAll(RelaxAll);
  return S;
}
} // namespace llvm
