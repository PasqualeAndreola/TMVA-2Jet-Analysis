/*!
 *  \file test_StatusPrinter.cpp
 *  \brief Unit test for \ref StatusPrinter(int progress) function
 */

#include "headers/catch.hpp"
#include "headers/StatusPrinter.h"

TEST_CASE("Checking the output of the function: StatusPrinter", "[StatusPrinter][Output]")
{
    StatusPrinter(0);
    string confronto;
    ostringstream output_buffer;
    StatusPrinter(output_buffer, 0);
    confronto.append("[                                                      ]0%\r");

    /* We require that the output stream is not equivalent to the known string, due to the color */
    REQUIRE(output_buffer.str().compare(confronto) != 0);

    /* We require that the output stream is not equivalent to the known string, due to the color */
    output_buffer.clear();
    confronto.clear();
    StatusPrinter(output_buffer, 100);
    cout << output_buffer.str();
    confronto.append("[=======================================================]100% ETA: 0[s] Elapsed time: 0[s]        \r\n\n\n");
    cout << confronto.data() << endl;
    REQUIRE(output_buffer.str().compare(confronto) != 0);
}