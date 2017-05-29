# Part-3: Hybrid/Meta Search Engine using Rank Aggregation

In this part, you need to combine search results (ranks) from multiple sources (say from Part-1 and Part-2) using "Scaled Footrule Rank Aggregation" method, described below. All the required information for this method are provided below. However, if you are interested, you may want to check out this presentation on "Rank aggregation method for the web".
Let T1 and T2 are search results (ranks) obtained from Part-1 and Part-2 respectively. Let's assume S is a union of T1 and T2. A weighted bipartite graph for scaled footrule optimization (C,P,W) is defined as,
C = set of nodes to be ranked
P = set of positions available
W(c,p) is the scaled-footrule distance (from T1 and T2 ) of a ranking that places element 'c' at position 'p', given by

where n is the cardinality (size) of S, |T1| is the cardinality (size) of T1, |T2| is the cardinality (size) of T2,
T1(x3) is the position of x3 in T1.

## Example
The final ranking is derived by finding possible values of position 'P' such that the scaled-footrule distance is minimum. There are many different ways to assign possible values for 'P'. In the above example P = [1, 3, 2, 5, 4]. Some other possible values are, P = [1, 2, 4, 3, 5], P = [5, 2, 1, 4, 3], P = [1, 2, 3, 4, 5], etc. For n = 5, possible alternatives are 5! For n = 10, possible alternatives would be 10! that is 3,628,800 alternatives. A very simple and obviously inefficient approach could use brute-force search and generate all possible alternatives, calculate scaled-footrule distance for each alternative, and find the alternative with minimum scaled-footrule distance. If you use such a brute-force search, you will receive maximum of 2 marks (out of 3) for Part-3. However, you will be rewarded upto 1 mark if you implement a "smart" algorithm that avoids generating unnecessary alternatives, in the process of finding the minimum scaled-footrule distance. Please document your algorithm such that your tutor can easily understand your logic, and clearly outline how you plan to reduce search space, otherwise you will not be awarded mark for your "smart" algorithm! Yes, it's only a mark, but if you try it, you will find it very challenging and rewarding.
Write a program scaledFootrule.c that aggregates ranks from files given as commandline arguments, and output aggregated rank list with minimum scaled footrule distance.

[More Information](https://www.cse.unsw.edu.au/~cs1927/17s1/ass/ass02/Ass2.html)
