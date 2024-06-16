#ifndef _PATH_H_
#define _PATH_H_

#include "Graph.h"
#include "Priority_Queue.h"
#include "File.h"
#include <chrono>

using namespace std::chrono;

void Initialize_Single_Soure(string path_planning, Graph& G, int x_start, int y_start, int x_goal = 0, int y_goal = 0);
void Relax(string path_planning, Graph& G, Priority_Queue& Q, VERTEX& v_adj, VERTEX& v_cur, double w, int x_goal = 0, int y_goal = 0);
VERTEX* Path_Planning(string path_planning, Graph& G, int x_width, int y_width, int x_start, int y_start, int x_goal, int y_goal);
void Map_Final_Path(VERTEX** map, VERTEX& v, int x_width);
void Map_Update_Final_Path(VERTEX** map, int x_width);


#endif
