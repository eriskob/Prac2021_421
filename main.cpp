#include "factory.h"
#include "short_path.h"
#include <gtest/gtest.h>

int main(int argc, char **argv){
    std::vector<char> p1 {'A','B','C','D'};
    std::vector<char> p2 {'E','F'};
    auto bipartite = TFactory().Create("bipartite", std::make_unique<bipartite_args>(p1, p2));
    std::cout << bipartite->ToString() << std::endl;
    // BipartiteGraph {{A, B, C, D}, {E, F}}
    std::vector<char> vrt1 {'A', 'B', 'F'};
    auto complete = TFactory().Create("complete", std::make_unique<complete_args>(vrt1));
    std::cout << complete->ToString() << std::endl;
    // CompleteGraph {A, B, F}
    std::vector<std::string> v1 {{"EF"}, {"FA"}};
    auto simple = TFactory().Create("simple", std::make_unique<simple_args>(v1));
    std::cout << simple->ToString() << std::endl;
    // SimpleGraph {EF, FA}
    std::vector<std::string> v2 {{"FD"}, {"ED"}};
    std::vector<int> v3 {5, 6};
    auto weighted = TFactory().Create("weighted", std::make_unique<weighted_args>(v2, v3));
    std::cout << weighted->ToString() << std::endl;
    // WeightedGraph {FD:5, ED:6}
    auto p = *dynamic_cast<bipartite_graph*>(bipartite.get()) + *dynamic_cast<simple_graph*>(simple.get());
    std::cout << p.ToString() << std::endl;
    // SimpleGraph {AE, AF, BE, BF, CE, CF, DE, DF, EF, FA}
    p -= *dynamic_cast<complete_graph*>(complete.get());
    std::cout << p.ToString() << std::endl;
    // // SimpleGraph {AE, BE, CE, CF, DE, DF, EF, FA}
    auto w = p.AsWeighted(1);
    std::cout << w->ToString() << std::endl;
    std::vector<std::string> v4 {{"AB"}, {"AC"}, {"AF"}, {"BC"}, {"CF"}, {"FE"}, {"CD"}, {"BD"}, {"ED"}};
    std::vector<int> w1 {7, 9, 14, 10, 2, 9, 11, 15, 6};
    auto weight1 = TFactory().Create("weighted", std::make_unique<weighted_args>(v4, w1));
    auto weighted1 = dynamic_cast<weighted_graph*>(weight1.get());
    std::vector<std::pair<char, char>> res1 {{'A', 'C'}, {'C', 'F'}, {'F', 'E'}};
    // std::cout << "0\n";
    auto f = shortest_path(*weighted1, 'A', 'E');
    // std::cout << "4\n";
    for(int i = 0; i < f.size(); i++){
        std::cout << f[i].first << ", " << f[i].second << std::endl;
    }

    // std::vector<std::string> weight_edg = {{"AB"}, {"AC"}, {"AF"}, {"BC"}, {"BD"}, {"CD"}, {"CF"}, {"DE"}, {"EF"}};
    // std::vector<int> con_weights = {7, 9, 14, 10, 15, 11, 2, 6, 9};
    // auto con_graph = TFactory().Create("weighted", std::make_unique<weighted_args>(weight_edg, con_weights));
    // auto weighted_con = dynamic_cast<weighted_graph*>(con_graph.get());
    // std::vector<std::pair<char, char>> path = {{'A', 'C'}, {'C', 'F'}, {'F', 'E'}};
    // auto m = shortest_path(*weighted_con, 'A', 'E');
    // for(int i = 0; i < m.size(); i++){
    //     std::cout << m[i].first << ", " << m[i].second << std::endl;
    // }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    // *dynamic_cast<weighted_graph*>(w.get()) += *dynamic_cast<simple_graph*>(simple.get());
    // !!! std:: logic_error !!!
    // пример: удаление у взвешенного смежных с простым рёбер
    // w -= *simple;
    // std::cout << w->ToString() << std::endl;
    // // WeightedGraph {AE:1, BE:1, CE:1, CF:1, DE:1, DF:1}
    // // пример: добавление/перезапись у взвешенного смежных с другим взвешенным рёбер
    // w += *weighted;
    // std::cout << w->ToString() << std::endl;
    // // WeightedGraph {AE:1, BE:1, CE:1, CF:1, DE:6, DF:5}
    // // пример: удаление у взвешенного смежных с другим взвешенным рёбер
    // w -= *weighted;
    // std::cout << w->ToString() << std::endl;
    // // WeightedGraph {AE:1, BE:1, CE:1, CF:1}
}