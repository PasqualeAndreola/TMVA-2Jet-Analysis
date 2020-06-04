#include <unistd.h>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "headers/OpenH5.h"
#include "headers/Opfunc.h"
#define FILE_NAME "tiny.h5"

int main(void)
{
  hid_t file, dataset_id, dataspace_id;
  herr_t dataset;
  std::vector<hsize_t> offset, count, count_resto;
  int dimensionebuffer = 1000;
  double buf[dimensionebuffer][dimensionebuffer];
  for (int i=0; i<dimensionebuffer; i++)
  {
    for (int j=0; j<dimensionebuffer; j++)
    {
      buf[i][j]=0;
    }
  }
  /*Creo file*/
  std::ofstream Dati("ProvaDati.txt");
  if (!Dati) std::cout << "mammt";
  openh5(FILE_NAME);

  /*Viene aperto il file in lettura*/
  file = H5Fopen(FILE_NAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  /*Viene aperto il dataset*/
  dataset_id = H5Oopen_by_addr(file, dataset_info_list[3].get_addr());
  printf("\nStiamo esaminando il dataset: %s\n",dataset_info_list[3].get_name().c_str());
  
  /*Cerchiamo il rango del dataspace e la dimensione di ogni asse 
    nel dataspace*/
  dataspace_id = H5Dget_space(dataset_id);
  int rank = H5Sget_simple_extent_ndims(dataspace_id);
  printf("\nNumero di dimensioni del dataspace: %d\n", rank);

  hsize_t dims_out[rank];
  H5Sget_simple_extent_dims(dataspace_id,dims_out,NULL);
  printf("\nDimensione assi del dataspace: %d * %d\n", dims_out[0], dims_out[1]);
  sleep(10);
  /*Definisco vettori utili alla creazione di unmemoryspace e di un
    hyperslab rank-dimensionale che serve per leggere un dataset.
    Creo un vettore di resti che servirà per raccogliere le matrici
    più piccole, che escono fuori dall'hyperslab*/
  for(int i=0; i<rank; i++)
  {
    offset.push_back(0);
    count.push_back(dimensionebuffer);
    count_resto.push_back(dims_out[i]%dimensionebuffer);
  }  

  /*Controllo che il dataset sia più grande dell'hyperslab appena creato.
    Se così non fosse, andrebbero esaminati singolarmente gli assi più
    piccoli e, se fossero entrambi più piccoli, si creerebbe un hyperslab
    grande abbastanza da contenere direttamente questo piccolo resto*/
  if ((dims_out[0]>=dimensionebuffer)&&(dims_out[1]>=dimensionebuffer))  
  {  
    /*Si scorre prima una colonna di matrici, poi ci sposta alle colonne successive*/
    for (int b=0; b<round(dims_out[1]/dimensionebuffer); b++)
    {
      offset[1]=b*dimensionebuffer;
      for (int a=0; a<round(dims_out[0]/dimensionebuffer); a++)
      {
        offset[0] = a*dimensionebuffer;

        /*Creo uno spazio di memorizzazione ed una hyperslab che servono
          per leggere il dataset a blocchi. Questa accortezza è necessaria
          perché siamo in presenza di dataset abbastanza grandi da saturare
          la ram, rendendo impossibile una lettura singola del dataset*/
        hid_t memspace = H5Screate_simple(rank, count.data(), NULL);
        H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count.data(), NULL);

        /*Viene letto il dataset e viene scaricata una matrice nel buffer*/
        dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace, dataspace_id, H5P_DEFAULT, buf);
        for (int i = 0; i<count[0]; i++)
        {
          for (int j = 0; j<count[1]; j++)
          { 
            Dati << buf[i][j] << "\n";
          }
        }
      }
      /*Controllo l'eventuale presenza di un resto non compreso nella prima colonna
        di grandi hyperslab. Si tratta di leggere un rettangolo con le righe rimanenti*/
      if (count_resto[0]!=0)
      {
        /*Creiamo un hyperslab-resto rettangolo da resto*dimensionebuffer*/
        count_resto[1] = dimensionebuffer;
        hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
        H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
        dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);
        for (int i = 0; i<count_resto[0]; i++)
        {
          for (int j = 0; j<count_resto[1]; j++)
          { 
            Dati << buf[i][j] << "\n";
          }
        }
      }
    }
    /*Reinizializzo la dimensione orizzontale dell'hyperslab-resto*/
    count_resto[1] = dims_out[1]%dimensionebuffer;

    /*Controllo che non siano rimaste colonne non esaminate*/
    if (count_resto[1]!=0)
    {
      /*Reinizializzo la dimensione verticale dell'hyperslab-resto*/
      count_resto[0]=dimensionebuffer;
      for (int a=0; a<round(dims_out[0]/dimensionebuffer); a++)
      {
        offset[0] = a*dimensionebuffer;
        hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
        H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
        dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);
        for (int i = 0; i<count_resto[0]; i++)
        {
          for (int j = 0; j<count_resto[1]; j++)
          { 
            Dati << buf[i][j] << "\n";
          }
        }
      }
      
      /*Una volta finita la correzione sulla riga del dataset,
        controllo nuovamente che non ci sia una correzione nella parte
        finale della colonna del dataset, proprio come prima.
        In pratica è l'eventuale ultimo rettangolo diagonale della matrice*/
      count_resto[0] = dims_out[0]%dimensionebuffer;
      if (count_resto[0]!=0)
      {
        hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
        H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
        dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);
        for (int i = 0; i<count_resto[0]; i++)
        {
          for (int j = 0; j<count_resto[1]; j++)
          { 
            Dati << buf[i][j] << "\n";
          }
        }
      }
    }
  }
  /*Controlliamo una colonna di matrici con una dimensione orizzontale più
    piccola del primo hyperslab grande*/
  else if ((dims_out[0]>=dimensionebuffer)&&(dims_out[1]<dimensionebuffer))
  {
    count_resto[0] = dimensionebuffer;
    count_resto[1] = dims_out[1];
    for (int a=0; a<round(dims_out[0]/dimensionebuffer); a++)
    {
      offset[0] = a*dimensionebuffer;
      hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
      H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
      dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);    
      for (int i = 0; i<count_resto[0]; i++)
      {
        for (int j = 0; j<count_resto[1]; j++)
        { 
            Dati << buf[i][j] << "\n";
        }
      }
    }
    /*Controlliamo la fine della colonna*/
    count_resto[0] = dims_out[0]%dimensionebuffer;
    if (count_resto[0]!=0)
    {
      hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
      H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
      dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);
      for (int i = 0; i<count_resto[0]; i++)
      {
        for (int j = 0; j<count_resto[1]; j++)
        { 
            Dati << buf[i][j] << "\n";
        }
      }
    }
  }
  /*Controlliamo una riga di matrici con una dimensione verticale più
    piccola del primo hyperslab grande*/
  else if ((dims_out[0]<dimensionebuffer)&&(dims_out[1]>=dimensionebuffer))
  {
    count_resto[0] = dims_out[0];
    count_resto[1] = dimensionebuffer;
    for (int b=0; b<round(dims_out[1]/dimensionebuffer); b++)
    {
      offset[1] = b*dimensionebuffer;
      hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
      H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
      dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);
      for (int i = 0; i<count_resto[0]; i++)
      {
        for (int j = 0; j<count_resto[1]; j++)
        { 
            Dati << buf[i][j] << "\n";
        }
      }
    }
    /*Controlliamo la fine della riga*/
    count_resto[1] = dims_out[1]%dimensionebuffer;
    if (count_resto[1]!=0)
    {
      hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
      H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
      dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);      
      for (int i = 0; i<count_resto[0]; i++)
      {
        for (int j = 0; j<count_resto[1]; j++)
        { 
            Dati << buf[i][j] << "\n";
        }
      }
    }
  }
  else
  {
    count_resto[0] = dims_out[0]%dimensionebuffer;
    count_resto[1] = dims_out[1]%dimensionebuffer;
    hid_t memspace_resto = H5Screate_simple(rank, count_resto.data(), NULL);
    H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset.data(), NULL, count_resto.data(), NULL);
    dataset = H5Dread(dataset_id, H5Dget_type(dataset_id), memspace_resto, dataspace_id, H5P_DEFAULT, buf);   
    for (int i = 0; i<count_resto[0]; i++)
    {
      for (int j = 0; j<count_resto[1]; j++)
      { 
            Dati << buf[i][j] << "\n";
      }
    }
  }
  Dati.close();
}