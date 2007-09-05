CXXFLAGS+=-g3 -Wall
CXXFLAGS+=`pkg-config --cflags gtkmm-2.4 gtkspell-2.0`
LDFLAGS+=`pkg-config --libs gtkspell-2.0 gtk+-2.0 gtkmm-2.4`

translator: main.o Utils.o TranslateTxtView.o MainWindow.o MenuBar.o
	$(CXX) $(LDFLAGS) $^ -o $@


dep:
	$(CXX) -MM *.cc >makefile.dep

include makefile.dep

.PHONY: clean

clean:
	-rm *.o
	-rm  translator
