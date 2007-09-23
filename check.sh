#!/bin/sh

kol_czerw="\e[1;31m"
kol_zielo="\e[1;33m"
kol_reset="\e[0m"

function OKEJ {
echo -e "${kol_zielo}OK ${kol_reset}"
}

function SPRAWDZ_LIB {
if [ -z "$1" ]; then
	echo "check.sh Internal Error: You have to add library name as argumetn"
	exit 1;
fi

echo -ne "Checking $1 ... \t"
pkg-config --exists $1
if [ $? -ne 0 ]; then
	echo -e "${kol_czerw}$1 is not installed correctly${kol_reset}"
	exit 1
else
	OKEJ
fi

#Gdy drugi argument nie jest Zerem (pustym ci±giem)
if [ ! -z "$2" ]; then
	echo -ne "Checking if $1 is in version >= $2 ... \t"
	pkg-config $1 --atleast-version=$2
	if [ $? -ne 0 ]; then
		echo -e "${kol_czerw}$1 is not in version >= $2 ${kol_reset}"
		CURRENT_VERSION=`pkg-config --modversion $1`
		echo "Currently installed version of $1, is $CURRENT_VERSION"
		exit 1
	else
		OKEJ
	fi
fi
}

function CHECK_LIB_RAW {
echo -ne "Checking $1 ... \t"
if [ -z "$1" ]; then
	echo "check.sh interanl error You have to specify libaray name"
	exit 1;
fi

TMPFILE=`mktemp -q /tmp/$0.XXXXXX`
if [ $? -ne 0 ]; then
	echo "$0: Can't create temp file, exiting..."
	echo TMPFILE = $TMPFILE
	exit 1
fi

NEWTMP=${TMPFILE}.c
mv "${TMPFILE}" "${NEWTMP}"
echo "int main(int argc, char **argv) {return 0;}" >> ${NEWTMP}

cc -l$1 $NEWTMP -o /dev/null
if [ $? -ne 0 ]; then
	echo -e "${kol_czerw}$1 is not installed correctly${kol_reset}"
	rm ${NEWTMP} 2>/dev/null
	exit 1
else
	rm ${NEWTMP} 2>/dev/null
	OKEJ
fi

}

echo -ne "Checking C++ complier... \t"
g++ --version > /dev/null 2>/dev/null
if [ $? -ne 0 ]; then
	echo "You dont have C++ compiler"
	exit 1
else OKEJ
fi

echo -ne "Checking pkg-config... \t"
# sprawdzmy czy jest pkg-config, to co wypluwa jest niepotrzebne wiêc dajemy
# na /dev/null
pkg-config --version > /dev/null 2>/dev/null
#sprawdzwmy exit-code z poprzedniego polecenia
if [ $? -ne 0 ]; then
	echo -e "${kol_czerw}You have to install pkg-config ${kol_reset}"
	exit 1
else OKEJ
fi

#==============================================================================
# Tutaj mo¿na zapodaæ potrzebne biblioteki
# podanie jednego argumentu sprawdza tylko czy dana biblioteka istnieje,
# podanie drugiego sprawdza czy ta biblioteka jest >= wersji
#==============================================================================
SPRAWDZ_LIB gtkmm-2.4
SPRAWDZ_LIB gtkspell-2.0
CHECK_LIB_RAW gettextpo

echo -e "\nIt seems that you have all stuff needed to compile"
echo "Type make, to compile program"
