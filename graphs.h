#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <exception>

class arguments{
public:
    virtual ~arguments() = default;
};

class bipartite_args: public arguments{
public:    
    std::vector<char> part1;
    std::vector<char> part2;
    //~bipartite_args(){}
    bipartite_args(std::vector<char> p1, std::vector<char> p2){
        for(auto i: p1){
            part1.push_back(i);
        }
        for(auto i: p2){
            part2.push_back(i);
        }
    };
};

class simple_args: public arguments{
 public:   
    std::vector<std::string> edges;
    simple_args(std::vector<std::string> edg){
        for(auto i: edg){
            edges.push_back(i);
        }
    };
};

class complete_args: public arguments{
public:    
    std::vector<char> vertices;
    complete_args(std::vector<char> vrt){
        for(auto i: vrt){
            vertices.push_back(i);
        }
    };
};

class weighted_args: public arguments{
public:    
    std::vector<std::string> edges;
    std::vector<int> weights;
    weighted_args(std::vector<std::string> edg, std::vector<int> wgt){
        for (auto i: edg){
            edges.push_back(i);
        }
        for (auto i: wgt){
            weights.push_back(i);
        }
    };
};

class TGraph{
public:
    virtual const std::string ToString() const = 0;
    virtual const std::vector<char> GetVertices() const = 0;
    virtual const std::vector<std::pair<char, char>> GetEdges() const = 0;
    virtual std::unique_ptr<TGraph> AsWeighted(int default_weight) const = 0;
    virtual ~TGraph() {};
};

class weighted_graph: public TGraph{
    std::vector<char> vertices;
    std::vector<std::pair<char, char>> edges;
    std::vector<int> weights;
public:
    using arg_type = weighted_args;
    weighted_graph(std::unique_ptr<weighted_args> && args){
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
    };
    weighted_graph(std::vector<std::string> edg, std::vector<int> wgt){
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
    };
    weighted_graph(const weighted_graph &copy){
        std::vector<std::string> edg;
        for(auto i: copy.GetEdges()){
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
        }
        *this = weighted_graph(edg, copy.weights);
    };
    ~weighted_graph(){};
    const std::vector<char> GetVertices() const{
        return vertices;
    };
    const std::vector<std::pair<char, char>> GetEdges() const{
        return edges;
    };
    const std::vector<int> GetWeights() const{
        return weights;
    };
    const std::string ToString() const{
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
    };
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const{
        std::vector<std::string> edg;
        for(auto i: this->edges){
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
        }
        return std::make_unique<weighted_graph>(edg, weights);
    };
    // friend weighted_graph operator=(weighted_graph &first, weighted_graph &second);
    friend weighted_graph & operator+=(weighted_graph &first, weighted_graph &second);
    friend weighted_graph operator+(weighted_graph &first, weighted_graph &second);
    friend weighted_graph operator+(weighted_graph &first, TGraph &second);
    friend weighted_graph operator-=(weighted_graph &first, weighted_graph &second);
    friend weighted_graph operator-(weighted_graph &first, TGraph &second);
};

// weighted_graph operator=(weighted_graph &first, weighted_graph &second){
//     first.edges = second.edges;
//     first.vertices = second.vertices;
//     first.weights = second.weights;
//     return first;
// }

class simple_graph: public TGraph{
    std::vector<char> vertices;
    std::vector<std::pair<char, char>> edges;
public:
    using arg_type = simple_args;
    simple_graph(std::unique_ptr<simple_args> && args){
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
    simple_graph(std::vector<std::string> edg){
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
    simple_graph(const simple_graph &copy){
        std::vector<std::string> edg;
        for(auto i: copy.GetEdges()){
            std::stringstream ss;
            ss << i.first << i.second;
            edg.push_back(ss.str());
        }
        *this = simple_graph(edg);
    }
    ~simple_graph(){}
    const std::vector<char> GetVertices() const{
        return vertices;
    }
    const std::vector<std::pair<char, char>> GetEdges() const{
        return edges;
    }
    const std::string ToString() const{
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
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const{
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
    friend simple_graph operator+=(simple_graph &first, TGraph &second);
    friend simple_graph operator+(simple_graph &first, TGraph &second);
    friend simple_graph operator+(simple_graph &first, weighted_graph &second);
    friend simple_graph operator-=(simple_graph &first, TGraph &second);
    friend simple_graph operator-(simple_graph &first, TGraph &second);
};

class bipartite_graph: public TGraph{
    std::vector<char> part1;
    std::vector<char> part2;
public:
    using arg_type = bipartite_args;
    bipartite_graph(std::unique_ptr<bipartite_args> && args){
        for(auto i: args->part1){
            part1.push_back(i);
        }
        for(auto i: args->part2){
            part2.push_back(i);
        }
    }
    bipartite_graph(std::vector<char> p1, std::vector<char> p2){
        for(auto i: p1){
            part1.push_back(i);
        }
        for(auto i: p2){
            part2.push_back(i);
        }
    }
    bipartite_graph(const bipartite_graph &copy){
        *this = bipartite_graph(copy.part1, copy.part2);
    }
    ~bipartite_graph(){}
    const std::vector<char> GetVertices() const{
        std::vector<char> res;
        for(auto i: part1){
            res.push_back(i);
        }
        for(auto i: part2){
            res.push_back(i);
        }
        return res;
    }
    const std::vector<char> GetPart1() const{
        return part1;
    }
    const std::vector<char> GetPart2() const{
        return part2;
    }
    const std::vector<std::pair<char, char>> GetEdges() const{
        std::vector<std::pair<char, char>> edges;
        for(auto i: part1){
            for(auto j: part2){
                edges.push_back(std::make_pair(i, j));
            }
        }
        return edges;
    }
    const std::string ToString() const{
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
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const{
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
    friend bipartite_graph operator+=(bipartite_graph &first, bipartite_graph &second);
    friend bipartite_graph operator+(bipartite_graph &first, bipartite_graph &second);
    friend bipartite_graph operator+(bipartite_graph &first, weighted_graph &second);
    friend simple_graph operator+(bipartite_graph &first, TGraph &second);
    friend bipartite_graph operator-=(bipartite_graph &first, bipartite_graph &second);
    friend bipartite_graph operator-(bipartite_graph &first, bipartite_graph &second);
    friend simple_graph operator-(bipartite_graph &first, TGraph &second);
};

class complete_graph: public TGraph{
    std::vector<char> vertices;
public:
    using arg_type = complete_args;
    complete_graph(std::unique_ptr<complete_args> && args){
        for(auto i = args->vertices.begin(); i != args->vertices.end(); i++){
            vertices.push_back(*i);
        }
    }
    complete_graph(std::vector<char> verts){
        for(auto i = verts.begin(); i != verts.end(); i++){
            vertices.push_back(*i);
        }
    }
    complete_graph(const complete_graph &copy){
        *this = complete_graph(copy.GetVertices());
    }
    ~complete_graph(){}
    const std::vector<char> GetVertices() const{
        return vertices;
    }
    const std::vector<std::pair<char, char>> GetEdges() const{
        std::vector<std::pair<char, char>> edges;
        for(auto i = vertices.begin(); i != vertices.end(); i++){
            for(auto j = i + 1; j != vertices.end(); j++){
                edges.push_back(std::make_pair(*i, *j));
            }
        }
        return edges;
    }
    const std::string ToString() const{
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
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const{
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
    friend complete_graph operator+=(complete_graph &first, complete_graph &second);
    friend complete_graph operator+(complete_graph &first, complete_graph &second);
    friend simple_graph operator+(complete_graph &first, TGraph &second);
    friend simple_graph operator+(complete_graph &first, weighted_graph &second);
    friend complete_graph operator-=(complete_graph &first, complete_graph &second);
    friend complete_graph operator-(complete_graph &first, complete_graph &second);
    friend simple_graph operator-(complete_graph &first, TGraph &second);
};