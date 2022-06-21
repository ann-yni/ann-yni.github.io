// tideman.c tabulates the winner of a tideman election implementing a recursive loop. For specifications, visit: https://cs50.harvard.edu/x/2022/psets/3/tideman/


#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_lock(int winner, int loser);
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        //compare vote to candidate name in index
        if (strcmp(name, candidates[candidate]) == 0)
        {
            //assign rank to candidate
            ranks[rank] = candidate;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    //compare two candidates
    for (int rank1 = 0; rank1 < candidate_count; rank1++)
    {
        int candidate1 = ranks[rank1];
        for (int rank2 = rank1 + 1; rank2 < candidate_count; rank2++)
        {
            //compare relative ranks and update preferences array
            int candidate2 = ranks[rank2];
            if (rank1 < rank2)
            {
                preferences[candidate1][candidate2]++;
            }
            else if (rank1 > rank2)
            {
                preferences[candidate2][candidate1]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    //compare two candidates
    for (int candidate1 = 0; candidate1 < candidate_count; candidate1++)
    {
        for (int candidate2 = candidate1 + 1; candidate2 < candidate_count; candidate2++)
        {
            //store pairs in pairs array
            if (preferences[candidate1][candidate2] > preferences[candidate2][candidate1])
            {
                pairs[pair_count].winner = candidate1;
                pairs[pair_count].loser = candidate2;
                pair_count++;
            }
            else if (preferences[candidate1][candidate2] < preferences[candidate2][candidate1])
            {
                pairs[pair_count].winner = candidate2;
                pairs[pair_count].loser = candidate1;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //bubble sort pairs array
    for (int compare = 0; compare < pair_count - 1; compare++)
    {
        for (int pair = 0; pair < pair_count - compare - 1; pair++)
        {
            if (preferences[pairs[pair].winner][pairs[pair].loser] < preferences[pairs[pair + 1].winner][pairs[pair + 1].loser])
            {
                int winner = pairs[pair].winner;
                int loser = pairs[pair].loser;
                pairs[pair] = pairs[pair + 1];
                pairs[pair + 1].winner = winner;
                pairs[pair + 1].loser = loser;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // draw edges of tideman graph
    for (int pair = 0; pair < pair_count; pair++)
    {
        //use check_lock function to see if edge can be drawn
        if (check_lock(pairs[pair].winner, pairs[pair].loser) == true)
        {
            locked[pairs[pair].winner][pairs[pair].loser] = true;
        }
        else
        {
            locked[pairs[pair].winner][pairs[pair].loser] = false;
        }
    }
    return;
}

// Recursive check to see if any cycles are made by edges
bool check_lock(int winner, int loser)
{
    //base case
    if (loser == winner)
    {
        return false;
    }
    bool result = true;
    //check if cycle is made
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true)
        {
            if (check_lock(winner, i) == false)
            {
                result = false;
            }
        }
    }
    return result;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int winner;
    //check each candidate against other candidates to check existing edges
    for (int candidate1 = 0; candidate1 < candidate_count; candidate1++)
    {
        for (int candidate2 = 0; candidate2 < candidate_count; candidate2++)
        {
            //stop checking remaining candidates if any one edge points to candidate1
            if (locked[candidate2][candidate1] == true)
            {
                break;
            }
            //if no edges point to candidate1, candidate1 is winner
            if (locked[candidate2][candidate1] == false)
            {
                winner = candidate1;
            }
        }
    }
    //print winner
    printf("%s\n", candidates[winner]);
    return;
}
