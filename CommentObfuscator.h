#ifndef COMMMENT_OBFUSCATOR
#define COMMENT_OBFUSCATOR
#include "Obfuscator.h"

class CommentObfuscator : public Obfuscator
{
  public:
    void obfuscate(string fileName) ;   
    string generateComment();
};





#endif