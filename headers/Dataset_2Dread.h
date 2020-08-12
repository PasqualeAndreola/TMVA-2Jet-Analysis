#ifndef DATASET_2DREAD_H
#define DATASET_2DREAD_H
#include <fstream>
#include "H5Cpp.h"
#include <math.h>
#include <TFile.h>
#include <TTree.h>

template <typename buftype>
void Dataset_2Dread(hid_t dataset_id, int dimensionebuffer, int numerodataset,const char *scaricobuffer)
{

    /*Creo una stringa che servirà per dare i nomi ai file*/
    char nomefile[100], nomealbero[100];
    snprintf(nomealbero, sizeof(nomealbero), "Alberello%d", numerodataset);

    /*Creo un file e un albero dove scaricare i dataset,associandoli a foglie*/
    strcpy(nomefile, scaricobuffer);   
    TFile rootfile(strcat(nomefile,".root"), "update");
    /*Elimino eventuali residui di alberi scritti precedentemente*/
    if (rootfile.Get(nomealbero)!=0) rootfile.Get(nomealbero)->Delete("all");
    TTree roottree(nomealbero,"Alberello con dati");
    
    /*Creiamo il file dove scaricare il buffer*/
    strcpy(nomefile, scaricobuffer);
    
    /*Cerchiamo il rango del dataspace, la dimensione di ogni asse 
      nel dataspace e il tipo del dataset, per allocare la memoria*/
    hid_t datatype_id = H5Dget_type(dataset_id);
    size_t datatype_size = H5Tget_size(datatype_id);
    hid_t dataspace_id = H5Dget_space(dataset_id);
    int rank = H5Sget_simple_extent_ndims(dataspace_id);
    printf("\nNumero di dimensioni del dataspace: %d\n", rank);

    /*Definisco vettori utili alla creazione di un memoryspace e di un
      hyperslab rank-dimensionale che serve per leggere un dataset.
      Creo un vettore di resti che servirà per raccogliere le matrici
      più piccole, che escono fuori dall'hyperslab*/
    hsize_t *dims_out = new hsize_t[(rank)*sizeof(hsize_t)]();
    hsize_t *offset = new hsize_t[(rank)*sizeof(hsize_t)]();
    hsize_t *count = new hsize_t[(rank)*sizeof(hsize_t)]();
    hsize_t *count_resto = new hsize_t[(rank)*sizeof(hsize_t)]();
    
    H5Sget_simple_extent_dims(dataspace_id,dims_out,NULL);
    printf("\nIl dataset ha dimensioni: ");
    for(int i=0; i<std::min(rank,2); i++)
    {
      std::cout << dims_out[i];
      if(i<rank-1) std::cout << "*";
      offset[i]=0;
      count[i]=dimensionebuffer;
      count_resto[i]=dims_out[i]%dimensionebuffer;
    }
    std::cout << "\n\n";
    
    /*Alloco la memoria adatta al tipo del buffer*/
    buftype *buf = new buftype[dimensionebuffer*dimensionebuffer*datatype_size]();

    /*Aggiungo un branch dove aggiungere i dati letti per il dataset che si sta scorrendo*/
    Double_t branchbuf;
    roottree.Branch(dataset_info_list[numerodataset].get_name().c_str(), &branchbuf);

    /*Scorro tutto il dataset, facendo attenzione ai bordi*/
    if (rank==1)
    {
        for (int a=0; a<round(dims_out[0]/dimensionebuffer); a++)
        {
            /*La lettura della riga i inizia dove finisce la riga i-dimensionebuffer*/
            offset[0] = a*dimensionebuffer;

            /*In queste ipotesi, le sottomatrici sono dimensionebuffer*dimensionebuffer,
            quindi usiamo hyperslab e memoryspace grandi quanto il nostro buffer massimo*/
            hid_t memspace = H5Screate_simple(rank, count, NULL);
            if (memspace<0) { printf("\nMemory space non creato correttamente\n"); }
            if(H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL)<0)
                { printf("\nHyperslab non creata correttamente\n"); }
            if(H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf)<0)
                { printf("\nDataset non letto correttamente\n");}   
            
            /*Scarico il buffer appena letto*/
            for (int i=0; i<count[0]; i++)
            {
                branchbuf = buf[i];
                roottree.Fill();
            }
        }

        /*In queste ipotesi restano da esaminare delle colonne,
        quindi leggiamo matrici dimensionebuffer*resto */
        count[0] = count_resto[0];
        hid_t memspace = H5Screate_simple(rank, count, NULL);
        if (memspace<0) { printf("\nMemory space non creato correttamente\n"); }
        if(H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL)<0)
            { printf("\nHyperslab non creata correttamente\n"); }
        if(H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf)<0)
            { printf("\nDataset non letto correttamente\n");}

        /*Scarico il buffer appena letto*/
        for (int i=0; i<count[0]; i++)
        {
            branchbuf = buf[i*count[0]];
            roottree.Fill();
        }
    }    
    else
    {
        for (int a=0; a<round(dims_out[0]/dimensionebuffer); a++)
        {
            /*La lettura della riga i inizia dove finisce la riga i-dimensionebuffer*/
            offset[0] = a*dimensionebuffer;
            for (int b=0; b<round(dims_out[1]/dimensionebuffer);b++)
            {
                /*Calcolo l'offset di partenza anche per le colonne*/
                offset[1] = b*dimensionebuffer;

                /*In queste ipotesi, le sottomatrici sono dimensionebuffer*dimensionebuffer,
                quindi usiamo hyperslab e memoryspace grandi quanto il nostro buffer massimo*/
                hid_t memspace = H5Screate_simple(rank, count, NULL);
                if (memspace<0) { printf("\nMemory space non creato correttamente\n"); }
                if(H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL)<0)
                    { printf("\nHyperslab non creata correttamente\n"); }
                if(H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf)<0)
                    { printf("\nDataset non letto correttamente\n");}   
            
                /*Scarico il buffer appena letto*/
                for (int i=0; i<count[1]; i++)
                {
                    {
                        for (int j = 0; j<count[0]; j++)
                        { 
                            branchbuf = buf[i*count[0]+j];
                            roottree.Fill();
                        }
                    }
                }
            }

            /*In queste ipotesi restano da esaminare delle colonne,
            quindi leggiamo matrici dimensionebuffer*resto */
            count[1] = count_resto[1];
            hid_t memspace = H5Screate_simple(rank, count, NULL);
            if (memspace<0) { printf("\nMemory space non creato correttamente\n"); }
            if(H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL)<0)
                { printf("\nHyperslab non creata correttamente\n"); }
            if(H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf)<0)
                { printf("\nDataset non letto correttamente\n");}

            /*Scarico il buffer appena letto*/
            for (int i=0; i<count[1]; i++)
            {
                for (int j=0; j<count[0]; j++)
                {
                    branchbuf = buf[i*count[0]+j];
                    roottree.Fill();
                }
            }      
        }

        /*In queste ipotesi restano da esaminare delle righe,
        quindi leggiamo matrici resto*dimensionebuffer */
        count[0] = count_resto[0];
        count[1] = dimensionebuffer;
        for (int b=0; b<round(dims_out[1]/dimensionebuffer); b++)
        {
            offset[1] = b*dimensionebuffer;
            hid_t memspace = H5Screate_simple(rank, count, NULL);
            if (memspace<0) { printf("\nMemory space non creato correttamente\n"); }
            if(H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL)<0)
                { printf("\nHyperslab non creata correttamente\n"); }
            if(H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf)<0)
                { printf("\nDataset non letto correttamente\n");}

            /*Scarico il buffer appena letto*/
            for (int i=0; i<count[1]; i++)
            {
                for (int j=0; j<count[0]; j++)
                {
                    branchbuf = buf[i*count[0]+j];
                    roottree.Fill();
                }
            }
        }

        /*In queste ipotesi resta solo una matrice resto*resto */
        hid_t memspace = H5Screate_simple(rank, count_resto, NULL);
        if (memspace<0) { printf("\nMemory space non creato correttamente\n"); }
        if(H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count_resto, NULL)<0)
            { printf("\nHyperslab non creata correttamente\n"); }
        if(H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf)<0)
            { printf("\nDataset non letto correttamente\n");} 
    
        /*Scarico il buffer appena letto*/
        for (int i=0; i<count_resto[1]; i++)
        {
            for (int j=0; j<count_resto[0]; j++)
            {
                branchbuf = buf[i*count_resto[0]+j];
                roottree.Fill();
            }
        }
    }

    /*Libero tutta la memoria allocata durante la lettura*/
    delete [] dims_out;
    delete [] offset;
    delete [] count;
    delete [] count_resto;
    delete [] buf;
    roottree.Write("");
}
#endif