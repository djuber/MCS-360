/** @file item.h
    @author Daniel Uber
    @brief the Item class. Most functions are inline, some in item.cc.
*/

#ifndef _ITEM_H_
#define _ITEM_H_
#include <string>
#include "dollar.h"
#include "month.h"
#include "supplier-map.h"
#include "project1.h"

/** Item is the representation of a single type of goods sold
    in the grocery store. This is used for inventory control
*/
class Item{
 private:
  // doxygen hides private members by default

  /** the month at present, not sure why this is an item property */
  Month currentMonth;

  /** name of the item */
  std::string name;

  /** unique identification code */
  std::string code;

  /** actual quantity in stock */
  int onHand;

  /** desired quantity in stock */
  int target;

  /** cost to purchase item from wholesale */
  Dollar cost;

  /** price charged to customer for each unit */
  Dollar price;

  /** source of item */
  Supplier itemSupplier;

  /** number of days until item perishes.
      A value of -1 indicates shelf stable.
  */
  int shelfLife;

  /** average monthly volume in units */
  double avgVolume;

  /** sales total in Dollars for the current month */
  Dollar currentSales;

 public:
  Item();
  /** month accessor
      @return current month */
  Month current_month() const {return currentMonth;}

  /** month modifier
      @param m is month to set */
  void current_month(Month m) {currentMonth=m;}

  /** name accessor
      @return item's name */
  std::string Name() const {return name;}

  /** name modifier
      @param n is new string name of item */
  void Name(std::string  n) {name = n;}

  /** unique identification code accessor
      @return code
  */
  std::string Code() const {return code;}

  /** code modifier
      @param c is a string with a unique identification code
  */
  void Code(std::string c) {code = c;}

  /** actual quantity in stock accessor
      @return quantity in stock, or -1 if unknown
  */
  int inStock() const {return onHand;}

  /** actual quantity in stock modifier
      @param qty is the new amount in inventory
  */
  void inStock(int qty) {onHand = qty;}

  /** desired quantity in stock accessor
      @return quantity in stock
  */
  int desired() const {return target;}

  /** desired quantity in stock modifier
      @param qty is the new target amount
  */
  void desired(int qty) {target = qty;}

  /** cost of item accessor
      @return cost, a Dollar price from supplier
  */
  Dollar Cost() const {return cost;}

  /** cost of item modifier
      @param c is the Dollar cost
  */
  void Cost(Dollar c) { cost = c;}


  /** price of item accessor
      @return price, the dollar price of this item
  */
  Dollar Price() const {return price;}

  /** price of item modifier
      @param p is the new price
  */
  void Price(Dollar p) { price = p;}

  /** price of item modifier
      @param p is the double representation of the price
  */
  void Price(double p) {price.fromDouble(p);}

  /** supplier accessor
      @return supplier of item
  */
  Supplier supplier() const {return itemSupplier;}

  /** supplier accessor
      @return the string name of supplier only
  */
  std::string supplierName() const {return itemSupplier.name;}

  /** supplier accessor
      @return the code number of supplier only
  */
  int supplierCode() const {return itemSupplier.code;}

  /** supplier modifier
      @param s is the supplier of this item
      @note this also adds supplier data to the lookup table.
  */
  void supplier(Supplier s){itemSupplier = s; addSupplier(itemSupplier);}

  // documented in item.h
  void supplier(int c);
  void supplier(std::string s);

  /** shelf life accessor
      @return number of days item may be in stock before perishing
  */
  int ShelfLife() const {return shelfLife;}
  /** shelf life modifier
      @param life is the number of days item may be in stock before perishing
  */
  void ShelfLife(int life) {shelfLife = life;}

  /** average volume accessor
      @return the average number of units sold per month
  */
  double volume() const {return avgVolume;}

  /** average volume accessor
      @param vol is new average monthly volume
  */
  void volume(double vol) { avgVolume = vol;}

  /** current monthly sales accessor

      @return Current Sales for the month
  */
  Dollar sales() const {return currentSales;}
  /** current monthly sales accessor
      @return Current Sales for the month as a double
  */

  /** current monthly sales modifier
      @param s is the sales total for this month
  */
  void sales(Dollar s){ currentSales = s;}

  /** current monthly sales modifier
      @param s is a double representation of current sales
  */
  void sales(double s) {currentSales.fromDouble(s);}
};
/////////////////////////////////////////////////////////////
// Insert and extract from streams
/** write Item to istream and include a newline */
std::istream& operator>>(std::istream& is, Item& item);
/** read Item record line from ostream */
std::ostream& operator<<(std::ostream& os, Item& item);

////////////////////////////////////////////////////////////
/**
   accessor classes are used in templated isort as a way
   to yield values for sorting.
   @see isort() in isort.h
*/


/** accessor class for sort */
struct codeGetter{
  /** @return code */
  std::string operator() (Item* v){
    return (*v).Code();
  }
};

/** accessor class for sort */
struct nameGetter{
  /** @return name, a string */
  std::string operator() (Item* v){
    return (*v).Name();
  }
};

/** accessor class for sort */
struct supplierNameGetter{
  /** return supplier name, a string */
  std::string operator() (Item* v){
    return (*v).supplierName();
  }
};

/** accessor class for sort */
struct stockGetter{
  /** @return quantity in stock */
  int operator() (Item *v){
    return (*v).inStock();
  }
};

/** accessor class for sort */
struct supplierCodeGetter{
  /** @return supplier code */
  int operator() (Item* v){
    return (*v).supplierCode();
  }
};

/** accessor class for sort */
struct targetGetter{
  /** @return target quantity for stock */
  int operator() (Item *v){
    return (*v).desired();
  }
};
/** accessor class for sort */
struct shelfLifeGetter{
  /** @return shelfLife */
  int operator() (Item* v){
    return (*v).ShelfLife();
  }
};

/** accessor class for sort */
struct costGetter{
  /** @return cost */
  Dollar operator() (Item *v){
    return  (*v).Cost();
  }
};

/** accessor class for sort */
struct priceGetter {
  /** @return price */
  Dollar operator() (Item *v){
    return (*v).Price();
  }
};

/** accessor class for sort */
struct salesGetter {
  /** @return sales */
  Dollar operator() (Item *v){
    return (*v).sales();
  }
};
/** accessor class for sort */
struct volumeGetter {
  /** @return average volume */
  double operator() (Item *v) {
    return (*v).volume();
  }
};
#endif
