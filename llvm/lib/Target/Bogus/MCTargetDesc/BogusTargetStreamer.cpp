#include "BogusTargetStreamer.h"
#include "BogusBaseInfo.h"
#include "BogusMCTargetDesc.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;


// void BogusTargetStreamer::finish() { finishAttributeSection(); }
// void BogusTargetStreamer::reset() {}

// void BogusTargetStreamer::emitDirectiveOptionPush() {}
// void BogusTargetStreamer::emitDirectiveOptionPop() {}
// void BogusTargetStreamer::emitDirectiveOptionPIC() {}
// void BogusTargetStreamer::emitDirectiveOptionNoPIC() {}
// void BogusTargetStreamer::emitDirectiveOptionRVC() {}
// void BogusTargetStreamer::emitDirectiveOptionNoRVC() {}
// void BogusTargetStreamer::emitDirectiveOptionRelax() {}
// void BogusTargetStreamer::emitDirectiveOptionNoRelax() {}
// void BogusTargetStreamer::emitDirectiveOptionArch(
//     ArrayRef<BogusOptionArchArg> Args) {}
// void BogusTargetStreamer::emitDirectiveVariantCC(MCSymbol &Symbol) {}
// void BogusTargetStreamer::emitAttribute(unsigned Attribute, unsigned Value) {}
// void BogusTargetStreamer::finishAttributeSection() {}
// void BogusTargetStreamer::emitTextAttribute(unsigned Attribute,
//                                             StringRef String) {}
// void BogusTargetStreamer::emitIntTextAttribute(unsigned Attribute,
//                                                unsigned IntValue,
//                                                StringRef StringValue) {}
// void BogusTargetStreamer::setTargetABI(BogusABI::ABI ABI) {
//   assert(ABI != BogusABI::ABI_Unknown && "Improperly initialized target ABI");
//   TargetABI = ABI;
// }

// void BogusTargetStreamer::emitTargetAttributes(const MCSubtargetInfo &STI,
//                                                bool EmitStackAlign) {
//   if (STI.hasFeature(Bogus::FeatureRVE))
//     report_fatal_error("Codegen not yet implemented for RVE");

//   if (EmitStackAlign)
//     emitAttribute(BogusAttrs::STACK_ALIGN, BogusAttrs::ALIGN_16);

//   auto ParseResult = BogusFeatures::parseFeatureBits(
//       STI.hasFeature(Bogus::Feature64Bit), STI.getFeatureBits());
//   if (!ParseResult) {
//     report_fatal_error(ParseResult.takeError());
//   } else {
//     auto &ISAInfo = *ParseResult;
//     emitTextAttribute(BogusAttrs::ARCH, ISAInfo->toString());
//   }
// }

// // This part is for ascii assembly output
// BogusTargetAsmStreamer::BogusTargetAsmStreamer(MCStreamer &S,
//                                                formatted_raw_ostream &OS)
//     : BogusTargetStreamer(S), OS(OS) {}

// void BogusTargetAsmStreamer::emitDirectiveOptionPush() {
//   OS << "\t.option\tpush\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionPop() {
//   OS << "\t.option\tpop\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionPIC() {
//   OS << "\t.option\tpic\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionNoPIC() {
//   OS << "\t.option\tnopic\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionRVC() {
//   OS << "\t.option\trvc\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionNoRVC() {
//   OS << "\t.option\tnorvc\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionRelax() {
//   OS << "\t.option\trelax\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionNoRelax() {
//   OS << "\t.option\tnorelax\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveOptionArch(
//     ArrayRef<BogusOptionArchArg> Args) {
//   OS << "\t.option\tarch";
//   for (const auto &Arg : Args) {
//     OS << ", ";
//     switch (Arg.Type) {
//     case BogusOptionArchArgType::Full:
//       break;
//     case BogusOptionArchArgType::Plus:
//       OS << "+";
//       break;
//     case BogusOptionArchArgType::Minus:
//       OS << "-";
//       break;
//     }
//     OS << Arg.Value;
//   }
//   OS << "\n";
// }

// void BogusTargetAsmStreamer::emitDirectiveVariantCC(MCSymbol &Symbol) {
//   OS << "\t.variant_cc\t" << Symbol.getName() << "\n";
// }

// void BogusTargetAsmStreamer::emitAttribute(unsigned Attribute, unsigned Value) {
//   OS << "\t.attribute\t" << Attribute << ", " << Twine(Value) << "\n";
// }

// void BogusTargetAsmStreamer::emitTextAttribute(unsigned Attribute,
//                                                StringRef String) {
//   OS << "\t.attribute\t" << Attribute << ", \"" << String << "\"\n";
// }

// void BogusTargetAsmStreamer::emitIntTextAttribute(unsigned Attribute,
//                                                   unsigned IntValue,
//                                                   StringRef StringValue) {}

// void BogusTargetAsmStreamer::finishAttributeSection() {}
