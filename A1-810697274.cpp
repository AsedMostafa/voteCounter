#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int initilizeTimeSlots(){
    int slotsNumber{0};
    cin >> slotsNumber;
    cin.ignore(10,'\n');
    return slotsNumber;
}

void getParticipantsName(vector<string>& names){
    string name;
    string nameTemp;
    getline(cin, name);
    stringstream namesList(name);
    while(namesList >> nameTemp){
        names.push_back(nameTemp);
    }
}

vector<string> getParticipantsVote(){
    string participantVote;
    vector<string> voteHolder;
    while(getline(cin, participantVote)){
        voteHolder.push_back(participantVote);
    }
    return voteHolder;
}

string getVoterName(string voteLine){
    int first = voteLine.find(":");
    string name = voteLine.substr(0, first);
    return name;
}

int findVoterNameIndex(vector<string> names, string voter){
    int position{0};
    for(string h : names){
        if(h == voter){
            break;
        }
        position++;
    }
    return position;
}

vector<int> getWhiteSpacesIndex(string timeString){
    int whiteSpace{0};
    vector<int> whiteSpaces;
    while(whiteSpace != -1){
        whiteSpace = timeString.find(" ", whiteSpace + 1);
        whiteSpaces.push_back(whiteSpace);
    }
    whiteSpaces.pop_back();
    return whiteSpaces;
}

int getTimes(string participantVote, int i){
    int counter{1};
    while(isdigit(participantVote[i - counter])){
        counter++;
    }
    return counter;
}
char getVote(string participantVote, int i){
    char voteSign = participantVote[i+1];
    return voteSign;
}

int checkSigns(char voteSign){
    if(voteSign == 'Y'){
        return 1;
    }
    else if(voteSign == 'N'){
        return -1;
    }
    return 0;
}

int getVoteTime(string participantVote, int counter, int i){
    int votedTime{0};
    string votedTimeString = participantVote.substr(i-counter + 1, counter - 1);
    votedTime = stoi(votedTimeString);
    return votedTime;
}



void putVotesInto(vector<vector<int>>& inputVotes, string participantVote, int voterIndex){
    vector<int> ws = getWhiteSpacesIndex(participantVote);
    int counter{0};
    int votedTime{0};
    char vote;
    for(int i : ws){
        counter = getTimes(participantVote, i);
        votedTime = getVoteTime(participantVote, counter, i);
        vote = getVote(participantVote, i);
        inputVotes[votedTime][voterIndex] = checkSigns(vote);
        counter = 0;
    }
}

vector<int> countLeastVotes(vector<int> countVote){//count how many of a vote is there
    vector<int> vec;
    for(int i = 0; i < countVote.size(); i++){
        int mini = *min_element(countVote.begin(), countVote.end());
        if(countVote[i] == mini){
            vec.push_back(i);
        }
    }
    return vec;
}

void printTimeSlot(int slot){
    cout << "Time slot " << "slot" <<":" << endl;
    cout << "YES: " << "yesVoter" << endl;
    cout << "--" << slot << "--" << endl;
    cout << "NO: " << "noVoter" << endl;
    cout << "IF_NECESSARY: " << "ifVoter" << endl;
    cout << "###" << endl;
}


void checkRepeatedSlot(vector<int>& vote, vector<int> printed){
    for(int i = 0; i < vote.size(); i++){
        for(int x: printed){
            if(x == vote[i]){
                vote.erase(vote.begin() + i);
            }
        }
    }

}

int main(){

    int timeSlots{0};
    vector<string> participantNames;
    vector<string> votersOpinion;

    timeSlots = initilizeTimeSlots();
    getParticipantsName(participantNames);
    votersOpinion = getParticipantsVote();
    vector<vector<int>> votes(participantNames.size(), vector<int>(timeSlots, 0));

    vector<int> ws;
    string voterName;
    int counter{0};
    int votedTime{0};
    int voterIndex{0};
    char vote;

    for(string participantVote : votersOpinion){
        voterName = getVoterName(participantVote);
        voterIndex = findVoterNameIndex(participantNames, voterName);
        putVotesInto(votes, participantVote, voterIndex);
    }

    vector<int> noVotes;
    vector<int> ifVotes;

// this calculte how many no or if on time slots
    for(int row = 0; row < votes.size(); row++){
        int tempNoVoteHolder{0};
        int tempifVoteHolder{0};
        for(int column = 0; column < votes.size(); column++){
            if(votes[row][column] == -1){
                tempNoVoteHolder++;
            }
            else if(votes[row][column] == 0){
                tempifVoteHolder++;
            }
            
        }

        noVotes.push_back(tempNoVoteHolder);
        ifVotes.push_back(tempifVoteHolder);
    }

    vector<int> leastNoVote;
    vector<int> printedSlots;
    vector<int> ifChooser;
    vector<int> whichIfIsLower;
    int loopcounter{0};


    while(loopcounter < 3){
        leastNoVote = countLeastVotes(noVotes);
        checkRepeatedSlot(leastNoVote, printedSlots);
        if(leastNoVote.size() == 1){
            printTimeSlot(leastNoVote[0]);
            printedSlots.push_back(leastNoVote[0]);
        }
        else if(leastNoVote.size() != 1) {
            for(int x: leastNoVote){
                ifChooser.push_back(ifVotes[x]);
                cout << "Is this printing? " << ifVotes[x] << endl;
            }
            if(leastNoVote.size() != 0){
                whichIfIsLower = countLeastVotes(ifChooser);
            }
            else {
                whichIfIsLower = countLeastVotes(ifVotes);
            }
            if(whichIfIsLower.size() == 1){
                for(int i = 0; i < ifVotes.size(); i++){
                    if(ifChooser[0] == ifVotes[i]){
                        printTimeSlot(i);
                        printedSlots.push_back(i);
                        checkRepeatedSlot(ifChooser, printedSlots);
                        break;
                    }
                }
            }
            else if(whichIfIsLower.size() != 1){
                cout << whichIfIsLower.size();
            }

        }
        loopcounter++;
    }
    

    for(int x:printedSlots){
        cout << " these Are printed " << x << endl;
    }

}

