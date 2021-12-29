#include <functional>
#include <iostream>
#include "short_path.h"

std::set<char> get_neighbours(weighted_graph & graph, const char & vertice){
    std::vector<std::pair<char, char>> chosen_edges, all_edges = graph.GetEdges();
    std::set<char> neighbours;
    std::copy_if(all_edges.begin(), all_edges.end(), std::back_inserter(chosen_edges), [vertice](const std::pair<char, char> & num){return ((num.first == vertice) or (num.second == vertice));});
    std::transform(chosen_edges.begin(), chosen_edges.end(), std::inserter(neighbours, neighbours.begin()), [vertice](const std::pair<char, char> & num){return (num.first == vertice) ? num.second : num.first;});
    return neighbours;
}

std::vector<std::pair<char, char>> shortest_path(weighted_graph graph, char first, char second){
    // std::cout << "1\n";
    std::map<char, int> vert_weights;
    // std::cout << "1\n";
    auto all_verts = graph.GetVertices();
    auto verts = std::set<char>(all_verts.begin(), all_verts.end());
    // std::cout << "1\n";
    auto edges = graph.GetEdges();
    // std::cout << "1\n";
    auto weights_int = graph.GetWeights();
    // std::cout << "1\n";
    std::map<std::pair<char, char>, int> weights;// = graph.GetWeights();
    // std::cout << "1\n";
    for(int i = 0; i < graph.GetWeights().size(); i++){
        weights.insert(std::make_pair(edges[i], weights_int[i]));
    }
    // std::cout << "1\n";
    std::set<char> not_visited(verts.begin(), verts.end());
    // std::cout << "1\n";
    std::transform(verts.begin(), verts.end(), std::inserter(vert_weights, vert_weights.begin()), [](char n){return std::make_pair<char, int>(std::forward<char>(n), INT_MAX);});
    // std::cout << "1\n";
    vert_weights[first] = 0;
    // std::cout << "1\n";
    std::map<char, int> remained_verts(vert_weights.begin(), vert_weights.end());
    // std::cout << "1\n";
    while(!not_visited.empty()){
        auto min_vert_weight = std::min_element(remained_verts.begin(), remained_verts.end(), [](const auto& l, const auto& r){return (l.second < r.second);});
        auto min_vert = min_vert_weight->first;
        not_visited.erase(min_vert);
        remained_verts.erase(min_vert);
        std::vector<std::pair<char, char>> chosen_edges;
        std::set<char> neighbours = get_neighbours(graph, min_vert);
        for(const auto & i : neighbours){
            vert_weights[i] = std::min(vert_weights[i], vert_weights[min_vert] + std::max(weights[std::make_pair(min_vert, i)], weights[std::make_pair(i, min_vert)]));
            if (remained_verts.contains(i))
                remained_verts[i] = vert_weights[i];
        }
    }
    // std::cout << "2\n";
    std::vector<std::pair<char, char>> path;
    // std::cout << "2\n";
    char cur_vert = second;
    // std::cout << "2\n";
    while(cur_vert != first){
        auto cur_neighb = get_neighbours(graph, cur_vert);
        for(const auto & next_vert : cur_neighb){
            if (vert_weights[cur_vert] - vert_weights[next_vert] == std::max(weights[std::make_pair(cur_vert, next_vert)], weights[std::make_pair(next_vert, cur_vert)])){
                path.insert(path.begin(), std::make_pair(next_vert, cur_vert));
                cur_vert = next_vert;
                break;
            }
        }
    }
    // std::cout << "3\n";
    return path;
}