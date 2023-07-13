// --------------
// RunVoting.cpp
// --------------

// --------
// includes
// --------

#include <iostream> // cin, cout, endl
#include <vector>

#include "Voting.hpp"

using namespace std;

// ----
// main
// ----

int main () {

    unsigned num_test, num_cand;

    cin >> num_test;

    for (uint cur_test = 1; cur_test <= num_test; ++cur_test) {
        cin >> num_cand;
        string skip_line;
        getline(cin, skip_line); // gets past \n of numCand (prev line)
        //intialize vector list of Candidates
        vector<Candidate> all_candidates;


        for(uint i = 0; i < num_cand; ++i) {
            string name;
            getline(cin, name);
            Candidate temp = Candidate(name);
            all_candidates.push_back(temp);

        }


        // start reading ballots
        string ballot_line;
        vector<Ballot> all_ballots;
        bool stop_reading = false;
        while (!stop_reading) {
            getline(cin, ballot_line);
            if (ballot_line.empty()) {
                stop_reading = true;
            } else {
                //passing in string and loading vector in constructor
                Ballot ballot = Ballot(ballot_line);
                all_ballots.push_back(ballot);

                if (cin.eof()) {
                    stop_reading = true;
                }
            }
        }

        // Assigning Ballots to respective candidate
        for (uint x = 0; x < all_ballots.size(); x++) {
            Ballot b_now = all_ballots.at(x);
            uint first_chocie = b_now.ballot_votes.at(0);
            all_candidates.at(first_chocie-1).candidate_ballots.push_back(&all_ballots.at(x));
        }

        find_winner(&all_candidates, all_ballots.size());

        //only print new line between tests that are not the last one
        if(cur_test != num_test){
            cout << "\n"; //extra new line is being printed
        }
        
    }

    return 0;
}

