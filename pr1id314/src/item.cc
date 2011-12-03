/** @file item.cc
    @author Daniel Uber
    @brief Item::supplier modifiers using lookup table.
*/

#include "item.h"
#include "project1.h"
#include "dollar.h"
#include <string>
#include <iostream>
#include <cstring>
/** generate an empty new Item */
Item::Item()
{
    currentMonth = INVALID;
    name = "*";
    code = "*";
    onHand = -1;
    target= -1;
    cost.whole=-1;
    cost.cents=0;
    price.whole=-1;
    price.cents=0;
    itemSupplier.code=-1;
    itemSupplier.name="*";
    shelfLife=-1;
    avgVolume=-1.0;
    currentSales=-1.0;
}

/** supplier modifier
    @param c is supplier code
    supplier name is provided from lookup table
*/
void Item::supplier(int c) {
  itemSupplier.code = c;
  itemSupplier.name = SupplierNameFromCode(c);
  return;
}

/** supplier modifier
    @param n is supplier name
    supplier code is provided by lookup table
*/
void Item::supplier(std::string n){
  itemSupplier.name = n;
  itemSupplier.code = SupplierCodeFromName(n);
}

/** generate a string representation of item and insert it into
    an ostream.
*/
std::ostream& operator<<(std::ostream& os, Item& item){
  os<<"_ITEM_ "
    <<" _MONTH_ "         << printMonth(item.current_month())
    <<" _NAME_ "          << item.Name()
    <<" _CODE_ "          << item.Code()
    <<" _ONHAND_ "        << item.inStock()
    <<" _TARGET_ "        << item.desired()
    <<" _COST_ "          << item.Cost().print()
    <<" _PRICE_ "         << item.Price().print()
    <<" _ITEM_SUPPLIER_ " << item.supplierCode() <<' '
                          << item.supplierName()
    <<" _SHELF_LIFE_ "    << item.ShelfLife()
    <<" _AVGVOLUME_ "     << item.volume()
    <<" _CURRENT_SALES_ " << item.sales().print()
    << std::endl;
  return os;
}

/** extract Item from istream (with newline.)

    really this only will work when the input was provided from
    ostream operator<<, i.e., it's really unlikely that this would work
    for hand edited files.
*/
std::istream& operator>>(std::istream& is, Item& item){
  std::string s,a;
  int d;
  Dollar dol;
  is>>s;
  if(!strcmp(s.c_str(), "_ITEM_")){
    is>>s;
    is>>s;
    item.current_month(readMonth(s));
    is>>s;
    is>>s;
    while(strcmp(s.c_str(),"_CODE_")){
      a+=' '+s;
      is>>s;
    }
    item.Name(a);
    is>>s;
    item.Code(s);
    is>>s;
    is>>d;
    item.inStock(d);
    is>>s;
    is>>d;
    item.desired(d);
    is>>s;
    is>>dol;
    item.Cost(dol);
    is>>s;
    is>>dol;
    item.Price(dol);
    is>>s;
    is>>d;
    is>>s;
    Supplier x;
    x.code=d;
    x.name=s;
    is>>s;
    while(strcmp(s.c_str(),"_SHELF_LIFE_")){
      x.name+=' '+s;
      is>>s;
    }
    item.supplier(x);
    is>>d;
    item.ShelfLife(d);
    is>>s;
    is>>d;
    item.volume(d);
    is>>s;
    is>>dol;
    item.sales(dol);
    is.ignore(1,'\n');
  } else {
    // not an item record, return buffered input to stream
    for(size_t i=0; i<s.length();i++)
      is.putback(s[s.length() - 1 -i]);
    // signal a problem with fail
    std::ios_base::iostate state = std::ios_base::failbit;
    is.setstate(state);
  }
  return is;
}
