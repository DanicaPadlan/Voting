#include "gtest/gtest.h"
#include <vector>
#include <string>

#include "Voting.hpp"

using namespace std;


//make list of candidates and ballots into textfile
//

//copy code from run voting in here and give a certain file

//4 or 5 tests per method


Ballot ballot1 = Ballot("1 2 3 4");
Ballot ballot2 = Ballot("2 1 3 4");
Ballot ballot3 = Ballot("3 2 4 1");
Ballot ballot4 = Ballot("4 3 1 2");

vector<Candidate> all_candidates;
vector<Candidate> winners;

Candidate cand1("A");


Candidate cand2 = Candidate("B");
//cand2.candidate_ballots.push_back(&ballot2);

Candidate cand3 = Candidate("C");
//cand3.candidate_ballots.push_back(&ballot3);

Candidate cand4 = Candidate("D");
//cand4.candidate_ballots.push_back(&ballot4);

//find_max_cand() tests
//testing out only one candidate in list
TEST(VotingFixture, find_max_cand_0) {

    cand1.candidate_ballots.push_back(&ballot1);
    all_candidates.push_back(cand1);


    ASSERT_EQ(find_max_cand(&all_candidates, 1, &winners), true);

    cand1.candidate_ballots.clear();
    all_candidates.clear();
}

//tied candidates, no max
TEST(VotingFixture, find_max_cand_1) {


    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    ASSERT_EQ(find_max_cand(&all_candidates, 2, &winners), false);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
}

//2 candidates where B has maxVotes
TEST(VotingFixture, find_max_cand_2) {


    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    ASSERT_EQ(find_max_cand(&all_candidates, 2, &winners), true);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
}

//testing all candidates tied
TEST(VotingFixture, find_max_cand_3) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    //testing out only one candidate in list
    ASSERT_EQ(find_max_cand(&all_candidates, 8, &winners), false);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
}


//reuse data to next tie test
//4 candidates, tie between A and C, B and D are losers
TEST(VotingFixture, find_max_cand_4) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    //testing out only one candidate in list
    ASSERT_EQ(find_max_cand(&all_candidates, 6, &winners), false);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
}

//find_tie()

// one candidate is both a tie and a win because it ties with itself
// this case would never actually be reached, because a winner would be declared first
TEST(VotingFixture, find_tie_0) {
    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    all_candidates.push_back(cand1);
    set_num_valid_candidates(all_candidates.size());

    ASSERT_EQ(find_tie(&all_candidates, 2, &winners), true);

    cand1.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

// is a tie between two cands
TEST(VotingFixture, find_tie_1) {


    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    set_num_valid_candidates(all_candidates.size());
    ASSERT_EQ(find_tie(&all_candidates, 2, &winners), true);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

// multiple candidates, no tie
TEST(VotingFixture, find_tie_2) {


    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    set_num_valid_candidates(all_candidates.size());

    ASSERT_EQ(find_tie(&all_candidates, 2, &winners), false);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//testing all candidates tied
TEST(VotingFixture, find_tie_3) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    set_num_valid_candidates(all_candidates.size());
    //testing out only one candidate in list
    ASSERT_EQ(find_tie(&all_candidates, 8, &winners), true);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//4 candidates, tie between A and C, B and D are losers
TEST(VotingFixture, find_tie_4) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    set_num_valid_candidates(all_candidates.size());
    //testing out only one candidate in list
    ASSERT_EQ(find_tie(&all_candidates, 6, &winners), false);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//findLosers()

//would never get to this case bc found max or tied candidate before this is called
//1 candidate, its loser is itself
TEST(VotingFixture, find_losers_0) {

    cand1.candidate_ballots.push_back(&ballot1);
    all_candidates.push_back(cand1);

    ASSERT_EQ(findLosers(&all_candidates).size(), 1);

    cand1.candidate_ballots.clear();
    all_candidates.clear();
}

//would never get to this case bc found max or tied candidate before this is called
//tied candidates, 2 losers
TEST(VotingFixture, find_losers_1) {


    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    ASSERT_EQ(findLosers(&all_candidates).size(), 2);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
}

//2 candidates with one loser
TEST(VotingFixture, find_losers_2) {


    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    ASSERT_EQ(findLosers(&all_candidates).size(), 1);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
}

//4 candidates, 2 losers
TEST(VotingFixture, find_losers_3) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    //testing out only one candidate in list
    ASSERT_EQ(findLosers(&all_candidates).size(), 2);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
}

//sort_loser()

//2 candidates with one loser
TEST(VotingFixture, sort_losers_0) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    set_num_valid_candidates(all_candidates.size());
    ASSERT_EQ(sort_loser(&all_candidates), 1);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//4 candidates, 2 losers
TEST(VotingFixture, sort_losers_1) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    set_num_valid_candidates(all_candidates.size());
    ASSERT_EQ(sort_loser(&all_candidates), 2);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//come back to test later!!!
Ballot temp2("2 1 3 4");
Ballot temp3("3 2 4 1");
Ballot temp4("4 3 1 2");

//TODO what is this test
//3 losers, 1 winner
TEST(VotingFixture, sort_losers_2) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&temp2);
    cand3.candidate_ballots.push_back(&temp3);
    cand4.candidate_ballots.push_back(&temp4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    set_num_valid_candidates(all_candidates.size());
    ASSERT_EQ(sort_loser(&all_candidates), 1u);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//2 candidates with one loser
TEST(VotingFixture, sort_losers_3) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    cand3.candidate_ballots.push_back(&ballot3);
    cand4.candidate_ballots.push_back(&ballot4);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    set_num_valid_candidates(all_candidates.size());
    ASSERT_EQ(sort_loser(&all_candidates), 2);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
    set_num_valid_candidates(0);
}

//find_winner()

//immediately findMax
TEST(VotingFixture, find_winner_0) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    ASSERT_EQ(find_winner(&all_candidates, 3), 1);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
}

//immediately find_tie
TEST(VotingFixture, find_winner_1) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&ballot2);
    cand2.candidate_ballots.push_back(&ballot2);
    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);

    ASSERT_EQ(find_winner(&all_candidates, 4), 2);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    all_candidates.clear();
}

Ballot temp2_2("2 1 3 4");
Ballot temp3_2("3 2 4 1");
Ballot temp4_2("4 3 1 2");

//sort_loser then findMax
TEST(VotingFixture, find_winner_2) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&temp2_2);
    cand3.candidate_ballots.push_back(&temp3_2);
    cand4.candidate_ballots.push_back(&temp4_2);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    ASSERT_EQ(find_winner(&all_candidates, 5), 1);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
}

Ballot temp2_3("2 1 3 4");
Ballot temp3_3("3 2 4 1");
Ballot temp4_3("4 3 1 2");
//sort_loser, find_tie
TEST(VotingFixture, find_winner_3) {

    cand1.candidate_ballots.push_back(&ballot1);
    cand1.candidate_ballots.push_back(&ballot1);
    cand2.candidate_ballots.push_back(&temp2_3);
    cand3.candidate_ballots.push_back(&temp3_3);
    cand3.candidate_ballots.push_back(&temp3_3);
    cand4.candidate_ballots.push_back(&temp4_3);

    all_candidates.push_back(cand1);
    all_candidates.push_back(cand2);
    all_candidates.push_back(cand3);
    all_candidates.push_back(cand4);

    //testing out only one candidate in list
    ASSERT_EQ(find_winner(&all_candidates, 6), 2);

    cand1.candidate_ballots.clear();
    cand2.candidate_ballots.clear();
    cand3.candidate_ballots.clear();
    cand4.candidate_ballots.clear();
    all_candidates.clear();
}
