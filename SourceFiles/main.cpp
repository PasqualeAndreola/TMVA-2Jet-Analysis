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
#include "headers/JetCreator.h"

//Può essere comodo usare questi namespace, visto che si vedono tanti jet
using namespace std;
using namespace fastjet;

int main(int argc, char *argv[])
{
  /*Definisco variabili utili e i nomi dei file da analizzare */
  vector<TString> filenames;
  vector<int> sbflags;
  TString SBOutputfile = "SBoutput";
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
  char str[256];

  /*Definisco variabili utili e i vettori che conterrano le quantità importanti dei jet*/
  int i = 0;
  /*TFile SBOutputroot(TString::Format("%s.root", SBOutputfile.Data()),"recreate");
  SBOutputroot.Close();*/

  for (vector<TString>::iterator stringit = filenames.begin(); stringit != filenames.end(); ++stringit, i++)
  {
    /*Leggo il file .h5 e creo un file contenente un albero per ciascun dataset*/
    /*
    cout << "Si sta analizzando il file: " << *stringit << ".h5." <<endl;
    cout << "Esso è costituito da:" << endl;
    strcpy(str,*stringit);
    strcat(str,".h5");
    openh5(str);
    strcpy(str,*stringit);
    cout << "Would you create the tree " << *stringit << " containing kinematic quantities? [Y/N]" << endl;
    cin.get(str,256);
    if(strcmp(str,"Y") == 0) TreeCreator(*stringit);
    cin.ignore();
    cout << "Would you add to the file " << *stringit << " a tree containing the jet? [Y/N]" << endl;
    cin.get(str,256);
    if(strcmp(str,"Y") == 0) TreeJetCreator(*stringit, 1.0, 20);
    cin.ignore();
    cout << "Would you analize the jets stored in " << *stringit << " ? [Y/N]" << endl;
    cin.get(str,256);
    if(strcmp(str,"N") == 0) return 0;
    cin.ignore();
    */
    
    cout << "Analyzing file: " << *stringit << ".h5." << endl;
    cout << "It is made up of:" << endl;
    openh5(TString::Format("InputFiles/%s.h5", stringit->Data()));
    TreeCreator(*stringit, 2101);
    SBTreeCreator(TString::Format("%s.root", stringit->Data()), TString::Format("%s.root", SBOutputfile.Data()), sbflags[i], i);
    dataset_info_list.clear();

    //TApplication *Analysisroot_app = new TApplication("Analysis", &argc, argv);

    //Istogrammi per l'impulso dei leading jet e per la massa
    /*TH1F *hpTsignal = new TH1F("Sign", "Sign[GeV]", 50, 1.1e3, 2.6 * 1e3);
    TH1F *hmjjsignal = new TH1F("M_Sign", "M_Sign[GeV]", 50, 2e3, 7e3);
    TH1F *hpTbackground = new TH1F("Back", "Back[GeV]", 50, 1.1e3, 2.6 * 1e3);
    TH1F *hmjjbackground = new TH1F("M_Back", "M_Back[GeV]", 50, 2e3, 7e3);*/
    /*
      //Creo il vettore di jet per l'evento rappresentato dalla riga i-sima
      jets = JetCreator(kinematics_per_event, R, pT_min);

      if (flag_segnale == 0 && (dataset_info_list[3].get_column() % 3 != 0))
      {
        //Viene riempito l'istogramma del background
        hpTbackground->Fill(jets[0].pt());
        E = jets[0].e() + jets[1].e();
        px = jets[0].px() + jets[1].px();
        py = jets[0].py() + jets[1].py();
        pz = jets[0].pz() + jets[1].pz();
        hmjjbackground->Fill(sqrt(pow(E, 2) - pow(px, 2) - pow(py, 2) - pow(pz, 2)));
      }
      else
      {
        //Viene riempito l'istogramma del segnale
        hpTsignal->Fill(jets[0].pt());
        E = jets[0].e() + jets[1].e();
        px = jets[0].px() + jets[1].px();
        py = jets[0].py() + jets[1].py();
        pz = jets[0].pz() + jets[1].pz();
        hmjjsignal->Fill(sqrt(pow(E, 2) - pow(px, 2) - pow(py, 2) - pow(pz, 2)));
      }
    

    // we fill a 3-d scatter plot with the particle step coordinates
    TCanvas *c1 = new TCanvas("c1", "c1", 1366, 768);
*/
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
    /*
    //Inserisco gli istogrammi del pt in una collezione e li rappresento
    THStack *hpTstack = new THStack("hs", "");
    hpTbackground->SetLineColor(kRed);
    hpTbackground->SetFillColor(kRed);
    hpTbackground->SetStats(kFALSE);
    hpTsignal->SetLineColor(kBlue);
    hpTsignal->SetFillColorAlpha(kBlue, 0.3);
    hpTsignal->SetStats(kFALSE);
    hpTstack->Add(hpTbackground);
    hpTstack->Add(hpTsignal);
    hpTstack->Draw();
    hpTstack->SetTitle("Leading jet transverse momentum: p_{T}[GeV]");
    hpTstack->GetXaxis()->SetTitle("Leading jet p_{T}[GeV]");
    hpTstack->GetYaxis()->SetTitle("Number of events");

    //Disegno la legenda
    auto legend = new TLegend(0.65, 0.8, 0.9, 0.9);
    //legend->SetHeader("Leading jet p_{T}","C"); // option "C" allows to center the header
    legend->AddEntry(hpTbackground, "Background", "f");
    legend->AddEntry(hpTsignal, "Signal", "f");
    legend->Draw("same");

    //Carico i disegni nel canvas
    c1->SetTitle("Leading jet transvers momentum: p_{T}[GeV]");
    c1->Update();
    c1->SaveAs("leadingpt.png");

    //Inserisco gli istogrammi della massa in una collezione e li rappresento
    TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
    c2->cd();
    THStack *hmjjstack = new THStack("hmjj", "");
    hmjjbackground->SetLineColor(kRed);
    hmjjbackground->SetFillColor(kRed);
    hmjjbackground->SetStats(kFALSE);
    hmjjsignal->SetLineColor(kBlue);
    hmjjsignal->SetFillColorAlpha(kBlue, 0.3);
    hmjjsignal->SetStats(kFALSE);
    hmjjstack->Add(hmjjbackground);
    hmjjstack->Add(hmjjsignal);
    hmjjstack->Draw();
    hmjjstack->SetTitle("Particle reconstructed mass m_{jj}[GeV]");
    hmjjstack->GetXaxis()->SetTitle("m_{jj}[GeV]");
    hmjjstack->GetYaxis()->SetTitle("Number of events");

    //Disegno la legenda
    auto legendmjj = new TLegend(0.65, 0.8, 0.9, 0.9);
    //legend->SetHeader("Leading jet p_{T}","C"); // option "C" allows to center the header
    legendmjj->AddEntry(hmjjbackground, "Background", "f");
    legendmjj->AddEntry(hmjjsignal, "Signal", "f");
    legendmjj->Draw("same");

    //Carico i disegni nel canvas
    c2->SetTitle("Leading jet transvers momentum: p_{T}[GeV]");
    c2->Update();
    c2->SaveAs("massjj.png");
*/
  }
  SBTreeJetKinematicsCreator(SBOutputfile, 5, 10, 10, 1, 20);
  /*
  TString outfilename("TMVA.root");
  TFile *inputfile = TFile::Open("SBoutput.root", "read");
  TFile *outputfile = TFile::Open(outfilename, "recreate");
  TMVA::DataLoader *loader = new TMVA::DataLoader("Wprimo");
  TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", outputfile, "AnalysisType=Classification");
  loader->AddVariable("MVAjet1_pT := sqrt(pow(jet1_px,2) + pow(jet1_py,2))", 'F');
  loader->AddVariable("MVAjet2_pT := sqrt(pow(jet2_px,2) + pow(jet2_py,2))", 'F');
  loader->AddVariable("MVAjet1_m := sqrt( abs(pow(jet1_E,2) - pow(jet1_px,2) - pow(jet1_py,2) - pow(jet1_pz,2)))",'F');
  loader->AddVariable("MVAjet2_m := sqrt( abs(pow(jet2_E,2) - pow(jet2_px,2) - pow(jet2_py,2) - pow(jet2_pz,2)))", 'F');
  loader->AddVariable("MVAjet_mjj := sqrt( abs(pow(jet1_E+jet2_E,2) - pow(jet1_px+jet2_px,2) - pow(jet1_py+jet2_py,2) - pow(jet1_pz+jet2_pz,2)))", 'F');
  loader->AddVariable("MVAjet1_px := jet1_px", 'F');
  loader->AddVariable("MVAjet2_px := jet2_px", 'F');
  TTree *signal = (TTree *)inputfile->Get("SignalJet");
  TTree *background = (TTree *)inputfile->Get("BackgroundJet");
  Double_t signalweight = 1.0, backgroundweight = 1.0;
  loader->AddSignalTree(signal, signalweight);
  loader->AddBackgroundTree(background, backgroundweight);

  TString dataString = "nTrain_Signal=10000:nTrain_Background=10000:nTest_Signal=10000:nTest_Background=10000:SplitMode=Random:NormMode=NumEvents:!V";
  loader->PrepareTrainingAndTestTree("", "", dataString);
  TString configString = "!H:V";
  configString += ":VarTransform=N";
  configString += ":ErrorStrategy=CROSSENTROPY";
  configString += ":WeightInitialization=XAVIERUNIFORM";

  TString layoutString = "Layout=TANH|100, TANH|50, TANH|10, LINEAR";

  TString trainingString1 = "TrainingStrategy=LearningRate=1e-1,Momentum=0.5, Repetitions=1,ConvergenceSteps=1000,BatchSize=20,DropConfig=0.0+0.5+0.5+0.0,WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True";

  TString trainingString2 = " | LearningRate=1e-2,Momentum=0.1, Repetitions=1,ConvergenceSteps=1000,BatchSize=20,DropConfig=0.0+0.1+0.1+0.0,WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True";

  TString trainingString3 = " | LearningRate=1e-3,Momentum=0.0, Repetitions=10,ConvergenceSteps=1000,BatchSize=50,DropConfig=0.0+0.1+0.1+0.0,WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True";

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
  cout << "Ci sono " << hmjjsignal->GetEntries() << " eventi riconducibili a W' " << endl;

  //Inserisco gli istogrammi del pt e della massa in una collezione e li rappresento
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
  TCanvas *c1 = new TCanvas("c1", "c1", 1366, 768);
  hpTstack->Draw();
  c1->Update();
  c1->SaveAs("hpTtotal.png");

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
  TCanvas *c2 = new TCanvas("c2", "c2", 1366, 768);
  hmjjstack->Draw("");
  c2->Update();
  c2->SaveAs("hmjjtotal.png");

  TCanvas *c3 = new TCanvas("c3", "c3", 1366, 768);
  hmjjsignal->Draw("");
  c3->Update();
  c3->SaveAs("hmjjsignal.png");

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