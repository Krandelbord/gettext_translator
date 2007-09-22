CXXFLAGS+=-Wall
prefix=/usr/
DEBUG='true'

############ You can edit above this line #######################
CXXFLAGS+=`pkg-config --cflags gtkmm-2.4 gtkspell-2.0`
LDFLAGS+=`pkg-config --libs gtkspell-2.0 gtk+-2.0 gtkmm-2.4` -lgettextpo

# internal stuff - usally you don't have to edit below this line
CPPFLAGS+=-DGETTEXT_PATH=\"$(prefix)/share/locale\"

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG
endif

translator: main.o Utils.o SpellTxtView.o MainWindow.o MenuBar.o Configuration.o TextPanel.o \
			TranslatedTextPanel.o IndicatorWidget.o PoReader.o HelperPanel.o Toolbar.o DictionariesMenu.o \
			ErrorHandlers.o Statistics.o StatusBar.o HelpMenu.o HeaderEdit.o
	$(CXX) $(LDFLAGS) $^ -o $@

test_replace: test_replace.o Utils.o
	$(CXX) $(LDFLAGS) $^ -o $@

po:
	$(MAKE) -C po/

dep:
	$(CXX) -MM *.cc >makefile.dep

include makefile.dep

.PHONY: clean

clean:
	-rm *.o
	-rm  translator
	-rm test_replace
