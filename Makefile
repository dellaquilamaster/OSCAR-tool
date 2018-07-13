CXXFLAGS = -g

all:
	$(MAKE) root
	$(MAKE) -C UnpackerMain  ;		$(MAKE) -C UnpackerMain install
	$(MAKE) -C MapperMain ;			$(MAKE) -C MapperMain install

root:
	$(MAKE) -C FAIRBufferReader ; 		$(MAKE) -C FAIRBufferReader install
	$(MAKE) -C FAIRelectronics ; 		$(MAKE) -C FAIRelectronics install
	$(MAKE) -C FAIRRootWriter ; 		$(MAKE) -C FAIRRootWriter install
	$(MAKE) -C OSCARRawDataReader ;		$(MAKE) -C OSCARRawDataReader install
	$(MAKE) -C OSCARAnalyzer ; 		$(MAKE) -C OSCARAnalyzer install
	$(MAKE) -C detectors/OSDetector ; 	$(MAKE) -C detectors/OSDetector install
	$(MAKE) -C detectors/OSOSCAR ; 	        $(MAKE) -C detectors/OSOSCAR install
	$(MAKE) -C detectors/OSSingleTelescope ;$(MAKE) -C detectors/OSSingleTelescope install
	$(MAKE) -C OSCARDetectorMap ; 		$(MAKE) -C OSCARDetectorMap install
	$(MAKE) -C shared ; 			$(MAKE) -C shared install
	$(MAKE) -C logo ; 			$(MAKE) -C logo install

install:
	$(MAKE) -C FAIRBufferReader install
	$(MAKE) -C FAIRelectronics install
	$(MAKE) -C FAIRRootWriter install
	$(MAKE) -C OSCARRawDataReader install
	$(MAKE) -C OSCARAnalyzer install
	$(MAKE) -C detectors/OSDetector install
	$(MAKE) -C detectors/OSOSCAR install
	$(MAKE) -C detectors/OSSingleTelescope install
	$(MAKE) -C OSCARDetectorMap install
	$(MAKE) -C shared install
	$(MAKE) -C logo install

distclean:
	$(MAKE) -C FAIRBufferReader distclean
	$(MAKE) -C FAIRelectronics distclean
	$(MAKE) -C FAIRRootWriter distclean
	$(MAKE) -C OSCARRawDataReader distclean
	$(MAKE) -C OSCARAnalyzer distclean
	$(MAKE) -C detectors/OSDetector distclean
	$(MAKE) -C detectors/OSOSCAR distclean
	$(MAKE) -C detectors/OSSingleTelescope distclean
	$(MAKE) -C OSCARDetectorMap distclean
	$(MAKE) -C shared distclean
	$(MAKE) -C logo distclean

	$(MAKE) -C UnpackerMain  distclean
	$(MAKE) -C MapperMain  distclean

clean:
	$(MAKE) -C FAIRBufferReader  clean
	$(MAKE) -C FAIRelectronics  clean
	$(MAKE) -C FAIRRootWriter  clean
	$(MAKE) -C OSCARRawDataReader  clean
	$(MAKE) -C OSCARAnalyzer  clean
	$(MAKE) -C detectors/OSDetector  clean
	$(MAKE) -C detectors/OSOSCAR  clean
	$(MAKE) -C detectors/OSSingleTelescope  clean
	$(MAKE) -C OSCARDetectorMap  clean
	$(MAKE) -C shared  clean
	$(MAKE) -C logo  clean

	$(MAKE) -C UnpackerMain  clean
	$(MAKE) -C MapperMain  clean

debug:	CXXFLAGS += -DDEBUG -g

debug:
	$(MAKE) -C FAIRBufferReader
	$(MAKE) -C FAIRelectronics
	$(MAKE) -C FAIRRootWriter
	$(MAKE) -C OSCARRawDataReader
	$(MAKE) -C OSCARAnalyzer
	$(MAKE) -C detectors/OSDetector
	$(MAKE) -C detectors/OSOSCAR
	$(MAKE) -C detectors/OSSingleTelescope
	$(MAKE) -C OSCARDetectorMap
	$(MAKE) -C shared
	$(MAKE) -C logo

	$(MAKE) -C UnpackerMain
	$(MAKE) -C MapperMain  clean