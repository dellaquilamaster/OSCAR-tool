CFLAGS    :=`root-config --cflags --libs`
SYSLIB    := -lMathMore

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o
PcmSuf    := _rdict.pcm

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/detectors/OSDetector
INCLUDES  += -I$(OSCARSRC)/detectors/OSSingleTelescope
INCLUDES  += -I$(OSCARSRC)/OSCARDetectorMap
INCLUDES  += -I$(OSCARSRC)/shared

RLIBS     := -L$(OSCARLIB)

CXXFLAGS  += $(INCLUDES) -fPIC -O3 -Wall -Wpedantic -std=c++11 

OSSINGLETELESCOPE_DICT  := OSSingleTelescopeDict.$(SrcSuf)
OSSINGLETELESCOPE_DICTH := $(OSSINGLETELESCOPE_DICT:.$(SrcSuf)=.h)
OSSINGLETELESCOPE_DICTO := $(OSSINGLETELESCOPE_DICT:.$(SrcSuf)=.$(ObjSuf))
OSSINGLETELESCOPE_PCM   := OSSingleTelescopeDict$(PcmSuf)
OSSINGLETELESCOPE_HDRS  := $(wildcard OS*.$(SrcSuf))


OSSINGLETELESCOPE_HDRS  := $(OSSINGLETELESCOPE_HDRS:.$(SrcSuf)=.h) OSSingleTelescopeLinkDef.h
OSSINGLETELESCOPE_HDRS  := $(filter-out $(OSSINGLETELESCOPE_DICTH),$(OSSINGLETELESCOPE_HDRS))

OSSINGLETELESCOPE_LIB := libOSSingleTelescope.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(OSSINGLETELESCOPE_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf) .$(PcmSuf)

$(OSSINGLETELESCOPE_DICT): $(OSSINGLETELESCOPE_HDRS)
	@echo "Generating dictionary $@..."
	$(ROOTCLINGORCINT) -f $@ -c $(INCLUDES) $^

$(OSSINGLETELESCOPE_LIB): $(OBJS) $(OSSINGLETELESCOPE_DICTO)
	@$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@
	@echo "$(CXX) -shared $(CXXFLAGS) $^ $(SYSLIB) $(CFLAGS) $(RLIBS) -o $@"

install:
	@cp $(OSSINGLETELESCOPE_LIB) $(OSSINGLETELESCOPE_PCM) $(OSCARLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(OSSINGLETELESCOPE_LIB) $(OSSINGLETELESCOPE_DICT) $(OSSINGLETELESCOPE_DICTH) $(OSSINGLETELESCOPE_PCM)
	@rm -f $(OSCARLIB)/$(OSSINGLETELESCOPE_LIB)
	@rm -f $(OSCARLIB)/$(OSSINGLETELESCOPE_PCM)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(OSSINGLETELESCOPE_DICTO) $(OSSINGLETELESCOPE_DICT) $(OSSINGLETELESCOPE_DICTH) $(OSSINGLETELESCOPE_PCM)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)