
/**
 * Domain class
 *
 * An abstract class for all objects assigning a name as cstring to them
 */

#ifndef DOMAIN_C_H_
#define DOMAIN_C_H_

#include <cstring>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "strlcpy.h"

class DomainClass{

protected:
  char name[50];

public:
  DomainClass(){ setObjName("No name assigned"); }
  DomainClass(const char* objName){
      setObjName(objName);
  }
  ~DomainClass(){
      ;
  }

  char* getName(){
      return name;
  }

  void getName(char* c_out, int len)
  {
      if (c_out != NULL) strlcpy(c_out, name, len);
  }

  void setObjName(const char* objName)
  {
      strlcpy(name, objName, sizeof(name));
  }

};

#endif /* DOMAIN_C_H_ */
