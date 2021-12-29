#include "graphs.h"


bipartite_args::bipartite_args(std::vector<char> p1, std::vector<char> p2){
    for(auto i: p1){
        part1.push_back(i);
    }
    for(auto i: p2){
        part2.push_back(i);
    }
}

simple_args::simple_args(std::vector<std::string> edg){
    for(auto i: edg){
        edges.push_back(i);
    }
}

complete_args::complete_args(std::vector<char> vrt){
    for(auto i: vrt){
        vertices.push_back(i);
    }
}

weighted_args::weighted_args(std::vector<std::string> edg, std::vector<int> wgt){
    for (auto i: edg){
        edges.push_back(i);
    }
    for (auto i: wgt){
        weights.push_back(i);
    }
}

weighted_graph::weighted_graph(std::unique_ptr<weighted_args> && args){
    auto edg = args->edges;
    auto wgt = args->weights;
    for(auto i: edg){
        edges.push_back(std::make_pair(i[0], i[1]));
        if(std::find(vertices.begin(), vertices.end(), i[0]) == vertices.end()){
            vertices.push_back(i[0]);
        }
        if(std::find(vertices.begin(), vertices.end(), i[1]) == vertices.end()){
            vertices.push_back(i[1]);
        }
    }
    std::sort(vertices.begin(), vertices.end());
    for(auto i: wgt){
        weights.push_back(i);
    }
}

weighted_graph::weighted_graph(std::vector<std::string> edg, std::vector<int> wgt){
        for(auto i: edg){
            edges.push_back(std::make_pair(i[0], i[1]));
            if(std::find(vertices.begin(), vertices.end(), i[0]) == vertices.end()){
                vertices.push_back(i[0]);
            }
            if(std::find(vertices.begin(), vertices.end(), i[1]) == vertices.end()){
                vertices.push_back(i[1]);
            }
        }
        std::sort(vertices.begin(), vertices.end());
        for(auto i: wgt){
            weights.push_back(i);
        }
    }

weighted_graph::weighted_graph(const weighted_graph &copy){
    std::vector<std::string> edg;
    auto c_edgs = copy.GetEdges();
    for(auto i: c_edgs){
        std::string s = "";
        s = s + std::string(& i.first) + std::string(& i.second);
        edg.push_back(s);
    }
    *this = weighted_graph(edg, copy.weights);
}

const std::vector<char> weighted_graph::GetVertices() const{
    return vertices;
}

const std::vector<std::pair<char, char>> weighted_graph::GetEdges() const{
    return edges;
}

const std::vector<int> weighted_graph::GetWeights() const{
    return weights;
}

const std::string weighted_graph::ToString() const{
    std::string s = "";
    s += "WeightedGraph {";
    for(int i = 0; i < edges.size(); ++i){
        s += std::string(1, edges[i].first) + std::string(1, edges[i].second) + ":" + std::to_string(weights[i]);
        if(i != edges.size() - 1){
            s += ", ";
        }
    }
    s += "}";
    return s;
}

std::unique_ptr<TGraph> weighted_graph::AsWeighted(int default_weight) const{
    std::vector<std::string> edg;
    for(auto i: this->edges){
        std::string s = "";
        s += std::string(1, i.first) + std::string(1, i.second);
        edg.push_back(s);
    }
    return std::make_unique<weighted_graph>(edg, weights);
}

weighted_graph operator+=(weighted_graph &first, weighted_graph &second){
    auto second_eds = second.GetEdges();
    auto second_w = second.GetWeights();
    auto len = second_eds.size();
    for(int i = 0; i < len; ++i){
        if(std::find(first.edges.begin(), first.edges.end(), second_eds[i]) == first.edges.end() && std::find(first.edges.begin(), first.edges.end(), std::make_pair(second_eds[i].second, second_eds[i].first)) == first.edges.end()){
            first.edges.push_back(second_eds[i]);
            first.weights.push_back(second_w[i]);
        }
    }
    return first;
}

weighted_graph operator+(weighted_graph &first, weighted_graph &second){
    weighted_graph tmp = weighted_graph(first);
    return tmp += second;
}

weighted_graph operator+(weighted_graph &first, TGraph &second){
    throw std::logic_error("diff graphs");
}

weighted_graph operator+=(weighted_graph &first, TGraph &second){
    throw std::logic_error("diff graphs");
}

weighted_graph operator-=(weighted_graph &first, weighted_graph &second){
    auto second_edg = second.GetEdges();
    for(auto i: second_edg){
        auto place = std::find(first.edges.begin(), first.edges.end(), i);
        if(place != first.edges.end()){
            first.edges.erase(place);
            int index = place - first.edges.begin();
            first.weights.erase(first.weights.begin() + index);
        }
        place = std::find(first.edges.begin(), first.edges.end(), std::make_pair(i.second, i.first));
        if(place != first.edges.end()){
            first.edges.erase(place);
            int index = place - first.edges.begin();
            first.weights.erase(first.weights.begin() + index);
        }
    }
    return first;
}

weighted_graph operator-(weighted_graph &first, TGraph &second){
    auto second_edg = second.GetEdges();
    auto first_edg = first.GetEdges();
    auto first_weights = first.GetWeights();
    for(auto i: second_edg){
        auto place = std::find(first_edg.begin(), first_edg.end(), i);
        if(place != first_edg.end()){
            first_edg.erase(place);
            int index = place - first_edg.begin();
            first_weights.erase(first_weights.begin() + index);
        }
        place = std::find(first_edg.begin(), first_edg.end(), std::make_pair(i.second, i.first));
        if(place != first_edg.end()){
            first_edg.erase(place);
            int index = place - first_edg.begin();
            first_weights.erase(first_weights.begin() + index);
        }
    }
    std::vector<std::string> new_edges;
    for(auto i: first_edg){
        std::string s = "";
        s += std::string(1, i.first) + std::string(1, i.second);
        new_edges.push_back(s);
    }
    return weighted_graph(new_edges, first_weights);
}

simple_graph::simple_graph(std::unique_ptr<simple_args> && args){
    auto edgs = args->edges;
    for(auto i: edgs){
        edges.push_back(std::make_pair(i[0], i[1]));
        if(std::find(vertices.begin(), vertices.end(), i[0]) == vertices.end()){
            vertices.push_back(i[0]);
        }
        if(std::find(vertices.begin(), vertices.end(), i[1]) == vertices.end()){
            vertices.push_back(i[1]);
        }
    }
    std::sort(vertices.begin(), vertices.end());
}

simple_graph::simple_graph(std::vector<std::string> edg){
    for(auto i: edg){
        edges.push_back(std::make_pair(i[0], i[1]));
        if(std::find(vertices.begin(), vertices.end(), i[0]) == vertices.end()){
            vertices.push_back(i[0]);
        }
        if(std::find(vertices.begin(), vertices.end(), i[1]) == vertices.end()){
            vertices.push_back(i[1]);
        }
    }
    std::sort(vertices.begin(), vertices.end());
}

simple_graph::simple_graph(const simple_graph &copy){
    std::vector<std::string> edg;
    for(auto i: copy.GetEdges()){
        std::string s = "";
        s += std::string(1, i.first) + std::string(1, i.second);
        edg.push_back(s);
    }
    *this = simple_graph(edg);
}

const std::vector<char> simple_graph::GetVertices() const{
    return vertices;
}

const std::vector<std::pair<char, char>> simple_graph::GetEdges() const{
    return edges;
}

const std::string simple_graph::ToString() const{
    std::string s = "";
    s += "SimpleGraph {";
    for(auto i: edges){
        s += std::string(1, i.first) + std::string(1, i.second);
        if(i != *(edges.end() - 1)){
            s += ", ";
        }
    }
    s += "}";
    return s;
}

std::unique_ptr<TGraph> simple_graph::AsWeighted(int default_weight) const{
    std::vector<std::string> edg;
    std::vector<int> weights;
    for(auto i: edges){
        std::string s = "";
        s += std::string(1, i.first) + std::string(1, i.second);
        edg.push_back(s);
        weights.push_back(default_weight);
    }
    return std::make_unique<weighted_graph>(std::make_unique<weighted_args>(edg, weights));
}

simple_graph operator+=(simple_graph &first, TGraph &second){
    std::vector<std::string> edges;
    auto second_edg = second.GetEdges();
    for(int i = 0; i < second_edg.size(); ++i){
        if(std::find(first.edges.begin(), first.edges.end(), second_edg[i]) == first.edges.end() && std::find(first.edges.begin(), first.edges.end(), std::make_pair(second_edg[i].second, second_edg[i].first)) == first.edges.end()){
            first.edges.push_back(second_edg[i]);
        }
    }
    return first;
}

simple_graph operator+(simple_graph &first, TGraph &second){
    simple_graph tmp(first);
    return tmp += second;
}

simple_graph operator+(simple_graph &first, weighted_graph &second){
    throw std::logic_error("diff graphs");
}

simple_graph operator-=(simple_graph &first, TGraph &second){
    for(auto i: second.GetEdges()){
        auto place = std::find(first.edges.begin(), first.edges.end(), i);
        if(place != first.edges.end()){
            first.edges.erase(place);
        }
        place = std::find(first.edges.begin(), first.edges.end(), std::make_pair(i.second, i.first));
        if(place != first.edges.end()){
            first.edges.erase(place);
        }
    }
    return first;
}

simple_graph operator-(simple_graph &first, TGraph &second){
    simple_graph tmp(first);
    return tmp -= second;
}

bipartite_graph::bipartite_graph(std::unique_ptr<bipartite_args> && args){
    for(auto i: args->part1){
        part1.push_back(i);
    }
    for(auto i: args->part2){
        part2.push_back(i);
    }
}

bipartite_graph::bipartite_graph(std::vector<char> p1, std::vector<char> p2){
    for(auto i: p1){
        part1.push_back(i);
    }
    for(auto i: p2){
        part2.push_back(i);
    }
}

bipartite_graph::bipartite_graph(const bipartite_graph &copy){
    *this = bipartite_graph(copy.part1, copy.part2);
}

const std::vector<char> bipartite_graph::GetVertices() const{
    std::vector<char> res;
    for(auto i: part1){
        res.push_back(i);
    }
    for(auto i: part2){
        res.push_back(i);
    }
    return res;
}

const std::vector<char> bipartite_graph::GetPart1() const{
    return part1;
}

const std::vector<char> bipartite_graph::GetPart2() const{
    return part2;
}

const std::vector<std::pair<char, char>> bipartite_graph::GetEdges() const{
    std::vector<std::pair<char, char>> edges;
    for(auto i: part1){
        for(auto j: part2){
            edges.push_back(std::make_pair(i, j));
        }
    }
    return edges;
}

const std::string bipartite_graph::ToString() const{
    std::string s = "";
    s += "BipartiteGraph {{";
    for(auto &i: part1){
        s += std::string(1, i);
        if(i != *(part1.end() - 1)){
            s += ", ";
        }
    }
    s += "}, {";
    for(auto &i: part2){
        s += std::string(1, i);
        if(i != *(part2.end() - 1)){
            s += ", ";
        }
    }
    s += "}}";
    return s;
}

std::unique_ptr<TGraph> bipartite_graph::AsWeighted(int default_weight) const{
    std::vector<std::string> edges;
    std::vector<int> weights;
    for(auto i: part1){
        for(auto j: part2){
            std::string s = "";
            s += std::string(1, i) + std::string(1, j);
            edges.push_back(s);
            weights.push_back(default_weight);
        }
    }
    return std::make_unique<weighted_graph>(std::make_unique<weighted_args>(edges, weights));
}

bipartite_graph operator+=(bipartite_graph &first, bipartite_graph &second){
    for(auto i: second.GetPart1()){
        if(std::find(first.part1.begin(), first.part1.end(), i) == first.part1.end()){
            if(std::find(first.part2.begin(), first.part2.end(), i) != first.part2.end()){
                throw std::logic_error("diff graphs");
            }
            first.part1.push_back(i);
        }
    }
    for(auto i: second.GetPart2()){
        if(std::find(first.part2.begin(), first.part2.end(), i) == first.part2.end()){
            if(std::find(first.part1.begin(), first.part1.end(), i) != first.part1.end()){
                throw std::logic_error("diff graphs");
            }
            first.part2.push_back(i);
        }
    }
    return first;
}

bipartite_graph operator+(bipartite_graph &first, bipartite_graph &second){
    bipartite_graph tmp(first);
    return (tmp += second);
}

bipartite_graph operator+(bipartite_graph &first, weighted_graph &second){
    throw std::logic_error("diff graphs");
}

simple_graph operator+(bipartite_graph &first, TGraph &second){
    std::vector<std::string> edges;
    auto first_eds = first.GetEdges();
    auto second_eds = second.GetEdges();
    for(auto i: first_eds){
        std::string s1 = "", s2 = "";
        s1 += std::string(1, i.first) + std::string(1, i.second);
        s2 += std::string(1, i.second) + std::string(1, i.first);
        if(std::find(edges.begin(), edges.end(), s1) == edges.end() && std::find(edges.begin(), edges.end(), s2) == edges.end()){
            edges.push_back(s1);
        }
    }
    // for(auto i: second.GetEdges()){
    //     std::cout << i.first << i.second << std::endl;
    // }
    
    for(auto i: second_eds){
        // std::cout << "!" << std::endl;
        std::string s1 = "", s2 = "";
        s1 += std::string(1, i.first) + std::string(1, i.second);
        s2 += std::string(1, i.second) + std::string(1, i.first);
        if(std::find(edges.begin(), edges.end(), s1) == edges.end() && std::find(edges.begin(), edges.end(), s2) == edges.end()){
            edges.push_back(s2);
        }
    }
    // for(auto i: edges){
    //     std::cout << i << std::endl;
    // }
    return simple_graph(edges);
}

bipartite_graph operator-=(bipartite_graph &first, bipartite_graph &second){
    for(auto i: second.GetPart1()) {
        auto place = std::find(first.part1.begin(), first.part1.end(), i);
        if(place != first.part1.end()){
            first.part1.erase(place);
        }
    }
    for(auto i: second.GetPart2()){
        auto place = std::find(first.part2.begin(), first.part2.end(), i);
        if(place != first.part2.end()){
            first.part2.erase(place);
        }
    }
    return first;
}

bipartite_graph operator-(bipartite_graph &first, bipartite_graph &second){
    bipartite_graph tmp(first);
    return (tmp -= second);
}

simple_graph operator-(bipartite_graph &first, TGraph &second){
    auto f_edgs = first.GetEdges();
    for(auto i: second.GetEdges()){
        auto place = std::find(f_edgs.begin(), f_edgs.end(), i);
        if(place != f_edgs.end()){
            f_edgs.erase(place);
        }
        place = std::find(f_edgs.begin(), f_edgs.end(), std::make_pair(i.second, i.first));
        if(place != f_edgs.end()){
            f_edgs.erase(place);
        }
    }
    std::vector<std::string> new_edges;
    for(auto i: first.GetEdges()){
        std::string s = "";
        s += std::string(1, i.first) + std::string(1, i.second);
        new_edges.push_back(s);
    }
    return simple_graph(new_edges);
}

complete_graph::complete_graph(std::unique_ptr<complete_args> && args){
    for(auto i = args->vertices.begin(); i != args->vertices.end(); i++){
        vertices.push_back(*i);
    }
}

complete_graph::complete_graph(std::vector<char> verts){
    for(auto i = verts.begin(); i != verts.end(); i++){
        vertices.push_back(*i);
    }
}

complete_graph::complete_graph(const complete_graph &copy){
    *this = complete_graph(copy.GetVertices());
}

const std::vector<char> complete_graph::GetVertices() const{
    return vertices;
}

const std::vector<std::pair<char, char>> complete_graph::GetEdges() const{
    std::vector<std::pair<char, char>> edges;
    for(auto i = vertices.begin(); i != vertices.end(); i++){
        for(auto j = i + 1; j != vertices.end(); j++){
            edges.push_back(std::make_pair(*i, *j));
        }
    }
    return edges;
}

const std::string complete_graph::ToString() const{
    std::string s = "";
    s += "CompleteGraph {";
    for(auto &i: vertices){
        s += std::string(1, i);
        if(i != *(vertices.end() - 1)){
            s += ", ";
        }
    }
    s += "}";
    return s;
}

std::unique_ptr<TGraph> complete_graph::AsWeighted(int default_weight) const{
    std::vector<std::string> edges;
    std::vector<int> weights;
    for(auto i = vertices.begin(); i != vertices.end(); i++){
        for(auto j = i + 1; j != vertices.end(); j++){
            std::string s = "";
            s += std::string(1, *i) + std::string(1, *j);
            edges.push_back(s);
            weights.push_back(default_weight);
        }
    }
    return std::make_unique<weighted_graph>(std::make_unique<weighted_args>(edges, weights));
}

complete_graph operator+=(complete_graph &first, complete_graph &second){
    for(auto i: second.GetVertices()){
        if(std::find(first.vertices.begin(), first.vertices.end(), i) == first.vertices.end()){
            first.vertices.push_back(i);
        }
    }
    return first;
}

complete_graph operator+(complete_graph &first, complete_graph &second){
    complete_graph tmp(first);
    return (tmp += second);
}

simple_graph operator+(complete_graph &first, TGraph &second){
    std::vector<std::string> edges;
    for(auto i: first.GetEdges()){
        std::string s = "";
        std::string s1 = "", s2 = "";
        s += std::string(1, i.first) + std::string(1, i.second) + " " + std::string(1, i.second) + std::string(1, i.first);
        s1 += std::string(1, i.first) + std::string(1, i.second);
        s2 += std::string(1, i.second) + std::string(1, i.first);
        if(std::find(edges.begin(), edges.end(), s1) == edges.end() && std::find(edges.begin(), edges.end(), s2) == edges.end()){
            edges.push_back(s1);
        }
    }
    for(auto i: second.GetEdges()){
        std::string s = "";
        std::string s1 = "", s2 = "";
        s += std::string(1, i.first) + std::string(1, i.second) + " " + std::string(1, i.second) + std::string(1, i.first);
        s1 += std::string(1, i.first) + std::string(1, i.second);
        s2 += std::string(1, i.second) + std::string(1, i.first);
        if(std::find(edges.begin(), edges.end(), s1) == edges.end() && std::find(edges.begin(), edges.end(), s2) == edges.end()){
            edges.push_back(s1);
        }
    }
    return simple_graph(edges);
}

simple_graph operator+(complete_graph &first, weighted_graph &second){
    throw std::logic_error("diff graphs");
}

complete_graph operator-=(complete_graph &first, complete_graph &second){
    for (auto i: second.GetVertices()){
        auto place = std::find(first.vertices.begin(), first.vertices.end(), i);
        if(place != first.vertices.end()){
            first.vertices.erase(place);
        }
    }
    return first;
}

complete_graph operator-(complete_graph &first, complete_graph &second){
    complete_graph tmp(first);
    return (tmp -= second);
}

simple_graph operator-(complete_graph &first, TGraph &second){
    auto f_edgs = first.GetEdges();
    for(auto i: second.GetEdges()){
        auto place = std::find(f_edgs.begin(), f_edgs.end(), i);
        if(place != f_edgs.end()){
            f_edgs.erase(place);
        }
        place = std::find(f_edgs.begin(), f_edgs.end(), std::make_pair(i.second, i.first));
        if(place != f_edgs.end()){
            f_edgs.erase(place);
        }
    }
    std::vector<std::string> new_edges;
    for(auto i: first.GetEdges()){
        std::string s = "";
        s += std::string(1, i.first) + std::string(1, i.second);
        new_edges.push_back(s);
    }
    return simple_graph(new_edges);
}