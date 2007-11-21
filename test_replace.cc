#include "Utils.h"

#define assertEquals(expected, second) if (expected!=second) { \
	notifyFail(__FUNCTION__, expected, second); \
} else notifyPassed(__FUNCTION__);

void notifyFail(const Glib::ustring &test_name, const Glib::ustring &expected, const Glib::ustring &rec) {
	g_print("\033[1;101m");
	g_print("Test %s FAILED!", test_name.c_str());
	g_print("\033[1;0m\n");
	g_print("Expected       :\t%s\n", expected.c_str());
	g_print("Reveived result:\t%s\n", rec.c_str());
}

void notifyPassed(const Glib::ustring &test_name) {
	g_print("\033[2;106m");
	g_print("Test %s passed OK.", test_name.c_str());
	g_print("\033[1;0m \n");
}

void test_oneToTwo() {
	Glib::ustring str("abcdef.abcdef");
	replaceAll(str, "c", "ec");
	assertEquals("abecdef.abecdef", str);
}

void test_ThreeToOne() {
	Glib::ustring str("Some example text. Funny example like kaxam or sth");
	replaceAll(str, "xam", "m");
	assertEquals("Some emple text. Funny emple like kam or sth", str);
}

void test_UnderScores() {
	Glib::ustring str("Welcome_home_sanitatium__sth");
	replaceAll(str, "_", " ");
	assertEquals("Welcome home sanitatium  sth", str);
}

void test_newlines() {
	Glib::ustring str("Some txt\nWith newlines\nThree lines");
	replaceAll(str, "\n", "\\n\n");
	assertEquals("Some txt\\n\nWith newlines\\n\nThree lines", str);
}

void test_long2short() {
	Glib::ustring str("Some txt\\n\nWith newlines\\n\nThree lines");
	replaceAll(str, "\\n\n", "\n");
	assertEquals("Some txt\nWith newlines\nThree lines", str);
}

int main(int argc, char **argv) {
	test_oneToTwo();
	test_ThreeToOne();
	test_UnderScores();
	test_newlines();
	test_long2short();
	return 0;
}
