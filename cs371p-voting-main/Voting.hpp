// -----------
// Voting.hpp
// -----------

#ifndef Voting_hpp
#define Voting_hpp

#include <vector>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

struct Ballot {
    int ballot_index;
    vector<int> ballot_votes;

    Ballot(string ballot_vals) {
        ballot_index = 0;

        istringstream is (ballot_vals);
        ballot_votes.assign( (istream_iterator<int>( is ) ), (istream_iterator<int>()) );

    }
};

struct Candidate {
    vector<Ballot*> candidate_ballots;
    string candidate_name;
    bool is_loser;

    Candidate(string name) {
        candidate_name = name;
        is_loser = false;
    }
};

// for testing purposes
void set_num_valid_candidates(uint num_cand);

uint find_winner(vector<Candidate>* all_candidates, uint total_ballots);

//Xfind candidate with more than 50% total votes
bool find_max_cand(vector<Candidate>* all_candidates, uint total_ballots, vector<Candidate>* winners);

//Xcheck if a tie is possible with ALL candidates
bool find_tie(vector<Candidate>* all_candidates, uint total_ballots, vector<Candidate>* winners);

//find the candidate with lowest num ballots, and sort to other candidates
uint sort_loser(vector<Candidate>* all_candidates);

//XReturns vector of indicies for the candidates with the lowest number of votes
vector<uint> findLosers(vector<Candidate>* all_candidates);

// distribute loser candidate's ballots to next preference candidate
void sort_ballots(Candidate& curCand, vector<Candidate>* all_candidates);

#endif // Voting_hpp
