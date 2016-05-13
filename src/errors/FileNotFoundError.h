#ifndef _FILE_NOT_FOUND_
#define _FILE_NOT_FOUND_

class FileNotFoundError
{
  public:
    static void Raise(string filename);
};

#endif
