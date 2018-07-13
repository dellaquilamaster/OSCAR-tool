CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/detectors/OSDetector
INCLUDES  += -I$(OSCARSRC)/detectors/OSOSCAR
INCLUDES  += -I$(OSCARSRC)/OSCARDetectorMap
INCLUDES  += -I$(OSCARSRC)/shared

RLIBS     := -L$(OSCARLIB)

CXXFLAGS  += $(INCLUDES) -std=c++11 -fPIC -O3 -Wall

OSOSCAR_DICT  := OSOSCARDict.$(SrcSuf)
OSOSCAR_DICTH := $(OSOSCAR_DICT:.$(SrcSuf)=.h)
OSOSCAR_DICTO := $(OSOSCAR_DICT:.$(SrcSuf)=.$(ObjSuf))
OSOSCAR_PCM   := OSOSCARDict$(PcmSuf)
OSOSCAR_HDRS  := $(wildcard OS*.$(SrcSuf))


OSOSCAR_HDRS  := $(OSOSCAR_HDRS:.$(SrcSuf)=.h) OSOSCARLinkDef.h
OSOSCAR_HDRS  := $(filter-out $(OSOSCAR_DICTH),$(OSOSCAR_HDRS))

OSOSCAR_LIB := libOSOSCAR.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(OSOSCAR_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(OSOSCAR_DICT): $(OSOSCAR_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(OSOSCAR_LIB): $(OBJS) $(OSOSCAR_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(OSOSCAR_LIB) $(OSOSCAR_PCM) $(OSCARLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(OSOSCAR_LIB) $(OSOSCAR_DICT) $(OSOSCAR_DICTH) $(OSOSCAR_PCM)
	@rm -f $(OSCARLIB)/$(OSOSCAR_LIB)
	@rm -f $(OSCARLIB)/$(OSOSCAR_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(OSOSCAR_DICTO) $(OSOSCAR_DICT) $(OSOSCAR_DICTH) $(OSOSCAR_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)