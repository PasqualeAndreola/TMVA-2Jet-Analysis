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
  /*filenames.push_back("events_anomalydetection_Z_XY_qqq");
  sbflags.push_back(1);
  filenames.push_back("events_anomalydetection");
  sbflags.push_back(0);
  filenames.push_back("events_LHCO2020_backgroundMC_Pythia");
  sbflags.push_back(-1);
  filenames.push_back("events_LHCO2020_BlackBox1");
  sbflags.push_back(0);*/
  filenames.push_back("lhc_anomalydetection_small");
  sbflags.push_back(0);

  /* Name of output file*/
  TString SBOutputfile = "SBOutput";
  TString SBJetOutputfile = "SBJetOutput";
  TString TMVAFactoryoutputname = "TMVAFactory";

  /* Number of jets that has to be clustered from event data*/
  unsigned long sbjetnumber = 10, eventjetnumber = 10;
  double_t R = 1.0, pT_min = 20;

  /*Defining number of jet that has to be put in the TMVA factory*/
  unsigned long ntrainsign = 10;
  unsigned long ntrainback = 10;
  unsigned long ntestsign = 10;
  unsigned long ntestback = 10;

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

  /*The user wants to analyze the files*/
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
        /*Converting *.h5 files to *.root files*/
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
          /*Distinguishing signal from background and event and vice versa*/
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
          /*Distinguishing signal from background and event and vice versa*/
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
  }
  else
  {
    question.push_back("The user doesn't want to analyze those files");
    PrintFuncInfo(question);
    question.clear();
    return 0;
  }
/*  
  TString outfilename(TString::Format("TMVA/%s.root", TMVAFactoryoutputname.Data()));
  TFile *inputfile = TFile::Open(TString::Format("OutputFiles/%s.root", SBOutputfile.Data()), "read");
  TFile *outputfile = TFile::Open(outfilename, "recreate");

  TMVA::DataLoader *loader = new TMVA::DataLoader("Wprimo");
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

  TString dataString = TString::Format("nTrain_Signal=%d", ntrainsign);
  dataString.Append(TString::Format(":nTrain_Background=%d", ntrainback));
  dataString.Append(TString::Format(":nTest_Signal=%d", ntestsign));
  dataString.Append(TString::Format(":nTest_Background=%d", ntestback));
  dataString.Append(":SplitMode=Random:NormMode=NumEvents:!V");

  loader->PrepareTrainingAndTestTree("", "", dataString);
  TString configString = "!H:V";
  configString += ":VarTransform=N";
  configString += ":ErrorStrategy=CROSSENTROPY";
  configString += ":WeightInitialization=XAVIERUNIFORM";

  TString layoutString = "Layout=TANH|100, TANH|50, TANH|10, LINEAR";

  TString trainingString1 = "TrainingStrategy=LearningRate=1e-1,Momentum=0.5, Repetitions=1,ConvergenceSteps=1000,BatchSize=20,DropConfig=0.0+0.5+0.5+0.0";
  trainingString1.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

  TString trainingString2 = " | LearningRate=1e-2,Momentum=0.1, Repetitions=1,ConvergenceSteps=1000,BatchSize=20,DropConfig=0.0+0.1+0.1+0.0";
  trainingString2.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

  TString trainingString3 = " | LearningRate=1e-3,Momentum=0.0, Repetitions=10,ConvergenceSteps=1000,BatchSize=50,DropConfig=0.0+0.1+0.1+0.0";
  trainingString3.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

  //Eventuali fasi aggiuntive

  configString += ":" + layoutString + ":" + trainingString1;
  factory->BookMethod(loader, TMVA::Types::kDL, "DL1", configString);

  configString += trainingString2;
  factory->BookMethod(loader, TMVA::Types::kDL, "DL2", configString);

  configString += trainingString3;
  factory->BookMethod(loader, TMVA::Types::kDL, "DL3", configString);

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();

  inputfile->Close();
  outputfile->Close();
*/
  /*
  TFile *eventinputfile = TFile::Open("SBoutput.root", "read");
  TFile *eventoutputfile = TFile::Open("Outclassevent.root", "recreate");
  TTree *EventJet = (TTree *)eventinputfile->Get("EventJet");
  int event_entries = EventJet->GetEntries();
  Float_t MVAjet1_pT, MVAjet2_pT, MVAjet1_m, MVAjet2_m, MVAjet1_px, MVAjet2_px, MVAjet2_mjj;
  Double_t jet1_px, jet1_py, jet1_pz, jet1_E, jet2_px, jet2_py, jet2_pz, jet2_E;
  Double_t mjj;
  EventJet->SetBranchAddress("jet1_E", &jet1_E);
  EventJet->SetBranchAddress("jet1_px", &jet1_px);
  EventJet->SetBranchAddress("jet1_py", &jet1_py);
  EventJet->SetBranchAddress("jet1_pz", &jet1_pz);
  EventJet->SetBranchAddress("jet2_E", &jet2_E);
  EventJet->SetBranchAddress("jet2_px", &jet2_px);
  EventJet->SetBranchAddress("jet2_py", &jet2_py);
  EventJet->SetBranchAddress("jet2_pz", &jet2_pz);

  TMVA::Reader *reader = new TMVA::Reader("Color");
  reader->AddVariable("MVAjet1_pT := sqrt(pow(jet1_px,2) + pow(jet1_py,2))", &MVAjet1_pT);
  reader->AddVariable("MVAjet2_pT := sqrt(pow(jet2_px,2) + pow(jet2_py,2))", &MVAjet2_pT);
  reader->AddVariable("MVAjet1_m := sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)))", &MVAjet1_m);
  reader->AddVariable("MVAjet2_m := sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)))", &MVAjet2_m);
  reader->AddVariable("MVAjet_mjj := sqrt( abs(pow(jet1_E+jet2_E,2) - pow(jet1_px+jet2_px,2) - pow(jet1_py+jet2_py,2) - pow(jet1_pz+jet2_pz,2)))", &MVAjet2_mjj);
  reader->AddVariable("MVAjet1_px := jet1_px", &MVAjet1_px);
  reader->AddVariable("MVAjet2_px := jet2_px", &MVAjet2_px);
  reader->BookMVA("kDL", "Wprimo/weights/TMVAClassification_DL1.weights.xml");

  TH1F *histkDL = new TH1F("MVA_kDL", "MVA_kDL", 100, 0, 1);
  TH1F *hpTbackground = new TH1F("pTbackground", "pTbackground", 50, 1.1e3, 2.6 * 1e3);
  TH1F *hpTsignal = new TH1F("pTsignal", "pTsignal", 50, 1.1e3, 2.6 * 1e3);
  TH1F *hmjjbackground = new TH1F("mjj_total", "mjj_total", 50, 1e3, 7e3);
  TH1F *hmjjsignal = new TH1F("mjj_signal", "mjj_signal", 50, 1e3, 7e3);

  for (int readerindex = 0; readerindex < event_entries; readerindex++)
  {
    EventJet->GetEntry(readerindex);
    MVAjet1_pT = sqrt(pow(jet1_px, 2) + pow(jet1_py, 2));
    MVAjet2_pT = sqrt(pow(jet2_px, 2) + pow(jet2_py, 2));
    MVAjet1_m = sqrt(pow(jet1_E, 2) - pow(jet1_px, 2) - pow(jet1_py, 2) - pow(jet1_pz, 2));
    MVAjet2_m = sqrt(pow(jet2_E, 2) - pow(jet2_px, 2) - pow(jet2_py, 2) - pow(jet2_pz, 2));
    MVAjet1_px = (Float_t)(jet1_px);
    MVAjet2_px = (Float_t)(jet2_px);
    histkDL->Fill(reader->EvaluateMVA("kDL"));
    mjj = sqrt(pow((jet1_E + jet2_E), 2) - pow((jet1_px + jet2_px), 2) - pow((jet1_py + jet2_py), 2) - pow((jet1_pz + jet2_pz), 2));
    if (reader->EvaluateMVA("kDL") < 0.73)
      hpTbackground->Fill(MVAjet1_pT);
    if (reader->EvaluateMVA("kDL") < 0.73)
      hmjjbackground->Fill(mjj);
    if (reader->EvaluateMVA("kDL") > 0.73)
      hpTsignal->Fill(MVAjet1_pT);
    if (reader->EvaluateMVA("kDL") > 0.73)
      hmjjsignal->Fill(mjj);
  }
  //Stampo il numero di eventi di segnale trovato
  cout << "There are " << hmjjsignal->GetEntries() << " events containing a W' " << endl;

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
  hpTstack->GetXaxis()->SetTitle("Leading jet p_{T}[GeV]");
  hpTstack->GetYaxis()->SetTitle("Number of events");
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
  hmjjstack->GetXaxis()->SetTitle("m_{jj}[GeV]");
  hmjjstack->GetYaxis()->SetTitle("Number of events");
  hmjjstack->Draw("");
  c3->Update();
  c3->SaveAs("hmjjtotal.png");

  TCanvas *c4 = new TCanvas("c4", "c4", 1366, 768);
  hmjjsignal->Draw("");
  c4->Update();
  c4->SaveAs("hmjjsignal.png");

  histkDL->Write();
  hpTbackground->Write();
  hpTsignal->Write();
  hmjjbackground->Write();
  hmjjsignal->Write();
  eventinputfile->Close();
  eventoutputfile->Close();
  delete reader;
*/
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