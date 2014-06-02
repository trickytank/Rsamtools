#ifndef RESULT_MANAGER_H
#define RESULT_MANAGER_H

#include <map>
#include <vector>
#include <utility>
#ifdef PILEUP_DEBUG
#include <stdio.h>
#include <cassert>
#include "nate_utilities.h"
#endif
#include "PosCache.h"
#include <Rinternals.h>
typedef std::vector<int>::const_iterator int_const_it;
typedef std::vector<char>::const_iterator char_const_it;

class ResultMgrInterface
{
public:
    virtual void signalPosStart(int pos) = 0;
    virtual void forwardTuple(BamTuple bTuple) = 0;
    virtual void extractFromPosCache() = 0;
    virtual void signalPosEnd() = 0;
    virtual int size() const = 0;
    virtual void signalYieldEnd() = 0;
    virtual ~ResultMgrInterface() {}
    virtual int_const_it posBeg() const = 0;
    virtual int_const_it posEnd() const = 0;
    virtual int_const_it countBeg() const = 0;
    virtual int_const_it countEnd() const = 0;
    virtual char_const_it strandBeg() const = 0;
    virtual char_const_it strandEnd() const = 0;
    virtual char_const_it nucBeg() const = 0;
    virtual char_const_it nucEnd() const = 0;
    virtual int_const_it binBeg() const = 0;
    virtual int_const_it binEnd() const = 0;
};

class ResultMgr : public ResultMgrInterface
{
private:
    std::vector<int> posVec, binVec, countVec;
    std::vector<char> strandVec, nucVec;
    PosCache posCache;
    int curPos;
    const int min_nuc_depth, min_minor_allele_depth;
    const bool hasStrands, hasNucleotides, hasBins;
    template <bool wantNuc, bool wantStrand, bool wantBin>
    void doExtractFromPosCache();
public:
    virtual void signalPosStart(int pos);
    virtual void forwardTuple(BamTuple bTuple);
    virtual void extractFromPosCache();
    template <bool wantNuc, bool wantStrand, bool wantBin>
    void doExtractFromPosCache(const std::set<char>& nucs);
    virtual void signalPosEnd();
    virtual int size() const;
    virtual void printVecs() const;
    virtual void signalYieldEnd();
    virtual ~ResultMgr() {}
    ResultMgr(int min_nuc_depth_, int min_minor_allele_depth_,
              bool hasStrands_, bool hasNucleotides_, bool hasBins_) :
        posVec(),  binVec(), countVec(), strandVec(), nucVec(), posCache(),
        curPos(), min_nuc_depth(min_nuc_depth_),
        min_minor_allele_depth(min_minor_allele_depth_),
        hasStrands(hasStrands_), hasNucleotides(hasNucleotides_),
        hasBins(hasBins_) {}
    virtual int_const_it posBeg() const;
    virtual int_const_it posEnd() const;
    virtual int_const_it binBeg() const;
    virtual int_const_it binEnd() const;
    virtual int_const_it countBeg() const;
    virtual int_const_it countEnd() const;
    virtual char_const_it strandBeg() const;
    virtual char_const_it strandEnd() const;
    virtual char_const_it nucBeg() const;
    virtual char_const_it nucEnd() const;
};

#endif // RESULT_MANAGER_H
