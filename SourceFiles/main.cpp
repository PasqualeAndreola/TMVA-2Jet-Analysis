/*! \mainpage TMVA-2Jet-Analysis
 *
 * \section intro_sec Introduction
 *
 * This project has been developed as an assignment for the Computing (in HEP) exam.\n
 * The work is divided in three parts:
 * 1. Data reading
 * 2. Data manipulation
 * 3. TMVA algorithm implementation
 *
 * \section dataread_sec Data reading
 * 
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */

#include <TROOT.h>
#include <TApplication.h>
#include <TString.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <THStack.h>
#include <TLegend.h>
#include <TMVA/Factory.h>
#include <TMVA/Reader.h>
#include <TMVA/TMVAGui.h>
#include <TMVA/DataLoader.h>
#include <TMVA/Tools.h>
#include "headers/TreeCreator.h"
#include "headers/TreeJetCreator.h"
#include "headers/SBTreeCreator.h"
#include "headers/SBTreeJetKinematicsCreator.h"

/*It can be useful to use these namespaces*/
using namespace std;
using namespace fastjet;

int main(int argc, char *argv[])
{
  /* Input files and relative flags (1 for event file, 0 for unknown, -1 for background)*/
  vector<TString> filenames;
  vector<int> sbflags;
  filenames.push_back("events_anomalydetection_Z_XY_qqq");
  sbflags.push_back(1);
  filenames.push_back("events_anomalydetection");
  sbflags.push_back(0);
  filenames.push_back("events_LHCO2020_backgroundMC_Pythia");
  sbflags.push_back(-1);
  filenames.push_back("events_LHCO2020_BlackBox1");
  sbflags.push_back(0);
  filenames.push_back("lhc_anomalydetection_small");
  sbflags.push_back(0);

  /* Name of output file*/
  TString SBOutputfile = "SBOutput";
  TString SBJetOutputfile = "SBJetOutput";
  TString TMVAFactoryoutputname = "TMVAFactory";

  /* Number of jets that has to be clustered from event data*/
  unsigned long sbjetnumber = 100000, eventjetnumber = 100000;
  double_t R = 1.0, pT_min = 20;

  /*Defining number of jet that has to be put in the TMVA factory*/
  unsigned long ntrainsign = 10000;
  unsigned long ntrainback = 10000;
  unsigned long ntestsign = 10000;
  unsigned long ntestback = 10000;

  /*Useful Variables*/
  int i = 0;
  vector<TString> question;
  string answer;

  question.push_back("Do you wish to analyze these files? (YES/NO)");
  PrintFuncInfo(question);
  question.clear();
  for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit)
  {
    cout << "\t" << stringit->Data() << endl;
  }
  cout << endl;
  cin >> answer;

  //The user wants to analyze the files
  if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
  {
    question.push_back("Do you wish to transform these *.h5 files in *.root files? (YES/NO)");
    question.push_back("(Answer no if these root files exist already)");
    PrintFuncInfo(question);
    question.clear();
    cin >> answer;
    if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
    {
      for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit)
      {
        //Converting *.h5 files to *.root files
        openh5(TString::Format("%s.h5", stringit->Data()));
        TreeCreator(*stringit);
        dataset_info_list.clear();
      }
      question.push_back("Do you wish to analyze these *.root files and distinguish signal/background/event? (YES/NO)");
      question.push_back("(Answer no if these root files have already been distinguished in a SBOutput.root file)");
      PrintFuncInfo(question);
      question.clear();
      cin >> answer;
      if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
      {
        for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit, i++)
        {
          //Distinguishing signal from background and event and vice versa
          openh5(TString::Format("%s.h5", stringit->Data()));
          SBTreeCreator(TString::Format("OutputFiles/%s.root", stringit->Data()), TString::Format("OutputFiles/%s.root", SBOutputfile.Data()), sbflags[i], i);
          dataset_info_list.clear();
        }
      }
    }
    else
    {
      question.push_back("Do you wish to analyze these already existing *.root files and distinguish signal/background/event? (YES/NO)");
      question.push_back("(Answer no if these root files have already been distinguished in a SBOutput.root file)");
      PrintFuncInfo(question);
      question.clear();
      cin >> answer;
      if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
      {
        for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit)
        {
          //Distinguishing signal from background and event and vice versa*
          openh5(TString::Format("%s.h5", stringit->Data()));
          SBTreeCreator(TString::Format("OutputFiles/%s.root", stringit->Data()), TString::Format("OutputFiles/%s.root", SBOutputfile.Data()), sbflags[i], i);
          dataset_info_list.clear();
        }
      }
    }
    question.push_back("Do you wish to create SBJetOutput.root file to store jet kinematic quantities? (YES/NO)");
    question.push_back(TString::Format("You will cluster %lu signal/background jet and %lu event jet. Are you ok? (YES/NO)", sbjetnumber, eventjetnumber));
    question.push_back("(Answer no if jets have already been clustered and stored in a SBJetOutput.root file)");
    PrintFuncInfo(question);
    question.clear();
    cin >> answer;
    if (answer.compare("YES") == 0 || answer.compare("yes") == 0 || answer.compare("Yes") == 0 || answer.compare("y") == 0 || answer.compare("Y") == 0)
    {
      SBTreeJetKinematicsCreator(TString::Format("OutputFiles/%s.root", SBOutputfile.Data()), TString::Format("OutputFiles/%s.root", SBJetOutputfile.Data()), filenames.size(), sbjetnumber, eventjetnumber, R, pT_min);
    }
  
   /*
    TString outfilename(TString::Format("TMVAResults/%s.root", TMVAFactoryoutputname.Data()));
    TFile *inputfile = TFile::Open(TString::Format("OutputFiles/%s.root", SBJetOutputfile.Data()), "read");
    TFile *outputfile = TFile::Open(outfilename, "recreate");

    TMVA::DataLoader *loader = new TMVA::DataLoader("TMVAResults/Wprimo");
    TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputfile, "AnalysisType=Classification");
    loader->AddVariable("MVAjet1_pT := sqrt(pow(jet1_px,2) + pow(jet1_py,2))", 'F');
    loader->AddVariable("MVAjet2_pT := sqrt(pow(jet2_px,2) + pow(jet2_py,2))", 'F');
    loader->AddVariable("MVAjet1_m := sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)))", 'F');
    loader->AddVariable("MVAjet2_m := sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)))", 'F');
    loader->AddVariable("MVAjet_mjj := sqrt( abs(pow(jet1_E+jet2_E,2) - pow(jet1_px+jet2_px,2) - pow(jet1_py+jet2_py,2) - pow(jet1_pz+jet2_pz,2)))", 'F');
    loader->AddVariable("MVAjet1_px := jet1_px", 'F');
    loader->AddVariable("MVAjet2_px := jet2_px", 'F');
    TTree *signal = (TTree *)inputfile->Get("SignalJet");
    TTree *background = (TTree *)inputfile->Get("BackgroundJet");
    Double_t signalweight = 1.0, backgroundweight = 1.0;
    loader->AddSignalTree(signal, signalweight);
    loader->AddBackgroundTree(background, backgroundweight);

    TString dataString = TString::Format("nTrain_Signal=%lu", ntrainsign);
    dataString.Append(TString::Format(":nTrain_Background=%lu", ntrainback));
    dataString.Append(TString::Format(":nTest_Signal=%lu", ntestsign));
    dataString.Append(TString::Format(":nTest_Background=%lu", ntestback));
    dataString.Append(":SplitMode=Random:NormMode=NumEvents:!V");

    loader->PrepareTrainingAndTestTree("", "", dataString);
    TString configString = "!H:V";
    configString += ":VarTransform=N";
    configString += ":ErrorStrategy=CROSSENTROPY";
    configString += ":WeightInitialization=XAVIERUNIFORM";

    TString layoutString = "Layout=TANH|100, TANH|50, TANH|10, LINEAR";

    // Training strategies for PDE-Foam
    TString trainingPDEF1 = "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=100000:nBin=5:Nmin=100:Kernel=None:Compress=T";

    // Training strategies for deep learning
    TString trainingString1 = "TrainingStrategy=LearningRate=1e-2,Momentum=0.5, Repetitions=1,ConvergenceSteps=100,BatchSize=100,DropConfig=0.0+0.5+0.5+0.0";
    trainingString1.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

    TString trainingString2 = " | LearningRate=1e-3,Momentum=0.1, Repetitions=1,ConvergenceSteps=100,BatchSize=50,DropConfig=0.0+0.1+0.1+0.0";
    trainingString2.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

    TString trainingString3 = " | LearningRate=1e-4,Momentum=0.0, Repetitions=10,ConvergenceSteps=100,BatchSize=25,DropConfig=0.0+0.1+0.1+0.0";
    trainingString3.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

    // Training strategies for MultiLayerOerceptron
    TString trainingMLP1 = "VarTransform=N, NCycles=1000, HiddenLayers=N+5, NeuronType=tanh, EstimatorType=CE, TrainingMethod=BP, LearningRate=0.2, DecayRate=0.1";
    
    TString trainingMLP2 = "VarTransform=N, NCycles=500, HiddenLayers=N, NeuronType=Sigmoid, EstimatorType=MSE, TrainingMethod=BFGS, LearningRate=0.2, DecayRate=0.1";

    TString trainingMLP3 = "VarTransform=N, NCycles=1000, HiddenLayers=N-5, NeuronType=tanh, EstimatorType=CE, TrainingMethod=BP, LearningRate=0.1, DecayRate=0.05";


    // Training strategies for BDT
    TString trainingBDT1 = "Ntrees=800, MaxDepth=7, MinNodeSize=5%, nCuts=35, BoostType=RealAdaBoost, UseRandomisedTrees=Treue, UseNvars=3, UsePoissonNvars=True";

    TString trainingBDT2 = "Ntrees=1000, MaxDepth=5, MinNodeSize=15%, nCuts=-1, BoostType=RealAdaBoost, UseRandomisedTrees=Treue, UseNvars=3, UsePoissonNvars=True";

    TString trainingBDT3 = "Ntrees=1200, MaxDepth=7, MinNodeSize=5%, nCuts=-1, BoostType=AdaBoost, UseRandomisedTrees=Treue, SeparationType=CrossEntropy";

    factory->BookMethod(loader, TMVA::Types::kPDEFoam, "PDEFoam1", trainingPDEF1);

    configString += ":" + layoutString + ":" + trainingString1;
    //factory->BookMethod(loader, TMVA::Types::kDL, "DL1", configString);

    configString += trainingString2;
    //factory->BookMethod(loader, TMVA::Types::kDL, "DL2", configString);

    configString += trainingString3;
    //factory->BookMethod(loader, TMVA::Types::kDL, "DL3", configString);

    //factory->BookMethod(loader, TMVA::Types::kMLP, "MLP1", trainingMLP1);
    //factory->BookMethod(loader, TMVA::Types::kMLP, "MLP2", trainingMLP2);
    //factory->BookMethod(loader, TMVA::Types::kMLP, "MLP3", trainingMLP3);

    //factory->BookMethod(loader, TMVA::Types::kBDT, "BDT1", trainingBDT1);
    //factory->BookMethod(loader, TMVA::Types::kBDT, "BDT2", trainingBDT2);
    //factory->BookMethod(loader, TMVA::Types::kBDT, "BDT3", trainingBDT3);

    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    inputfile->Close();
    outputfile->Close();*/
  }/*
  else
  {
    question.push_back("The user doesn't want to analyze those files");
    PrintFuncInfo(question);
    question.clear();
    return 0;
  }
  
  TFile *eventinputfile = TFile::Open("OutputFiles/SBJetOutput.root", "read");
  TFile *eventoutputfile = TFile::Open("TMVAResults/Outclassevent.root", "recreate");
  TTree *EventJet = (TTree *)eventinputfile->Get("EventJet");
  int event_entries = EventJet->GetEntries();
  Float_t MVAjet1_pT, MVAjet2_pT, MVAjet1_m, MVAjet2_m, MVAjet1_px, MVAjet2_px, MVAjet2_mjj;
  Double_t d_jet1_px, d_jet1_py, d_jet1_pz, d_jet1_E, d_jet2_px, d_jet2_py, d_jet2_pz, d_jet2_E;
  Double_t mjj;
  EventJet->SetBranchAddress("jet1_E", &d_jet1_E);
  EventJet->SetBranchAddress("jet1_px", &d_jet1_px);
  EventJet->SetBranchAddress("jet1_py", &d_jet1_py);
  EventJet->SetBranchAddress("jet1_pz", &d_jet1_pz);
  EventJet->SetBranchAddress("jet2_E", &d_jet2_E);
  EventJet->SetBranchAddress("jet2_px", &d_jet2_px);
  EventJet->SetBranchAddress("jet2_py", &d_jet2_py);
  EventJet->SetBranchAddress("jet2_pz", &d_jet2_pz);

  TMVA::Reader *reader = new TMVA::Reader("Color");
  Float_t jet1_px = (Float_t) d_jet1_px;
  Float_t jet1_py = (Float_t) d_jet1_py;
  Float_t jet1_pz = (Float_t) d_jet1_pz;
  Float_t jet1_E = (Float_t) d_jet1_E;
  Float_t jet2_px = (Float_t) d_jet2_px;
  Float_t jet2_py = (Float_t) d_jet2_py;
  Float_t jet2_pz = (Float_t) d_jet2_pz;
  Float_t jet2_E = (Float_t) d_jet2_E;
  reader->AddVariable("MVAjet1_pT := sqrt(pow(jet1_px,2) + pow(jet1_py,2))", &MVAjet1_pT);
  reader->AddVariable("MVAjet2_pT := sqrt(pow(jet2_px,2) + pow(jet2_py,2))", &MVAjet2_pT);
  reader->AddVariable("MVAjet1_m := sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)))", &MVAjet1_m);
  reader->AddVariable("MVAjet2_m := sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)))", &MVAjet2_m);
  reader->AddVariable("MVAjet_mjj := sqrt( abs(pow(jet1_E+jet2_E,2) - pow(jet1_px+jet2_px,2) - pow(jet1_py+jet2_py,2) - pow(jet1_pz+jet2_pz,2)))", &MVAjet2_mjj);
  reader->AddVariable("MVAjet1_px := jet1_px", &MVAjet1_px);
  reader->AddVariable("MVAjet2_px := jet2_px", &MVAjet2_px);
  reader->BookMVA("kPDEFoam", "TMVAResults/Wprimo/weights/TMVAClassification_PDEFoam1.weights.xml");

  TH1F *histMVA = new TH1F("MVA", "MVA", 100, -1, 1);
  TH1F *histMVAErr = new TH1F("MVAErr", "MVAErr", 100, -1, 1);
  TH1F *histMVASig = new TH1F("MVASig", "MVASig", 1000, 10000000000, 1000000000000);
  TH1F *hpTbackground = new TH1F("pTbackground", "pTbackground", 50, 1.1e3, 2.6 * 1e3);
  TH1F *hpTsignal = new TH1F("pTsignal", "pTsignal", 50, 1.1e3, 2.6 * 1e3);
  TH1F *hmjjbackground = new TH1F("mjj_total", "mjj_total", 50, 1e3, 7e3);
  TH1F *hmjjsignal = new TH1F("mjj_signal", "mjj_signal", 50, 1e3, 7e3);

  for (int readerindex = 0; readerindex < event_entries; readerindex++)
  {
    jet1_px = (Float_t) d_jet1_px;
    jet1_py = (Float_t) d_jet1_py;
    jet1_pz = (Float_t) d_jet1_pz;
    jet1_E = (Float_t) d_jet1_E;
    jet2_px = (Float_t) d_jet2_px;
    jet2_py = (Float_t) d_jet2_py;
    jet2_pz = (Float_t) d_jet2_pz;
    jet2_E = (Float_t) d_jet2_E;
    EventJet->GetEntry(readerindex);
    MVAjet1_pT = sqrt(pow(jet1_px, 2) + pow(jet1_py, 2));
    MVAjet2_pT = sqrt(pow(jet2_px, 2) + pow(jet2_py, 2));
    MVAjet1_m = sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)));
    MVAjet2_m = sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)));
    MVAjet1_px = jet1_px;
    MVAjet2_px = jet2_px;
    histMVA->Fill(reader->EvaluateMVA("kPDEFoam"));
    histMVAErr->Fill(reader->GetMVAError());
    histMVASig->Fill( (reader->EvaluateMVA("kPDEFoam")/(reader->GetMVAError() ) ) );
    mjj = (Double_t)sqrt(pow((jet1_E + jet2_E), 2) - pow((jet1_px + jet2_px), 2) - pow((jet1_py + jet2_py), 2) - pow((jet1_pz + jet2_pz), 2));
    if (reader->EvaluateMVA("kPDEFoam") > 0.3)
    {
      hpTsignal->Fill(MVAjet1_pT);
      hmjjsignal->Fill(mjj);
    }
    else
    {
      hpTbackground->Fill(MVAjet1_pT);
      hmjjbackground->Fill(mjj);
    }
  }
  //Stampo il numero di eventi di segnale trovato
  cout << "There are " << hmjjsignal->GetEntries() << " events containing a W' " << endl;

  //Drawing TMVAEvaluation histogram
  TCanvas *c0 = new TCanvas("c0", "c0", 1366, 768);
  c0->cd();
  histMVA->SetLineColor(kBlue);
  histMVA->SetFillColorAlpha(kBlue, 0.04);
  histMVA->SetTitle("MVAEvaluation");
  histMVA->GetXaxis()->SetTitle("EvaluateMVA \"kPDEFoam\"");
  histMVA->GetYaxis()->SetTitle("Occurences");
  histMVA->Draw();
  c0->Update();
  c0->SaveAs("MVAEvaluation.png");

  TCanvas *c0err = new TCanvas("c0err", "c0err", 1366, 768);
  c0err->cd();
  histMVAErr->SetLineColor(kBlue);
  histMVAErr->SetFillColorAlpha(kBlue, 0.04);
  histMVAErr->SetTitle("MVAEvaluation Error");
  histMVAErr->GetXaxis()->SetTitle("EvaluateMVA Error \"kPDEFoam\"");
  histMVAErr->GetYaxis()->SetTitle("Occurences");
  histMVAErr->Draw();
  c0err->Update();
  c0err->SaveAs("MVAEvaluationError.png");
  
  TCanvas *c0sig = new TCanvas("c0sig", "c0sig", 1366, 768);
  c0sig->cd();
  histMVASig->SetLineColor(kBlue);
  histMVASig->SetFillColorAlpha(kBlue, 0.04);
  histMVASig->SetTitle("MVAEvaluation Significance");
  histMVASig->GetXaxis()->SetTitle("EvaluateMVA Significance \"kPDEFoam\"");
  histMVASig->GetYaxis()->SetTitle("Occurences");
  histMVASig->Draw();
  c0sig->Update();
  c0sig->SaveAs("MVAEvaluationSignificance.png");

  //Inserisco gli istogrammi del pt e della massa in una collezione e li rappresento
  TCanvas *c1 = new TCanvas("c1", "c1", 1366, 768);
  c1->cd();
  THStack *hpTstack = new THStack("hs", "");
  hpTbackground->SetLineColor(kRed);
  hpTbackground->SetFillColor(kRed);
  hpTbackground->SetStats(kFALSE);
  hpTsignal->SetLineColor(kBlue);
  hpTsignal->SetFillColorAlpha(kBlue, 0.3);
  hpTsignal->SetStats(kFALSE);
  hpTstack->Add(hpTbackground);
  hpTstack->Add(hpTsignal);
  hpTstack->SetTitle("Leading jet transverse momentum: p_{T}[GeV]");
  hpTstack->Draw();

  //Adjusting the legend
  auto legend = new TLegend(0.65, 0.8, 0.9, 0.9);
  legend->SetHeader("Leading jet p_{T}","C"); // option "C" allows to center the header
  legend->AddEntry(hpTbackground, "Background", "f");
  legend->AddEntry(hpTsignal, "Signal", "f");
  legend->Draw("same");

  c1->Update();
  c1->SaveAs("hpTtotal.png");

  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  c2->cd();
  hpTsignal->Draw("");
  c2->Update();
  c2->SaveAs("hpTsignal.png");
  
  TCanvas *c3 = new TCanvas("c3", "c3", 1366, 768);
  c3->cd();
  THStack *hmjjstack = new THStack("hsm", "");
  hmjjbackground->SetLineColor(kRed);
  hmjjbackground->SetFillColor(kRed);
  hmjjbackground->SetStats(kFALSE);
  hmjjsignal->SetLineColor(kBlue);
  hmjjsignal->SetFillColorAlpha(kBlue, 0.3);
  hmjjsignal->SetStats(kFALSE);
  hmjjstack->Add(hmjjbackground);
  hmjjstack->Add(hmjjsignal);
  hmjjstack->SetTitle("Combined jet mass: m_{jj}[GeV]");
  hmjjstack->Draw("");
  c3->Update();
  c3->SaveAs("hmjjtotal.png");

  TCanvas *c4 = new TCanvas("c4", "c4", 1366, 768);
  hmjjsignal->Draw("");
  c4->Update();
  c4->SaveAs("hmjjsignal.png");

  eventoutputfile->cd();
  histMVA->Write();
  histMVASig->Write();
  histMVAErr->Write();
  hpTbackground->Write();
  hpTsignal->Write();
  hmjjbackground->Write();
  hmjjsignal->Write();
  eventinputfile->Close();
  eventoutputfile->Close();
  delete reader;*/

  return 0;
}

    //TApplication *Analysisroot_app = new TApplication("Analysis", &argc, argv);
    /*Se l'utente vuole visionare i risultati subito si avvia un applicativo root*/
    /*std::cout << "\nWould you see the results now? [Y/N]" << std::endl;
    std::cin.get(str,256);
    if(strcmp(str,"Y") == 0)
    {
      hdestep->Draw();
      c1->Update();
      c1->SaveAs("c1.png");
      Analysisroot_app->Run();
    }*/