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

	size_t nrows = 0;
	size_t ncols = 0;
	double ulxmap = -999;
	double ulymap = -999;
	double xdim = 0;
	double ydim = 0;
	int nodata = 0;

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
		if (startswith(s, "NODATA")) {
			nodata = atoi(word2(s));
		}
	}
	fclose(hdr);

	std::vector<std::vector<short>> vals;

	FILE *data = fopen(argv[2], "rb");
	if (data == NULL) {
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}

	for (size_t y = 0; y < nrows; y++) {
		vals.push_back(std::vector<short>());

		for (size_t x = 0; x < ncols; x++) {
			int c = getc(data);
			int c1 = getc(data);

			if (c == EOF || c1 == EOF) {
				fprintf(stderr, "short read\n");
				exit(EXIT_FAILURE);
			}

			int val = c * 256 + c1;

			vals[y].push_back(val);
		}
	}

	fclose(data);

	for (size_t zoom = 0; zoom <= 9; zoom++) {
		size_t increment = 3 * (1 << (9 - zoom));

		for (size_t y = 0; y + increment - 1 < nrows; y += increment) {
			for (size_t x = 0; x + increment - 1 < ncols; x += increment) {
				double sum = 0;
				size_t count = 0;

				for (size_t xx = x; xx < x + increment && xx < ncols; xx++) {
					for (size_t yy = y; yy < y + increment && yy < nrows; yy++) {
						if (vals[y][x] != nodata) {
							sum += vals[y][x];
							count++;
						}
					}
				}

				if (count > 0) {
					printf("{\"type\": \"Feature\", \"properties\":{\"elevation\":%f}, \"tippecanoe\":{\"minzoom\":%zu, \"maxzoom\": %zu}, \"geometry\": {\"type\": \"Point\", \"coordinates\" : [ %f, %f ] } }\n",
					       sum / count, zoom, zoom, ulxmap + (x + increment * .5) * xdim, ulymap - (y + increment * .5) * ydim);
				}
			}
		}
	}
}
