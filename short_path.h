#ifndef SHORTPATH_H
#define SHORTPATH_H

#include "graphs.h"
#include <set>
#include <map>
#include <vector>
#include <string>
#include <utility>
std::set<char> get_neighbours(weighted_graph & graph, const char & vertice);
std::vector<std::pair<char, char>> shortest_path(weighted_graph graph, char first, char second);

#endif