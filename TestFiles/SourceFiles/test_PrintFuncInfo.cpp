/*!
 *  \file test_PrintFuncInfo.cpp
 *  \brief Unit test for \ref PrintFuncInfo function
 */

#include "headers/catch.hpp"
#include "headers/PrintFuncInfo.h"

TEST_CASE("Checking the output of the function: PrintFuncInfo", "[PrintFuncInfo][Output]")
{
    vector<TString> prt;
    prt.push_back("Esempio di test");
    PrintFuncInfo(prt);
    ostringstream output_buffer;
    PrintFuncInfo(output_buffer, prt);

    /* We require that the output stream is not equivalent to the input string */
    REQUIRE(output_buffer.str().compare("Esempio di test") != 0);

    /* */
    REQUIRE(output_buffer.str().compare("\n*******************************************************\n*                                                     *\n*                   Esempio di test                   *\n*                                                     *\n*******************************************************\n\n") == 0);
}