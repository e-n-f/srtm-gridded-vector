#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <string>

std::string getline(FILE *f) {
	std::string out;
	int c;
	while ((c = getc(f)) != EOF) {
		out.push_back(c);
		if (c == '\n' || c == '\r') {
			break;
		}
	}
	return out;
}

bool startswith(std::string s, std::string prefix) {
	return s.substr(0, prefix.size()) == prefix;
}

const char *word2(std::string &s) {
	const char *cp = s.c_str();

	while (*cp != '\0' && !isspace(*cp)) {
		cp++;
	}
	while (*cp != '\0' && isspace(*cp)) {
		cp++;
	}

	return cp;
}

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s file.hdr file.dem\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int nrows = -1;
	int ncols = -1;
	double ulxmap = -999;
	double ulymap = -999;
	double xdim = 0;
	double ydim = 0;

	FILE *hdr = fopen(argv[1], "r");
	if (hdr == NULL) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	std::string s;
	while ((s = getline(hdr)) != "") {
		if (startswith(s, "NROWS")) {
			nrows = atoi(word2(s));
		}
		if (startswith(s, "NCOLS")) {
			ncols = atoi(word2(s));
		}
		if (startswith(s, "ULXMAP")) {
			ulxmap = atof(word2(s));
		}
		if (startswith(s, "ULYMAP")) {
			ulymap = atof(word2(s));
		}
		if (startswith(s, "XDIM")) {
			xdim = atof(word2(s));
		}
		if (startswith(s, "YDIM")) {
			ydim = atof(word2(s));
		}
	}
	fclose(hdr);

	printf("%d %d %f %f %f %f\n", nrows, ncols, ulxmap, ulymap, xdim, ydim);
}
