#include "../headers/catch.hpp"
#include "H5Cpp.h"
#include "../OpenH5.cpp"
#include "../Groupcheck.cpp"
#include "../Opfunc.cpp"

H5O_info_t infobuf;

TEST_CASE( "Apertura ed estrazione informazioni dal file .h5", "[OpenH5]" )
{
  /* Il file di test "test_OpenH5_0" non esiste: la funzione restituisce -1  */
  REQUIRE( openh5("test_OpenH5_0.h5", infobuf) == -1);
  /* Il file di test "test_OpenH5_1" esiste: la funzione restituisce 0       */ 
  REQUIRE( openh5("test_OpenH5_1.h5", infobuf) == 0);
}
