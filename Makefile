CXXFLAGS = -g

all:
	$(MAKE) root
	$(MAKE) -C UnpackerMain  ;		$(MAKE) -C UnpackerMain install
#	$(MAKE) -C MapperMain ;			$(MAKE) -C MapperMain install

root:
	$(MAKE) -C FAIRBufferReader ; 		$(MAKE) -C FAIRBufferReader install
	$(MAKE) -C FAIRelectronics ; 		$(MAKE) -C FAIRelectronics install
	$(MAKE) -C FAIRRootWriter ; 		$(MAKE) -C FAIRRootWriter install
	$(MAKE) -C shared ; 			$(MAKE) -C shared install
	$(MAKE) -C logo ; 			$(MAKE) -C logo install

install:
	$(MAKE) -C FAIRBufferReader install
	$(MAKE) -C FAIRelectronics install
	$(MAKE) -C FAIRRootWriter install
	$(MAKE) -C shared install
	$(MAKE) -C logo install

distclean:
	$(MAKE) -C FAIRBufferReader distclean
	$(MAKE) -C FAIRelectronics distclean
	$(MAKE) -C FAIRRootWriter distclean
	$(MAKE) -C shared distclean
	$(MAKE) -C logo distclean

	$(MAKE) -C UnpackerMain  distclean
	$(MAKE) -C MapperMain  distclean

clean:
	$(MAKE) -C FAIRBufferReader  clean
	$(MAKE) -C FAIRelectronics  clean
	$(MAKE) -C FAIRRootWriter  clean
	$(MAKE) -C shared  clean
	$(MAKE) -C logo  clean

	$(MAKE) -C UnpackerMain  clean
	$(MAKE) -C MapperMain  clean

debug:	CXXFLAGS += -DDEBUG -g

debug:
	$(MAKE) -C FAIRBufferReader
	$(MAKE) -C FAIRelectronics
	$(MAKE) -C FAIRRootWriter
	$(MAKE) -C shared
	$(MAKE) -C logo

	$(MAKE) -C UnpackerMain
	$(MAKE) -C MapperMain  clean