/*!
 *
 */

/*!
 *
 */

#include "headers/TMVAFactoryAnalysis.h"

//These namespaces can be useful
using namespace std;

void TMVAFactoryAnalysis(vector<TString> tmvamethods, vector<long unsigned int> nevents, string SBJetOutputFilename, string TMVAOutputFilename)
{
    TString outfilename(TString::Format("TMVAResults/%s.root", TMVAOutputFilename.data()));
    TFile *inputfile = TFile::Open(TString::Format("OutputFiles/%s.root", SBJetOutputFilename.data()), "read");
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

    long unsigned int ntrainsign = nevents[0]; /*!< Number of events used to train signal identification in the sample */
    long unsigned int ntrainback = nevents[1]; /*!< Number of events used to train background identification in the sample */
    long unsigned int ntestsign  = nevents[2]; /*!< Number of events used to test signal identification in the sample */
    long unsigned int ntestback  = nevents[3]; /*!< Number of events used to test background identification in the sample */
    TString dataString = TString::Format("nTrain_Signal=%lu", ntrainsign);
    dataString.Append(TString::Format(":nTrain_Background=%lu", ntrainback));
    dataString.Append(TString::Format(":nTest_Signal=%lu", ntestsign));
    dataString.Append(TString::Format(":nTest_Background=%lu", ntestback));
    dataString.Append(":SplitMode=Random:NormMode=NumEvents:!V");

    loader->PrepareTrainingAndTestTree("", "", dataString);
    for (vector<TString>::iterator stringit = tmvamethods.begin(); stringit != tmvamethods.end(); ++stringit)
    {
        if (stringit->CompareTo("kDL") == 0)
        {
            // Training strategies for deep learning

            TString configString = "!H:V";
            configString += ":VarTransform=N";
            configString += ":ErrorStrategy=CROSSENTROPY";
            configString += ":WeightInitialization=XAVIERUNIFORM";

            TString layoutString = "Layout=TANH|100, TANH|50, TANH|10, LINEAR";

            TString trainingString1 = "TrainingStrategy=LearningRate=1e-2,Momentum=0.5, Repetitions=1,ConvergenceSteps=100,BatchSize=100,DropConfig=0.0+0.5+0.5+0.0";
            trainingString1.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

            TString trainingString2 = " | LearningRate=1e-3,Momentum=0.1, Repetitions=1,ConvergenceSteps=100,BatchSize=50,DropConfig=0.0+0.1+0.1+0.0";
            trainingString2.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

            TString trainingString3 = " | LearningRate=1e-4,Momentum=0.0, Repetitions=10,ConvergenceSteps=100,BatchSize=25,DropConfig=0.0+0.1+0.1+0.0";
            trainingString3.Append(",WeightDecay=0.001,Regularization=L2,TestRepetitions=15,Multithreading=True");

            configString += ":" + layoutString + ":" + trainingString1;
            factory->BookMethod(loader, TMVA::Types::kDL, "kDL1", configString);

            configString += trainingString2;
            factory->BookMethod(loader, TMVA::Types::kDL, "kDL2", configString);

            configString += trainingString3;
            factory->BookMethod(loader, TMVA::Types::kDL, "kDL3", configString);
        }
        else if (stringit->CompareTo("kMLP") == 0)
        {
            // Training strategies for MultiLayerPerceptron

            TString trainingMLP1 = "VarTransform=N, NCycles=1000, HiddenLayers=N+5, NeuronType=tanh, EstimatorType=CE, TrainingMethod=BP, LearningRate=0.2, DecayRate=0.1";
            
            TString trainingMLP2 = "VarTransform=N, NCycles=500, HiddenLayers=N, NeuronType=Sigmoid, EstimatorType=MSE, TrainingMethod=BFGS, LearningRate=0.2, DecayRate=0.1";

            TString trainingMLP3 = "VarTransform=N, NCycles=1000, HiddenLayers=N-5, NeuronType=tanh, EstimatorType=CE, TrainingMethod=BP, LearningRate=0.1, DecayRate=0.05";

            factory->BookMethod(loader, TMVA::Types::kMLP, "kMLP1", trainingMLP1);
            factory->BookMethod(loader, TMVA::Types::kMLP, "kMLP2", trainingMLP2);
            factory->BookMethod(loader, TMVA::Types::kMLP, "kMLP3", trainingMLP3);
        }
        else if (stringit->CompareTo("kPDEFoam") == 0)
        {
            // Training strategies for PDE-Foam

            TString trainingPDEF1 = "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=100000:nBin=5:Nmin=100:Kernel=None:Compress=T";

            factory->BookMethod(loader, TMVA::Types::kPDEFoam, "kPDEFoam1", trainingPDEF1);
        }
        else if (stringit->CompareTo("kBDT") == 0)
        {
            // Training strategies for BDT

            TString trainingBDT1 = "Ntrees=800, MaxDepth=7, MinNodeSize=5%, nCuts=35, BoostType=RealAdaBoost, UseRandomisedTrees=True, UseNvars=3, UsePoissonNvars=True";

            TString trainingBDT2 = "Ntrees=1000, MaxDepth=5, MinNodeSize=15%, nCuts=-1, BoostType=RealAdaBoost, UseRandomisedTrees=True, UseNvars=3, UsePoissonNvars=True";

            TString trainingBDT3 = "Ntrees=1200, MaxDepth=7, MinNodeSize=5%, nCuts=-1, BoostType=AdaBoost, UseRandomisedTrees=Truee, SeparationType=CrossEntropy";

            factory->BookMethod(loader, TMVA::Types::kBDT, "kBDT1", trainingBDT1);
            factory->BookMethod(loader, TMVA::Types::kBDT, "kBDT2", trainingBDT2);
            factory->BookMethod(loader, TMVA::Types::kBDT, "kBDT3", trainingBDT3);
        }
    }
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();
    inputfile->Close();
    outputfile->Close();
}