#include "SGHash.h"

SGHash getHashFromString(const char* name) 
{
  unsigned int sum = 0;
  while (*name != '\0') {
    sum = (sum * 31) + * name;
    ++name;
  }

  return static_cast<SGHash>(sum);
}