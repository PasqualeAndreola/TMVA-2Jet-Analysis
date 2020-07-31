#include <TROOT.h>
#include <TApplication.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <THStack.h>
#include <TLegend.h>
#include <ClusterSequence.hh>
#include "headers/TreeCreator.h"

//Può essere comodo usare questi namespace, visto che si vedono tanti jet
using namespace std;
using namespace fastjet;

int main(int argc, char *argv[])
{
  /*Definisco variabili utili e i vettori che conterrano le quantità importanti dei jet*/
  char nomefile[100] = "lhc_anomalydetection_small";
  char str[256];
  Double_t pT, eta, phi, mass, pT_min = 20;
  Double_t E, px, py, pz;

  /*Leggo il file .h5 e creo un file contenente un albero per ciascun dataset*/
  cout << "Vuoi creare l'albero: " << nomefile << " ? [Y/N]" << endl;
  cin.get(str,256);
  if(strcmp(str,"Y") == 0) TreeCreator(nomefile);
  cin.ignore();
  cout << "Vuoi analizzare l'albero: " << nomefile << " ? [Y/N]" << endl;
  cin.get(str,256);
  if(strcmp(str,"N") == 0) return 0;
  cout << "Stiamo analizzando il file: " << nomefile << ".h5" << " costituito da:" << endl;
  strcpy(str,nomefile);
  strcat(str,".h5");
  openh5(str);

  /*Leggo il file .h5 e creo un file contenente un albero per ciascun dataset*/
  TApplication *Analysisroot_app = new TApplication("Analysis", &argc, argv);
  TFile *filealberello = new TFile(strcat(nomefile,".root"));
  TTree *alberello = (TTree*)filealberello->Get("Alberello3");
  Double_t value;
  TBranch *block0values = alberello->GetBranch("block0_values");
  block0values->SetAddress(&value);

  /*Scelgo la mia definizione di jet, specificando:
    algoritmo di clustering;
    raggio del cono dello sviluppo del jet;
    schema di ricombinazione (tipicamente si usa l'E_scheme);
    strategia(tipicamente best).
    Definisco anche un vettore di particelle da clusterare, di jet e di jet_background*/
  JetDefinition jet_def = JetDefinition(antikt_algorithm, 1.0, E_scheme, Best);
  vector<PseudoJet> particelle, jets;
  vector<vector<PseudoJet>> jets_signal, jets_background;
  
  //read only the destep branch for all entries
  Int_t nentries = (Int_t)alberello->GetEntries();
  Int_t i = 0, j = 0, flag_segnale = 0;
  for (i=0; i<dataset_info_list[3].get_column()*1000; i+=dataset_info_list[3].get_column()) 
  {
    particelle.clear();
    jets.clear();
    for (j=0; j<=dataset_info_list[3].get_column()-3; j+=3)
    {
      block0values->GetEntry(i+dataset_info_list[3].get_column()-1);
      flag_segnale = value;
      block0values->GetEntry(i+j);
      if (value > 0)
      {
        pT = value;
        block0values->GetEntry(i+j+1);
        eta = value;
        block0values->GetEntry(i+j+2);
        phi = value;
        particelle.push_back(PseudoJet(pT*cos(phi), pT*sin(phi), pT*sinh(eta), pT*cosh(eta)));
      }
    }
    ClusterSequence cluster_seq(particelle, jet_def);
    jets = sorted_by_pt(cluster_seq.inclusive_jets(pT_min));
    //cout << jets[0].pt() << endl;
    if (flag_segnale != 0) jets_signal.push_back(jets);
    else jets_background.push_back(jets);
  }

  //Istogrammi per l'impulso dei leading jet e per la massa
  TH1F *hpTsignal = new TH1F("Sign","Sign[GeV]", 50,1.1e3,2.6*1e3);
  TH1F *hmjjsignal = new TH1F("M_Sign","M_Sign[GeV]", 50, 2e3, 7e3);
  for (vector<vector<PseudoJet>>::size_type i = 0; i != jets_signal.size(); i++)
  {
    hpTsignal->Fill(jets_signal[i][0].pt());
    E = jets_signal[i][0].e() + jets_signal[i][1].e();
    px = jets_signal[i][0].px() + jets_signal[i][1].px();
    py = jets_signal[i][0].py() + jets_signal[i][1].py();
    pz = jets_signal[i][0].pz() + jets_signal[i][1].pz();
    hmjjsignal->Fill(sqrt(pow(E,2)-pow(px,2)-pow(py,2)-pow(pz,2)));
  }
  TH1F *hpTbackground = new TH1F("Back","Back[GeV]", 50,1.1e3,2.6*1e3);
  TH1F *hmjjbackground = new TH1F("M_Back","M_Back[GeV]", 50, 2e3, 7e3);
  for (vector<vector<PseudoJet>>::size_type i = 0; i != jets_background.size(); i++)
  {
    hpTbackground->Fill(jets_background[i][0].pt());
    E = jets_background[i][0].e() + jets_background[i][1].e();
    px = jets_background[i][0].px() + jets_background[i][1].px();
    py = jets_background[i][0].py() + jets_background[i][1].py();
    pz = jets_background[i][0].pz() + jets_background[i][1].pz();
    hmjjbackground->Fill(sqrt(pow(E,2)-pow(px,2)-pow(py,2)-pow(pz,2)));
  }

  // we fill a 3-d scatter plot with the particle step coordinates
  TCanvas *c1 = new TCanvas("c1","c1",1366,768);

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
  
  //Inserisco gli istogrammi del pt in una collezione e li rappresento
  THStack *hpTstack = new THStack("hs","");
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
  auto legend = new TLegend(0.65,0.8,0.9,0.9);
  //legend->SetHeader("Leading jet p_{T}","C"); // option "C" allows to center the header
  legend->AddEntry(hpTbackground,"Background","f");
  legend->AddEntry(hpTsignal,"Signal","f");
  legend->Draw("same");
  
  //Carico i disegni nel canvas
  c1->SetTitle("Leading jet transvers momentum: p_{T}[GeV]");
  c1->Update();
  c1->SaveAs("leadingpt.png");
  
  //Inserisco gli istogrammi della massa in una collezione e li rappresento
  TCanvas *c2 = new TCanvas("c2","c2",1366,768);
  c2->cd();
  THStack *hmjjstack = new THStack("hmjj","");
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
  auto legendmjj = new TLegend(0.65,0.8,0.9,0.9);
  //legend->SetHeader("Leading jet p_{T}","C"); // option "C" allows to center the header
  legendmjj->AddEntry(hmjjbackground,"Background","f");
  legendmjj->AddEntry(hmjjsignal,"Signal","f");
  legendmjj->Draw("same");
  
  //Carico i disegni nel canvas
  c2->SetTitle("Leading jet transvers momentum: p_{T}[GeV]");
  c2->Update();
  c2->SaveAs("massjj.png");

  return 0;
}