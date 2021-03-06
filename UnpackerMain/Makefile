CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/UnpackerMain
INCLUDES  += -I$(OSCARSRC)/FAIRBufferReader
INCLUDES  += -I$(OSCARSRC)/FAIRelectronics
INCLUDES  += -I$(OSCARSRC)/FAIRRootWriter
INCLUDES  += -I$(OSCARSRC)/OSRunInfo
INCLUDES  += -I$(OSCARSRC)/shared
INCLUDES  += -I$(OSCARSRC)/logo
INCLUDES  += -I$(OSCARSRC)/define

RLIBS     := -L$(OSCARLIB) -lFAIRBufferReader -lFAIRelectronics -lFAIRRootWriter -lOSCARShared -lOSCARLogo -lOSRunInfo

SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

CXXFLAGS  += $(INCLUDES) -fPIC -O3 -Wall -Wpedantic -std=c++11 

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

.PHONEY : all build
.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all : build

build : FAIRUnpacker.exe

FAIRUnpacker.exe : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(CFLAGS) $(RLIBS)

install:
	@cp FAIRUnpacker.exe $(OSCARBIN)/

.PHONY: clean
clean :
	rm -f $(OBJS) FAIRUnpacker.exe

.PHONY: distclean
distclean: clean
	@rm -f $(OSCARBIN)/FAIRUnpacker.exe

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)