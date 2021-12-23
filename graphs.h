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
    bipartite_args(std::vector<char> p1, std::vector<char> p2);
};

class simple_args: public arguments{
 public:   
    std::vector<std::string> edges;
    simple_args(std::vector<std::string> edg);
};

class complete_args: public arguments{
public:    
    std::vector<char> vertices;
    complete_args(std::vector<char> vrt);
};

class weighted_args: public arguments{
public:    
    std::vector<std::string> edges;
    std::vector<int> weights;
    weighted_args(std::vector<std::string> edg, std::vector<int> wgt);
};

class TGraph{
public:
    virtual const std::string ToString() const = 0;
    virtual const std::vector<char> GetVertices() const = 0;
    virtual const std::vector<std::pair<char, char>> GetEdges() const = 0;
    virtual std::unique_ptr<TGraph> AsWeighted(int default_weight) const = 0;
    virtual ~TGraph(){};
};

class weighted_graph: public TGraph{
    std::vector<char> vertices;
    std::vector<std::pair<char, char>> edges;
    std::vector<int> weights;
public:
    using arg_type = weighted_args;
    weighted_graph(std::unique_ptr<weighted_args> && args);
    weighted_graph(std::vector<std::string> edg, std::vector<int> wgt);
    weighted_graph(const weighted_graph &copy);
    ~weighted_graph(){};
    const std::vector<char> GetVertices() const;
    const std::vector<std::pair<char, char>> GetEdges() const;
    const std::vector<int> GetWeights() const;
    const std::string ToString() const;
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const;
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
    simple_graph(std::unique_ptr<simple_args> && args);
    simple_graph(std::vector<std::string> edg);
    simple_graph(const simple_graph &copy);
    ~simple_graph(){};
    const std::vector<char> GetVertices() const;
    const std::vector<std::pair<char, char>> GetEdges() const;
    const std::string ToString() const;
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const;
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
    bipartite_graph(std::unique_ptr<bipartite_args> && args);
    bipartite_graph(std::vector<char> p1, std::vector<char> p2);
    bipartite_graph(const bipartite_graph &copy);
    ~bipartite_graph(){};
    const std::vector<char> GetVertices() const;
    const std::vector<char> GetPart1() const;
    const std::vector<char> GetPart2() const;
    const std::vector<std::pair<char, char>> GetEdges() const;
    const std::string ToString() const;
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const;
    friend bipartite_graph operator+=(bipartite_graph &first, bipartite_graph &second);
    friend bipartite_graph operator+(bipartite_graph &first, bipartite_graph &second);
    friend bipartite_graph operator+(bipartite_graph &first, weighted_graph &second);
    friend simple_graph operator+(bipartite_graph& first, TGraph& second);
    friend bipartite_graph operator-=(bipartite_graph &first, bipartite_graph &second);
    friend bipartite_graph operator-(bipartite_graph &first, bipartite_graph &second);
    friend simple_graph operator-(bipartite_graph &first, TGraph &second);
};


class complete_graph: public TGraph{
    std::vector<char> vertices;
public:
    using arg_type = complete_args;
    complete_graph(std::unique_ptr<complete_args> && args);
    complete_graph(std::vector<char> verts);
    complete_graph(const complete_graph &copy);
    ~complete_graph(){};
    const std::vector<char> GetVertices() const;
    const std::vector<std::pair<char, char>> GetEdges() const;
    const std::string ToString() const;
    std::unique_ptr<TGraph> AsWeighted(int default_weight) const;
    friend complete_graph operator+=(complete_graph &first, complete_graph &second);
    friend complete_graph operator+(complete_graph &first, complete_graph &second);
    friend simple_graph operator+(complete_graph &first, TGraph &second);
    friend simple_graph operator+(complete_graph &first, weighted_graph &second);
    friend complete_graph operator-=(complete_graph &first, complete_graph &second);
    friend complete_graph operator-(complete_graph &first, complete_graph &second);
    friend simple_graph operator-(complete_graph &first, TGraph &second);
};