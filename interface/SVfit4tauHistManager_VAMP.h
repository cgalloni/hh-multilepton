#ifndef hhAnalysis_multilepton_SVfit4tauHistManager_VAMP_h
#define hhAnalysis_multilepton_SVfit4tauHistManager_VAMP_h

/** \class SVfit4tauHistManager_VAMP
 *
 * Book and fill histograms for di-Higgs mass reconstructed by ClassicSVfit4tau algorithm with integration performed by VAMP,
 * used by HH->tttt, WWtt, and WWWW analysis 
 *
 * \author Christian Veelken, Tallinn
 *
 */

#include "tthAnalysis/HiggsToTauTau/interface/HistManagerBase.h" // HistManagerBase

#include "hhAnalysis/multilepton/interface/mySVfit4tauAuxFunctions.h" // SVfit4tauResult

class SVfit4tauHistManager_VAMP
  : public HistManagerBase
{
public:
  SVfit4tauHistManager_VAMP(const edm::ParameterSet & cfg);
  ~SVfit4tauHistManager_VAMP() {}

  /// book and fill histograms
  void
  bookHistograms(TFileDirectory & dir) override;
  void
  bookHistograms2d(TFileDirectory & dir);

  void
  fillHistograms(const std::vector<SVfit4tauResult>& results,
                 double evtWeight);

 private:

  TH1 * histogram_numValidSolutions_;

  TH1 * histogram_dihiggsVisMass1_;
  TH1 * histogram_dihiggsMass1_;
  TH1 * histogram_logLmax1_;
  TH2 * histogram_logLmax1_vs_dihiggsMass1_;

  TH1 * histogram_dihiggsVisMass2_;
  TH1 * histogram_dihiggsMass2_;
  TH1 * histogram_logLmax2_;
  TH2 * histogram_logLmax2_vs_dihiggsMass2_;
};

#endif
