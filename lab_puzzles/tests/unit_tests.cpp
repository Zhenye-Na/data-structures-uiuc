#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "catchlib.h"

#include "../anagram_dict.h"
#include "../fib.h"
#include "../cartalk_puzzle.h"
#include "../pronounce_dict.h"
#include "../common_words.h"

#include <sstream>
#include <algorithm>
#include <utility>
#include <string>
#include <set>

using namespace std;

static vector< unsigned int > fib_results = 
{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584,
  4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811 };
                               

static vector< string > words = 
{ "dog", "god", "good", "super", "cow", "powers", "skin", "kins" };

static map< string, vector< string > > pronunciations = 
                            { { "SCENT", { "DUMMY" } }, 
                              { "CENT", { "DUMMY" } },
                              { "SENT", { "DUMMY" } },
                              { "DOG", { "DOGE" } }
                            };

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


TEST_CASE("test_get_anagrams", "[weight=15]")
{
    AnagramDict d(words);
    const vector< string > canon = { "dog", "god" };
    vector< string > result = d.get_anagrams("dog");
    REQUIRE(canon == result);
    REQUIRE(d.get_anagrams("z").empty());
}



TEST_CASE("test_get_all_anagrams", "[weight=15]")
{
    AnagramDict d(words);
    set< set< string > > canon = { { "dog", "god" }, { "skin", "kins" } };
    vector< vector< string > > result = d.get_all_anagrams();
    /* We want to be agnostic to all orderings. */
    set< set< string > > result_set;
    for(auto& anagram_vec : result)
    {
        /* Has to be insert because GCC 4.7 didn't implemet emplace for set. */
        set< string > s(anagram_vec.begin(), anagram_vec.end());
        result_set.insert(s);
    }
    REQUIRE(canon == result_set);
}



TEST_CASE("test_fib", "[weight=10]")
{
    for(size_t i = 0; i < 6; i ++)
    {
        REQUIRE(fib(i) == fib_results[i]);
    }
}



TEST_CASE("test_memoized_fib", "[weight=10]")
{
    for(int i = 0; i < 10; i ++)
    {
        REQUIRE(memoized_fib(28) == fib_results[28]);
    }
}
 


TEST_CASE("test_homophones", "[weight=10]")
{
    PronounceDict d(pronunciations);
    REQUIRE(d.homophones("scent", "CeNt"));
    REQUIRE((! d.homophones("scent", "DOG")));
    REQUIRE((! d.homophones("garbage", "Tim")));
}


TEST_CASE("test_cartalk_puzzle", "[weight=10]")
{
    PronounceDict d(pronunciations);
    vector< string > canon = {"scent", "cent", "sent"};
    auto result = cartalk_puzzle(d, "cartalk_words.txt");
    REQUIRE(result.size() == 1);
    vector< string > result_vec = { get<0>(result[0]),
                                    get<1>(result[0]),
                                    get<2>(result[0]) };
    REQUIRE(is_permutation(canon.begin(), canon.end(), result_vec.begin()));
}


TEST_CASE("test_get_common_words_3", "[weight=15]")
{
    vector<string> in;
    in.push_back("small1.txt");
    in.push_back("small2.txt");
    CommonWords cw(in);
    vector<string> students = cw.get_common_words(3);
	vector<string> canon = {"dog", "pig"};
    REQUIRE(canon == students);
}

TEST_CASE("test_get_common_words_999", "[weight=15]")
{
    vector<string> in;
    in.push_back("small1.txt");
    in.push_back("small2.txt");
    CommonWords cw(in);
    vector<string> students = cw.get_common_words(999);
	vector<string> canon = {};
    REQUIRE(canon == students);

	in.clear();
    in.push_back("PrideAndPrejudice.txt");
    in.push_back("Beowulf.txt");
    cw = CommonWords(in);
    students = cw.get_common_words(999);
	canon = {"of", "the"};

    REQUIRE(canon == students);

}


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
///////////////////////// End of Tests /////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    srand(time(NULL));

    // put our beloved quotes
    //print_quote("tests/quotes.txt");

    // easier than prepending tests/ to all paths above
    chdir("tests");

    int result = Catch::Session().run(argc, argv);

    return (result < 0xFF ? result : 0xFF);
}
