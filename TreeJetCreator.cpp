#include "headers/TreeJetCreator.h"

using namespace std;
using namespace fastjet;

int TreeJetCreator(const char * filename, double R, double pT_min)
{
    //Definisco delle variabili utili
    char nomefile[256];
    strcpy(nomefile, filename);
    strcat(nomefile,".root");
    Double_t pT, eta, phi, mass;
    Double_t E, px, py, pz;

    /*Scelgo la mia definizione di jet, specificando:
      algoritmo di clustering;
      raggio del cono dello sviluppo del jet;
      schema di ricombinazione (tipicamente si usa l'E_scheme);
      strategia(tipicamente best).
      Definisco anche un vettore di particelle da clusterare, di jet e di jet_background*/
    JetDefinition jet_def = JetDefinition(antikt_algorithm, R, E_scheme, Best);
    vector<PseudoJet> particelle, jets;

    //Definisco l'albero ed il file in cui inserirlo
    TFile rootfile(nomefile,"update");
    if (rootfile.Get("Jet_tree")!=0) rootfile.Get("Jet_tree")->Delete("all");
    TTree Jet_tree("Jet_tree","Jet_tree");
    TBranch *jetbranch = Jet_tree.Branch("Jet.", &jets);
    TTree *alberello = (TTree*)rootfile.Get("Alberello3");
    Double_t value;
    TBranch *block0values = alberello->GetBranch("block0_values");
    block0values->SetAddress(&value);
  
    //read only the destep branch for all entries
    Int_t nentries = (Int_t)alberello->GetEntries();
    Int_t i = 0, j = 0, flag_segnale = 0;
    for (i=0; i<nentries; i+=dataset_info_list[3].get_column()) 
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
        jetbranch->Fill();
    }
    Jet_tree.Write("");
    return 0;
}