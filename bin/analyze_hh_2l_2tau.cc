#include "FWCore/ParameterSet/interface/ParameterSet.h" // edm::ParameterSet
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h" // edm::readPSetsFrom()
#include "FWCore/Utilities/interface/Exception.h" // cms::Exception
#include "PhysicsTools/FWLite/interface/TFileService.h" // fwlite::TFileService
#include "DataFormats/FWLite/interface/InputSource.h" // fwlite::InputSource
#include "DataFormats/FWLite/interface/OutputFiles.h" // fwlite::OutputFiles
#include "DataFormats/Math/interface/LorentzVector.h" // math::PtEtaPhiMLorentzVector
#include "DataFormats/Math/interface/deltaR.h" // deltaR

#include <TBenchmark.h> // TBenchmark
#include <TString.h> // TString, Form
#include <TError.h> // gErrorAbortLevel, kError
#include <TRandom3.h> // TRandom3
#include <TLorentzVector.h> // TLorentzVector


#include "tthAnalysis/HiggsToTauTau/interface/RecoLepton.h" // RecoLepton
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTau.h" // RecoHadTau
#include "tthAnalysis/HiggsToTauTau/interface/RecoJet.h" // RecoJet
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEt.h" // RecoMEt
#include "tthAnalysis/HiggsToTauTau/interface/GenLepton.h" // GenLepton
#include "tthAnalysis/HiggsToTauTau/interface/GenJet.h" // GenJet
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTau.h" // GenHadTau
#include "tthAnalysis/HiggsToTauTau/interface/EventInfo.h" // EventInfo
#include "tthAnalysis/HiggsToTauTau/interface/LeptonFakeRateInterface.h" // LeptonFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/JetToTauFakeRateInterface.h" // JetToTauFakeRateInterface
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronReader.h" // RecoElectronReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonReader.h" // RecoMuonReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauReader.h" // RecoHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetReader.h" // RecoJetReader
#include "tthAnalysis/HiggsToTauTau/interface/RecoMEtReader.h" // RecoMEtReader
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterReader.h" // MEtFilterReader
#include "tthAnalysis/HiggsToTauTau/interface/GenLeptonReader.h" // GenLeptonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenParticleReader.h" // GenParticleReader
#include "tthAnalysis/HiggsToTauTau/interface/GenHadTauReader.h" // GenHadTauReader
#include "tthAnalysis/HiggsToTauTau/interface/GenPhotonReader.h" // GenPhotonReader
#include "tthAnalysis/HiggsToTauTau/interface/GenJetReader.h" // GenJetReader
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoReader.h" // LHEInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/EventInfoReader.h" // EventInfoReader
#include "tthAnalysis/HiggsToTauTau/interface/convert_to_ptrs.h" // convert_to_ptrs
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionCleaner.h" // RecoElectronCollectionCleaner, RecoMuonCollectionCleaner, RecoHadTauCollectionCleaner, RecoJetCollectionCleaner
#include "tthAnalysis/HiggsToTauTau/interface/ParticleCollectionGenMatcher.h" // RecoElectronCollectionGenMatcher, RecoMuonCollectionGenMatcher, RecoHadTauCollectionGenMatcher, RecoJetCollectionGenMatcher
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorLoose.h" // RecoElectronCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorFakeable.h" // RecoElectronCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoElectronCollectionSelectorTight.h" // RecoElectronCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorLoose.h" // RecoMuonCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorFakeable.h" // RecoMuonCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoMuonCollectionSelectorTight.h" // RecoMuonCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorLoose.h" // RecoHadTauCollectionSelectorLoose
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorFakeable.h" // RecoHadTauCollectionSelectorFakeable
#include "tthAnalysis/HiggsToTauTau/interface/RecoHadTauCollectionSelectorTight.h" // RecoHadTauCollectionSelectorTight
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelector.h" // RecoJetCollectionSelector
#include "tthAnalysis/HiggsToTauTau/interface/RecoJetCollectionSelectorBtag.h" // RecoJetCollectionSelectorBtagLoose, RecoJetCollectionSelectorBtagMedium
#include "tthAnalysis/HiggsToTauTau/interface/RunLumiEventSelector.h" // RunLumiEventSelector
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterSelector.h" // MEtFilterSelector
#include "tthAnalysis/HiggsToTauTau/interface/ElectronHistManager.h" // ElectronHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MuonHistManager.h" // MuonHistManager
#include "tthAnalysis/HiggsToTauTau/interface/HadTauHistManager.h" // HadTauHistManager
#include "tthAnalysis/HiggsToTauTau/interface/JetHistManager.h" // JetHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtHistManager.h" // MEtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/MEtFilterHistManager.h" // MEtFilterHistManager
#include "tthAnalysis/HiggsToTauTau/interface/EvtYieldHistManager.h" // EvtYieldHistManager
#include "tthAnalysis/HiggsToTauTau/interface/CutFlowTableHistManager.h" // CutFlowTableHistManager
#include "tthAnalysis/HiggsToTauTau/interface/WeightHistManager.h" // WeightHistManager
#include "tthAnalysis/HiggsToTauTau/interface/GenEvtHistManager.h" // GenEvtHistManager
#include "tthAnalysis/HiggsToTauTau/interface/LHEInfoHistManager.h" // LHEInfoHistManager
#include "tthAnalysis/HiggsToTauTau/interface/leptonTypes.h" // getLeptonType, kElectron, kMuon
#include "tthAnalysis/HiggsToTauTau/interface/analysisAuxFunctions.h" // getBTagWeight_option, getHadTau_genPdgId, isHigherPt, isMatched
#include "tthAnalysis/HiggsToTauTau/interface/leptonGenMatchingAuxFunctions.h" // getLeptonGenMatch_definitions_3lepton, getLeptonGenMatch_string, getLeptonGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/hadTauGenMatchingAuxFunctions.h" // getHadTauGenMatch_definitions_3tau, getHadTauGenMatch_string, getHadTauGenMatch_int
#include "tthAnalysis/HiggsToTauTau/interface/fakeBackgroundAuxFunctions.h"
#include "tthAnalysis/HiggsToTauTau/interface/hltPath.h" // hltPath, create_hltPaths, hltPaths_isTriggered, hltPaths_delete
#include "tthAnalysis/HiggsToTauTau/interface/hltPathReader.h" // hltPathReader
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2016.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2017.h"
#include "tthAnalysis/HiggsToTauTau/interface/Data_to_MC_CorrectionInterface_2018.h"
#include "tthAnalysis/HiggsToTauTau/interface/lutAuxFunctions.h" // loadTH2, get_sf_from_TH2
#include "tthAnalysis/HiggsToTauTau/interface/cutFlowTable.h" // cutFlowTableType
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/TTreeWrapper.h" // TTreeWrapper
#include "tthAnalysis/HiggsToTauTau/interface/hltFilter.h" // hltFilter()
#include "tthAnalysis/HiggsToTauTau/interface/EvtWeightManager.h" // EvtWeightManager
#include "tthAnalysis/HiggsToTauTau/interface/NtupleFillerBDT.h" // NtupleFillerBDT
#include "tthAnalysis/HiggsToTauTau/interface/mvaInputVariables.h" // comp_*()
#include "tthAnalysis/HiggsToTauTau/interface/Topness.h" // Topness
#include "tthAnalysis/HiggsToTauTau/interface/backgroundEstimation.h" // prob_chargeMisId
#include "tthAnalysis/HiggsToTauTau/interface/XGBInterface.h" // XGBInterface 
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface_OddEven.h" // TMVAInterface_OddEven
#include "tthAnalysis/HiggsToTauTau/interface/TMVAInterface.h" // TMVAInterface
#include "hhAnalysis/multilepton/interface/EvtHistManager_hh_2l_2tau.h" // EvtHistManager_hh_2l_2tau
#include "hhAnalysis/multilepton/interface/SVfit4tauHistManager_MarkovChain.h" // SVfit4tauHistManager_MarkovChain
#include "hhAnalysis/multilepton/interface/mySVfit4tauAuxFunctions.h" // getMeasuredTauLeptonType, getHadTauDecayMode

#include "TauAnalysis/ClassicSVfit4tau/interface/svFitHistogramAdapter4tau.h" // HistogramAdapterDiHiggs, HistogramAdapterHiggs
#include "TauAnalysis/ClassicSVfit/interface/ClassicSVfit.h" // ClassicSVfit                                                                                                                        
#include "TauAnalysis/ClassicSVfit/interface/MeasuredTauLepton.h" // classic_svFit::MeasuredTauLepton                                                                                                
#include "TauAnalysis/ClassicSVfit/interface/svFitHistogramAdapter.h"
#include "TauAnalysis/ClassicSVfit/interface/svFitAuxFunctions.h"

#include <boost/range/algorithm/copy.hpp> // boost::copy()                                                                                                                                          
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_keys                                                                                                                                 
#include <boost/math/special_functions/sign.hpp> // boost::math::sign()

#include <iostream> // std::cerr, std::fixed
#include <iomanip> // std::setprecision(), std::setw()
#include <string> // std::string
#include <vector> // std::vector<>
#include <cstdlib> // EXIT_SUCCESS, EXIT_FAILURE
#include <fstream> // std::ofstream
#include <assert.h> // assert

#include <sstream>
#include <map>
#include <iterator>


edm::ParameterSet
makeHistManager_cfg(const std::string & process,
                    const std::string & category,
                    const std::string & era,
                    const std::string & central_or_shift,
		    const std::vector<double> & gen_mHH,
                    int idx = -1)
{
  edm::ParameterSet cfg = makeHistManager_cfg(process, category, era, central_or_shift, idx);
  cfg.addParameter<std::vector<double>>("gen_mHH", gen_mHH);
  return cfg;
}

edm::ParameterSet
makeHistManager_cfg(const std::string & process,
                    const std::string & category,
                    const std::string & era,
                    const std::string & central_or_shift,
		    const std::vector<double> & gen_mHH,
                    const std::string & option,
                    int idx = -1)
{
  edm::ParameterSet cfg = makeHistManager_cfg(process, category, era, central_or_shift, gen_mHH, idx);
  cfg.addParameter<std::string>("option", option);
  return cfg;
}


typedef math::PtEtaPhiMLorentzVector LV;
typedef std::vector<std::string> vstring;
typedef std::vector<double> vdouble;

enum { kFR_disabled, kFR_2lepton, kFR_4L, kFR_2tau };

//const int hadTauSelection_antiElectron = 1; // vLoose
//const int hadTauSelection_antiMuon = 1; // Loose
const int hadTauSelection_antiElectron = -1; // not applied
const int hadTauSelection_antiMuon = -1; // not applied

struct HadTauHistManagerWrapper_eta
{
  HadTauHistManager* histManager_;
  double etaMin_;
  double etaMax_;
};



/**
 * @brief Produce datacard and control plots for 2l_2tau category of HH "multilepton" (HH->WWWW,WWtt,tttt) analysis.
 */
int main(int argc, char* argv[])
{
//--- throw an exception in case ROOT encounters an error
  gErrorAbortLevel = kError;

//--- parse command-line arguments
  if ( argc < 2 ) {
    std::cout << "Usage: " << argv[0] << " [parameters.py]" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "<analyze_hh_2l_2tau>:" << std::endl;

//--- keep track of time it takes the macro to execute
  TBenchmark clock;
  clock.Start("analyze_hh_2l_2tau");

//--- read python configuration parameters
  if ( !edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process") )
    throw cms::Exception("analyze_hh_2l_2tau")
      << "No ParameterSet 'process' found in configuration file = " << argv[1] << " !!\n";

  edm::ParameterSet cfg = edm::readPSetsFrom(argv[1])->getParameter<edm::ParameterSet>("process");

  edm::ParameterSet cfg_analyze = cfg.getParameter<edm::ParameterSet>("analyze_hh_2l_2tau");

  std::string treeName = cfg_analyze.getParameter<std::string>("treeName");

  std::string process_string = cfg_analyze.getParameter<std::string>("process");
  bool isSignal = ( process_string == "signal" ) ? true : false;

  std::string histogramDir = cfg_analyze.getParameter<std::string>("histogramDir");
  bool isMCClosure_e = histogramDir.find("mcClosure_e") != std::string::npos;
  bool isMCClosure_m = histogramDir.find("mcClosure_m") != std::string::npos;
  bool isMCClosure_t = histogramDir.find("mcClosure_t") != std::string::npos;

  std::string era_string = cfg_analyze.getParameter<std::string>("era");
  const int era = get_era(era_string);

  vstring triggerNames_1e = cfg_analyze.getParameter<vstring>("triggers_1e");
  std::vector<hltPath*> triggers_1e = create_hltPaths(triggerNames_1e);
  bool use_triggers_1e = cfg_analyze.getParameter<bool>("use_triggers_1e");
  vstring triggerNames_2e = cfg_analyze.getParameter<vstring>("triggers_2e");
  std::vector<hltPath*> triggers_2e = create_hltPaths(triggerNames_2e);
  bool use_triggers_2e = cfg_analyze.getParameter<bool>("use_triggers_2e");
  vstring triggerNames_1mu = cfg_analyze.getParameter<vstring>("triggers_1mu");
  std::vector<hltPath*> triggers_1mu = create_hltPaths(triggerNames_1mu);
  bool use_triggers_1mu = cfg_analyze.getParameter<bool>("use_triggers_1mu");
  vstring triggerNames_2mu = cfg_analyze.getParameter<vstring>("triggers_2mu");
  std::vector<hltPath*> triggers_2mu = create_hltPaths(triggerNames_2mu);
  bool use_triggers_2mu = cfg_analyze.getParameter<bool>("use_triggers_2mu");
  vstring triggerNames_1e1mu = cfg_analyze.getParameter<vstring>("triggers_1e1mu");
  std::vector<hltPath*> triggers_1e1mu = create_hltPaths(triggerNames_1e1mu);
  bool use_triggers_1e1mu = cfg_analyze.getParameter<bool>("use_triggers_1e1mu");

  bool apply_offline_e_trigger_cuts_1e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e");
  bool apply_offline_e_trigger_cuts_2e = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2e");
  bool apply_offline_e_trigger_cuts_1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1mu");
  bool apply_offline_e_trigger_cuts_2mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_2mu");
  bool apply_offline_e_trigger_cuts_1e1mu = cfg_analyze.getParameter<bool>("apply_offline_e_trigger_cuts_1e1mu");

  enum { kOS, kSS, kDisabled };
  std::string leptonChargeSelection_string = cfg_analyze.getParameter<std::string>("leptonChargeSelection");
  int leptonChargeSelection = -1;
  if      ( leptonChargeSelection_string == "OS"       ) leptonChargeSelection = kOS;
  else if ( leptonChargeSelection_string == "SS"       ) leptonChargeSelection = kSS;
  else if ( leptonChargeSelection_string == "disabled" ) leptonChargeSelection = kDisabled;
  else throw cms::Exception("analyze_hh_2l_2tau")
    << "Invalid Configuration parameter 'leptonChargeSelection' = " << leptonChargeSelection_string << " !!\n";
  std::string hadTauChargeSelection_string = cfg_analyze.getParameter<std::string>("hadTauChargeSelection");
  int hadTauChargeSelection = -1;
  if      ( hadTauChargeSelection_string == "OS"       ) hadTauChargeSelection = kOS;
  else if ( hadTauChargeSelection_string == "SS"       ) hadTauChargeSelection = kSS;
  else if ( hadTauChargeSelection_string == "disabled" ) hadTauChargeSelection = kDisabled;
  else throw cms::Exception("analyze_hh_2l_2tau")
    << "Invalid Configuration parameter 'hadTauChargeSelection' = " << hadTauChargeSelection_string << " !!\n";

  const std::string electronSelection_string = cfg_analyze.getParameter<std::string>("electronSelection");
  const std::string muonSelection_string     = cfg_analyze.getParameter<std::string>("muonSelection");
  std::cout << "electronSelection_string = " << electronSelection_string << "\n"
               "muonSelection_string     = " << muonSelection_string     << '\n'
  ;
  const int electronSelection = get_selection(electronSelection_string);
  const int muonSelection     = get_selection(muonSelection_string);
  double lep_mva_cut = cfg_analyze.getParameter<double>("lep_mva_cut"); // CV: used for tight lepton selection only

  bool apply_leptonGenMatching = cfg_analyze.getParameter<bool>("apply_leptonGenMatching");
  std::vector<leptonChargeFlipGenMatchEntry> leptonGenMatch_definitions = getLeptonChargeFlipGenMatch_definitions_2lepton(apply_leptonGenMatching);
  std::cout << "leptonGenMatch_definitions:" << std::endl;
  std::cout << leptonGenMatch_definitions;

  TString hadTauSelection_string = cfg_analyze.getParameter<std::string>("hadTauSelection").data();
  TObjArray* hadTauSelection_parts = hadTauSelection_string.Tokenize("|");
  assert(hadTauSelection_parts->GetEntries() >= 1);
  const std::string hadTauSelection_part1 = (dynamic_cast<TObjString*>(hadTauSelection_parts->At(0)))->GetString().Data();
  const int hadTauSelection = get_selection(hadTauSelection_part1);
  std::string hadTauSelection_part2 = ( hadTauSelection_parts->GetEntries() == 2 ) ? (dynamic_cast<TObjString*>(hadTauSelection_parts->At(1)))->GetString().Data() : "";
  delete hadTauSelection_parts;

  bool apply_hadTauGenMatching = cfg_analyze.getParameter<bool>("apply_hadTauGenMatching");
  std::vector<hadTauGenMatchEntry> hadTauGenMatch_definitions = getHadTauGenMatch_definitions_2tau(apply_hadTauGenMatching);
  std::cout << "hadTauGenMatch_definitions:" << std::endl;
  std::cout << hadTauGenMatch_definitions;

  std::string chargeSumSelection_string = cfg_analyze.getParameter<std::string>("chargeSumSelection");
  int chargeSumSelection = -1;
  if      ( chargeSumSelection_string == "OS"       ) chargeSumSelection = kOS;
  else if ( chargeSumSelection_string == "SS"       ) chargeSumSelection = kSS;
  else if ( chargeSumSelection_string == "disabled" ) chargeSumSelection = kDisabled;
  else throw cms::Exception("analyze_hh_2l_2tau")
    << "Invalid Configuration parameter 'chargeSumSelection' = " << chargeSumSelection_string << " !!\n";
  TRandom3 rnd; // used to randomly kill one of three possible combination of measuredTauLeptons into pairs in case chargeSumSelection is "SS" or "disabled",
                // to ensure that exactly two possible combination of measuredTauLeptons are considered, regardless of chargeSumSelection

  bool isMC = cfg_analyze.getParameter<bool>("isMC");
  bool isMC_tH = ( process_string == "tHq" || process_string == "tHW" ) ? true : false;
  bool hasLHE = cfg_analyze.getParameter<bool>("hasLHE");
  std::string central_or_shift = cfg_analyze.getParameter<std::string>("central_or_shift");
  double lumiScale = ( process_string != "data_obs" ) ? cfg_analyze.getParameter<double>("lumiScale") : 1.;
  bool apply_genWeight = cfg_analyze.getParameter<bool>("apply_genWeight");
  bool apply_hlt_filter = cfg_analyze.getParameter<bool>("apply_hlt_filter");
  bool apply_met_filters = cfg_analyze.getParameter<bool>("apply_met_filters");
  edm::ParameterSet cfgMEtFilter = cfg_analyze.getParameter<edm::ParameterSet>("cfgMEtFilter");
  MEtFilterSelector metFilterSelector(cfgMEtFilter, isMC);
  bool apply_hadTauFakeRateSF = cfg_analyze.getParameter<bool>("apply_hadTauFakeRateSF");
  const bool useNonNominal = cfg_analyze.getParameter<bool>("useNonNominal");
  const bool useNonNominal_jetmet = useNonNominal || ! isMC;

  const edm::ParameterSet additionalEvtWeight = cfg_analyze.getParameter<edm::ParameterSet>("evtWeight");
  const bool applyAdditionalEvtWeight = additionalEvtWeight.getParameter<bool>("apply");
  EvtWeightManager * eventWeightManager = nullptr;
  if(applyAdditionalEvtWeight)
  {
    eventWeightManager = new EvtWeightManager(additionalEvtWeight);
  }

  bool isDEBUG = cfg_analyze.getParameter<bool>("isDEBUG");
  if ( isDEBUG ) std::cout << "Warning: DEBUG mode enabled -> trigger selection will not be applied for data !!" << std::endl;

  checkOptionValidity(central_or_shift, isMC);
  const int jetToLeptonFakeRate_option = getJetToLeptonFR_option(central_or_shift);
  const int hadTauPt_option            = getHadTauPt_option     (central_or_shift);
  const int jetToTauFakeRate_option    = getJetToTauFR_option   (central_or_shift);
  const int lheScale_option            = getLHEscale_option     (central_or_shift);
  const int jetBtagSF_option           = getBTagWeight_option   (central_or_shift);

  const int met_option   = useNonNominal_jetmet ? kMEt_central_nonNominal : getMET_option(central_or_shift, isMC);
  const int jetPt_option = useNonNominal_jetmet ? kMEt_central_nonNominal : getJet_option(central_or_shift, isMC);

  std::cout
    << "central_or_shift = "               << central_or_shift           << "\n"
       " -> jetToLeptonFakeRate_option = " << jetToLeptonFakeRate_option << "\n"
       " -> hadTauPt_option            = " << hadTauPt_option            << "\n"
       " -> jetToTauFakeRate_option    = " << jetToTauFakeRate_option    << "\n"
       " -> lheScale_option            = " << lheScale_option            << "\n"
       " -> jetBtagSF_option           = " << jetBtagSF_option           << "\n"
       " -> met_option                 = " << met_option                 << "\n"
       " -> jetPt_option               = " << jetPt_option               << '\n'
  ;

  edm::ParameterSet cfg_dataToMCcorrectionInterface;
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("era", era_string);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiElectron", hadTauSelection_antiElectron);
  cfg_dataToMCcorrectionInterface.addParameter<int>("hadTauSelection_antiMuon", hadTauSelection_antiMuon);
  cfg_dataToMCcorrectionInterface.addParameter<std::string>("central_or_shift", central_or_shift);
  cfg_dataToMCcorrectionInterface.addParameter<bool>("isDEBUG", isDEBUG);
  Data_to_MC_CorrectionInterface_Base * dataToMCcorrectionInterface = nullptr;
  switch(era)
  {
    case kEra_2016: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2016(cfg_dataToMCcorrectionInterface); break;
    case kEra_2017: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2017(cfg_dataToMCcorrectionInterface); break;
    case kEra_2018: dataToMCcorrectionInterface = new Data_to_MC_CorrectionInterface_2018(cfg_dataToMCcorrectionInterface); break;
    default: throw cmsException("analyze_0l_2tau", __LINE__) << "Invalid era = " << era;
  }

  std::string applyFakeRateWeights_string = cfg_analyze.getParameter<std::string>("applyFakeRateWeights");
  int applyFakeRateWeights = -1;
  if      ( applyFakeRateWeights_string == "disabled" ) applyFakeRateWeights = kFR_disabled;
  else if ( applyFakeRateWeights_string == "2lepton"  ) applyFakeRateWeights = kFR_2lepton;
  else if ( applyFakeRateWeights_string == "4L"       ) applyFakeRateWeights = kFR_4L;
  else if ( applyFakeRateWeights_string == "2tau"     ) applyFakeRateWeights = kFR_2tau;
  else throw cms::Exception("analyze_hh_2l_2tau")
    << "Invalid Configuration parameter 'applyFakeRateWeights' = " << applyFakeRateWeights_string << " !!\n";

  LeptonFakeRateInterface* leptonFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_2lepton || applyFakeRateWeights == kFR_4L ) {
    edm::ParameterSet cfg_leptonFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("leptonFakeRateWeight");
    leptonFakeRateInterface = new LeptonFakeRateInterface(cfg_leptonFakeRateWeight, jetToLeptonFakeRate_option);
  }

  JetToTauFakeRateInterface* jetToTauFakeRateInterface = 0;
  if ( applyFakeRateWeights == kFR_4L || applyFakeRateWeights == kFR_2tau ) {
    edm::ParameterSet cfg_hadTauFakeRateWeight = cfg_analyze.getParameter<edm::ParameterSet>("hadTauFakeRateWeight");
    cfg_hadTauFakeRateWeight.addParameter<std::string>("hadTauSelection", hadTauSelection_part2);
    jetToTauFakeRateInterface = new JetToTauFakeRateInterface(cfg_hadTauFakeRateWeight, jetToTauFakeRate_option);
  }

  bool fillGenEvtHistograms = cfg_analyze.getParameter<bool>("fillGenEvtHistograms");
  edm::ParameterSet cfg_EvtYieldHistManager = cfg_analyze.getParameter<edm::ParameterSet>("cfgEvtYieldHistManager");

  std::string branchName_electrons = cfg_analyze.getParameter<std::string>("branchName_electrons");
  std::string branchName_muons = cfg_analyze.getParameter<std::string>("branchName_muons");
  std::string branchName_hadTaus = cfg_analyze.getParameter<std::string>("branchName_hadTaus");
  std::string branchName_jets = cfg_analyze.getParameter<std::string>("branchName_jets");
  std::string branchName_met = cfg_analyze.getParameter<std::string>("branchName_met");

  std::string branchName_genLeptons = cfg_analyze.getParameter<std::string>("branchName_genLeptons");
  std::string branchName_genHadTaus = cfg_analyze.getParameter<std::string>("branchName_genHadTaus");
  std::string branchName_genPhotons = cfg_analyze.getParameter<std::string>("branchName_genPhotons");
  std::string branchName_genJets = cfg_analyze.getParameter<std::string>("branchName_genJets");
  bool redoGenMatching = cfg_analyze.getParameter<bool>("redoGenMatching");

  const bool selectBDT = cfg_analyze.exists("selectBDT") ? cfg_analyze.getParameter<bool>("selectBDT") : false;

  std::string BDTFileName_even  = cfg_analyze.getParameter<std::string>("BDT_xml_FileName_even");
  std::string BDTFileName_odd   = cfg_analyze.getParameter<std::string>("BDT_xml_FileName_odd");
  std::vector<double> gen_mHH = cfg_analyze.getParameter<std::vector<double>>("gen_mHH");
  std::string BDTFileName_even_pkl  = cfg_analyze.getParameter<std::string>("pkl_FileName_even");
  std::string BDTFileName_odd_pkl   = cfg_analyze.getParameter<std::string>("pkl_FileName_odd");
  std::string fitFunctionFileName = cfg_analyze.getParameter<std::string>("fitFunctionFileName");


  std::string selEventsFileName_input = cfg_analyze.getParameter<std::string>("selEventsFileName_input");
  std::cout << "selEventsFileName_input = " << selEventsFileName_input << std::endl;
  RunLumiEventSelector* run_lumi_eventSelector = 0;
  if ( selEventsFileName_input != "" ) {
    edm::ParameterSet cfg_runLumiEventSelector;
    cfg_runLumiEventSelector.addParameter<std::string>("inputFileName", selEventsFileName_input);
    cfg_runLumiEventSelector.addParameter<std::string>("separator", ":");
    run_lumi_eventSelector = new RunLumiEventSelector(cfg_runLumiEventSelector);
  }

  std::string selEventsFileName_output = cfg_analyze.getParameter<std::string>("selEventsFileName_output");
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

  fwlite::InputSource inputFiles(cfg);
  int maxEvents = inputFiles.maxEvents();
  std::cout << " maxEvents = " << maxEvents << std::endl;
  unsigned reportEvery = inputFiles.reportAfter();

  fwlite::OutputFiles outputFile(cfg);
  fwlite::TFileService fs = fwlite::TFileService(outputFile.file().data());

  TTreeWrapper* inputTree = new TTreeWrapper(treeName.data(), inputFiles.files(), maxEvents);
  std::cout << "Loaded " << inputTree->getFileCount() << " file(s)." << std::endl;

//--- declare event-level variables
  EventInfo eventInfo(isSignal, isMC, isMC_tH);
  EventInfoReader eventInfoReader(&eventInfo);
  inputTree->registerReader(&eventInfoReader);

  hltPathReader hltPathReader_instance({ triggers_1e, triggers_2e, triggers_1mu, triggers_2mu, triggers_1e1mu });
  inputTree -> registerReader(&hltPathReader_instance);

  if(eventWeightManager)
  {
    inputTree->registerReader(eventWeightManager);
  }

//--- declare particle collections
  const bool readGenObjects = isMC && !redoGenMatching;
  RecoMuonReader* muonReader = new RecoMuonReader(era, branchName_muons, readGenObjects);
  inputTree->registerReader(muonReader);
  RecoMuonCollectionGenMatcher muonGenMatcher;
  RecoMuonCollectionSelectorLoose preselMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorFakeable fakeableMuonSelector(era, -1, isDEBUG);
  RecoMuonCollectionSelectorTight tightMuonSelector(era, -1, isDEBUG);
  tightMuonSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoElectronReader* electronReader = new RecoElectronReader(era, branchName_electrons, readGenObjects);
  electronReader->readUncorrected(useNonNominal);
  inputTree->registerReader(electronReader);
  RecoElectronCollectionGenMatcher electronGenMatcher;
  RecoElectronCollectionCleaner electronCleaner(0.3, isDEBUG);
  RecoElectronCollectionSelectorLoose preselElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorFakeable fakeableElectronSelector(era, -1, isDEBUG);
  RecoElectronCollectionSelectorTight tightElectronSelector(era, -1, isDEBUG);
  tightElectronSelector.getSelector().set_min_mvaTTH(lep_mva_cut);

  RecoHadTauReader* hadTauReader = new RecoHadTauReader(era, branchName_hadTaus, readGenObjects);
  hadTauReader->setHadTauPt_central_or_shift(hadTauPt_option);
  inputTree->registerReader(hadTauReader);
  RecoHadTauCollectionGenMatcher hadTauGenMatcher;
  RecoHadTauCollectionCleaner hadTauCleaner(0.3, isDEBUG);
  RecoHadTauCollectionSelectorLoose preselHadTauSelector(era, -1, isDEBUG);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) preselHadTauSelector.set(hadTauSelection_part2);
  preselHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  preselHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorFakeable fakeableHadTauSelector(era, -1, isDEBUG);
  if ( hadTauSelection_part2 == "dR03mvaVLoose" || hadTauSelection_part2 == "dR03mvaVVLoose" ) fakeableHadTauSelector.set(hadTauSelection_part2);
  fakeableHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  fakeableHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauCollectionSelectorTight tightHadTauSelector(era, -1, isDEBUG);
  if ( hadTauSelection_part2 != "" ) tightHadTauSelector.set(hadTauSelection_part2);
  tightHadTauSelector.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauSelector.set_min_antiMuon(hadTauSelection_antiMuon);
  RecoHadTauSelectorTight tightHadTauFilter(era, -1, isDEBUG);
  tightHadTauFilter.set("dR03mvaVTight");
  tightHadTauFilter.set_min_antiElectron(hadTauSelection_antiElectron);
  tightHadTauFilter.set_min_antiMuon(hadTauSelection_antiMuon);

  RecoJetReader* jetReader = new RecoJetReader(era, isMC, branchName_jets, readGenObjects);
  jetReader->setPtMass_central_or_shift(jetPt_option);
  jetReader->setBranchName_BtagWeight(jetBtagSF_option);
  inputTree->registerReader(jetReader);
  RecoJetCollectionGenMatcher jetGenMatcher;
  RecoJetCollectionCleaner jetCleaner(0.4, isDEBUG);
  RecoJetCollectionSelector jetSelector(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagLoose jetSelectorBtagLoose(era, -1, isDEBUG);
  RecoJetCollectionSelectorBtagMedium jetSelectorBtagMedium(era, -1, isDEBUG);

//--- declare missing transverse energy
  RecoMEtReader* metReader = new RecoMEtReader(era, isMC, branchName_met);
  metReader->setMEt_central_or_shift(met_option);
  inputTree->registerReader(metReader);

  MEtFilter metFilters;
  MEtFilterReader* metFilterReader = new MEtFilterReader(&metFilters, era);
  inputTree -> registerReader(metFilterReader);

//--- declare generator level information
  GenLeptonReader* genLeptonReader = 0;
  GenHadTauReader* genHadTauReader = 0;
  GenPhotonReader* genPhotonReader = 0;
  GenJetReader* genJetReader = 0;
  LHEInfoReader* lheInfoReader = 0;
  if ( isMC ) {
    if(! readGenObjects)
    {
      if ( branchName_genLeptons != "" ) {
        genLeptonReader = new GenLeptonReader(branchName_genLeptons);
        inputTree->registerReader(genLeptonReader);
      }
      if ( branchName_genHadTaus != "" ) {
        genHadTauReader = new GenHadTauReader(branchName_genHadTaus);
        inputTree->registerReader(genHadTauReader);
      }
      if ( branchName_genPhotons != "" ) {
        genPhotonReader = new GenPhotonReader(branchName_genPhotons);
        inputTree -> registerReader(genPhotonReader);
      }
      if ( branchName_genJets != "" ) {
        genJetReader = new GenJetReader(branchName_genJets);
        inputTree->registerReader(genJetReader);
      }
    }
    lheInfoReader = new LHEInfoReader(hasLHE);
    inputTree->registerReader(lheInfoReader);
  }



  //--- initialize BDTs
  /* 
  // Sandeep's mwthod
  std::string BDTFileName = "";
  if(eventInfo.event % 2){// ODD EVENT NUMBER CASE
    BDTFileName = BDTFileName_odd;
  }else{ // EVEN EVENT NUMBER CASE
    BDTFileName = BDTFileName_even; 
  }
  */

  std::vector<std::string> BDTInputVariables_SUM = 
    {
      "diHiggsMass", 
      "diHiggsVisMass", 
      "tau1_pt", 
      "nBJet_medium", 
      "gen_mHH", 
      "nElectron", 
      "dr_lep_tau_min_SS", 
      "met_LD", 
      "tau2_pt", 
      "dr_lep_tau_min_OS"
    }; // Need to adapt to different mass training modes: all, low and High (Currently this is for all mass traning)

  std::vector<std::string> BDTSpectatorVars = {};

  XGBInterface* XGB_SUM  = NULL;
  TMVAInterface* BDT_SUM = NULL;

  if(fitFunctionFileName != ""){ // Transfrom Input Var.s before feeding into the BDT .pkl/.xml files
    // Xandra's method (with .pkl file)
    XGB_SUM = new XGBInterface(BDTFileName_odd_pkl, BDTFileName_even_pkl , fitFunctionFileName,  BDTInputVariables_SUM); 

    // -----  Using New TMVAInterface class with built-in Odd-Even interface ----- 
    BDT_SUM = new TMVAInterface(BDTFileName_odd, BDTFileName_even, BDTInputVariables_SUM, fitFunctionFileName, BDTSpectatorVars); 
    BDT_SUM->enableBDTTransform();
  }else{
    // Xandra's method (with .pkl file)
    XGB_SUM = new XGBInterface(BDTFileName_odd_pkl, BDTFileName_even_pkl, BDTInputVariables_SUM); 
  
    // -----  Using New TMVAInterface class with built-in Odd-Even interface ----- 
    BDT_SUM = new TMVAInterface(BDTFileName_odd, BDTFileName_even, BDTInputVariables_SUM, BDTSpectatorVars); 
    BDT_SUM->enableBDTTransform();

    // ------- Using special TMVAInterface_OddEven class [Used in July11 submission]
    // TMVAInterface_OddEven BDT_SUM(BDTFileName_odd, BDTFileName_even, BDTInputVariables_SUM, BDTSpectatorVars); 
    // BDT_SUM.enableBDTTransform();
  }


  std::map<std::string, double> BDTInputs_SUM;
  



//--- open output file containing run:lumi:event numbers of events passing final event selection criteria
  std::ostream* selEventsFile = ( selEventsFileName_output != "" ) ? new std::ofstream(selEventsFileName_output.data(), std::ios::out) : 0;
  std::cout << "selEventsFileName_output = " << selEventsFileName_output << std::endl;

//--- declare histograms
  GenEvtHistManager* genEvtHistManager_beforeCuts = nullptr;
  LHEInfoHistManager* lheInfoHistManager_beforeCuts = nullptr;
  if ( isMC ) {
    genEvtHistManager_beforeCuts = new GenEvtHistManager(makeHistManager_cfg(process_string,
      Form("%s/unbiased/genEvt", histogramDir.data()), era_string, central_or_shift));
    genEvtHistManager_beforeCuts->bookHistograms(fs);
    lheInfoHistManager_beforeCuts = new LHEInfoHistManager(makeHistManager_cfg(process_string,
      Form("%s/unbiased/lheInfo", histogramDir.data()), era_string, central_or_shift));
    lheInfoHistManager_beforeCuts->bookHistograms(fs);

    if(eventWeightManager)
    {
      genEvtHistManager_beforeCuts->bookHistograms(fs, eventWeightManager);
    }
  }

  struct selHistManagerType
  {
    ElectronHistManager* electrons_;
    ElectronHistManager* leadElectron_;
    ElectronHistManager* subleadElectron_;
    MuonHistManager* muons_;
    MuonHistManager* leadMuon_;
    MuonHistManager* subleadMuon_;
    HadTauHistManager* hadTaus_;
    HadTauHistManager* leadHadTau_;
    HadTauHistManager* subleadHadTau_;
    JetHistManager* jets_;
    JetHistManager* BJets_loose_;
    JetHistManager* BJets_medium_;
    MEtHistManager* met_;
    MEtFilterHistManager* metFilters_;
    EvtHistManager_hh_2l_2tau* evt_;
    SVfit4tauHistManager_MarkovChain* svFit4tau_wMassConstraint_;
    std::map<std::string, EvtHistManager_hh_2l_2tau*> evt_in_decayModes_;
    std::map<std::string, SVfit4tauHistManager_MarkovChain*> svFit4tau_wMassConstraint_in_decayModes_;
    std::map<std::string, EvtHistManager_hh_2l_2tau*> evt_in_categories_;
    std::map<std::string, SVfit4tauHistManager_MarkovChain*> svFit4tau_wMassConstraint_in_categories_;
    GenEvtHistManager* genEvtHistManager_afterCuts_;
    LHEInfoHistManager* lheInfoHistManager_afterCuts_;
    std::map<std::string, LHEInfoHistManager*> lheInfoHistManager_afterCuts_in_categories_;
    EvtYieldHistManager* evtYield_;
    WeightHistManager* weights_;
  };

  typedef std::map<int, selHistManagerType*> int_to_selHistManagerMap;
  std::map<int, int_to_selHistManagerMap> selHistManagers;
  for ( std::vector<leptonChargeFlipGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
        leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {
    for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
          hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition->name_;
      if ( apply_leptonGenMatching && apply_hadTauGenMatching ) process_and_genMatch += "&";
      if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;
      int idxLepton = leptonGenMatch_definition->idx_;
      int idxHadTau = hadTauGenMatch_definition->idx_;

      selHistManagerType* selHistManager = new selHistManagerType();
      selHistManager->electrons_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/electrons", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
      selHistManager->electrons_->bookHistograms(fs);
      selHistManager->leadElectron_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/leadElectron", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 0));
      selHistManager->leadElectron_->bookHistograms(fs);
      selHistManager->subleadElectron_ = new ElectronHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/subleadElectron", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 1));
      selHistManager->subleadElectron_->bookHistograms(fs);
      selHistManager->muons_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/muons", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
      selHistManager->muons_->bookHistograms(fs);
      selHistManager->leadMuon_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/leadMuon", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 0));
      selHistManager->leadMuon_->bookHistograms(fs);
      selHistManager->subleadMuon_ = new MuonHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/subleadMuon", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 1));
      selHistManager->subleadMuon_->bookHistograms(fs);
      selHistManager->hadTaus_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/hadTaus", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
      selHistManager->hadTaus_->bookHistograms(fs);
      selHistManager->leadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/leadHadTau", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 0));
      selHistManager->leadHadTau_->bookHistograms(fs);
      selHistManager->subleadHadTau_ = new HadTauHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/subleadHadTau", histogramDir.data()), era_string, central_or_shift, "minimalHistograms", 1));
      selHistManager->subleadHadTau_->bookHistograms(fs);
      selHistManager->jets_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/jets", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
      selHistManager->jets_->bookHistograms(fs);
      selHistManager->BJets_loose_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/BJets_loose", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
      selHistManager->BJets_loose_->bookHistograms(fs);
      selHistManager->BJets_medium_ = new JetHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/BJets_medium", histogramDir.data()), era_string, central_or_shift, "allHistograms"));
      selHistManager->BJets_medium_->bookHistograms(fs);
      selHistManager->met_ = new MEtHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/met", histogramDir.data()), era_string, central_or_shift));
      selHistManager->met_->bookHistograms(fs);
      selHistManager->metFilters_ = new MEtFilterHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/metFilters", histogramDir.data()), era_string, central_or_shift));
      selHistManager->metFilters_->bookHistograms(fs);
      selHistManager->evt_ = new EvtHistManager_hh_2l_2tau(makeHistManager_cfg(process_and_genMatch,
	Form("%s/sel/evt", histogramDir.data()), era_string, central_or_shift, gen_mHH));
      selHistManager->evt_->bookHistograms(fs);
      selHistManager->svFit4tau_wMassConstraint_ = new SVfit4tauHistManager_MarkovChain(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/svFit4tau_wMassConstraint", histogramDir.data()), era_string, central_or_shift));
      selHistManager->svFit4tau_wMassConstraint_->bookHistograms(fs);
      selHistManager->genEvtHistManager_afterCuts_ = nullptr;
      selHistManager->lheInfoHistManager_afterCuts_ = nullptr;
      if ( isMC ) {
        selHistManager->genEvtHistManager_afterCuts_ = new GenEvtHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/genEvt", histogramDir.data()), era_string, central_or_shift));
        selHistManager->genEvtHistManager_afterCuts_->bookHistograms(fs);
        selHistManager->lheInfoHistManager_afterCuts_ = new LHEInfoHistManager(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/lheInfo", histogramDir.data()), era_string, central_or_shift));
        selHistManager->lheInfoHistManager_afterCuts_->bookHistograms(fs);

        if(eventWeightManager)
        {
          selHistManager->genEvtHistManager_afterCuts_->bookHistograms(fs, eventWeightManager);
        }
      }
      vstring categories_evt = {
        "2lSS_2tau", "2lOS_2tau", 
        "2e_2tau", "1e1mu_2tau", "2mu_2tau",
        "2eSS_2tau", "2eOS_2tau", "1e1muSS_2tau", "1e1muOS_2tau", "2muSS_2tau", "2muOS_2tau"
        ,"2lOS_2tau_wChargeFlipWeights", "2eOS_2tau_wChargeFlipWeights", "1e1muOS_2tau_wChargeFlipWeights", "2muOS_2tau_wChargeFlipWeights"
      };
      for ( vstring::const_iterator category = categories_evt.begin();
            category != categories_evt.end(); ++category ) {
        TString histogramDir_category = histogramDir.data();
        histogramDir_category.ReplaceAll("2l_2tau", category->data());
        selHistManager->evt_in_categories_[*category] = new EvtHistManager_hh_2l_2tau(makeHistManager_cfg(process_and_genMatch,
	  Form("%s/sel/evt", histogramDir_category.Data()), era_string, central_or_shift, gen_mHH)); // Added the signal mass vector
        selHistManager->evt_in_categories_[*category]->bookHistograms(fs);
        selHistManager->svFit4tau_wMassConstraint_in_categories_[*category] = new SVfit4tauHistManager_MarkovChain(makeHistManager_cfg(process_and_genMatch,
          Form("%s/sel/svFit4tau_wMassConstraint", histogramDir_category.Data()), era_string, central_or_shift));
        selHistManager->svFit4tau_wMassConstraint_in_categories_[*category]->bookHistograms(fs);
        if ( isMC ) {
	  selHistManager->lheInfoHistManager_afterCuts_in_categories_[*category] = new LHEInfoHistManager(makeHistManager_cfg(process_and_genMatch,
            Form("%s/sel/lheInfo", histogramDir_category.Data()), era_string, central_or_shift));
          selHistManager->lheInfoHistManager_afterCuts_in_categories_[*category]->bookHistograms(fs);
	}
      }
      edm::ParameterSet cfg_EvtYieldHistManager_sel = makeHistManager_cfg(process_and_genMatch, 
        Form("%s/sel/evtYield", histogramDir.data()), era_string, central_or_shift);
      cfg_EvtYieldHistManager_sel.addParameter<edm::ParameterSet>("runPeriods", cfg_EvtYieldHistManager);
      cfg_EvtYieldHistManager_sel.addParameter<bool>("isMC", isMC);
      selHistManager->evtYield_ = new EvtYieldHistManager(cfg_EvtYieldHistManager_sel);
      selHistManager->evtYield_->bookHistograms(fs);  
      selHistManager->weights_ = new WeightHistManager(makeHistManager_cfg(process_and_genMatch,
        Form("%s/sel/weights", histogramDir.data()), era_string, central_or_shift));
      selHistManager->weights_->bookHistograms(fs, { "genWeight", "pileupWeight", "triggerWeight", "data_to_MC_correction", "fakeRate" });
      selHistManagers[idxLepton][idxHadTau] = selHistManager;
    }
  }


  NtupleFillerBDT<float, int>* bdt_filler = nullptr;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::float_type float_type;
  typedef std::remove_pointer<decltype(bdt_filler)>::type::int_type int_type;
  if(selectBDT)
  {
    bdt_filler = new std::remove_pointer<decltype(bdt_filler)>::type(
      makeHistManager_cfg(process_string, Form("%s/sel/evtntuple", histogramDir.data()), era_string, central_or_shift)
    );
    bdt_filler->register_variable<float_type>(
      "lep1_pt", "lep1_conePt", "lep1_eta", "lep1_tth_mva", "mT_lep1", "lep1_phi",
      "lep2_pt", "lep2_conePt", "lep2_eta", "lep2_tth_mva", "mT_lep2", "lep2_phi",
      "tau1_pt", "tau1_eta", "tau1_mva", "tau1_phi",
      "tau2_pt", "tau2_eta", "tau2_mva", "tau2_phi",
      "dr_lep1_tau1", "dr_lep1_tau2", "dr_lep2_tau1", "dr_lep2_tau2",
      "dr_leps", "dr_taus", "avg_dr_jet",
      "met", "mht", "met_LD", "HT", "STMET", "met_phi",
      "Smin_llMEt", "m_ll", "pT_ll", "pT_llMEt", "Smin_lltautau", "mTauTau",
      "mTauTauVis", "ptTauTauVis", "diHiggsVisMass", "diHiggsMass",
      "logTopness_publishedChi2", "logTopness_fixedChi2",
      "genWeight", "evtWeight",
      "m_lep1_tau1", "m_lep2_tau1", "m_lep1_tau2", "m_lep2_tau2", "pt_HH_recoil",
      "deltaEta_lep1_lep2", "deltaEta_lep1_tau1", "deltaEta_lep1_tau2", "deltaEta_lep2_tau1", "deltaEta_lep2_tau2", "deltaEta_tau1_tau2",
      "deltaPhi_lep1_lep2", "deltaPhi_lep1_tau1", "deltaPhi_lep1_tau2", "deltaPhi_lep2_tau1", "deltaPhi_lep2_tau2", "deltaPhi_tau1_tau2",
      "dr_lep1_tau1_tau2_min", "dr_lep1_tau1_tau2_max", "dr_lep2_tau1_tau2_min", "dr_lep2_tau1_tau2_max",
      "dr_lep_tau_min_OS", "dr_lep_tau_min_SS"
    );
    bdt_filler->register_variable<int_type>(
      "nJet", "nBJet_loose", "nBJet_medium",
      "lep1_isElectron", "lep1_charge", "lep2_isElectron", "lep2_charge",
      "nElectron", "nMuon"
    );
    bdt_filler->bookTree(fs);
  }

  int analyzedEntries = 0;
  int selectedEntries = 0;
  double selectedEntries_weighted = 0.;
  TH1* histogram_analyzedEntries = fs.make<TH1D>("analyzedEntries", "analyzedEntries", 1, -0.5, +0.5);
  TH1* histogram_selectedEntries = fs.make<TH1D>("selectedEntries", "selectedEntries", 1, -0.5, +0.5);
  cutFlowTableType cutFlowTable;
  const edm::ParameterSet cutFlowTableCfg = makeHistManager_cfg(
    process_string, Form("%s/sel/cutFlow", histogramDir.data()), era_string, central_or_shift
  );
  const std::vector<std::string> cuts = {
    "run:ls:event selection",
    "trigger",
    ">= 2 presel leptons",
    ">= 2 sel leptons", 
    "lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV", 
    "<= 2 tight leptons",  
    ">= 2 sel taus",     
    "tau-pair OS/SS charge", 
    "sel lepton+tau charge", 
    "fakeable lepton trigger match", 
    "HLT filter matching",   
    "b-jet veto",   
    "m(ll) > 12 GeV", 
    "Z-boson mass veto",
    "MEt filters",
    "signal region veto", 
  };

  CutFlowTableHistManager * cutFlowHistManager = new CutFlowTableHistManager(cutFlowTableCfg, cuts);
  cutFlowHistManager->bookHistograms(fs);
  while ( inputTree->hasNextEvent() && (! run_lumi_eventSelector || (run_lumi_eventSelector && ! run_lumi_eventSelector -> areWeDone())) ) {
    if(inputTree -> canReport(reportEvery))
    {
      std::cout << "processing Entry " << inputTree -> getCurrentMaxEventIdx()
                << " or " << inputTree -> getCurrentEventIdx() << " entry in #"
                << (inputTree -> getProcessedFileCount() - 1)
                << " (" << eventInfo
                << ") file (" << selectedEntries << " Entries selected)\n";
    }
    ++analyzedEntries;
    histogram_analyzedEntries->Fill(0.);

    if ( isDEBUG ) {
      std::cout << "event #" << inputTree -> getCurrentMaxEventIdx() << ' ' << eventInfo << '\n';
    }

    if ( run_lumi_eventSelector && !(*run_lumi_eventSelector)(eventInfo) ) continue;
    cutFlowTable.update("run:ls:event selection");
    cutFlowHistManager->fillHistograms("run:ls:event selection", lumiScale);

    if ( run_lumi_eventSelector ) {
      std::cout << "processing Entry #" << inputTree->getCumulativeMaxEventCount() << ": " << eventInfo << std::endl;
      if ( inputTree -> isOpen() ) {
        std::cout << "input File = " << inputTree->getCurrentFileName() << std::endl;
      }
    }

    // std::cout << "processing Entry #" << " run: " << eventInfo.run << " lumi: " << eventInfo.lumi << " event: " << eventInfo.event << '\n';

//--- build collections of generator level particles (before any cuts are applied, to check distributions in unbiased event samples)
    std::vector<GenLepton> genLeptons;
    std::vector<GenLepton> genElectrons;
    std::vector<GenLepton> genMuons;
    std::vector<GenHadTau> genHadTaus;
    std::vector<GenPhoton> genPhotons;
    std::vector<GenJet> genJets;
    if ( isMC && fillGenEvtHistograms ) {
      if ( genLeptonReader ) {
        genLeptons = genLeptonReader->read();
        for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
              genLepton != genLeptons.end(); ++genLepton ) {
          int abs_pdgId = std::abs(genLepton->pdgId());
          if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
          else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
        }
      }
      if ( genHadTauReader ) {
        genHadTaus = genHadTauReader->read();
      }
      if ( genPhotonReader ) {
        genPhotons = genPhotonReader->read();
      }
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
      if ( isDEBUG ) {
        printCollection("genLeptons", genLeptons);
        printCollection("genHadTaus", genHadTaus);
        printCollection("genPhotons", genPhotons);
        printCollection("genJets", genJets);
      }
    }

    double evtWeight_inclusive = 1.;
    if(isMC)
    {
      if(apply_genWeight)    evtWeight_inclusive *= boost::math::sign(eventInfo.genWeight);
      if(isMC_tH)            evtWeight_inclusive *= eventInfo.genWeight_tH;
      if(eventWeightManager) evtWeight_inclusive *= eventWeightManager->getWeight();
      lheInfoReader->read();
      evtWeight_inclusive *= lheInfoReader->getWeight_scale(lheScale_option);
      evtWeight_inclusive *= eventInfo.pileupWeight;
      evtWeight_inclusive *= lumiScale;
      genEvtHistManager_beforeCuts->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      lheInfoHistManager_beforeCuts->fillHistograms(*lheInfoReader, evtWeight_inclusive);
      if(eventWeightManager)
      {
        genEvtHistManager_beforeCuts->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }

    bool isTriggered_1e = hltPaths_isTriggered(triggers_1e);
    bool isTriggered_2e = hltPaths_isTriggered(triggers_2e);
    bool isTriggered_1mu = hltPaths_isTriggered(triggers_1mu);
    bool isTriggered_2mu = hltPaths_isTriggered(triggers_2mu);
    bool isTriggered_1e1mu = hltPaths_isTriggered(triggers_1e1mu);

    bool selTrigger_1e = use_triggers_1e && isTriggered_1e;
    bool selTrigger_2e = use_triggers_2e && isTriggered_2e;
    bool selTrigger_1mu = use_triggers_1mu && isTriggered_1mu;
    bool selTrigger_2mu = use_triggers_2mu && isTriggered_2mu;
    bool selTrigger_1e1mu = use_triggers_1e1mu && isTriggered_1e1mu;
    if ( !(selTrigger_1e || selTrigger_2e || selTrigger_1mu || selTrigger_2mu || selTrigger_1e1mu) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
        std::cout << " (selTrigger_1e = " << selTrigger_1e
                  << ", selTrigger_2e = " << selTrigger_2e
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_2mu = " << selTrigger_2mu
                  << ", selTrigger_1e1mu = " << selTrigger_1e1mu << ")" << std::endl;
      }
      continue;
    }

//--- rank triggers by priority and ignore triggers of lower priority if a trigger of higher priority has fired for given event;
//    the ranking of the triggers is as follows: 2mu, 1e1mu, 2e, 1mu, 1e
// CV: this logic is necessary to avoid that the same event is selected multiple times when processing different primary datasets
    if ( !isMC && !isDEBUG ) {
      if ( selTrigger_1e && (isTriggered_2e || isTriggered_1mu || isTriggered_2mu || isTriggered_1e1mu) ) {
        if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1e = " << selTrigger_1e
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_1mu = " << isTriggered_1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_2e && (isTriggered_2mu || isTriggered_1e1mu) ) {
        if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_2e = " << selTrigger_2e
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1mu && (isTriggered_2e || isTriggered_2mu || isTriggered_1e1mu) ) {
        if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1mu = " << selTrigger_1mu
                    << ", isTriggered_2e = " << isTriggered_2e
                    << ", isTriggered_2mu = " << isTriggered_2mu
                    << ", isTriggered_1e1mu = " << isTriggered_1e1mu << ")" << std::endl;
        }
        continue;
      }
      if ( selTrigger_1e1mu && isTriggered_2mu ) {
        if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS trigger selection." << std::endl;
          std::cout << " (selTrigger_1e1mu = " << selTrigger_1e1mu
                    << ", isTriggered_2mu = " << isTriggered_2mu << ")" << std::endl;
        }
        continue;
      }
    }
    cutFlowTable.update("trigger");
    cutFlowHistManager->fillHistograms("trigger", lumiScale);

    if ( (selTrigger_2e    && !apply_offline_e_trigger_cuts_2e)    ||
         (selTrigger_1e1mu && !apply_offline_e_trigger_cuts_1e1mu) ||
         (selTrigger_1e    && !apply_offline_e_trigger_cuts_1e)    ||
         (selTrigger_1mu   && !apply_offline_e_trigger_cuts_1mu)   ||
         (selTrigger_2mu   && !apply_offline_e_trigger_cuts_2mu)  ) {
      fakeableElectronSelector.disable_offline_e_trigger_cuts();
      tightElectronSelector.disable_offline_e_trigger_cuts();
    } else {
      tightElectronSelector.enable_offline_e_trigger_cuts();
      fakeableElectronSelector.enable_offline_e_trigger_cuts();
    }

//--- build collections of electrons, muons and hadronic taus;
//    resolve overlaps in order of priority: muon, electron,
    std::vector<RecoMuon> muons = muonReader->read();
    std::vector<const RecoMuon*> muon_ptrs = convert_to_ptrs(muons);
    std::vector<const RecoMuon*> cleanedMuons = muon_ptrs; // CV: no cleaning needed for muons, as they have the highest priority in the overlap removal
    std::vector<const RecoMuon*> preselMuons = preselMuonSelector(cleanedMuons, isHigherConePt);
    std::vector<const RecoMuon*> fakeableMuons = fakeableMuonSelector(preselMuons, isHigherConePt);
    std::vector<const RecoMuon*> tightMuons = tightMuonSelector(fakeableMuons, isHigherConePt);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselMuons",   preselMuons);
      printCollection("fakeableMuons", fakeableMuons);
      printCollection("tightMuons",    tightMuons);
    }

    std::vector<RecoElectron> electrons = electronReader->read();
    std::vector<const RecoElectron*> electron_ptrs = convert_to_ptrs(electrons);
    std::vector<const RecoElectron*> cleanedElectrons = electronCleaner(electron_ptrs, preselMuons);
    std::vector<const RecoElectron*> preselElectrons = preselElectronSelector(cleanedElectrons, isHigherConePt);
    std::vector<const RecoElectron*> fakeableElectrons = fakeableElectronSelector(preselElectrons, isHigherConePt);
    std::vector<const RecoElectron*> tightElectrons = tightElectronSelector(fakeableElectrons, isHigherConePt);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselElectrons",   preselElectrons);
      printCollection("fakeableElectrons", fakeableElectrons);
      printCollection("tightElectrons",    tightElectrons);
    }

    std::vector<const RecoLepton*> preselLeptonsFull = mergeLeptonCollections(preselElectrons, preselMuons, isHigherConePt);
    std::vector<const RecoLepton*> fakeableLeptonsFull = mergeLeptonCollections(fakeableElectrons, fakeableMuons, isHigherConePt);
    std::vector<const RecoLepton*> tightLeptonsFull = mergeLeptonCollections(tightElectrons, tightMuons, isHigherConePt);

    std::vector<const RecoLepton*> preselLeptons = pickFirstNobjects(preselLeptonsFull, 2);
    std::vector<const RecoLepton*> fakeableLeptons = pickFirstNobjects(fakeableLeptonsFull, 2);
    std::vector<const RecoLepton*> tightLeptons = getIntersection(fakeableLeptons, tightLeptonsFull, isHigherConePt);

    std::vector<const RecoLepton*> selLeptons;
    std::vector<const RecoMuon*> selMuons;
    std::vector<const RecoElectron*> selElectrons;
    if(electronSelection == muonSelection)
    {
      // for SR, flip region and fake CR
      // doesn't matter if we supply electronSelection or muonSelection here
      selLeptons = selectObjects(muonSelection, preselLeptons, fakeableLeptons, tightLeptons);
      selMuons = getIntersection(preselMuons, selLeptons, isHigherConePt);
      selElectrons = getIntersection(preselElectrons, selLeptons, isHigherConePt);
    }
    else
    {
      // for MC closure
      // make sure that neither electron nor muon selections are loose
      assert(electronSelection != kLoose && muonSelection != kLoose);
      selMuons = selectObjects(muonSelection, preselMuons, fakeableMuons, tightMuons);
      selElectrons = selectObjects(electronSelection, preselElectrons, fakeableElectrons, tightElectrons);
      std::vector<const RecoLepton*> selLeptons_full = mergeLeptonCollections(selElectrons, selMuons, isHigherConePt);
      selLeptons = getIntersection(fakeableLeptons, selLeptons_full, isHigherConePt);
    }

    std::vector<RecoHadTau> hadTaus = hadTauReader->read();
    std::vector<const RecoHadTau*> hadTau_ptrs = convert_to_ptrs(hadTaus);
    std::vector<const RecoHadTau*> cleanedHadTaus = hadTauCleaner(hadTau_ptrs, preselMuons, preselElectrons);
    std::vector<const RecoHadTau*> preselHadTausFull = preselHadTauSelector(cleanedHadTaus, isHigherPt);
    std::vector<const RecoHadTau*> fakeableHadTausFull = fakeableHadTauSelector(preselHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> tightHadTausFull = tightHadTauSelector(fakeableHadTausFull, isHigherPt);

    std::vector<const RecoHadTau*> preselHadTaus = pickFirstNobjects(preselHadTausFull, 2);
    std::vector<const RecoHadTau*> fakeableHadTaus = pickFirstNobjects(fakeableHadTausFull, 2);
    std::vector<const RecoHadTau*> tightHadTaus = getIntersection(fakeableHadTaus, tightHadTausFull, isHigherPt);
    std::vector<const RecoHadTau*> selHadTaus = selectObjects(hadTauSelection, preselHadTaus, fakeableHadTaus, tightHadTaus);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("preselHadTaus",   preselHadTaus);
      printCollection("fakeableHadTaus", fakeableHadTaus);
      printCollection("tightHadTaus",    tightHadTaus);
    }

    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("selMuons", selMuons);
      printCollection("selElectrons", selElectrons);
      printCollection("selLeptons", selLeptons);
      printCollection("selHadTaus", selHadTaus);
    }

//--- build collections of jets and select subset of jets passing b-tagging criteria
    std::vector<RecoJet> jets = jetReader->read();
    std::vector<const RecoJet*> jet_ptrs = convert_to_ptrs(jets);
    std::vector<const RecoJet*> cleanedJets = jetCleaner(jet_ptrs, fakeableLeptons, fakeableHadTaus);
    std::vector<const RecoJet*> selJets = jetSelector(cleanedJets, isHigherPt);
    std::vector<const RecoJet*> selBJets_loose = jetSelectorBtagLoose(cleanedJets, isHigherPt);
    std::vector<const RecoJet*> selBJets_medium = jetSelectorBtagMedium(cleanedJets, isHigherPt);
    int numSelJetsPtGt40 = countHighPtObjects(selJets, 40.);
    if(isDEBUG || run_lumi_eventSelector)
    {
      printCollection("uncleanedJets", jet_ptrs);
      printCollection("selJets",       selJets);
    }

//--- build collections of generator level particles (after some cuts are applied, to save computing time)
    if ( isMC && redoGenMatching && !fillGenEvtHistograms ) {
      if ( genLeptonReader ) {
        genLeptons = genLeptonReader->read();
        for ( std::vector<GenLepton>::const_iterator genLepton = genLeptons.begin();
              genLepton != genLeptons.end(); ++genLepton ) {
          int abs_pdgId = std::abs(genLepton->pdgId());
          if      ( abs_pdgId == 11 ) genElectrons.push_back(*genLepton);
          else if ( abs_pdgId == 13 ) genMuons.push_back(*genLepton);
        }
      }
      if ( genHadTauReader ) {
        genHadTaus = genHadTauReader->read();
      }
      if ( genPhotonReader ) {
        genPhotons = genPhotonReader->read();
      }
      if ( genJetReader ) {
        genJets = genJetReader->read();
      }
    }

//--- match reconstructed to generator level particles
    if ( isMC && redoGenMatching ) {
      muonGenMatcher.addGenLeptonMatch(preselMuons, genLeptons, 0.2);
      muonGenMatcher.addGenHadTauMatch(preselMuons, genHadTaus, 0.2);
      muonGenMatcher.addGenJetMatch(preselMuons, genJets, 0.2);

      electronGenMatcher.addGenLeptonMatch(preselElectrons, genLeptons, 0.2);
      electronGenMatcher.addGenHadTauMatch(preselElectrons, genHadTaus, 0.2);
      electronGenMatcher.addGenPhotonMatch(preselElectrons, genPhotons, 0.2);
      electronGenMatcher.addGenJetMatch(preselElectrons, genJets, 0.2);

      hadTauGenMatcher.addGenLeptonMatch(preselHadTausFull, genLeptons, 0.2);
      hadTauGenMatcher.addGenHadTauMatch(preselHadTausFull, genHadTaus, 0.2);
      hadTauGenMatcher.addGenJetMatch(preselHadTausFull, genJets, 0.2);

      jetGenMatcher.addGenLeptonMatch(selJets, genLeptons, 0.2);
      jetGenMatcher.addGenHadTauMatch(selJets, genHadTaus, 0.2);
      jetGenMatcher.addGenJetMatch(selJets, genJets, 0.2);
    }

//--- apply preselection
    // require exactly two leptons passing loose preselection criteria
    if ( !(preselLeptonsFull.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS preselLeptons selection." << std::endl;
        printCollection("preselLeptons", preselLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update(">= 2 presel leptons");
    cutFlowHistManager->fillHistograms(">= 2 presel leptons", lumiScale);
    const RecoLepton* preselLepton_lead = preselLeptonsFull[0];
    const RecoLepton* preselLepton_sublead = preselLeptonsFull[1];
    const leptonChargeFlipGenMatchEntry& preselLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, preselLepton_lead, preselLepton_sublead);
    int idxPreselLepton_genMatch = preselLepton_genMatch.idx_;
    assert(idxPreselLepton_genMatch != kGen_LeptonUndefined2);

//--- compute MHT and linear MET discriminant (met_LD)
    RecoMEt met = metReader->read();
    Particle::LorentzVector mht_p4 = compMHT(fakeableLeptons, fakeableHadTaus, selJets);
    double met_LD = compMEt_LD(met.p4(), mht_p4);
    double HT = compHT(fakeableLeptons, fakeableHadTaus, selJets);
    double STMET = compSTMEt(fakeableLeptons, fakeableHadTaus, selJets, met.p4());

//--- apply final event selection
    // require exactly two leptons passing tight selection criteria of final event selection
    if ( !(selLeptons.size() >= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS selLeptons selection." << std::endl;
        printCollection("selLeptons", selLeptons);
      }
      continue;
    }
    cutFlowTable.update(">= 2 sel leptons", 1.);
    cutFlowHistManager->fillHistograms(">= 2 sel leptons", 1.);
    const RecoLepton* selLepton_lead = selLeptons[0];
    int selLepton_lead_type = getLeptonType(selLepton_lead->pdgId());
    const RecoLepton* selLepton_sublead = selLeptons[1];
    int selLepton_sublead_type = getLeptonType(selLepton_sublead->pdgId());
    const leptonChargeFlipGenMatchEntry& selLepton_genMatch = getLeptonChargeFlipGenMatch(leptonGenMatch_definitions, selLepton_lead, selLepton_sublead);
    int idxSelLepton_genMatch = selLepton_genMatch.idx_;
    assert(idxSelLepton_genMatch != kGen_LeptonUndefined2);

    if ( isMC ) {
      lheInfoReader->read();
    }

//--- compute event-level weight for data/MC correction of b-tagging efficiency and mistag rate
//   (using the method "Event reweighting using scale factors calculated with a tag and probe method",
//    described on the BTV POG twiki https://twiki.cern.ch/twiki/bin/view/CMS/BTagShapeCalibration )
    double evtWeight = 1.;
    double btagWeight = 1.;
    if ( isMC ) {
      evtWeight *= evtWeight_inclusive;
      btagWeight = get_BtagWeight(selJets);
      evtWeight *= btagWeight;
      if ( isDEBUG ) {
        std::cout << "lumiScale = " << lumiScale << std::endl;
        if ( apply_genWeight ) std::cout << "genWeight = " << boost::math::sign(eventInfo.genWeight) << std::endl;
        std::cout << "pileupWeight = " << eventInfo.pileupWeight << std::endl;
        std::cout << "btagWeight = " << btagWeight << std::endl;
      }
    }

    double minPt_lead = -1.;
    if      ( era == kEra_2016 ) minPt_lead = 25.;
    else if ( era == kEra_2017 ) minPt_lead = 25.;
    else assert(0);
    double minPt_sublead = 15.;
    if ( !(selLepton_lead->cone_pt() > minPt_lead && selLepton_sublead->cone_pt() > minPt_sublead) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS lepton pT selection." << std::endl;
        std::cout << " (leading selLepton pT = " << selLepton_lead->pt() << ", minPt_lead = " << minPt_lead
                  << ", subleading selLepton pT = " << selLepton_sublead->pt() << ", minPt_sublead = " << minPt_sublead << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("lead lepton pT > 25 GeV && sublead lepton pT > 15 GeV", evtWeight);

    bool isLeptonCharge_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isLeptonCharge_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;
    if ( leptonChargeSelection == kOS && isLeptonCharge_SS ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( leptonChargeSelection == kSS && isLeptonCharge_OS ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS lepton charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge() << ", leptonChargeSelection = SS)" << std::endl;
      }
      continue;
    }

   
    // require exactly two leptons passing tight selection criteria, to avoid overlap with other channels
    if ( !(tightLeptonsFull.size() <= 2) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS tightLeptons selection." << std::endl;
        printCollection("tightLeptonsFull", tightLeptonsFull);
      }
      continue;
    }
    cutFlowTable.update("<= 2 tight leptons", evtWeight);
    cutFlowHistManager->fillHistograms("<= 2 tight leptons", evtWeight);


    if ( !(selHadTaus.size() >= 2) ) continue;
    cutFlowTable.update(">= 2 sel taus", evtWeight);
    const RecoHadTau* selHadTau_lead = selHadTaus[0];
    const RecoHadTau* selHadTau_sublead = selHadTaus[1];
    const hadTauGenMatchEntry& selHadTau_genMatch = getHadTauGenMatch(hadTauGenMatch_definitions, selHadTau_lead, selHadTau_sublead);
    int idxSelHadTau_genMatch = selHadTau_genMatch.idx_;
    assert(idxSelHadTau_genMatch != kGen_HadTauUndefined2);


    bool isCharge_hadTau_SS = selHadTau_lead->charge()*selHadTau_sublead->charge() > 0;
    bool isCharge_hadTau_OS = selHadTau_lead->charge()*selHadTau_sublead->charge() < 0;
    if ( hadTauChargeSelection == kOS && isCharge_hadTau_SS ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS hadTau charge selection." << std::endl;
        std::cout << " (leading selHadTau charge = " << selHadTau_lead->charge()
                  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ", hadTauChargeSelection = SS)" << std::endl;
      }
      continue;
    }
    if ( hadTauChargeSelection == kSS && isCharge_hadTau_OS ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS hadTau charge selection." << std::endl;
        std::cout << " (leading selHadTau charge = " << selHadTau_lead->charge()
                  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ", hadTauChargeSelection = OS)" << std::endl;
      }
      continue;
    }
    if ( hadTauChargeSelection != kDisabled ) {
      cutFlowTable.update(Form("tau-pair %s charge", hadTauChargeSelection_string.data()), evtWeight);
    }
    cutFlowHistManager->fillHistograms("tau-pair OS/SS charge", evtWeight);

    if ( (chargeSumSelection == kOS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau_lead->charge() + selHadTau_sublead->charge()) != 0) ||
         (chargeSumSelection == kSS && std::abs(selLepton_lead->charge() + selLepton_sublead->charge() + selHadTau_lead->charge() + selHadTau_sublead->charge()) == 0) ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS lepton+tau charge selection." << std::endl;
        std::cout << " (leading selLepton charge = " << selLepton_lead->charge()
                  << ", subleading selLepton charge = " << selLepton_sublead->charge()
                  << ", leading selHadTau charge = " << selHadTau_lead->charge()
                  << ", subleading selHadTau charge = " << selHadTau_sublead->charge() << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update(Form("sel lepton+tau %s charge", chargeSumSelection_string.data()), evtWeight);
    cutFlowHistManager->fillHistograms("sel lepton+tau charge", evtWeight);


    // require that trigger paths match event category (with event category based on fakeableLeptons)
    if ( !((fakeableElectrons.size() >= 2 &&                              (selTrigger_2e    || selTrigger_1e                  )) ||
           (fakeableElectrons.size() >= 1 && fakeableMuons.size() >= 1 && (selTrigger_1e1mu || selTrigger_1mu || selTrigger_1e)) ||
           (                                 fakeableMuons.size() >= 2 && (selTrigger_2mu   || selTrigger_1mu                 ))) ) {
      if ( run_lumi_eventSelector ) {
    std::cout << "event " << eventInfo.str() << " FAILS trigger selection for given fakeableLepton multiplicity." << std::endl;
        std::cout << " (#fakeableElectrons = " << fakeableElectrons.size()
                  << ", #fakeableMuons = " << fakeableMuons.size()
                  << ", selTrigger_2mu = " << selTrigger_2mu
                  << ", selTrigger_1e1mu = " << selTrigger_1e1mu
                  << ", selTrigger_2e = " << selTrigger_2e
                  << ", selTrigger_1mu = " << selTrigger_1mu
                  << ", selTrigger_1e = " << selTrigger_1e << ")" << std::endl;
      }
      continue;
    }
    cutFlowTable.update("fakeable lepton trigger match", evtWeight);
    cutFlowHistManager->fillHistograms("fakeable lepton trigger match", evtWeight);


//--- apply HLT filter
    if(apply_hlt_filter)
    {
      const std::map<hltPathsE, bool> trigger_bits = {
        { hltPathsE::trigger_1e,    selTrigger_1e    },
        { hltPathsE::trigger_1mu,   selTrigger_1mu   },
        { hltPathsE::trigger_2e,    selTrigger_2e    },
        { hltPathsE::trigger_2mu,   selTrigger_2mu   },
        { hltPathsE::trigger_1e1mu, selTrigger_1e1mu },
      };
      if(! hltFilter(trigger_bits, fakeableLeptons, fakeableHadTaus))
      {
        if(run_lumi_eventSelector || isDEBUG)
        {
          std::cout << "event " << eventInfo.str() << " FAILS HLT filter matching\n";
        }
        continue;
      }
    }
    cutFlowTable.update("HLT filter matching", evtWeight);
    cutFlowHistManager->fillHistograms("HLT filter matching", evtWeight);

    double weight_data_to_MC_correction = 1.;
    double triggerWeight = 1.;
    double leptonSF_weight = 1.;
    double tauSF_weight = 1.;
    if ( isMC ) {
      dataToMCcorrectionInterface->setLeptons(
        selLepton_lead_type, selLepton_lead->pt(), selLepton_lead->eta(),
        selLepton_sublead_type, selLepton_sublead->pt(), selLepton_sublead->eta());

//--- apply data/MC corrections for trigger efficiency
      double sf_triggerEff = dataToMCcorrectionInterface->getSF_leptonTriggerEff();
      if ( isDEBUG ) {
        std::cout << "sf_triggerEff = " << sf_triggerEff << std::endl;
      }
      triggerWeight *= sf_triggerEff;
      weight_data_to_MC_correction *= sf_triggerEff;

//--- apply data/MC corrections for efficiencies for lepton to pass loose identification and isolation criteria
      leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_loose();

//--- apply data/MC corrections for efficiencies of leptons passing the loose identification and isolation criteria
//    to also pass the tight identification and isolation criteria
      if ( electronSelection == kFakeable && muonSelection == kFakeable ) {
        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_fakeable_to_loose();
      } else if ( electronSelection >= kFakeable && muonSelection >= kFakeable ) {
        // apply loose-to-tight lepton ID SFs if either of the following is true:
        // 1) both electron and muon selections are tight -> corresponds to SR
        // 2) electron selection is relaxed to fakeable and muon selection is kept as tight -> corresponds to MC closure w/ relaxed e selection
        // 3) muon selection is relaxed to fakeable and electron selection is kept as tight -> corresponds to MC closure w/ relaxed mu selection
        // we allow (2) and (3) so that the MC closure regions would more compatible w/ the SR (1) in comparison
        leptonSF_weight *= dataToMCcorrectionInterface->getSF_leptonID_and_Iso_tight_to_loose_wTightCharge();
      }
      weight_data_to_MC_correction *= leptonSF_weight;

//--- apply data/MC corrections for hadronic tau identification efficiency
//    and for e->tau and mu->tau misidentification rates
      int selHadTau_lead_genPdgId = getHadTau_genPdgId(selHadTau_lead);
      int selHadTau_sublead_genPdgId = getHadTau_genPdgId(selHadTau_sublead);
      dataToMCcorrectionInterface->setHadTaus(
        selHadTau_lead_genPdgId, selHadTau_lead->pt(), selHadTau_lead->eta(), selHadTau_lead->decayMode(),
        selHadTau_sublead_genPdgId, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->decayMode());
      tauSF_weight *= dataToMCcorrectionInterface->getSF_hadTauID_and_Iso();
      tauSF_weight *= dataToMCcorrectionInterface->getSF_eToTauFakeRate();
      tauSF_weight *= dataToMCcorrectionInterface->getSF_muToTauFakeRate();
      weight_data_to_MC_correction *= tauSF_weight;
      if ( isDEBUG ) {
        std::cout << "weight_data_to_MC_correction = " << weight_data_to_MC_correction << std::endl;
      }

      evtWeight *= weight_data_to_MC_correction;
    }

    bool passesTight_lepton_lead = isMatched(*selLepton_lead, tightElectrons) || isMatched(*selLepton_lead, tightMuons);
    bool passesTight_hadTau_lead = isMatched(*selHadTau_lead, tightHadTausFull);
    bool passesTight_lepton_sublead = isMatched(*selLepton_sublead, tightElectrons) || isMatched(*selLepton_sublead, tightMuons);
    bool passesTight_hadTau_sublead = isMatched(*selHadTau_sublead, tightHadTausFull);

    double weight_fakeRate = 1.;
    double prob_fake_lepton_lead = 1.;
    double prob_fake_lepton_sublead = 1.;
    if(leptonFakeRateInterface) {
        if      ( std::abs(selLepton_lead->pdgId()) == 11 )
          {prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_e(selLepton_lead->cone_pt(), selLepton_lead->absEta());}
        else if ( std::abs(selLepton_lead->pdgId()) == 13 )
          {prob_fake_lepton_lead = leptonFakeRateInterface->getWeight_mu(selLepton_lead->cone_pt(), selLepton_lead->absEta());}
        else assert(0);
        if      ( std::abs(selLepton_sublead->pdgId()) == 11 )
          {prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_e(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());}
        else if ( std::abs(selLepton_sublead->pdgId()) == 13 )
          {prob_fake_lepton_sublead = leptonFakeRateInterface->getWeight_mu(selLepton_sublead->cone_pt(), selLepton_sublead->absEta());}
        else assert(0);
    }

    double prob_fake_hadTau_lead = 1.;
    double prob_fake_hadTau_sublead = 1.;
    if(jetToTauFakeRateInterface) {
    prob_fake_hadTau_lead = jetToTauFakeRateInterface->getWeight_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
    prob_fake_hadTau_sublead = jetToTauFakeRateInterface->getWeight_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
    }

    if ( applyFakeRateWeights == kFR_4L )  {
      weight_fakeRate = getWeight_4L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead,
        prob_fake_hadTau_lead, passesTight_hadTau_lead,
        prob_fake_hadTau_sublead, passesTight_hadTau_sublead
      );
    } else if ( applyFakeRateWeights == kFR_2lepton)  {
      weight_fakeRate = getWeight_2L(
        prob_fake_lepton_lead, passesTight_lepton_lead,
        prob_fake_lepton_sublead, passesTight_lepton_sublead
      );
    } else if ( applyFakeRateWeights == kFR_2tau) {
      weight_fakeRate = getWeight_2L(
        prob_fake_hadTau_lead, passesTight_hadTau_lead,
        prob_fake_hadTau_sublead, passesTight_hadTau_sublead
      );
    }

    // CV: apply data/MC ratio for jet->tau fake-rates in case data-driven "fake" background estimation is applied to leptons only
    double weight_data_to_MC_correction_hadTau_lead = 1.;
    double weight_data_to_MC_correction_hadTau_sublead = 1.;
    if ( isMC && apply_hadTauFakeRateSF && hadTauSelection == kTight ) {
      if ( !(selHadTau_lead->genHadTau() || selHadTau_lead->genLepton()) && jetToTauFakeRateInterface ) {
        weight_data_to_MC_correction_hadTau_lead = jetToTauFakeRateInterface->getSF_lead(selHadTau_lead->pt(), selHadTau_lead->absEta());
      }
      if ( !(selHadTau_sublead->genHadTau() || selHadTau_sublead->genLepton()) && jetToTauFakeRateInterface ) {
        weight_data_to_MC_correction_hadTau_sublead = jetToTauFakeRateInterface->getSF_sublead(selHadTau_sublead->pt(), selHadTau_sublead->absEta());
      }
      if ( isDEBUG ) {
        std::cout << "weight_data_to_MC_correction_hadTau:"
                  << " lead = " << weight_data_to_MC_correction_hadTau_lead << ","
                  << " sublead = " << weight_data_to_MC_correction_hadTau_sublead << std::endl;
      }
      evtWeight *= (weight_data_to_MC_correction_hadTau_lead*weight_data_to_MC_correction_hadTau_sublead);
    }
    evtWeight *= weight_fakeRate;
    if ( isDEBUG ) {
      std::cout << "evtWeight = " << evtWeight << std::endl;
    }


    if ( selBJets_loose.size() >= 2 || selBJets_medium.size() >= 1 )
    {
      if(run_lumi_eventSelector)
      {
        std::cout << "event " << eventInfo.str() << " FAILS b-jet veto\n";
      }
      continue;
    }
    cutFlowTable.update("b-jet veto", evtWeight);
    cutFlowHistManager->fillHistograms("b-jet veto", evtWeight);

    bool failsLowMassVeto = false;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
    lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
      lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
        double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
        if ( mass < 12. ) {
          failsLowMassVeto = true;
        }
      }
    }
    if ( failsLowMassVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS low mass lepton pair veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("m(ll) > 12 GeV", evtWeight);
    cutFlowHistManager->fillHistograms("m(ll) > 12 GeV", evtWeight);

    bool isSameFlavor_OS = false;
    double massSameFlavor_OS = -1.;
    for ( std::vector<const RecoLepton*>::const_iterator lepton1 = preselLeptonsFull.begin();
    lepton1 != preselLeptonsFull.end(); ++lepton1 ) {
      for ( std::vector<const RecoLepton*>::const_iterator lepton2 = lepton1 + 1;
      lepton2 != preselLeptonsFull.end(); ++lepton2 ) {
        if ( (*lepton1)->pdgId() == -(*lepton2)->pdgId() ) { // pair of same flavor leptons of opposite charge
          isSameFlavor_OS = true;
          double mass = ((*lepton1)->p4() + (*lepton2)->p4()).mass();
          if ( std::fabs(mass - z_mass) < std::fabs(massSameFlavor_OS - z_mass) ) massSameFlavor_OS = mass;
        }
      }
    }
    bool failsZbosonMassVeto = isSameFlavor_OS && std::fabs(massSameFlavor_OS - z_mass) < z_window;
    if ( failsZbosonMassVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS Z-boson veto." << std::endl;
      }
      continue;
    }
    cutFlowTable.update("Z-boson mass veto", evtWeight);
    cutFlowHistManager->fillHistograms("Z-boson mass veto", evtWeight);

    if ( apply_met_filters ) {
      if ( !metFilterSelector(metFilters) ) {
        if ( run_lumi_eventSelector ) {
      std::cout << "event " << eventInfo.str() << " FAILS MEt filters." << std::endl;
        }
        continue;
      }
    }
    cutFlowTable.update("MEt filters", evtWeight);
    cutFlowHistManager->fillHistograms("MEt filters", evtWeight);

    bool failsSignalRegionVeto = false;
    if ( isMCClosure_e || isMCClosure_m || isMCClosure_t ) {
      bool applySignalRegionVeto_lepton = (isMCClosure_e && countFakeElectrons(selLeptons) >= 1) || (isMCClosure_m && countFakeMuons(selLeptons) >= 1);
      bool applySignalRegionVeto_hadTau = isMCClosure_t && countFakeHadTaus(selHadTaus) >= 1;
      if ( applySignalRegionVeto_lepton && tightLeptons.size() >= 2 ) failsSignalRegionVeto = true;
      if ( applySignalRegionVeto_hadTau && tightHadTaus.size() >= 2 ) failsSignalRegionVeto = true;
    } else if ( electronSelection == kFakeable || muonSelection == kFakeable || hadTauSelection == kFakeable ) {
      if ( tightLeptons.size() >= 2 && tightHadTaus.size() >= 2 ) failsSignalRegionVeto = true;
    }
    if ( failsSignalRegionVeto ) {
      if ( run_lumi_eventSelector ) {
        std::cout << "event " << eventInfo.str() << " FAILS overlap w/ the SR: "
                     "# tight leptons = " << tightLeptons.size() << " >= 2 and "
                     "# tight taus = " << tightHadTaus.size() << " >= 2\n"
        ;
        printCollection("tightLeptons", tightLeptons);
        printCollection("tightHadTaus", tightHadTaus);
      }
      continue; // CV: avoid overlap with signal region
    }
    cutFlowTable.update("signal region veto", evtWeight);
    cutFlowHistManager->fillHistograms("signal region veto", evtWeight);

    const Particle::LorentzVector tautau_p4 = selHadTau_lead->p4() + selHadTau_sublead->p4();
    const double mTauTauVis_sel = tautau_p4.mass();
            
    double leptonPairCharge_sel = selLepton_lead->charge() + selLepton_sublead->charge();
    double hadTauPairCharge_sel = selHadTau_lead->charge() + selHadTau_sublead->charge();

    bool isCharge_lepton_SS = selLepton_lead->charge()*selLepton_sublead->charge() > 0;
    bool isCharge_lepton_OS = selLepton_lead->charge()*selLepton_sublead->charge() < 0;


    std::vector<SVfit4tauResult> svFit4tauResults_woMassConstraint = compSVfit4tau(
      *selLepton_lead, *selLepton_sublead, *selHadTau_lead, *selHadTau_sublead, met, chargeSumSelection_string, rnd,  -1., 2.);
    std::vector<SVfit4tauResult> svFit4tauResults_wMassConstraint = compSVfit4tau(
      *selLepton_lead, *selLepton_sublead, *selHadTau_lead, *selHadTau_sublead, met, chargeSumSelection_string, rnd, 125., 2.);

    double dihiggsVisMass_sel = (selLepton_lead->p4() + selLepton_sublead->p4() + selHadTau_lead->p4() + selHadTau_sublead->p4()).mass();
    double dihiggsMass = ( svFit4tauResults_wMassConstraint.size() >= 1 && svFit4tauResults_wMassConstraint[0].isValidSolution_ ) ? 
      svFit4tauResults_wMassConstraint[0].dihiggs_mass_ : -1.;

    // pre-compute BDT variables-1
    const double deltaEta_lep1_lep2 = (selLepton_lead->p4() - selLepton_sublead->p4()).eta();
    std::cout<< "deltaEta_lep1_lep2 " << deltaEta_lep1_lep2 << std::endl;
    const double deltaEta_lep1_tau1 = (selLepton_lead->p4() - selHadTau_lead->p4()).eta();
    const double deltaEta_lep1_tau2 = (selLepton_lead->p4() - selHadTau_sublead->p4()).eta();
    const double deltaEta_lep2_tau1 = (selLepton_sublead->p4() - selHadTau_lead->p4()).eta();
    const double deltaEta_lep2_tau2 = (selLepton_sublead->p4() - selHadTau_sublead->p4()).eta();
    const double deltaEta_tau1_tau2 = (selHadTau_lead->p4() - selHadTau_sublead->p4()).eta();
    const double deltaPhi_lep1_lep2 = (selLepton_lead->p4() - selLepton_sublead->p4()).phi();
    const double deltaPhi_lep1_tau1 = (selLepton_lead->p4() - selHadTau_lead->p4()).phi();
    const double deltaPhi_lep1_tau2 = (selLepton_lead->p4() - selHadTau_sublead->p4()).phi();
    const double deltaPhi_lep2_tau1 = (selLepton_sublead->p4() - selHadTau_lead->p4()).phi();
    const double deltaPhi_lep2_tau2 = (selLepton_sublead->p4() - selHadTau_sublead->p4()).phi();
    const double deltaPhi_tau1_tau2 = (selHadTau_lead->p4() - selHadTau_sublead->p4()).phi();
    const double m_lep1_tau1 = (selLepton_lead->p4() + selHadTau_lead->p4()).mass();
    const double m_lep2_tau1 = (selLepton_sublead->p4() + selHadTau_lead->p4()).mass();
    const double m_lep1_tau2 = (selLepton_lead->p4() + selHadTau_sublead->p4()).mass();
    const double m_lep2_tau2 = (selLepton_sublead->p4() + selHadTau_sublead->p4()).mass();
    const double pt_HH_recoil = (selLepton_lead->p4() + selLepton_sublead->p4() + selHadTau_lead->p4() + selHadTau_sublead->p4() - met.p4()).pt();
    const double mT_lep1 = comp_MT_met_lep1(*selLepton_lead, met.pt(), met.phi());
    const double mT_lep2 = comp_MT_met_lep2(*selLepton_sublead, met.pt(), met.phi());
    const double dr_lep1_tau1 = deltaR(selLepton_lead->p4(),    selHadTau_lead->p4());
    const double dr_lep2_tau1 = deltaR(selLepton_sublead->p4(), selHadTau_lead->p4());
    const double dr_lep1_tau2 = deltaR(selLepton_lead->p4(),    selHadTau_sublead->p4());
    const double dr_lep2_tau2 = deltaR(selLepton_sublead->p4(), selHadTau_sublead->p4());
    const double dr_lep1_tau1_tau2_min = std::min(dr_lep1_tau1, dr_lep1_tau2); 
    const double dr_lep1_tau1_tau2_max = std::max(dr_lep1_tau1, dr_lep1_tau2); 
    const double dr_lep2_tau1_tau2_min = std::min(dr_lep2_tau1, dr_lep2_tau2); 
    const double dr_lep2_tau1_tau2_max = std::max(dr_lep2_tau1, dr_lep2_tau2); 
    double dr_lep_tau_min_OS = 0.;
    if(isCharge_lepton_OS){
      dr_lep_tau_min_OS = std::min(std::min(dr_lep1_tau1, dr_lep1_tau2), std::min(dr_lep2_tau1, dr_lep2_tau2));
    }else{
      dr_lep_tau_min_OS = -1.;
    }
    double dr_lep_tau_min_SS = 0.;
    if(isCharge_lepton_SS){
      dr_lep_tau_min_SS = std::min(std::min(dr_lep1_tau1, dr_lep1_tau2), std::min(dr_lep2_tau1, dr_lep2_tau2));
    }else{
      dr_lep_tau_min_SS = -1.;
    }
    const double dr_leps = deltaR(selLepton_lead->p4(), selLepton_sublead->p4());
    const double dr_taus = deltaR(selHadTau_lead->p4(), selHadTau_sublead->p4());
    const double avg_dr_jet = comp_avg_dr_jet(selJets);
    const Particle::LorentzVector ll_p4 = selLepton_lead->p4() + selLepton_sublead->p4();
    const double Smin_llMEt = comp_Smin(ll_p4, met.p4().px(), met.p4().py());
    const double ptTauTauVis_sel = (selHadTau_lead->p4() + selHadTau_sublead->p4()).pt();
    const Particle::LorentzVector lltautau_p4 = ll_p4 + tautau_p4;
    const double Smin_lltautau = comp_Smin(lltautau_p4, met.p4().px(), met.p4().py());
    const std::vector<const RecoJet*> cleanedJets_wrt_leptons = jetCleaner(jet_ptrs, fakeableLeptons);
    const std::vector<const RecoJet*> selJets_btag = jetSelector(cleanedJets_wrt_leptons, isHigherCSV);
    const std::vector<const RecoJet*> selBJets_btag_loose = jetSelectorBtagLoose(selJets_btag, isHigherPt);
    const std::vector<const RecoJet*> selBJets_btag_medium = jetSelectorBtagMedium(selJets_btag, isHigherPt);
    const RecoJet * selBJet_lead    = selJets_btag.size() > 0 ? selJets_btag.at(0) : nullptr;
    const RecoJet * selBJet_sublead = selJets_btag.size() > 1 ? selJets_btag.at(1) : nullptr;

    //--- compute variables BDTs used to discriminate in the .xml files (NEW)
    BDTInputs_SUM["diHiggsMass"]          = dihiggsMass;
    BDTInputs_SUM["diHiggsVisMass"]       = dihiggsVisMass_sel;
    BDTInputs_SUM["tau1_pt"]              = selHadTau_lead->pt();
    BDTInputs_SUM["nBJet_medium"]         = selBJets_btag_medium.size();
    BDTInputs_SUM["gen_mHH"]              = 250.; // setting a Dummy value which will be reset depending on mass hypothesis 
    BDTInputs_SUM["nElectron"]            = selElectrons.size();
    BDTInputs_SUM["dr_lep_tau_min_SS"]    = dr_lep_tau_min_SS;
    BDTInputs_SUM["met_LD"]               = met_LD;
    BDTInputs_SUM["tau2_pt"]              = selHadTau_sublead->pt();
    BDTInputs_SUM["dr_lep_tau_min_OS"]    = dr_lep_tau_min_OS;
    std::cout << "dihiggsMass " << dihiggsMass << " dihiggsVisMass_sel: " << dihiggsVisMass_sel << " tau1_pt: " << selHadTau_lead->pt() <<
      " nBJet_medium: " << selBJets_btag_medium.size() << " nElectron: " << selElectrons.size() << " dr_lep_tau_min_SS: " << dr_lep_tau_min_SS <<
      " met_LD: " << met_LD << " dr_lep_tau_min_OS: " << dr_lep_tau_min_OS << " tau2_pt: " << selHadTau_sublead->pt() << std::endl; 


    /*
    //double BDTOutput_SUM = BDT_SUM(BDTInputs_SUM);
    std::vector<double> BDTOutput_SUM; // vector of BDT outputs for each signal mass
    for (size_t i=0; i<gen_mHH.size(); i++){ // Loop over signal masses
      BDTInputs_SUM["gen_mHH"] = gen_mHH[i];
      BDTOutput_SUM.push_back(BDT_SUM(BDTInputs_SUM, eventInfo.event)); // Event number (even/odd) dependent BDT output for a given signal mass
    }
    */

    std::map<std::string, double> BDTOutput_SUM_Map;
    std::map<std::string, double> XGBOutput_SUM_Map;

    for(unsigned int i=0; i<gen_mHH.size(); i++){ // Loop over signal masses
      std::cout<< "gen_mHH: " << gen_mHH[i] << std::endl;
      BDTInputs_SUM["gen_mHH"] = gen_mHH[i];
      unsigned int mass_int = (int)gen_mHH[i]; // Conversion from double to unsigned int
      std::string key = "";
      ostringstream temp;
      temp << mass_int;
      key = temp.str(); // Conversion from unsigned int to string
      std::string key_final = "BDTOutput_" + key;
      BDTOutput_SUM_Map.insert( std::make_pair(key_final, (*BDT_SUM)(BDTInputs_SUM, eventInfo.event)) );
      std::string XGB_key_final = "BDTOutput_" + key + "_pkl";
      XGBOutput_SUM_Map.insert( std::make_pair(XGB_key_final, (*XGB_SUM)(BDTInputs_SUM, eventInfo.event)) );
    }
    // ---- NEW ENDS ------



//--- fill histograms with events passing final selection
    selHistManagerType* selHistManager = selHistManagers[idxSelLepton_genMatch][idxSelHadTau_genMatch];
    assert(selHistManager != 0);
    selHistManager->electrons_->fillHistograms(selElectrons, evtWeight);
    if ( selElectrons.size() >= 1 ) {
      selHistManager->leadElectron_->fillHistograms({ selElectrons[0] }, evtWeight);
    }
    if ( selElectrons.size() >= 2 ) {
      selHistManager->subleadElectron_->fillHistograms({ selElectrons[1] }, evtWeight);
    }
    selHistManager->muons_->fillHistograms(selMuons, evtWeight);
    if ( selMuons.size() >= 1 ) {
      selHistManager->leadMuon_->fillHistograms({ selMuons[0] }, evtWeight);
    }
    if ( selMuons.size() >= 2 ) {
      selHistManager->subleadMuon_->fillHistograms({ selMuons[1] }, evtWeight);
    }
    selHistManager->hadTaus_->fillHistograms(selHadTaus, evtWeight);
    selHistManager->leadHadTau_->fillHistograms({ selHadTau_lead }, evtWeight);
    selHistManager->subleadHadTau_->fillHistograms({ selHadTau_sublead }, evtWeight);
    selHistManager->jets_->fillHistograms(selJets, evtWeight);
    selHistManager->BJets_loose_->fillHistograms(selBJets_loose, evtWeight);
    selHistManager->BJets_medium_->fillHistograms(selBJets_medium, evtWeight);
    selHistManager->met_->fillHistograms(met, mht_p4, met_LD, evtWeight);
    selHistManager->metFilters_->fillHistograms(metFilters, evtWeight);
    selHistManager->evt_->fillHistograms(
      selElectrons.size(),
      selMuons.size(),
      selHadTaus.size(),
      selJets.size(),
      numSelJetsPtGt40,
      selBJets_loose.size(),
      selBJets_medium.size(),
      mTauTauVis_sel,
      leptonPairCharge_sel,
      hadTauPairCharge_sel,
      dihiggsVisMass_sel,
      dihiggsMass,
      HT, 
      STMET,
      BDTOutput_SUM_Map, // I AM HERE !!!
      XGBOutput_SUM_Map, // I AM HERE !!!
      eventInfo.event,
      evtWeight);
    selHistManager->svFit4tau_wMassConstraint_->fillHistograms(svFit4tauResults_wMassConstraint, evtWeight);
    if ( isMC ) {
      selHistManager->genEvtHistManager_afterCuts_->fillHistograms(genElectrons, genMuons, genHadTaus, genPhotons, genJets, evtWeight_inclusive);
      selHistManager->lheInfoHistManager_afterCuts_->fillHistograms(*lheInfoReader, evtWeight);

      if(eventWeightManager)
      {
        selHistManager->genEvtHistManager_afterCuts_->fillHistograms(eventWeightManager, evtWeight_inclusive);
      }
    }
    selHistManager->evtYield_->fillHistograms(eventInfo, evtWeight);
    selHistManager->weights_->fillHistograms("genWeight", eventInfo.genWeight);
    selHistManager->weights_->fillHistograms("pileupWeight", eventInfo.pileupWeight);
    selHistManager->weights_->fillHistograms("triggerWeight", triggerWeight);
    selHistManager->weights_->fillHistograms("data_to_MC_correction", weight_data_to_MC_correction);
    selHistManager->weights_->fillHistograms("fakeRate", weight_fakeRate);




    std::vector<std::string> categories;
    if      ( isCharge_lepton_SS ) categories.push_back("2lSS_2tau");
    else if ( isCharge_lepton_OS ){ 
      categories.push_back("2lOS_2tau");
      categories.push_back("2lOS_2tau_wChargeFlipWeights");
    } else assert(0);
    if ( selMuons.size() >= 2 ) {
      categories.push_back("2mu_2tau");
      if      ( isCharge_lepton_SS ) categories.push_back("2muSS_2tau");
      else if ( isCharge_lepton_OS ){
	categories.push_back("2muOS_2tau");
	categories.push_back("2muOS_2tau_wChargeFlipWeights");
      }else assert(0);
    } else if ( selMuons.size() >= 1 && selElectrons.size() >= 1 ) {
      categories.push_back("1e1mu_2tau");
      if      ( isCharge_lepton_SS ) categories.push_back("1e1muSS_2tau");
      else if ( isCharge_lepton_OS ){
	categories.push_back("1e1muOS_2tau");
	categories.push_back("1e1muOS_2tau_wChargeFlipWeights");
      }else assert(0);
    } else if ( selElectrons.size() >= 2 ) {
      categories.push_back("2e_2tau");
      if      ( isCharge_lepton_SS ) categories.push_back("2eSS_2tau");
      else if ( isCharge_lepton_OS ){
	categories.push_back("2eOS_2tau");
	categories.push_back("2eOS_2tau_wChargeFlipWeights");
      }else assert(0);
    } else assert(0);


    


    for ( std::vector<std::string>::const_iterator category = categories.begin();
          category != categories.end(); ++category ) {
      double evtWeight_category = evtWeight;
      if ( category->find("_wChargeFlipWeights") != std::string::npos ) {
	double prob_chargeMisId_lead = prob_chargeMisId(getLeptonType(selLepton_lead->pdgId()), selLepton_lead->pt(), selLepton_lead->eta());
	double prob_chargeMisId_sublead = prob_chargeMisId(getLeptonType(selLepton_sublead->pdgId()), selLepton_sublead->pt(), selLepton_sublead->eta());
	// double prob_chargeMisId_tau = 0.01; // CV: not implemented yet; take "guessed" value for now
	// evtWeight_category *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead + (2*prob_chargeMisId_tau));
	evtWeight_category *= ( prob_chargeMisId_lead + prob_chargeMisId_sublead);
      }
      std::cout << "Filling histograms for " << *category << std::endl; 
      // std::cout << "# Electrons " << selElectrons.size() << " # Muons " << selMuons.size() << " # Taus " << selHadTaus.size() << std::endl;
      if ( selHistManager->evt_in_categories_.find(*category) != selHistManager->evt_in_categories_.end() ) {
        selHistManager->evt_in_categories_[*category]->fillHistograms(
        selElectrons.size(),
        selMuons.size(),
        selHadTaus.size(),
        selJets.size(),
        numSelJetsPtGt40,
        selBJets_loose.size(),
        selBJets_medium.size(),
        mTauTauVis_sel,
        leptonPairCharge_sel,
        hadTauPairCharge_sel,
        dihiggsVisMass_sel,
        dihiggsMass,
        HT,
        STMET,
	BDTOutput_SUM_Map, // I AM HERE !!!
	XGBOutput_SUM_Map, // I AM HERE !!!
	eventInfo.event,
        evtWeight_category);
        selHistManager->svFit4tau_wMassConstraint_in_categories_[*category]->fillHistograms(svFit4tauResults_wMassConstraint, evtWeight_category);
      }
      if ( isMC ) {
	selHistManager->lheInfoHistManager_afterCuts_in_categories_[*category]->fillHistograms(*lheInfoReader, evtWeight_category);
      }
    }

    if ( selEventsFile ) {
      (*selEventsFile) << eventInfo.run << ':' << eventInfo.lumi << ':' << eventInfo.event << '\n';
    }

    //--- reconstruct mass of tau-pair using SVfit algorithm                                                                                                                                                                                                       
    //                                                                                                                                                                                                                                                             
    //    NOTE: SVfit needs to be run after all event selection cuts are applied,                                                                                                                                                                                   
    //          because the algorithm takes O(1 second per event) to run                                                                                                                                                                                           
    //                                                                                                                                                                                                                                                                    
    std::vector<classic_svFit::MeasuredTauLepton> measuredTauLeptons;
    classic_svFit::MeasuredTauLepton::kDecayType leg1Type = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
    double leg1Mass = selHadTau_lead->mass();
    if ( leg1Mass < classic_svFit::chargedPionMass ) leg1Mass = classic_svFit::chargedPionMass;
    if ( leg1Mass > 1.5                            ) leg1Mass = 1.5;
    classic_svFit::MeasuredTauLepton::kDecayType leg2Type = classic_svFit::MeasuredTauLepton::kTauToHadDecay;
    double leg2Mass = selHadTau_sublead->mass();
    if ( leg2Mass < classic_svFit::chargedPionMass ) leg2Mass = classic_svFit::chargedPionMass;
    if ( leg2Mass > 1.5                            ) leg2Mass = 1.5;
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg1Type, selHadTau_lead->pt(), selHadTau_lead->eta(), selHadTau_lead->phi(), leg1Mass));
    measuredTauLeptons.push_back(classic_svFit::MeasuredTauLepton(leg2Type, selHadTau_sublead->pt(), selHadTau_sublead->eta(), selHadTau_sublead->phi(), leg2Mass));
    ClassicSVfit svFitAlgo;
    svFitAlgo.addLogM_dynamic(false);
    svFitAlgo.addLogM_fixed(true, 5.);
    svFitAlgo.integrate(measuredTauLeptons, met.p4().px(), met.p4().py(), met.cov());


    // pre-compute BDT variables-2
    //double mTauTau = -1.; // CV: temporarily comment-out the following line, to make code compile with "old" and "new" version of ClassicSVfit                                                                                                          
    const double mTauTau   = ( svFitAlgo.isValidSolution() ) ? static_cast<classic_svFit::HistogramAdapterDiTau*>(svFitAlgo.getHistogramAdapter())->getMass() : -1.;
    
    Topness topness_publishedChi2(Topness::kPublishedChi2);
    if(selBJet_lead && selBJet_sublead)
    {
      topness_publishedChi2.fit(
        selLepton_lead->p4(), selLepton_sublead->p4(),
        selBJet_lead->p4(),   selBJet_sublead->p4(),
        met.p4().px(),        met.p4().py()
      );
    }
    const double logTopness_publishedChi2 =
      topness_publishedChi2.isValidSolution() ? topness_publishedChi2.logTopness() : -99.
    ;
    Topness topness_fixedChi2(Topness::kFixedChi2);
    if(selBJet_lead && selBJet_sublead)
    {
      topness_fixedChi2.fit(
        selLepton_lead->p4(), selLepton_sublead->p4(),
        selBJet_lead->p4(),   selBJet_sublead->p4(),
        met.p4().px(),        met.p4().py()
      );
    }
    const double logTopness_fixedChi2 =
      topness_fixedChi2.isValidSolution() ? topness_fixedChi2.logTopness() : -99.
    ;

    if(bdt_filler)
    {
      bdt_filler -> operator()({ eventInfo.run, eventInfo.lumi, eventInfo.event })
	  ("deltaEta_lep1_lep2", deltaEta_lep1_lep2)
	  ("deltaEta_lep1_tau1", deltaEta_lep1_tau1)
	  ("deltaEta_lep1_tau2", deltaEta_lep1_tau2)
	  ("deltaEta_lep2_tau1", deltaEta_lep2_tau1)
	  ("deltaEta_lep2_tau2", deltaEta_lep2_tau2)
	  ("deltaEta_tau1_tau2", deltaEta_tau1_tau2)
	  ("deltaPhi_lep1_lep2", deltaPhi_lep1_lep2)
	  ("deltaPhi_lep1_tau1", deltaPhi_lep1_tau1)
	  ("deltaPhi_lep1_tau2", deltaPhi_lep1_tau2)
	  ("deltaPhi_lep2_tau1", deltaPhi_lep2_tau1)
	  ("deltaPhi_lep2_tau2", deltaPhi_lep2_tau2)
	  ("deltaPhi_tau1_tau2", deltaPhi_tau1_tau2)
	  ("dr_lep1_tau1_tau2_min", dr_lep1_tau1_tau2_min)
	  ("dr_lep1_tau1_tau2_max", dr_lep1_tau1_tau2_max)
	  ("dr_lep2_tau1_tau2_min", dr_lep2_tau1_tau2_min)
	  ("dr_lep2_tau1_tau2_max", dr_lep2_tau1_tau2_max)
	  ("dr_lep_tau_min_OS", dr_lep_tau_min_OS) 
	  ("dr_lep_tau_min_SS", dr_lep_tau_min_SS) 
	  ("pt_HH_recoil",             pt_HH_recoil)
          ("lep1_pt",                  selLepton_lead->pt())
          ("lep1_conePt",              selLepton_lead->cone_pt())
          ("lep1_eta",                 selLepton_lead->eta())
          ("lep1_phi",                 selLepton_lead->phi())
          ("lep1_tth_mva",             selLepton_lead->mvaRawTTH())
          ("mT_lep1",                  mT_lep1)
          ("lep2_pt",                  selLepton_sublead->pt())
          ("lep2_conePt",              selLepton_sublead->cone_pt())
          ("lep2_eta",                 selLepton_sublead->eta())
          ("lep2_phi",                 selLepton_lead->phi())
          ("lep2_tth_mva",             selLepton_sublead->mvaRawTTH())
          ("mT_lep2",                  mT_lep2)
          ("tau1_pt",                  selHadTau_lead->pt())
          ("tau1_eta",                 selHadTau_lead->eta())
          ("tau1_phi",                 selHadTau_lead->phi())
          ("tau1_mva",                 selHadTau_lead->id_mva_dR03())
          ("tau2_pt",                  selHadTau_sublead->pt())
          ("tau2_eta",                 selHadTau_sublead->eta())
          ("tau2_phi",                 selHadTau_lead->phi())
          ("tau2_mva",                 selHadTau_sublead->id_mva_dR03())
          ("dr_lep1_tau1",             dr_lep1_tau1)
          ("dr_lep2_tau1",             dr_lep2_tau1)
          ("dr_lep1_tau2",             dr_lep1_tau2)
          ("dr_lep2_tau2",             dr_lep2_tau2)
	  ("m_lep1_tau1",              m_lep1_tau1)  
	  ("m_lep2_tau1",              m_lep2_tau1)
	  ("m_lep1_tau2",              m_lep1_tau2)
	  ("m_lep2_tau2",              m_lep2_tau2)
          ("dr_leps",                  dr_leps)
          ("dr_taus",                  dr_taus)
          ("avg_dr_jet",               avg_dr_jet)
          ("met",                      met.pt())
          ("met_phi",                  met.phi())
          ("mht",                      mht_p4.pt())
          ("met_LD",                   met_LD)
          ("HT",                       HT)
          ("STMET",                    STMET)
          ("m_ll",                     ll_p4.mass())
          ("pT_ll",                    ll_p4.pt())
          ("pT_llMEt",                 (ll_p4 + met.p4()).pt())
          ("Smin_llMEt",               Smin_llMEt)
          ("Smin_lltautau",            Smin_lltautau)
          ("mTauTauVis",               mTauTauVis_sel)
          ("mTauTau",                  mTauTau)
          ("ptTauTauVis",              ptTauTauVis_sel)
          ("diHiggsVisMass",           dihiggsVisMass_sel)
          ("diHiggsMass",              dihiggsMass)
          ("nJet",                     selJets.size())
          ("nBJet_loose",              selBJets_btag_loose.size())
          ("nBJet_medium",             selBJets_btag_medium.size())
          ("lep1_isElectron",          selLepton_lead_type == kElectron)
          ("lep1_charge",              selLepton_lead->charge())
          ("lep2_isElectron",          selLepton_sublead_type == kElectron)
          ("lep2_charge",              selLepton_sublead->charge())
          ("logTopness_publishedChi2", logTopness_publishedChi2)
          ("logTopness_fixedChi2",     logTopness_fixedChi2)
          ("genWeight",                eventInfo.genWeight)
          ("evtWeight",                evtWeight)
          ("nElectron",                selElectrons.size())
          ("nMuon",                    selMuons.size())
        .fill()
	;

    }

    ++selectedEntries;
    selectedEntries_weighted += evtWeight;
    histogram_selectedEntries->Fill(0.);
  }

  std::cout << "max num. Entries = " << inputTree -> getCumulativeMaxEventCount()
            << " (limited by " << maxEvents << ") processed in "
            << inputTree -> getProcessedFileCount() << " file(s) (out of "
            << inputTree -> getFileCount() << ")\n"
            << " analyzed = " << analyzedEntries << '\n'
            << " selected = " << selectedEntries << " (weighted = " << selectedEntries_weighted << ")\n\n"
            << "cut-flow table" << std::endl;
  cutFlowTable.print(std::cout);
  std::cout << std::endl;

  std::cout << "sel. Entries by gen. matching:" << std::endl;
  for ( std::vector<leptonChargeFlipGenMatchEntry>::const_iterator leptonGenMatch_definition = leptonGenMatch_definitions.begin();
        leptonGenMatch_definition != leptonGenMatch_definitions.end(); ++leptonGenMatch_definition ) {
    for ( std::vector<hadTauGenMatchEntry>::const_iterator hadTauGenMatch_definition = hadTauGenMatch_definitions.begin();
          hadTauGenMatch_definition != hadTauGenMatch_definitions.end(); ++hadTauGenMatch_definition ) {

      std::string process_and_genMatch = process_string;
      if ( apply_leptonGenMatching ) process_and_genMatch += leptonGenMatch_definition->name_;
      if ( apply_leptonGenMatching && apply_hadTauGenMatching ) process_and_genMatch += "&";
      if ( apply_hadTauGenMatching ) process_and_genMatch += hadTauGenMatch_definition->name_;

      int idxLepton = leptonGenMatch_definition->idx_;
      int idxHadTau = hadTauGenMatch_definition->idx_;

      const TH1* histogram_EventCounter = selHistManagers[idxLepton][idxHadTau]->evt_->getHistogram_EventCounter();
      std::cout << " " << process_and_genMatch << " = " << histogram_EventCounter->GetEntries() << " (weighted = " << histogram_EventCounter->Integral() << ")" << std::endl;
    }
  }

  std::cout << std::endl;

  delete dataToMCcorrectionInterface;

  delete leptonFakeRateInterface;
  delete jetToTauFakeRateInterface;

  delete run_lumi_eventSelector;

  delete selEventsFile;

  delete muonReader;
  delete electronReader;
  delete hadTauReader;
  delete jetReader;
  delete metReader;
  delete metFilterReader;
  delete genLeptonReader;
  delete genHadTauReader;
  delete genPhotonReader;
  delete genJetReader;
  delete lheInfoReader;

  delete bdt_filler;
  delete genEvtHistManager_beforeCuts;
  delete cutFlowHistManager;
  delete eventWeightManager;

  hltPaths_delete(triggers_1e);
  hltPaths_delete(triggers_2e);
  hltPaths_delete(triggers_1mu);
  hltPaths_delete(triggers_2mu);
  hltPaths_delete(triggers_1e1mu);

  delete inputTree;

  delete XGB_SUM;
  delete BDT_SUM;

  clock.Show("analyze_hh_2l_2tau");

  return EXIT_SUCCESS;
}
