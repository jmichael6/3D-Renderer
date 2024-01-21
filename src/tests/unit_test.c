#include "unit_test.h"

void passed() {
	printf("   Passed\n");
}

void failed() {
	printf("   Failed\n");
}

void sub_test(char *s) {
	printf("Testing: %s\n", s);
}

void end_test() {
	printf("\n*** Completed ***\n\n");
}

void new_test(char *s) {
	printf("*** Test Name - %s ***\n\n", s);
}

void display(char *s) {
	printf("%s\n", s);
}

