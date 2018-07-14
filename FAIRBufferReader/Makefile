CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/FAIRBufferReader
INCLUDES  += -I$(OSCARSRC)/FAIRelectronics
INCLUDES  += -I$(OSCARSRC)/FAIRRootWriter
INCLUDES  += -I$(OSCARSRC)/OSRunInfo
INCLUDES  += -I$(OSCARSRC)/shared
INCLUDES  += -I$(OSCARSRC)/define

CXXFLAGS  += $(INCLUDES) -fPIC -O3 -Wall -Wpedantic -std=c++11 

CXXFLAGS  += $(INCLUDES) -fPIC -O3 -Wall -Wpedantic -std=c++11 

OSFAIRBUFFERREADER_LIB := libFAIRBufferReader.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(OSFAIRBUFFERREADER_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(OSFAIRBUFFERREADER_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(OSFAIRBUFFERREADER_LIB) $(OSCARLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(OSFAIRBUFFERREADER_LIB)
	@rm -f $(OSCARLIB)/$(OSFAIRBUFFERREADER_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)