CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/MapperMain
INCLUDES  += -I$(OSCARSRC)/FAIRBufferReader
INCLUDES  += -I$(OSCARSRC)/OSCARRawDataReader
INCLUDES  += -I$(OSCARSRC)/OSCARAnalyzer
INCLUDES  += -I$(OSCARSRC)/FAIRelectronics
INCLUDES  += -I$(OSCARSRC)/detectors/OSDetector
INCLUDES  += -I$(OSCARSRC)/detectors/OSOSCAR
INCLUDES  += -I$(OSCARSRC)/detectors/OSSingleDetector
INCLUDES  += -I$(OSCARSRC)/detectors/OSSingleTelescope
INCLUDES  += -I$(OSCARSRC)/OSCARDetectorMap
INCLUDES  += -I$(OSCARSRC)/shared
INCLUDES  += -I$(OSCARSRC)/logo

RLIBS     := -L$(OSCARLIB) -lOSCARShared -lOSCARLogo -lOSCARRawDataReader -lOSCARAnalyzer -lFAIRelectronics -lOSDetector -lOSCARDetectorMap -lOSOSCAR

SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

.PHONEY : all build
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all : build

build : OSCARMapper.exe

OSCARMapper.exe : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(CFLAGS) $(RLIBS)

install:
	@cp OSCARMapper.exe $(OSCARBIN)/

.PHONY: clean
clean :
	rm -f $(OBJS) OSCARMapper.exe

.PHONY: distclean
distclean: clean
	@rm -f $(OSCARBIN)/OSCARMapper.exe

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)