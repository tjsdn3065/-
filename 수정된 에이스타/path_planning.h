#ifndef _PATH_H_
#define _PATH_H_

#include "Graph.h"
#include "Priority_Queue.h"
#include "File.h"
#include <chrono>

using namespace std::chrono;

double disntance_to_center(int x, int y);
double distance_to_goal(int x, int y, int x_goal, int y_goal);
double Direction_to_goal(int x_dir, int y_dir);

void Initialize_Single_Soure(string path_planning, Graph& G, int x_start, int y_start, int x_goal, int y_goal);
void Relax(string path_planning, Graph& G, Priority_Queue& Q, VERTEX& v_adj, VERTEX& v_cur, double w, int x_goal, int y_goal);
VERTEX* Path_Planning(string path_planning, Graph& G, int x_width, int y_width, int x_start, int y_start, int x_goal, int y_goal);
void Map_Final_Path(VERTEX** map, VERTEX& v, int x_width);
void Map_Update_Final_Path(VERTEX** map, int x_width, int y_width);


#endif
