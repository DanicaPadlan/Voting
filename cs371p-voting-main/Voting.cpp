#include <iostream> // cin, cout, endl
#include <vector>
#include <climits>
#include <cassert>

#include "Voting.hpp"

using namespace std;

uint num_valid_candidates = 0;

// for testing find_tie()
void set_num_valid_candidates(uint num_cand) {
    num_valid_candidates = num_cand;
}

uint find_winner(vector<Candidate>* all_candidates, uint total_ballots) {
    assert(all_candidates != nullptr);
    assert(total_ballots > 0);
    num_valid_candidates = all_candidates->size();


    vector<Candidate> winners;

    bool winnerFound = false;
    while(!winnerFound) {

        //if winner is found through by more than 50% votes
        //or all candidates tied, set winnerFound to true to stop loop
        if(find_max_cand(all_candidates, total_ballots, &winners)) {
            winnerFound = true;
        } else if (find_tie(all_candidates, total_ballots, &winners)) {
            winnerFound = true;
        } else {
            sort_loser(all_candidates);
        }
    }

    return winners.size(); //for unit testing purposes

};

//find candidate with more than 50% total votes
bool find_max_cand(vector<Candidate>* all_candidates, uint total_ballots, vector<Candidate>* winners) {
    assert(all_candidates != nullptr);
    assert(total_ballots > 0);

    uint halfVotes = total_ballots / 2;
    uint maxVotes = 0;
    Candidate maxCand = Candidate(""); //temporary Candidate object

    //loop through all candidates
    for(uint x = 0; x < all_candidates->size(); x++) {

        Candidate curCand = all_candidates->at(x);
        if(!curCand.is_loser && curCand.candidate_ballots.size() > maxVotes) {

            maxVotes = curCand.candidate_ballots.size();
            maxCand = curCand;

        }

    }

    //print out winner name if votes greater than 50%
    if(maxVotes > halfVotes) {
        winners->push_back(maxCand);
        cout << maxCand.candidate_name << "\n";
        return true;
    }
    return false;
};


//check if a tie is possible with ALL candidates
bool find_tie(vector<Candidate>* all_candidates, uint total_ballots, vector<Candidate>* winners) {

    assert(all_candidates != nullptr);
    assert(total_ballots > 0);

    // if not evenly divisible, tie not possible
    if (total_ballots % num_valid_candidates != 0) {
        return false;
    }

    uint tieVotes = total_ballots / num_valid_candidates;
    //loop through all candidates and check if all ballot vector sizes are the same as tieVotes
    for(uint x = 0; x < all_candidates->size(); x++) {

        Candidate curCand = all_candidates->at(x);

        if(!curCand.is_loser && curCand.candidate_ballots.size() != tieVotes) {
            return false;
        }
    }

    //reached to point where we know all candidates have the same number of votes
    //loop and print out all candidates in candidate list
    for (uint i = 0; i < all_candidates->size(); i++) {
        all_candidates->at(0).candidate_ballots.size();
        Candidate curCand = all_candidates->at(i);
        if (!curCand.is_loser) {
            winners->push_back(curCand);
            cout << curCand.candidate_name << "\n";
        }
    }
    return true;
};

// Returns vector of indicies for the candidates with the lowest number of votes
vector<uint> findLosers(vector<Candidate>* all_candidates) {
    assert(all_candidates != nullptr);

    vector<uint> loseIndices;
    uint minVotes = INT_MAX;

    for(uint x = 0; x < all_candidates->size(); x++) {

        Candidate curCand = all_candidates->at(x);

        //check if a candidate was already a loser and if its votes are less than minVotes
        if(!curCand.is_loser && curCand.candidate_ballots.size() < minVotes) {
            minVotes = curCand.candidate_ballots.size();

            //clear the vector and then add the new index of the new loser
            loseIndices.clear();
            loseIndices.push_back(x);

        } else if(!curCand.is_loser && curCand.candidate_ballots.size() == minVotes) {

            loseIndices.push_back(x);
        }
    }
    return loseIndices;
}

// distribute loser candidate's ballots to next preference candidate
void sort_ballots(Candidate& curCand, vector<Candidate>* all_candidates) {
    assert(all_candidates != nullptr);
    assert(curCand.candidate_ballots.size() > 0);

    for(uint x = 0; x < curCand.candidate_ballots.size(); x++) {

        Ballot* curBallot = curCand.candidate_ballots.at(x);

        //increase ballot index to look at next Candidate rank until
        //we reach a candidate that's not a loser
        curBallot->ballot_index = curBallot->ballot_index + 1;
        while(all_candidates->at(curBallot->ballot_votes.at(curBallot->ballot_index) - 1).is_loser) {
            curBallot->ballot_index = curBallot->ballot_index + 1;
        }

        Candidate& newCand = all_candidates->at(curBallot->ballot_votes.at(curBallot->ballot_index) - 1);
        newCand.candidate_ballots.push_back(curBallot);

    }
}

//find the candidate with lowest num ballots, and sort to other candidates
uint sort_loser(vector<Candidate>* all_candidates) {
    assert(all_candidates != nullptr);

    vector<uint> loserIndices = findLosers(all_candidates);
    //loop through loseIndices to add loser cands
    for(uint x = 0; x < loserIndices.size(); x++) {

        //gets loser Candidate at that index
        uint curIndex = loserIndices.at(x);
        Candidate& curCand = all_candidates->at(curIndex);
        curCand.is_loser = true;
        if (curCand.candidate_ballots.size() > 0) {
            sort_ballots(curCand, all_candidates);
        }
    }

    num_valid_candidates -= loserIndices.size();
    return num_valid_candidates;    // return num candidates for unit testing
};

