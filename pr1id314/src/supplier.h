/** @file supplier.h
    @author Daniel Uber
    @brief The Supplier struct definition.
*/

#ifndef _SUPPLIER_H_
#define _SUPPLIER_H_
#include <string>

/** Supplier is a name and code number for each wholesaler we deal with
 */
struct Supplier{
  /** name of the supplier */
  std::string name;
  /** supplier code */
  int code;
};

#endif
