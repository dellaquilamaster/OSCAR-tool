CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/OSCARRawDataReader
INCLUDES  += -I$(OSCARSRC)/OSCARAnalyzer
INCLUDES  += -I$(OSCARSRC)/FAIRelectronics
INCLUDES  += -I$(OSCARSRC)/detectors/OSDetector
INCLUDES  += -I$(OSCARSRC)/detectors/OSOSCAR
INCLUDES  += -I$(OSCARSRC)/OSCARDetectorMap
INCLUDES  += -I$(OSCARSRC)/shared
INCLUDES  += -I$(OSCARSRC)/define

RLIBS     := -L$(OSCARLIB)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall -Wpedantic

OSCARRAWDATAREADER_LIB := libOSCARRawDataReader.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(OSCARRAWDATAREADER_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(OSCARRAWDATAREADER_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(OSCARRAWDATAREADER_LIB) $(OSCARLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(OSCARRAWDATAREADER_LIB)
	@rm -f $(OSCARLIB)/$(OSCARRAWDATAREADER_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)