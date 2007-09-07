CXXFLAGS+=-Wall
DEBUG='true'

############ You can edit above this line #######################
CXXFLAGS+=`pkg-config --cflags gtkmm-2.4 gtkspell-2.0`
LDFLAGS+=`pkg-config --libs gtkspell-2.0 gtk+-2.0 gtkmm-2.4` -lgettextpo

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG
endif

translator: main.o Utils.o TranslateTxtView.o MainWindow.o MenuBar.o Configuration.o TextPanel.o \
			TranslatedTextPanel.o IndicatorWidget.o PoReader.o HelperPanel.o Toolbar.o
	$(CXX) $(LDFLAGS) $^ -o $@

tests: readerTest

readerTest: PoReader.o tests/readerTest.o
	$(CXX) $(LDFLAGS) $^ -o tests/$@

dep:
	$(CXX) -MM *.cc >makefile.dep
	$(CXX) -MT tests/readerTest.o -MM tests/readerTest.cc >>makefile.dep

include makefile.dep

.PHONY: clean

clean:
	-rm *.o
	-rm  translator
