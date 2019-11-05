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
    struct FPLICMCorrect : public LoopPass {
      public:  
	
	static char ID;
        FPLICMCorrect() : LoopPass(ID) {}
        virtual void getAnalysisUsage(AnalysisUsage &AU) const override;
        virtual bool runOnLoop(Loop *L, LPPassManager &LPM) override;

      private:
    
    };
    
    void FPLICMCorrect::getAnalysisUsage(AnalysisUsage &AU) const {
     
    }

    bool FPLICMCorrect::runOnLoop(Loop *L, LPPassManager &LPM) {
    
    }

} // namespace

char FPLICMCorrect::ID = 0;

static RegisterPass<FPLICMCorrect> X("fplicm-correctness", "Frequent Loop Invariant Code Motion for correctness test");

static void registerStatisticsPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
    PM.add(new BranchProbabilityInfoWrapperPass());
    PM.add(new BlockFrequencyInfoWrapperPass());                        
    PM.add(new FPLICMCorrect());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerStatisticsPass);

