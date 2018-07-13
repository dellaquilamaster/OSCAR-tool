#include <UnpackerPassArgument.h>

const char * RetrieveRunName(int argc, char ** argv)
{
  if(argc<2) return 0; //No argument specified
  std::string Argument (argv[1]);
  if(Argument.find("--run=")!=std::string::npos) {
    Argument.assign(Argument.substr(Argument.find("--run=")+6));
    char * RunName = new char[200];
    strcpy(RunName,Argument.c_str());
    return RunName;    
  }
  return 0;
}