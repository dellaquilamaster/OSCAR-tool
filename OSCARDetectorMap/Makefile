CFLAGS    :=`root-config --cflags --libs`

DllSuf    := so
SrcSuf    := cxx
ObjSuf    := o

INCLUDES  := -I$(OSCARSRC)/
INCLUDES  += -I$(OSCARSRC)/OSCARDetectorMap
INCLUDES  += -I$(OSCARSRC)/shared

RLIBS     := -L$(OSCARLIB)

CXXFLAGS  += $(INCLUDES) -fPIC -O3 -Wall -Wpedantic -std=c++11 

OSCARDETECTORMAP_LIB := libOSCARDetectorMap.$(DllSuf)
SRCS = $(wildcard *.$(SrcSuf))
OBJS = $(patsubst %.$(SrcSuf), %.$(ObjSuf), $(SRCS))

.$(SrcSuf).$(ObjSuf):
	@$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)
	@echo "$(CXX) $(CXXFLAGS) -c $< $(SYSLIB) $(CFLAGS)"

all: $(OSCARDETECTORMAP_LIB)

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

$(OSCARDETECTORMAP_LIB): $(OBJS)
	@$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)
	@echo "$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(CFLAGS) $(RLIBS)"

install:
	@cp $(OSCARDETECTORMAP_LIB) $(OSCARLIB)/.

.PHONY: distclean
distclean:
	@rm -f $(OSCARDETECTORMAP_LIB)
	@rm -f $(OSCARLIB)/$(OSCARDETECTORMAP_LIB)

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS)
	@$(RM) -f *.expand

.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)