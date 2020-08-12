#include "headers/TreeCreator.h"

int TreeCreator(const char * filename)
{
  const int dimensionebuffer = 2101;
  
  /*Creo file*/
  char nome[100];
  strcpy(nome, filename);
  strcat(nome,".h5");

  /*Viene aperto il file in lettura*/
  hid_t file = H5Fopen(nome, H5F_ACC_RDONLY, H5P_DEFAULT);
  strcpy(nome, filename);

  /*Scorro tutti i possibili dataset presenti nel file*/
  for (int numerodataset = 0; numerodataset<dataset_info_list.size(); numerodataset++)
  {
    /*Apro il dataset scelto per estrarne le informazioni*/
    hid_t dataset_id = H5Oopen_by_token(file, dataset_info_list[numerodataset].get_token());
    printf("\nStiamo esaminando il dataset: %s\n",dataset_info_list[numerodataset].get_name().c_str());
    
    /*Valuto il tipo del dataset e alloco la memoria adatta*/
    int classe = H5Tget_class(H5Dget_type(dataset_id));
    switch (classe)
    {
      case(0):
      {
        std::cout << "\nIl dataset è fatto di interi\n";
        Dataset_2Dread<int>(dataset_id, dimensionebuffer, numerodataset, nome);
        break;
      }
      case(1):
      {
        std::cout << "\nIl dataset è fatto di float\n";
        Dataset_2Dread<double>(dataset_id, dimensionebuffer, numerodataset, nome);
        break;
      }
      case(2):
      {
        std::cout << "\nIl dataset è fatto da byte\n";
        Dataset_2Dread<Byte_t>(dataset_id, dimensionebuffer, numerodataset, nome);
        break;
      }
    }
  }
  H5Fclose(file);
  return 0;
}