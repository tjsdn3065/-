#ifndef _FILE_H_
#define _FILE_H_

#include "Graph.h"
#include <string>
#include <fstream>

int Return_Num_In_File(FILE* fp, char until_when);
VERTEX** Make_Map(const char* path, const char* mode, const int x_width, const int y_width);
void SavePathToCSV(const string& filename, VERTEX** map, int x_width, int y_width);

#endif
