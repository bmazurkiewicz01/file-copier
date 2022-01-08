#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool fileExists(const char*);
bool copyFile(const char*, const char*, char*, const char*);

int main(int argc, char** argv) {
	if (argc < 4) {
		printf_s("Brak odpowiednich parametrow.");
	}
	printf_s("Plik zrodlowy: %s\nPlik docelowy: %s\nTryb: %s\nRozmiar buffera: %s\n", argv[1], argv[2], argv[3], argv[4]);
	
	if (!fileExists(argv[1])) {
		printf_s("Plik zrodlowy nie istnieje.\n");
		return -1;
	} 
	if (fileExists(argv[2])) {
		printf_s("Plik docelowy juz istnieje.\n");
		return -1;
	}

	int bufferSize = atoi(argv[4]);
	char* buffer = (char*)malloc(bufferSize);

	if (copyFile(argv[1], argv[2], buffer, argv[3])) {
		printf_s("Plik zostal skopiowany.\n");
	}
	
	free(buffer);
}

bool fileExists(const char* fileName) {
	FILE* file;
	if (file = fopen(fileName, "r")) {
		fclose(file);
		return true;
	}

	return false;
}

bool copyFile(const char* sourceFileName, const char* destFileName, char* buffer, const char* mode) {
	FILE* sourceFile;
	FILE* destFile;

	if (strcmp(mode, "t") == 0) {
		sourceFile = fopen(sourceFileName, "r");
		destFile = fopen(destFileName, "w");
	} else if (strcmp(mode, "b") == 0) {
		sourceFile = fopen(sourceFileName, "rb");
		destFile = fopen(destFileName, "wb");
	}
	else {
		printf_s("Zly tryb:\n\tWybierz t dla trybu tekstowego lub b dla trybu binarnego.\n");
		return false;
	}

	if (sourceFile == NULL || destFile == NULL) {
		printf_s("Blad otwarcia pliku zrodlowego lub docelowego.\n");
		return false;
	}

	size_t n;

	while (!feof(sourceFile)) {
		n = fread(buffer, 1, sizeof buffer, sourceFile);
		fwrite(buffer, 1, n, destFile);
	}

	fclose(sourceFile);
	fclose(destFile);

	return true;
}

