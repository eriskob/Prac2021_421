#include <gtest/gtest.h>
#include "factory.h"
#include "short_path.h"

class test_bipartite: public ::testing::Test{
protected:
	virtual void SetUp(){
		std::vector<char> b1_p1 {'A', 'B', 'C', 'M'};
        std::vector<char> b1_p2 {'D', 'E'};
        b1 = TFactory().Create(std::string("bipartite"), std::make_unique<bipartite_args> (b1_p1, b1_p2));
        std::vector<char> b2_p1 {'B', 'K', 'M', 'N'};
        std::vector<char> b2_p2 {'E', 'F'};
        b2 = TFactory().Create(std::string("bipartite"), std::make_unique<bipartite_args> (b2_p1, b2_p2));
        std::vector<char> b3_p1 {'A', 'B', 'M'};
        std::vector<char> b3_p2 {'K', 'F'};
        b3 = TFactory().Create(std::string("bipartite"), std::make_unique<bipartite_args> (b3_p1, b3_p2));
        std::vector<char> v {'A','B','M', 'N', 'D'};
        complete = TFactory().Create("complete", std::make_unique<complete_args> (v));
        std::vector<std::string> wv1{{"AB"}, {"BF"}, {"FD"}, {"AE"}, {"ED"}};
        std::vector<int> wv2 {10, 12, 3, 15, 20};
        weighted = TFactory().Create("weighted", std::make_unique<weighted_args>(wv1, wv2));
        std::vector<std::string> vec{"EF", "FA", "AB", "EC"};
        simple = TFactory().Create("simple", std::make_unique<simple_args>(vec));
	}
	std::unique_ptr<TGraph> b1;
    std::unique_ptr<TGraph> b2;
    std::unique_ptr<TGraph> b3;
    std::unique_ptr<TGraph> complete;
    std::unique_ptr<TGraph> weighted;
    std::unique_ptr<TGraph> simple;
};

class test_complete: public ::testing::Test
{
protected:
	virtual void SetUp(){
        std::vector<char> v1 {'A','B','M', 'N', 'D'};
        complete1 = TFactory().Create("complete", std::make_unique<complete_args> (v1));
        std::vector<char> v2 {'A', 'N', 'F'};
        complete2 = TFactory().Create("complete", std::make_unique<complete_args> (v2));
        std::vector<std::string> wv1{{"AB"}, {"BF"}, {"FD"}, {"AE"}, {"ED"}};
        std::vector<int> wv2 {10, 12, 3, 15, 20};
        weighted = TFactory().Create("weighted", std::make_unique<weighted_args>(wv1, wv2));
        std::vector<std::string> vec{{"EF"}, {"FA"}, {"AB"}, {"EC"}};
        simple = TFactory().Create("simple", std::make_unique<simple_args>(vec));
        std::vector<char> b1_p1 {'A', 'B', 'C', 'N'};
        std::vector<char> b1_p2 {'D', 'E'};
        bipart = TFactory().Create(std::string("bipartite"), std::make_unique<bipartite_args> (b1_p1, b1_p2));
	}
	std::unique_ptr<TGraph> bipart;
    std::unique_ptr<TGraph> complete1;
    std::unique_ptr<TGraph> complete2;
    std::unique_ptr<TGraph> weighted;
    std::unique_ptr<TGraph> simple;
};

class test_simple: public ::testing::Test{
protected:
	virtual void SetUp(){
        std::vector<std::string> vec1 {{"EF"}, {"FA"}, {"AB"}, {"EC"}};
        simple1 = TFactory().Create("simple", std::make_unique<simple_args>(vec1));
        std::vector<std::string> vec2 = {{"EF"}, {"FC"}, {"AE"}};
        simple2 = TFactory().Create("simple", std::make_unique<simple_args>(vec2));
        std::vector<char> v {'A', 'N', 'F'};
        complete = TFactory().Create("complete", std::make_unique<complete_args> (v));
        std::vector<std::string> wv1 {{"AB"}, {"BF"}, {"FD"}, {"AE"}, {"ED"}};
        std::vector<int> wv2 {10, 12, 3, 15, 20};
        weighted = TFactory().Create("weighted", std::make_unique<weighted_args>(wv1, wv2));
        std::vector<char> b1_p1 {'A', 'B', 'C', 'N'};
        std::vector<char> b1_p2 {'D', 'E'};
        bipart = TFactory().Create(std::string("bipartite"), std::make_unique<bipartite_args> (b1_p1, b1_p2));
	}
	std::unique_ptr<TGraph> bipart;
    std::unique_ptr<TGraph> complete;
    std::unique_ptr<TGraph> weighted;
    std::unique_ptr<TGraph> simple1;
    std::unique_ptr<TGraph> simple2;
};

class test_weighted: public ::testing::Test{
protected:
	virtual void SetUp(){
        std::vector<std::string> wv1{{"AB"}, {"BF"}, {"FD"}, {"AE"}, {"ED"}};
        std::vector<int> wv2 {10, 12, 3, 15, 20};
        weighted1 = TFactory().Create("weighted", std::make_unique<weighted_args>(wv1, wv2));
        std::vector<std::string> wv3{{"AB"}, {"AD"}, {"BF"}};
        std::vector<int> wv4 {10,12, 15};
        weighted2 = TFactory().Create("weighted", std::make_unique<weighted_args>(wv3, wv4));
        std::vector<std::string> vec2{{"EF"}, {"FC"}, {"AE"}};
        simple = TFactory().Create("simple", std::make_unique<simple_args>(vec2));
        std::vector<char> v {'A', 'N', 'F'};
        complete = TFactory().Create("complete", std::make_unique<complete_args> (v));
        std::vector<char> b1_p1 {'A', 'B', 'C', 'N'};
        std::vector<char> b1_p2 {'D', 'E'};
        bipart = TFactory().Create(std::string("bipartite"), std::make_unique<bipartite_args> (b1_p1, b1_p2));
	}
	std::unique_ptr<TGraph> bipart;
    std::unique_ptr<TGraph> complete;
    std::unique_ptr<TGraph> weighted1;
    std::unique_ptr<TGraph> weighted2;
    std::unique_ptr<TGraph> simple;
};

TEST(CheckCreation, BasicTypes){
    std::vector<std::string> vec1{{"EF"}, {"FA"}};
    std::vector<std::string> vec2 = {{"EF"}, {"FC"}, {"AE"}};
    std::vector<std::string> wv1{{"AB"}, {"BF"}, {"FD"}, {"AE"}, {"ED"}};
    std::vector<int> wv2 {10, 12, 3, 15, 20};
    std::vector<char> b1_p1 {'A', 'B', 'C', 'N'};
    std::vector<char> b1_p2 {'D', 'E'};
    ASSERT_THROW(TFactory().Create("graph", std::make_unique<simple_args>(vec1)), std::invalid_argument);
    ASSERT_THROW(TFactory().Create("complete", std::make_unique<simple_args>(vec2)), std::invalid_argument);
    ASSERT_THROW(TFactory().Create("complete", std::make_unique<weighted_args>(wv1, wv2)), std::invalid_argument);
    ASSERT_THROW(TFactory().Create("complete", std::make_unique<bipartite_args> (b1_p1, b1_p2)), std::invalid_argument);
    ASSERT_THROW(TFactory().Create("biparte", std::make_unique<weighted_args>(wv1, wv2)), std::invalid_argument);
    ASSERT_THROW(TFactory().Create("weighted", std::make_unique<simple_args>(vec2)), std::invalid_argument);
}

TEST_F(test_bipartite, basic_functions){
    std::vector<std::string> vec1{{"EF"}, {"FA"}};
    ASSERT_THROW(TFactory().Create("graph", std::make_unique<simple_args>(vec1)), std::invalid_argument);
    std::vector<std::string> vec2 = {{"EF"}, {"FC"}, {"AE"}};
    ASSERT_THROW(TFactory().Create("complete", std::make_unique<simple_args>(vec2)), std::invalid_argument);
    std::vector<std::string> wv1{{"AB"}, {"BF"}, {"FD"}, {"AE"}, {"ED"}};
    std::vector<int> wv2 {10, 12, 3, 15, 20};
    ASSERT_THROW(TFactory().Create("complete", std::make_unique<weighted_args>(wv1, wv2)), std::invalid_argument);
    std::vector<char> b1_p1 {'A', 'B', 'C', 'N'};
    std::vector<char> b1_p2 {'D', 'E'};
    ASSERT_THROW(TFactory().Create("complete", std::make_unique<bipartite_args> (b1_p1, b1_p2)), std::invalid_argument);

    ASSERT_EQ(std::vector<char>({'A', 'B', 'C', 'M', 'D', 'E'}), b1->GetVertices());
    ASSERT_EQ(std::vector<char>({'B', 'K', 'M', 'N', 'E', 'F'}), b2->GetVertices());
    std::vector<std::pair<char, char>> edg1 {{'A', 'D'}, {'A', 'E'}, {'B', 'D'}, {'B', 'E'}, {'C', 'D'}, {'C', 'E'}, {'M', 'D'}, {'M', 'E'}};
    ASSERT_EQ(edg1, b1->GetEdges());
    std::vector<std::pair<char, char>> edg2 {{'B', 'E'}, {'B', 'F'}, {'K', 'E'}, {'K', 'F'}, {'M', 'E'}, {'M', 'F'}, {'N', 'E'}, {'N', 'F'}};
    ASSERT_EQ(edg2, b2->GetEdges());
    ASSERT_EQ("BipartiteGraph {{A, B, C, M}, {D, E}}", b1->ToString());
    ASSERT_EQ("BipartiteGraph {{B, K, M, N}, {E, F}}", b2->ToString());
    ASSERT_EQ("WeightedGraph {AD:5, AE:5, BD:5, BE:5, CD:5, CE:5, MD:5, ME:5}", b1->AsWeighted(5)->ToString());
    ASSERT_EQ("WeightedGraph {BE:125, BF:125, KE:125, KF:125, ME:125, MF:125, NE:125, NF:125}", b2->AsWeighted(125)->ToString());
}

TEST_F(test_bipartite, arithmetic_operations){
    auto b4 = dynamic_cast<bipartite_graph*>(b1.get());
    auto b5 = dynamic_cast<bipartite_graph*>(b2.get());
    auto b6 = dynamic_cast<bipartite_graph*>(b3.get());
    auto complete2 = dynamic_cast<complete_graph*>(complete.get());
    auto weight2 = dynamic_cast<weighted_graph*>(weighted.get());
    auto simple2 = dynamic_cast<simple_graph*>(simple.get());
    ASSERT_EQ("SimpleGraph {AK, AF, BK, BF, MK, MF, BA, MA, NA, DA, MB, NB, DB, NM, DM, DN}", (*b6 + *complete2).ToString());
    ASSERT_EQ("SimpleGraph {AD, AE, BD, BE, CD, CE, MD, ME, FE, AF, BA}", (*b4 + *simple2).ToString());
    ASSERT_THROW(*b5 + *b6, std::logic_error);
    ASSERT_THROW(*b5 + *weight2, std::logic_error);
    ASSERT_EQ("BipartiteGraph {{A, B, C, M, K, N}, {D, E, F}}", (*b4 + *b5).ToString());
    *b4 += *b5;
    ASSERT_EQ("BipartiteGraph {{A, B, C, M, K, N}, {D, E, F}}", b4->ToString());
    ASSERT_EQ("BipartiteGraph {{A, C}, {D}}", (*b4 - *b5).ToString());
    ASSERT_EQ("SimpleGraph {AK, AF, BK, BF, MK, MF}", (*b6 - *complete2).ToString());
    ASSERT_EQ("SimpleGraph {AD, AE, AF, BD, BE, BF, CD, CE, CF, MD, ME, MF, KD, KE, KF, ND, NE, NF}", (*b4 - *simple2).ToString());
    ASSERT_EQ("SimpleGraph {AK, AF, BK, BF, MK, MF}", (*b6 - *weight2).ToString());
    *b5 -= *b6;
    ASSERT_EQ("BipartiteGraph {{K, N}, {E}}", b5->ToString());
}

TEST_F(test_complete, basic_functions){
    ASSERT_EQ(std::vector<char>({'A','B','M', 'N', 'D'}), complete1->GetVertices());
    ASSERT_EQ(std::vector<char>({'A', 'N', 'F'}), complete2->GetVertices());
    std::vector<std::pair<char, char>> res1 {{'A', 'B'}, {'A', 'M'}, {'A', 'N'}, {'A', 'D'}, {'B', 'M'}, {'B', 'N'}, {'B', 'D'}, {'M', 'N'}, {'M', 'D'}, {'N', 'D'}};
    ASSERT_EQ(res1, complete1->GetEdges());
    std::vector<std::pair<char, char>> res2 {{'A', 'N'}, {'A', 'F'}, {'N', 'F'}};
    ASSERT_EQ(res2, complete2->GetEdges());
    ASSERT_EQ("CompleteGraph {A, B, M, N, D}", complete1->ToString());
    ASSERT_EQ("CompleteGraph {A, N, F}", complete2->ToString());
    ASSERT_EQ("WeightedGraph {AB:9, AM:9, AN:9, AD:9, BM:9, BN:9, BD:9, MN:9, MD:9, ND:9}", complete1->AsWeighted(9)->ToString());
    ASSERT_EQ("WeightedGraph {AN:15, AF:15, NF:15}", complete2->AsWeighted(15)->ToString());
}

TEST_F(test_complete, arithmetic_operations){
    auto c1 = dynamic_cast<complete_graph*>(complete1.get());
    auto c2 = dynamic_cast<complete_graph*>(complete2.get());
    auto b = dynamic_cast<bipartite_graph*>(bipart.get());
    auto s = dynamic_cast<simple_graph*>(simple.get());
    auto w = dynamic_cast<weighted_graph*>(weighted.get());
    ASSERT_EQ("CompleteGraph {A, B, M, N, D, F}", (*c1 + *c2).ToString());
    ASSERT_EQ("SimpleGraph {AB, AM, AN, AD, BM, BN, BD, MN, MD, ND, AE, BE, CD, CE, NE}", (*c1 + *b).ToString());
    ASSERT_EQ("SimpleGraph {AN, AF, NF, EF, AB, EC}", (*c2 + *s).ToString());
    ASSERT_THROW(*c2 + *w, std::logic_error);
    *c1 += *c2;
    ASSERT_EQ("CompleteGraph {A, B, M, N, D, F}", c1->ToString());
    ASSERT_EQ("CompleteGraph {B, M, D}", (*c1 - *c2).ToString());
    ASSERT_EQ("SimpleGraph {AN, AF, NF}", (*c2 - *b).ToString());
    ASSERT_EQ("SimpleGraph {AB, AM, AN, AD, AF, BM, BN, BD, BF, MN, MD, MF, ND, NF, DF}", (*c1 - *s).ToString());
    ASSERT_EQ("SimpleGraph {AB, AM, AN, AD, AF, BM, BN, BD, BF, MN, MD, MF, ND, NF, DF}", (*c1 - *w).ToString());
    *c1 -= *c2;
    ASSERT_EQ("CompleteGraph {B, M, D}", c1->ToString());
}

TEST_F(test_simple, basic_functions){
    ASSERT_EQ(std::vector<char>({'A','B','C', 'E', 'F'}), simple1->GetVertices());
    ASSERT_EQ(std::vector<char>({'A', 'C', 'E', 'F'}), simple2->GetVertices());
    std::vector<std::pair<char, char>> res1 {{'E', 'F'}, {'F', 'A'}, {'A', 'B'}, {'E', 'C'}};
    ASSERT_EQ(res1, simple1->GetEdges());
    std::vector<std::pair<char, char>> res2 {{'E', 'F'}, {'F', 'C'}, {'A', 'E'}};
    ASSERT_EQ(res2, simple2->GetEdges());
    ASSERT_EQ("SimpleGraph {EF, FA, AB, EC}", simple1->ToString());
    ASSERT_EQ("SimpleGraph {EF, FC, AE}", simple2->ToString());
    ASSERT_EQ("WeightedGraph {EF:7, FA:7, AB:7, EC:7}", simple1->AsWeighted(7)->ToString());
    ASSERT_EQ("WeightedGraph {EF:10, FC:10, AE:10}", simple2->AsWeighted(10)->ToString());
}

TEST_F(test_simple, arithmetic_operations){
    auto s1 = dynamic_cast<simple_graph*>(simple1.get());
    auto s2 = dynamic_cast<simple_graph*>(simple2.get());
    auto b = dynamic_cast<bipartite_graph*>(bipart.get());
    auto c = dynamic_cast<complete_graph*>(complete.get());
    auto w = dynamic_cast<weighted_graph*>(weighted.get());
    ASSERT_EQ("SimpleGraph {EF, FA, AB, EC, FC, AE}", (*s1 + *s2).ToString());
    ASSERT_EQ("SimpleGraph {EF, FA, AB, EC, AD, AE, BD, BE, CD, ND, NE}", (*s1 + *b).ToString());
    ASSERT_EQ("SimpleGraph {EF, FC, AE, AN, AF, NF}", (*s2 + *c).ToString());
    ASSERT_THROW (*s1 + *w, std::logic_error);
    *s2 += *s1;
    ASSERT_EQ("SimpleGraph {EF, FC, AE, FA, AB, EC}", s2->ToString());
    ASSERT_EQ("SimpleGraph {}", (*s1 - *s2).ToString());
    ASSERT_EQ("SimpleGraph {EF, FC, FA, AB}", (*s2 - *b).ToString());
    ASSERT_EQ("SimpleGraph {EF, AB, EC}", (*s1 - *c).ToString());
    ASSERT_EQ("SimpleGraph {EF, FA, EC}", (*s1 - *w).ToString());
    *s1 -= *s2;
    ASSERT_EQ("SimpleGraph {}", s1->ToString());
}

TEST_F(test_weighted, basic_functions){
    ASSERT_EQ(std::vector<char>({'A','B', 'D', 'E', 'F'}), weighted1->GetVertices());
    ASSERT_EQ(std::vector<char>({'A', 'B', 'D', 'F'}), weighted2->GetVertices());
    std::vector<std::pair<char, char>> res1 {{'A', 'B'}, {'B', 'F'}, {'F', 'D'}, {'A', 'E'}, {'E', 'D'}};
    ASSERT_EQ(res1, weighted1->GetEdges());
    std::vector<std::pair<char, char>> res2 {{'A', 'B'}, {'A', 'D'}, {'B', 'F'}};
    ASSERT_EQ(res2, weighted2->GetEdges());
    ASSERT_EQ("WeightedGraph {AB:10, BF:12, FD:3, AE:15, ED:20}", weighted1->ToString());
    ASSERT_EQ("WeightedGraph {AB:10, AD:12, BF:15}", weighted2->ToString());
}

TEST_F(test_weighted, arithmetic_operations){
    auto s = dynamic_cast<simple_graph*>(simple.get());
    auto b = dynamic_cast<bipartite_graph*>(bipart.get());
    auto c = dynamic_cast<complete_graph*>(complete.get());
    auto w1 = dynamic_cast<weighted_graph*>(weighted1.get());
    auto w2 = dynamic_cast<weighted_graph*>(weighted2.get());
    ASSERT_EQ("WeightedGraph {AB:10, BF:12, FD:3, AE:15, ED:20, AD:12}", (*w1 + *w2).ToString());
    ASSERT_THROW(*w1 + *s, std::logic_error);
    ASSERT_THROW(*w1 + *b, std::logic_error);
    ASSERT_THROW(*w2 + *c, std::logic_error);
    *w1 += *w2;
    ASSERT_EQ("WeightedGraph {AB:10, BF:12, FD:3, AE:15, ED:20, AD:12}", w1->ToString());
    ASSERT_EQ("WeightedGraph {FD:3, AE:15, ED:20}", (*w1 - *w2).ToString());
    ASSERT_EQ("WeightedGraph {AB:10, BF:15}", (*w2 - *b).ToString());
    ASSERT_EQ("WeightedGraph {AB:10, BF:12, FD:3, AE:15, ED:20, AD:12}", (*w1 - *c).ToString());
    ASSERT_EQ("WeightedGraph {AB:10, BF:12, FD:3, ED:20, AD:12}", (*w1 - *s).ToString());
    *w1 -= *w2;
    ASSERT_EQ("WeightedGraph {FD:3, AE:15, ED:20}", w1->ToString());
}

TEST(find_path, all_cases){
    std::vector<std::string> weight_edg = {{"AB"}, {"AC"}, {"AF"}, {"BC"}, {"BD"}, {"CD"}, {"CF"}, {"DE"}, {"EF"}};
    std::vector<int> con_weights = {7, 9, 14, 10, 15, 11, 2, 6, 9};
    auto con_graph = TFactory().Create("weighted", std::make_unique<weighted_args>(weight_edg, con_weights));
    auto weighted_con = dynamic_cast<weighted_graph*>(con_graph.get());
    std::vector<std::pair<char, char>> path = {{'A', 'C'}, {'C', 'F'}, {'F', 'E'}};
    ASSERT_EQ(path, shortest_path(*weighted_con, 'A', 'E'));
    std::vector<std::string> v1 {{"AB"}, {"AC"}, {"AF"}, {"BC"}, {"CF"}, {"FE"}, {"CD"}, {"BD"}, {"ED"}};
    std::vector<int> w1 {7, 9, 14, 10, 2, 9, 11, 15, 6};
    auto weight1 = TFactory().Create("weighted", std::make_unique<weighted_args>(v1, w1));
    auto weighted1 = dynamic_cast<weighted_graph*>(weight1.get());
    std::vector<std::pair<char, char>> res1 {{'A', 'C'}, {'C', 'F'}, {'F', 'E'}};
    ASSERT_EQ(res1, shortest_path(*weighted1, 'A', 'E'));
    std::vector<std::string> v2 {"AB", "AC", "BC", "CE", "BD", "BE", "CD", "DE", "DG", "EG"};
    std::vector<int> w2 {2, 1, 2, 6, 4, 5, 4, 2, 6, 3};
    auto weight2 = TFactory().Create("weighted", std::make_unique<weighted_args>(v2, w2));
    auto weighted2 = dynamic_cast<weighted_graph*>(weight2.get());
    std::vector<std::pair<char, char>> res5 {{'B', 'E'}};
    ASSERT_EQ(res5, shortest_path(*weighted2, 'B', 'E'));
}