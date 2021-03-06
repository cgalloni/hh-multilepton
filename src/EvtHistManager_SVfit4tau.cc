#include "hhAnalysis/multilepton/interface/EvtHistManager_SVfit4tau.h"

#include "tthAnalysis/HiggsToTauTau/interface/histogramAuxFunctions.h" // fillWithOverFlow()
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // kEra_2017
#include "tthAnalysis/HiggsToTauTau/interface/cmsException.h" // cmsException()

#include <TMath.h> // TMath::Sqrt

EvtHistManager_SVfit4tau::EvtHistManager_SVfit4tau(const edm::ParameterSet& cfg)
  : HistManagerBase(cfg)
{
  central_or_shiftOptions_["mhh_MarkovChain"] = { "central" };
  central_or_shiftOptions_["mhh_VAMP"] = { "central" };
  central_or_shiftOptions_["mhh_gen"] = { "central" };
  central_or_shiftOptions_["mh1"] = { "central" };
  central_or_shiftOptions_["mh1_gen"] = { "central" };
  central_or_shiftOptions_["mh2"] = { "central" };
  central_or_shiftOptions_["mh2_gen"] = { "central" };
  central_or_shiftOptions_["mhhVis"] = { "central" };
  central_or_shiftOptions_["mhhVis_gen"] = { "central" };
  central_or_shiftOptions_["mh1Vis"] = { "central" };
  central_or_shiftOptions_["mh1Vis_gen"] = { "central" };
  central_or_shiftOptions_["mh2Vis"] = { "central" };
  central_or_shiftOptions_["mh2Vis_gen"] = { "central" };
  central_or_shiftOptions_["ratiomeasuredTau1Pt"] = { "central" };
  central_or_shiftOptions_["ratiomeasuredTau2Pt"] = { "central" };
  central_or_shiftOptions_["ratiomeasuredTau3Pt"] = { "central" };
  central_or_shiftOptions_["ratiomeasuredTau4Pt"] = { "central" };
  central_or_shiftOptions_["deltametPx"] = { "central" };
  central_or_shiftOptions_["pullmetPx"] = { "central" };
  central_or_shiftOptions_["deltametPy"] = { "central" };
  central_or_shiftOptions_["pullmetPy"] = { "central" };
  central_or_shiftOptions_["EventCounter"] = { "*" };
}

const TH1 *
EvtHistManager_SVfit4tau::getHistogram_EventCounter() const
{
  return histogram_EventCounter_;
}

void EvtHistManager_SVfit4tau::bookHistograms(TFileDirectory & dir)
{
  histogram_mhh_MarkovChain_     = book1D(dir, "mhh_MarkovChain",     "mhh_MarkovChain",     100,    0., 1000.);
  histogram_mhh_VAMP_            = book1D(dir, "mhh_VAMP",            "mhh_VAMP",            100,    0., 1000.);
  histogram_mhh_gen_             = book1D(dir, "mhh_gen",             "mhh_gen",             100,    0., 1000.);
  histogram_mh1_                 = book1D(dir, "mh1",                 "mh1",                  50,    0.,  500.);
  histogram_mh1_gen_             = book1D(dir, "mh1_gen",             "mh1_gen",              50,    0.,  500.);
  histogram_mh2_                 = book1D(dir, "mh2",                 "mh2",                  50,    0.,  500.);
  histogram_mh2_gen_             = book1D(dir, "mh2_gen",             "mh2_gen",              50,    0.,  500.);

  histogram_mhhVis_              = book1D(dir, "mhhVis",              "mhhVis",              100,    0., 1000.);
  histogram_mhhVis_gen_          = book1D(dir, "mhhVis_gen",          "mhhVis_gen",          100,    0., 1000.);
  histogram_mh1Vis_              = book1D(dir, "mh1Vis",              "mh1Vis",               50,    0.,  500.);
  histogram_mh1Vis_gen_          = book1D(dir, "mh1Vis_gen",          "mh1Vis_gen",           50,    0.,  500.);
  histogram_mh2Vis_              = book1D(dir, "mh2Vis",              "mh2Vis",               50,    0.,  500.);
  histogram_mh2Vis_gen_          = book1D(dir, "mh2Vis_gen",          "mh2Vis_gen",           50,    0.,  500.);

  histogram_ratiomeasuredTau1Pt_ = book1D(dir, "ratiomeasuredTau1Pt", "ratiomeasuredTau1Pt", 200,    0.,    2.);
  histogram_ratiomeasuredTau2Pt_ = book1D(dir, "ratiomeasuredTau2Pt", "ratiomeasuredTau2Pt", 200,    0.,    2.);
  histogram_ratiomeasuredTau3Pt_ = book1D(dir, "ratiomeasuredTau3Pt", "ratiomeasuredTau3Pt", 200,    0.,    2.);
  histogram_ratiomeasuredTau4Pt_ = book1D(dir, "ratiomeasuredTau4Pt", "ratiomeasuredTau4Pt", 200,    0.,    2.);
  
  histogram_deltametPx_          = book1D(dir, "deltametPx",          "deltametPx",          200, -100., +100.);
  histogram_pullmetPx_           = book1D(dir, "pullmetPx",           "pullmetPx",           200,  -10.,  +10.);
  histogram_deltametPy_          = book1D(dir, "deltametPy",          "deltametPy",          200, -100., +100.);
  histogram_pullmetPy_           = book1D(dir, "pullmetPy",           "pullmetPy",           200,  -10.,  +10.);

  histogram_EventCounter_        = book1D(dir, "EventCounter",        "EventCounter",          1,   -0.5,  +0.5);
}

void
EvtHistManager_SVfit4tau::fillHistograms(const SVfit4tauResult& svFit4tauResult_MarkovChain, const SVfit4tauResult& svFit4tauResult_VAMP,
					 const Particle::LorentzVector* genDiHiggsP4, 
					 const Particle::LorentzVector* genDiTau1P4, 
					 const Particle::LorentzVector* genDiTau2P4,
					 const Particle::LorentzVector& measuredTau1P4, const Particle::LorentzVector& measuredTau1P4_gen, 
					 const Particle::LorentzVector& measuredTau2P4, const Particle::LorentzVector& measuredTau2P4_gen, 
					 const Particle::LorentzVector& measuredTau3P4, const Particle::LorentzVector& measuredTau3P4_gen, 
					 const Particle::LorentzVector& measuredTau4P4, const Particle::LorentzVector& measuredTau4P4_gen,
					 double metPx, double metPy, const TMatrixD& metCov, double metPx_gen, double metPy_gen, 
					 double evtWeight)
{
  const double evtWeightErr = 0.;

  if ( svFit4tauResult_MarkovChain.isValidSolution_ ) {
    fillWithOverFlow(histogram_mhh_MarkovChain_, svFit4tauResult_MarkovChain.dihiggs_mass_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mh1_, svFit4tauResult_MarkovChain.ditau1_mass_, evtWeight, evtWeightErr);
    fillWithOverFlow(histogram_mh2_, svFit4tauResult_MarkovChain.ditau2_mass_, evtWeight, evtWeightErr);
  }
  if ( svFit4tauResult_VAMP.isValidSolution_ ) {
    fillWithOverFlow(histogram_mhh_VAMP_, svFit4tauResult_VAMP.dihiggs_mass_, evtWeight, evtWeightErr);
  }
  if ( genDiHiggsP4 ) {
    fillWithOverFlow(histogram_mhh_gen_, genDiHiggsP4->mass(), evtWeight, evtWeightErr);
  }
  if ( genDiTau1P4 ) {
    fillWithOverFlow(histogram_mh1_gen_, genDiTau1P4->mass(), evtWeight, evtWeightErr);
  }
  if ( genDiTau2P4 ) {
    fillWithOverFlow(histogram_mh2_gen_, genDiTau2P4->mass(), evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_mhhVis_, (measuredTau1P4 + measuredTau2P4 + measuredTau3P4 + measuredTau4P4).mass(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mhhVis_gen_, (measuredTau1P4_gen + measuredTau2P4_gen + measuredTau3P4_gen + measuredTau4P4_gen).mass(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mh1Vis_, (measuredTau1P4 + measuredTau2P4).mass(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mh1Vis_gen_, (measuredTau1P4_gen + measuredTau2P4_gen).mass(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mh2Vis_, (measuredTau3P4 + measuredTau4P4).mass(), evtWeight, evtWeightErr);
  fillWithOverFlow(histogram_mh2Vis_gen_, (measuredTau3P4_gen + measuredTau4P4_gen).mass(), evtWeight, evtWeightErr);

  if ( measuredTau1P4_gen.pt() > 10. ) {
    fillWithOverFlow(histogram_ratiomeasuredTau1Pt_, measuredTau1P4.pt()/measuredTau1P4_gen.pt(), evtWeight, evtWeightErr);
  }
  if ( measuredTau2P4_gen.pt() > 10. ) {
    fillWithOverFlow(histogram_ratiomeasuredTau2Pt_, measuredTau2P4.pt()/measuredTau2P4_gen.pt(), evtWeight, evtWeightErr);
  }
  if ( measuredTau3P4_gen.pt() > 10. ) {
    fillWithOverFlow(histogram_ratiomeasuredTau3Pt_, measuredTau3P4.pt()/measuredTau3P4_gen.pt(), evtWeight, evtWeightErr);
  }
  if ( measuredTau4P4_gen.pt() > 10. ) {
    fillWithOverFlow(histogram_ratiomeasuredTau4Pt_, measuredTau4P4.pt()/measuredTau4P4_gen.pt(), evtWeight, evtWeightErr);
  }

  fillWithOverFlow(histogram_deltametPx_, metPx - metPx_gen, evtWeight, evtWeightErr);
  double metPxErr = TMath::Sqrt(metCov[0][0]);
  if ( metPxErr > 1. ) {
    fillWithOverFlow(histogram_pullmetPx_, (metPx - metPx_gen)/metPxErr, evtWeight, evtWeightErr);
  }    
  fillWithOverFlow(histogram_deltametPy_, metPy - metPy_gen, evtWeight, evtWeightErr);
  double metPyErr = TMath::Sqrt(metCov[1][1]);
  if ( metPyErr > 1. ) {
    fillWithOverFlow(histogram_pullmetPy_, (metPy - metPy_gen)/metPyErr, evtWeight, evtWeightErr);
  }  

  fillWithOverFlow(histogram_EventCounter_, 0., evtWeight, evtWeightErr);
}
