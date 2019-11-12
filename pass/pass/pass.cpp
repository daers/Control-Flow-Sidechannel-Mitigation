#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/Format.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/BlockFrequencyInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/ADT/SetOperations.h"
#include "llvm/Support/Debug.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Analysis/LoopInfo.h"

#include "llvm/Analysis/Loads.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopIterator.h"
#include "llvm/Analysis/LoopPass.h"

#include "llvm/Transforms/Utils/Local.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Analysis/DominanceFrontier.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace llvm;
using std::unordered_set; using std::unordered_map; using std::vector;
using std::queue;



namespace {
  struct ControlDependentBlocks{
    ControlDependentBlocks(BasicBlock* taken_, BasicBlock* notTaken_): taken(taken_), notTaken(notTaken_){}

    BasicBlock* taken;
    BasicBlock* notTaken;
  };

  ControlDependentBlocks detectIfStatement(Loop *L){
    for(auto* bb: L->getBlocksVector()){
      //find the BB with two predecessors
      if (bb->hasNPredecessors(2) && bb != L->getHeader()){
        ControlDependentBlocks found(*(pred_begin(bb)), *(++(pred_begin(bb))));
        errs() << "FOUND CONTROL DEPENDENT BLOCKS\n";
        return found;
      }
      //Check whether the two blocks 
      if (*(pred_begin(found.taken)) != *(pred_begin(found.notTaken))){
        errs() << "TAKEN AND NOT TAKEN HAVE DIFFERENT PREDECESSOR";
        return NULL;
      }
    }
    return NULL;
  }

  struct CF_SEC : public LoopPass {
  public:

   static char ID;
   CF_SEC() : LoopPass(ID) {}
   virtual void getAnalysisUsage(AnalysisUsage &AU) const override;
   virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override;

 private:

 };

 void CF_SEC::getAnalysisUsage(AnalysisUsage &AU) const {

 }

 bool CF_SEC::runOnLoop(Loop *L, LPPassManager &LPM) {
  ControlDependentBlocks change = detectIfStatement(L);
  return false;
}

} // namespace

char CF_SEC::ID = 0;

static RegisterPass<CF_SEC> X("cf_sec", "Control Flow Security Pass by Jakiegona");

static void registerStatisticsPass(const PassManagerBuilder &,
 legacy::PassManagerBase &PM) {
  PM.add(new BranchProbabilityInfoWrapperPass());
  PM.add(new BlockFrequencyInfoWrapperPass());
  PM.add(new CF_SEC());
}
static RegisterStandardPasses
RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
 registerStatisticsPass);
