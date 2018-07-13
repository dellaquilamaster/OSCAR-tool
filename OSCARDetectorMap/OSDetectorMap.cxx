#include <OSDetectorMap.h>

//________________________________________________
OSDetectorMap::OSDetectorMap(const char * name) :
fName(name)
{}

//________________________________________________
OSDetectorMap::~OSDetectorMap()
{}

//________________________________________________
int OSDetectorMap::LoadMapping(const char * file_name)
{
  std::ifstream FileIn(file_name);

  if(!FileIn.is_open()) {
    return -1;
  }

  int NChannelsMapped=0;

  while (!FileIn.eof())
  {
    std::string LineRead;
    std::getline(FileIn, LineRead);
    std::string LineReadCommentLess(LineRead.substr(0,LineRead.find("*")));

    if(LineReadCommentLess.empty()) continue;

    if(LineReadCommentLess.find_first_not_of(' ') == std::string::npos) continue;

    if(LineReadCommentLess.find("map ")!=std::string::npos) {
      if(LineReadCommentLess.find(fName)!=std::string::npos) {
        NChannelsMapped+=ParseMapLine(LineReadCommentLess.c_str());
      }
    }
  }
  FileIn.close();

  return NChannelsMapped;
}

//________________________________________________
int OSDetectorMap::ParseMapLine(const char * line_to_parse)
{
  return 0;
}

//________________________________________________
void OSDetectorMap::Clear()
{}