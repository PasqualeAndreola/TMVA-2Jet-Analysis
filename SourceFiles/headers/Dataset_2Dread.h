/*! \file Dataset_2Dread.h
 *
 *  \brief Header file for \link Dataset_2Dread \endlink body, because templates are instantiated at compile time.
 */

/*!
 *  \fn void Dataset_2Dread(hid_t dataset_id, int bufferdimension, int datasetnumber, const char *outfile) Dataset_2Dread.h "Dataset_2Dread.h"
 *  \brief This function is used to read a dataset of dimension 1 or 2 from a *.h5 file.
 * 
 *  This function is used to read a dataset of dimension 1 or 2 from a *.h5 file.\n
 *  \link Dataset_2Dread \endlink reads the dataset given by the \p dataset_id scanning it
 *  with memory slab whose dimensions are designed to be located inside dataset limit.\n
 *  This is done because \c H5DRead  is designed to crash if the user tries to read 
 *  out of the dataset dimensions.\n
 *  \p bufferdimension Determines the dimension of the buffer used to collect data from the *.h5 file.\n
 *  It has to be chosen considering the datatype and the amount of RAM installed.\n
 *  Memory slab read from the dataset is stored in a buffer \p bufferdimension 
 *  \p bufferdimension (for 2D dataset or \p bufferdimension*1 for 1D dataset) of type \p buftype. \n
 *  Buffer is then written in the "output".root file 
 * 
 *  \tparam buftype Type of the buffer that is created to store data collected from the dataset
 *  \param dataset_id Unique dataset identifier, returned when the dataset is opened in \link TreeCreator \endlink
 *  \param datasetnumber Number assigned to the dataset when it is found from the \link openh5 \endlink.\n It is used to manage
 *  dataset information stored in the \link DatasetInfo \endlink structure
 *  \param *outfile Represents the name of the "output".root file
 * 
 */

#ifndef DATASET_2DREAD_H
#define DATASET_2DREAD_H

#include <unistd.h>
#include <iostream>
#include <fstream>
#include "H5Cpp.h"
#include <math.h>
#include <TFile.h>
#include <TTree.h>

//It can be useful to use these namespaces
using namespace std;

/*Defining global variables*/
const int bufferdimension = 2101;

template <typename buftype>
void Dataset_2Dread(hid_t dataset_id, int datasetnumber, const char *outfile)
{
    /*Defining a generic counter*/
    unsigned long long int counter = 0;

    /*Define some string used to name output file and trees*/
    string filename, treename;
    filename.append("OutputFiles/");
    filename.append(outfile);
    filename.append(".root");

    /*Cleaning root file with the same name*/
    if (datasetnumber == 0)
        TFile rootfile(filename.data(), "recreate");
    TFile rootfile(filename.data(), "update");

    /*Tree name is defined to be the dataset name*/
    treename.append(dataset_info_list[datasetnumber].get_name().data());
    TTree roottree(treename.data(), "Alberello con dati");

    /*Getting datatype, datatype size, dataspace, rank and dimensions of the dataset*/
    hid_t datatype_id = H5Dget_type(dataset_id);
    size_t datatype_size = H5Tget_size(datatype_id);
    hid_t dataspace_id = H5Dget_space(dataset_id);
    int rank = H5Sget_simple_extent_ndims(dataspace_id);
    printf("\nDataset dimension number: %d\n", rank);

    /*
      Defining arrays useful to create memoryspace and hyperslab with number
      of dimensions equal to rank, that will be used to read data.
      Some smaller matrices are defined to read the remaining part of the dataset
    */
    hsize_t *dims_out = new hsize_t[(rank) * sizeof(hsize_t)]();
    hsize_t *offset = new hsize_t[(rank) * sizeof(hsize_t)]();
    hsize_t *count = new hsize_t[(rank) * sizeof(hsize_t)]();
    hsize_t *count_rest = new hsize_t[(rank) * sizeof(hsize_t)]();

    H5Sget_simple_extent_dims(dataspace_id, dims_out, NULL);
    printf("\nDataset dimension are: ");
    for (int i = 0; i < std::min(rank, 2); i++)
    {
        cout << dims_out[i];
        if (i < rank - 1)
            cout << "*";
        offset[i] = 0;
        count[i] = bufferdimension;
        count_rest[i] = dims_out[i] % bufferdimension;
    }
    cout << "\n\n";

    /*Create the right buffer, using the template argument buftype*/
    buftype *buf = new buftype[bufferdimension * bufferdimension * datatype_size]();

    /*Defining branchbuf to store data read from the buffer in a branch*/
    Double_t branchbuf;
    roottree.Branch(dataset_info_list[datasetnumber].get_name().c_str(), &branchbuf);

    /*Going through the dataset, avoiding borders*/
    if (rank == 1)
    {
        for (int a = 0; a < round(dims_out[0] / bufferdimension); a++)
        {
            /*Reading the i-th line starts from i-bufferdimension line*/
            offset[0] = a * bufferdimension;

            /*In this case, submatrices are bufferdimension*bufferdimension,
            so we use hyperslab and memoryspace as big as our buffer */
            hid_t memspace = H5Screate_simple(rank, count, NULL);
            if (memspace < 0)
            {
                printf("\nMemory space was not correctly created\n");
            }
            if (H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL) < 0)
            {
                printf("\nHyperslab was not correctly created\n");
            }
            if (H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf) < 0)
            {
                printf("\nDataset was not correctly read\n");
            }

            /*Buffer is read*/
            for (int i = 0; i < count[0]; i++)
            {
                if (counter % 100000000 == 0 && counter > 0)
                {
                    cout << counter / 100000000 << " hundreds of millions data have been processed" << endl;
                }
                counter++;
                branchbuf = buf[i];
                roottree.Fill();
            }
        }

        /*In this case we have some columns left, so we read them */
        count[0] = count_rest[0];
        hid_t memspace = H5Screate_simple(rank, count, NULL);
        if (memspace < 0)
        {
            printf("\nMemory space was not correctly created\n");
        }
        if (H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL) < 0)
        {
            printf("\nHyperslab was not correctly created\n");
        }
        if (H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf) < 0)
        {
            printf("\nDataset was not correctly read\n");
        }

        /*Buffer is read*/
        for (int i = 0; i < count[0]; i++)
        {
            if (counter % 100000000 == 0 && counter > 0)
            {
                cout << counter / 100000000 << " hundreds of millions data have been processed" << endl;
            }
            counter++;
            branchbuf = buf[i * count[0]];
            roottree.Fill();
        }
    }
    else
    {
        for (int a = 0; a < round(dims_out[0] / bufferdimension); a++)
        {
            /*Reading the i-th line starts from i-bufferdimension line*/
            offset[0] = a * bufferdimension;
            for (int b = 0; b < round(dims_out[1] / bufferdimension); b++)
            {
                /*Resetting slab*/
                count[0] = bufferdimension;
                count[1] = bufferdimension;

                /*Computing column offset*/
                offset[1] = b * bufferdimension;

                /*In this case submatrices are bufferdimension*bufferdimension,
                so we can use our entire buffer */
                hid_t memspace = H5Screate_simple(rank, count, NULL);
                if (memspace < 0)
                {
                    printf("\nMemory space was not correctly created\n");
                }
                if (H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL) < 0)
                {
                    printf("\nHyperslab was not correctly created\n");
                }
                if (H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf) < 0)
                {
                    printf("\nDataset was not correctly read\n");
                }

                /*Buffer is read*/
                for (int i = 0; i < count[1]; i++)
                {
                    {
                        for (int j = 0; j < count[0]; j++)
                        {
                            if (counter % 100000000 == 0 && counter > 0)
                            {
                                cout << counter / 100000000 << " hundreds of millions data have been processed" << endl;
                            }
                            counter++;
                            branchbuf = buf[i * count[0] + j];
                            roottree.Fill();
                        }
                    }
                }
            }

            /*In this case we have to read other columns,so we use a slab bufferdimension*rest */
            count[1] = count_rest[1];
            hid_t memspace = H5Screate_simple(rank, count, NULL);
            if (memspace < 0)
            {
                printf("\nMemory space was not correctly created\n");
            }
            if (H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL) < 0)
            {
                printf("\nHyperslab was not correctly created\n");
            }
            if (H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf) < 0)
            {
                printf("\nDataset was not correctly read\n");
            }

            /*Buffer is read*/
            for (int i = 0; i < count[1]; i++)
            {
                for (int j = 0; j < count[0]; j++)
                {
                    if (counter % 100000000 == 0 && counter > 0)
                    {
                        cout << counter / 100000000 << " hundreds of millions data have been processed" << endl;
                    }
                    counter++;
                    branchbuf = buf[i * count[0] + j];
                    roottree.Fill();
                }
            }
        }

        /*Now we have to read other rows, so we use slab rest*bufferdimension */
        count[0] = count_rest[0];
        count[1] = bufferdimension;
        for (int b = 0; b < round(dims_out[1] / bufferdimension); b++)
        {
            offset[1] = b * bufferdimension;
            hid_t memspace = H5Screate_simple(rank, count, NULL);
            if (memspace < 0)
            {
                printf("\nMemory space was not correctly created\n");
            }
            if (H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count, NULL) < 0)
            {
                printf("\nHyperslab was not correctly created\n");
            }
            if (H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf) < 0)
            {
                printf("\nDataset was not correctly read\n");
            }

            /*Buffer is read*/
            for (int i = 0; i < count[1]; i++)
            {
                for (int j = 0; j < count[0]; j++)
                {
                    if (counter % 100000000 == 0 && counter > 0)
                    {
                        cout << counter / 100000000 << " hundreds of millions data have been processed" << endl;
                    }
                    counter++;
                    branchbuf = buf[i * count[0] + j];
                    roottree.Fill();
                }
            }
        }

        /*A rest*rest matrix is left to be read*/
        hid_t memspace = H5Screate_simple(rank, count_rest, NULL);
        if (memspace < 0)
        {
            printf("\nMemory space was not correctly created\n");
        }
        if (H5Sselect_hyperslab(dataspace_id, H5S_SELECT_SET, offset, NULL, count_rest, NULL) < 0)
        {
            printf("\nHyperslab was not correctly created\n");
        }
        if (H5Dread(dataset_id, datatype_id, memspace, dataspace_id, H5P_DEFAULT, buf) < 0)
        {
            printf("\nDataset was not correctly read\n");
        }

        /*Buffer is read*/
        for (int i = 0; i < count_rest[1]; i++)
        {
            for (int j = 0; j < count_rest[0]; j++)
            {
                if (counter % 100000000 == 0 && counter > 0)
                {
                    cout << counter / 100000000 << " hundreds of millions data have been processed" << endl;
                }
                counter++;
                branchbuf = buf[i * count_rest[0] + j];
                roottree.Fill();
            }
        }
    }

    /*Freeing memory*/
    delete[] dims_out;
    delete[] offset;
    delete[] count;
    delete[] count_rest;
    delete[] buf;
    roottree.Write("");
    rootfile.Close();
}
#endif