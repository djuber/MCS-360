/** @file main.cc
    @author Daniel Uber
    @brief Provide function main() required by the linker.
    @version 0.1
*/

#include "project1.h"

/** transfer control to the menu driven program in project1.cc
 @pre The program isn't running yet.
 @post The program isn't running anymore.
*/
int main(){
  runProgram();
 return 0;
}


/**
    @mainpage Grocery Store Inventory and Sales Program.

    @section intro_sec Introduction
    This Grocery Store Management Program was written as
    programming assignment 1 for MCS 360 Fall 2011.

    The overall layout is menu driven. A menu or prompt is
    displayed at each step. Sales records can be updated by
    noting sales. Daily Sales reports are available.
    Inventory can be written and read from external files,
    providing a persistent store of records.

    @section install_sec Installation
    Typical installation is accomplished by using the make
    utility. `make run` will start the system. `make manual`
    will generate this documentation. `make clean` will restore
    the system to clean source. An install target has not been
    provided. Simply move the compiled project1 file to the
    target directory.

    @section help_sec When Things Go Wrong
    Although some effort has been put into providing a reliable
    piece of software, occassionally the unforeseen and untested
    creeps in. Please contact duber3@uic.edu for assistance.
    Providing a log of the session where the bug occurred would
    be most helpful. Just copy the last few pages of screen output
    or attaching a inventory file should suffice.

    @section layout_sec Layout
    Much of the heavy lifting is implemented in the project1
    subroutines called by processResponse(), where all menu and
    input processing occurs. Class Item and structs Dollar and
    Supplier are used to collect information about the inventory
    items, and otherwise the control flow is subroutine driven.


    A templated isort is provided. It is not clear that this is the
    right level of generality. It presently needs three types and
    two adapters, making it a <i>pleasure</i> to use. It could easily be
    modified to handle two types and two adapters. If the caller
    was responsible for ensuring all contenttypes had a less than
    operator which was well defined, this could be restricted to a
    single adapter and one contenttype.

    Source and header files are in the src/ subdirectory, and generated
    html manual pages are located in the html director (created during
    the build). A pdf manual is created, manual.pdf.

    @section license_sec License
    Although it is unlikely that anyone will find the code or program
    useful, I release it into the public domain, with no royalties
    or requirements attached. In areas where there is no public domain
    this software is the property of the author, and all use is permitted
    by the owner. In short, you may do whatever you please, except hold
    me liable for damages.
 */
