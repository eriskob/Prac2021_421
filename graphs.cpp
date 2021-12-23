#include "graphs.h"
#include <vector>


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