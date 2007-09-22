translations := $(wildcard *.po)
mo_files:= $(patsubst %.po,%.mo,$(translations))
GETTEXT_DIR=../$(DESTDIR)$(prefix)share/locale/
POT_FILE=gettext_translator.pot

all: $(POT_FILE) $(mo_files)

$(POT_FILE):
	xgettext -cTranslators: --keyword=_ ../*.cc ../*.h -o $@

#updates all translation based on current pot file
$(translations): $(POT_FILE)
	msgmerge $@ $< -o $@

#generates all *.mo files
$(mo_files): $(translations)
	msgfmt $< -o $@

update-po: $(translations)

TRANS_DIRS := $(patsubst %.po, $(GETTEXT_DIR)%/LC_MESSAGES/,$(translations))

create_dirs: *.po
	@echo "Creating directiories"
	@echo "Translations = $(TRANS_DIRS)"
	$(foreach, plik, $^, touch $plik)
	install -d $(TRANS_DIRS)

install-translations: *.po
	#for plik in $^ ; do echo $$plik ; done

install: create_dirs
	msgfmt pl.po -o $(GETTEXT_DIR)pl/LC_MESSAGES/Gettext\ Translator.mo

.PHONY : clean
clean :
	-rm $(POT_FILE)
	-rm $(mo_files)
