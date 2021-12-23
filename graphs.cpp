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
        for(auto i: copy.GetEdges()){
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
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
        std::stringstream ss;
        ss << "WeightedGraph {";
        for(int i = 0; i < edges.size(); i++){
            ss << edges[i].first << edges[i].second;
            ss << ":";
            ss << weights[i];
            if(i != edges.size() - 1){
                ss << ", ";
            }
        }
        ss << "}";
        return ss.str();
    }

std::unique_ptr<TGraph> weighted_graph::AsWeighted(int default_weight) const{
        std::vector<std::string> edg;
        for(auto i: this->edges){
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
        }
        return std::make_unique<weighted_graph>(edg, weights);
    }

weighted_graph & operator+=(weighted_graph &first, weighted_graph &second){
    // weighted_graph tmp(first);
    // return (tmp = first + second);
    auto second_eds = second.GetEdges();
    auto second_w = second.GetWeights();
    auto len = second_eds.size();
    for (int i = 0; i < len; ++i) {
        if (std::find(first.edges.begin(), first.edges.end(), second_eds[i]) == first.edges.end() &&
            std::find(first.edges.begin(), first.edges.end(), 
            std::make_pair(second_eds[i].second, second_eds[i].first)) == first.edges.end()) {
            first.edges.push_back(second_eds[i]);
            first.weights.push_back(second_w[i]);
        }
    }
    return first;
}

weighted_graph operator+(weighted_graph &first, weighted_graph &second){
    weighted_graph another = weighted_graph(first);
    return another += second;
    // weighted_graph tmp(first);
    // for(int i = 0; i < second.GetEdges().size(); i++){
    //     if(std::find(first.edges.begin(), first.edges.end(), second.GetEdges()[i]) == first.edges.end() && std::find(first.edges.begin(), first.edges.end(), std::make_pair(second.GetEdges()[i].second, second.GetEdges()[i].first)) == first.edges.end()){
    //         tmp.edges.push_back(second.GetEdges()[i]);
    //         tmp.weights.push_back(second.GetWeights()[i]);
    //     }
    // }
    // return tmp;
}

weighted_graph operator+(weighted_graph &first, TGraph &second){
    throw std::logic_error("diff graphs");
}

weighted_graph operator-=(weighted_graph &first, weighted_graph &second){
    for(auto i: second.GetEdges()){
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
    auto f_edgs = first.GetEdges();
    auto f_wghts = first.GetWeights();
    for(auto i: second.GetEdges()) {
        auto place = std::find(first.GetEdges().begin(), first.GetEdges().end(), i);
        if(place != first.GetEdges().end()){
            f_edgs.erase(place);
            int index = place - first.GetEdges().begin();
            f_wghts.erase(first.GetWeights().begin() + index);
        }
        place = std::find(first.GetEdges().begin(), first.GetEdges().end(), std::make_pair(i.second, i.first));
        if(place != first.GetEdges().end()){
            f_edgs.erase(place);
            int index = place - first.GetEdges().begin();
            f_wghts.erase(first.GetWeights().begin() + index);
        }
    }
    std::vector<std::string> new_edges;
    for(auto i: first.GetEdges()){
        std::stringstream ss;
        ss << i.first << i.second;
        new_edges.push_back(ss.str());
    }
    return weighted_graph(new_edges, first.GetWeights());
}

simple_graph::simple_graph(std::unique_ptr<simple_args> && args){
        for(auto i: args->edges){
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
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
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
        std::stringstream ss;
        ss << "SimpleGraph {";
        for(auto &i: edges){
            ss << i.first << i.second;
            if(i != *(edges.end() - 1)){
                ss << ", ";
            }
        }
        ss << "}";
        return ss.str();
    }

std::unique_ptr<TGraph> simple_graph::AsWeighted(int default_weight) const{
        std::vector<std::string> edg;
        std::vector<int> weights;
        for(auto i: edges){
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
            weights.push_back(default_weight);
        }
        return std::make_unique<weighted_graph>(std::make_unique<weighted_args>(edg, weights));
    }

simple_graph operator+=(simple_graph &first, TGraph &second){
    std::vector<std::string> edges;
    for(int i = 0; i < second.GetEdges().size(); ++i){
        if(std::find(first.edges.begin(), first.edges.end(), second.GetEdges()[i]) == first.edges.end() && std::find(first.edges.begin(), first.edges.end(), std::make_pair(second.GetEdges()[i].second, second.GetEdges()[i].first)) == first.edges.end()){
            first.edges.push_back(second.GetEdges()[i]);
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
    auto second_edg = second.GetEdges();
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
        std::stringstream ss;
        ss << "BipartiteGraph {{";
        for(auto &i: part1){
            ss << i;
            if(i != *(part1.end() - 1)){
                ss << ", ";
            }
        }
        ss << "}, {";
        for(auto &i: part2){
            ss << i;
            if (i != *(part2.end() - 1)){
                ss << ", ";
            }
        }
        ss << "}}";
        return ss.str();
    }

std::unique_ptr<TGraph> bipartite_graph::AsWeighted(int default_weight) const{
        std::vector<std::string> edges;
        std::vector<int> weights;
        for(auto i: part1){
            for(auto j: part2){
                std::stringstream ss;
                ss << i << j;
                edges.push_back(ss.str());
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
    for(auto i: first.GetEdges()){
        std::stringstream ss;
        std::string straight, reverse;
        ss << i.first << i.second << " " << i.second << i.first;
        ss >> straight >> reverse;
        if(std::find(edges.begin(), edges.end(), straight) == edges.end() && std::find(edges.begin(), edges.end(), reverse) == edges.end()){
            edges.push_back(straight);
        }
    }
    for(auto i: second.GetEdges()){
        std::stringstream ss;
        std::string straight, reverse;
        ss << i.first << i.second << " " << i.second << i.first;
        ss >> straight >> reverse;
        if(std::find(edges.begin(), edges.end(), straight) == edges.end() && std::find(edges.begin(), edges.end(), reverse) == edges.end()){
            edges.push_back(straight);
        }
    }
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
        auto place = std::find(first.GetEdges().begin(), first.GetEdges().end(), i);
        if(place != first.GetEdges().end()){
            f_edgs.erase(place);
        }
        place = std::find(first.GetEdges().begin(), first.GetEdges().end(), std::make_pair(i.second, i.first));
        if(place != first.GetEdges().end()){
            f_edgs.erase(place);
        }
    }
    std::vector<std::string> new_edges;
    for(auto i: first.GetEdges()){
        std::stringstream ss;
        ss << i.first << i.second;
        new_edges.push_back(ss.str());
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
        std::stringstream ss;
        ss << "CompleteGraph {";
        for(auto &i: vertices){
            ss << i;
            if(i != *(vertices.end() - 1)){
                ss << ", ";
            }
        }
        ss << "}";
        return ss.str();
    }

std::unique_ptr<TGraph> complete_graph::AsWeighted(int default_weight) const{
        std::vector<std::string> edges;
        std::vector<int> weights;
        for(auto i = vertices.begin(); i != vertices.end(); i++){
            for(auto j = i + 1; j != vertices.end(); j++){
                std::stringstream ss;
                ss << *i << *j;
                edges.push_back(ss.str());
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
        std::stringstream ss;
        std::string straight, reverse;
        ss << i.first << i.second << " " << i.second << i.first;
        ss >> straight >> reverse;
        if(std::find(edges.begin(), edges.end(), straight) == edges.end() && std::find(edges.begin(), edges.end(), reverse) == edges.end()){
            edges.push_back(straight);
        }
    }
    for(auto i: second.GetEdges()){
        std::stringstream ss;
        std::string straight, reverse;
        ss << i.first << i.second << " " << i.second << i.first;
        ss >> straight >> reverse;
        if(std::find(edges.begin(), edges.end(), straight) == edges.end() && std::find(edges.begin(), edges.end(), reverse) == edges.end()){
            edges.push_back(straight);
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
        auto place = std::find(first.GetEdges().begin(), first.GetEdges().end(), i);
        if(place != first.GetEdges().end()){
            f_edgs.erase(place);
        }
        place = std::find(first.GetEdges().begin(), first.GetEdges().end(), std::make_pair(i.second, i.first));
        if(place != first.GetEdges().end()){
            f_edgs.erase(place);
        }
    }
    std::vector<std::string> new_edges;
    for(auto i: first.GetEdges()){
        std::stringstream ss;
        ss << i.first << i.second;
        new_edges.push_back(ss.str());
    }
    return simple_graph(new_edges);
}