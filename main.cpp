#include "factory.h"

int main(int argc, char **argv){
    std::vector<char> p1 {'A','B','C','D'};
    std::vector<char> p2 {'E','F'};
    std::unique_ptr<TGraph> bipartite = TFactory().Create("bipartite", std::make_unique<bipartite_args>(p1, p2));
    // std::cout << bipartite->ToString() << std::endl;
    // // BipartiteGraph {{A, B, C, D}, {E, F}}
    // std::vector<char> vrt1 {'A', 'B', 'F'};
    // std::unique_ptr<TGraph> complete = TFactory().Create("complete", std::make_unique<complete_args>(vrt1));
    // std::cout << complete->ToString() << std::endl;
    // // CompleteGraph {A, B, F}
    // std::vector<std::string> v1 {{"EF", "FA"}};
    // std::unique_ptr<TGraph> simple = TFactory().Create("simple", std::make_unique<simple_args>(v1));
    // std::cout << simple->ToString() << std::endl;
    // // SimpleGraph {EF, FA}
    // std::vector<std::string> v2 {{"FD", "ED"}};
    // std::vector<int> v3 {5, 6};
    // std::unique_ptr<TGraph> weighted = TFactory().Create("weighted", std::make_unique<weighted_args>(v2, v3));
    // std::cout << weighted->ToString() << std::endl;
    // WeightedGraph {FD:5, ED:6}
    // auto p = *bipartite + *simple;
    // std::cout << p.ToString() << std::endl;
    // // SimpleGraph {AE, AF, BE, BF, CE, CF, DE, DF, EF, FA}
    // p -= *complete;
    // std::cout << p.ToString() << std::endl;
    // // SimpleGraph {AE, BE, CE, CF, DE, DF, EF, FA}
    // auto w = p.AsWeighted(1);
    // std::cout << w->ToString() << std::endl;
}