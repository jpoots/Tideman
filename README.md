# CS50x Project 3
## Tideman
### About
This project is an implementation of the Tideman voting system in C. It makes use of a sorting algorithm and recursion. I produced this in the early stages of learning to program. Starter code for this project was obtained from https://cdn.cs50.net/2021/fall/psets/3/tideman.zip.

Descriptions of the functions completed as part of the project have been obtained from the project website. Further details of the project can be found at https://cdn.cs50.net/2021/fall/psets/3/tideman.zip.

#### vote
This function takes arguments rank, name, and ranks. If name is a match for the name of a valid candidate, then it will update the ranks array to indicate that the voter has the candidate as their rank preference (where 0 is the first preference, 1 is the second preference, etc.)

The function will return true if the rank was successfully recorded, and false otherwise (if, for instance, name is not the name of one of the candidates). This project assumes that no two candidates will have the same name.

#### record_preferences
This function is called once for each voter, and takes as argument the ranks array.

The function will update the global preferences array to add the current voter’s preferences. This project assumes that every voter will rank each of the candidates.

#### add_pairs
This function adds all pairs of candidates where one candidate is preferred to the pairs array. A pair of candidates who are tied (one is not preferred over the other) will not be added to the array.

The function will update the global variable pair_count to be the number of pairs of candidates.

#### sort_pairs
This function will sort the pairs array in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.

#### lock_pairs 
This function will create the locked graph, adding all edges in decreasing order of victory strength so long as the edge would not create a cycle.

#### print_winner 
This function will print out the name of the candidate who is the source of the graph. This project assumes there will not be more than one source.
