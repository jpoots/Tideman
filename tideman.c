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
bool isCycle(int startingCandidate, int lockedCandidate);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] = preferences[ranks[i]][ranks[j]] + 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            int valueI = preferences[i][j];
            int valueJ = preferences[j][i];
            bool alreadyPair = false;

            if (valueI != valueJ)
            {
                for (int k = 0; k < pair_count; k++)
                {
                    if (pairs[k].winner == i && pairs[k].loser == j)
                    {
                        alreadyPair = true;
                    }

                    else if (pairs[k].winner == j && pairs[k].loser == i)
                    {
                        alreadyPair = true;
                    }
                }

                if (!alreadyPair)
                {
                    if (valueI > valueJ)
                    {
                        pairs[pair_count].winner = i;
                        pairs[pair_count].loser = j;

                    }

                    else if (valueJ > valueI)
                    {
                        pairs[pair_count].winner = j;
                        pairs[pair_count].loser = i;
                    }

                    pair_count++;
                }

            }

        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int falseCount = 0;

        pair pair1 = pairs[i];
        pair pair2 = pairs[i + 1];

        int pairDifference1 = preferences[pair1.winner][pair1.loser] - preferences[pair1.loser][pair1.winner];
        int pairDifference2 = preferences[pair2.winner][pair2.loser] - preferences[pair2.loser][pair2.winner];

        if (pairDifference1 < pairDifference2)
        {
            pairs[i] = pair2;
            pairs[i + 1] = pair1;
        }

        for (int k = 0; k < pair_count - 1; k++)
        {
            int check1 = preferences[pairs[k].winner][pairs[k].loser] - preferences[pairs[k].loser][pairs[k].winner];
            int check2 = preferences[pairs[k + 1].winner][pairs[k + 1].loser] - preferences[pairs[k + 1].loser][pairs[k + 1].winner];

            if (check1 > check2)
            {
                falseCount++;
            }
        }

        if (falseCount == 0)
        {
            return;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int k = 0; k < pair_count; k++)
    {
        int winner = pairs[k].winner;
        int loser = pairs[k].loser;
        bool cycle = false;

        if (isCycle(winner, loser))
        {
            cycle = true;
        }

        if (!cycle)
        {
            locked[winner][loser] = true; //locks
        }

    }

    return;
}


// Print the winner of the election
void print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        bool notWinner = false;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                notWinner = true;
            }
        }

        if (notWinner == false)
        {
            printf("%s\n", candidates[i]); //prints the winner
            return;
        }
    }
}

bool isCycle(int winner, int loser) //recursive function
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (locked[loser][x])
        {
            if (x == winner || isCycle(winner, x)) //checks if you've found a loop 
            {
                return true;
            }
        }
    }
    return false;
}

