/** @file saveInventory.cc
    @brief option 7 from main menu
    @author Daniel Uber
*/
#include "inventory.h"
#include <fstream>
#include "project1.h"
#include "isort.h"
// needed for exists and moveExisting
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

/** exists check if file exists by trying to open it */
bool exists(const char *fn){
  int fd;
  fd = open(fn, O_RDONLY);
  // open returns -1 on failure
  if (fd == -1)
    return false;
  else
    close(fd);
  return true;
}
/** test if file exists, and make a backup

    this does not check to see if the backup exists,
    but adds some random numbers to the end of the backup
    extension. it is possible that there will be a collision
    which is not checked for.
*/
void moveExisting(const char *fn){
  static char buf[512];
  static char buf2[100];
  size_t len;
  long r;
  if (exists(fn)){
    strncpy(buf, fn, 511);
    buf[511]=0;
    len = strlen(buf);
    std::string extension= "-backup-";
    r = random();
    sprintf(buf2, "%ld", r);
    extension += buf2;
    strncpy((buf + len), extension.c_str(), 511-len);
    rename(fn, buf);
    std::cout<<"Renamed existing file "<< fn << " to "<<buf<<'\n';
  }
  return;
}
/** @fn saveInventory() handle option 7 from displayMenu()

    ask user for filename to write to
    make sure it's opened and writeable
    write each item to file
    close file and return.
*/
void saveInventory(){
  std::ofstream outfile;
  std::string filename;
  std::vector<Item*>::iterator index;
  do {
    std::cout<<"Enter Filename : ";
    std::cin>>filename;
    moveExisting(filename.c_str());
   outfile.open(filename.c_str());
  } while (!outfile);

  // sort inventory before writing
  isort<std::vector<Item*>, Item*, codeGetter, std::string, ltstr>
      (inventory);

  if(!inventory.empty())
    for(index = inventory.begin();
	index != inventory.end();
	index++)
      outfile<<(**index);
  outfile.close();
  return;
}
