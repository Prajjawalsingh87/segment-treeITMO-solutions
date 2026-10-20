# Segment Tree ITMO Solutions

[![Build](https://github.com/Prajjawalsingh87/segment-treeITMO-solutions/actions/workflows/build.yml/badge.svg)](https://github.com/Prajjawalsingh87/segment-treeITMO-solutions/actions/workflows/build.yml)

My C++ solutions to the segment tree lessons of the [ITMO Academy: pilot course](https://codeforces.com/edu/course/2) on Codeforces, plus related segment tree practice from CSES and a few contest problems (Codeforces, AtCoder).

Each solution is one self-contained `.cpp` file that reads stdin and writes stdout.

## Repository layout

```text
segment-treeITMO-solutions/
├── itmo-segment-tree-part1/     # ITMO "Segment Tree, part 1" (lesson 4), steps 1-4
├── itmo-segment-tree-part2/     # ITMO "Segment Tree, part 2" (lesson 5), steps 1-2 (mass operations)
├── cses/                        # CSES Problem Set, range queries
├── codeforces/                  # Codeforces contest problems, one folder per round
├── atcoder/                     # AtCoder contest problems, one folder per contest
└── .github/workflows/build.yml  # CI: compiles every .cpp file
```

## Build and run

You need `g++` with C++17 support. The solutions include `<bits/stdc++.h>`, and one uses GNU `pb_ds`, so use GCC (on macOS, install it with Homebrew; Apple clang won't work).

```bash
mkdir -p build
g++ -std=c++17 -O2 -Wall itmo-segment-tree-part1/step2/B_K_th_one.cpp -o build/B_K_th_one
./build/B_K_th_one < input.txt
```

To compile everything (CI does the same):

```bash
mkdir -p build
failed=0
while read -r f; do
  g++ -std=c++17 -O2 -Wall "$f" -o "build/$(basename "$f" .cpp)" || { echo "FAILED: $f"; failed=1; }
done < <(find . -name '*.cpp' -not -path './.git/*')
[ "$failed" -eq 0 ]
```

`build/` and `*.out` are git-ignored.

## ITMO Academy: Segment Tree, part 1

Course page: <https://codeforces.com/edu/course/2/lesson/4>

| Step | Problem | Solution | Key idea |
|---|---|---|---|
| 1 | C. Number of Minimums on a Segment | [C_Number_of_Minimums_on_a_Segment.cpp](itmo-segment-tree-part1/step1/C_Number_of_Minimums_on_a_Segment.cpp) | Each node stores (min, count of min); the merge adds the counts when the minimums are equal |
| 2 | A. Segment with the Maximum Sum | [A_Segment_with_the_Maximum_Sum.cpp](itmo-segment-tree-part1/step2/A_Segment_with_the_Maximum_Sum.cpp) | Each node stores (sum, best prefix, best suffix, best segment) |
| 2 | B. K-th one | [B_K_th_one.cpp](itmo-segment-tree-part1/step2/B_K_th_one.cpp) | Each node counts its ones; walk down the tree to find the k-th one |
| 2 | C. First element at least X | [C_First_element_at_least_X.cpp](itmo-segment-tree-part1/step2/C_First_element_at_least_X.cpp) | Max tree; go left first and stop at the first leaf with value >= x |
| 2 | D. First element at least X - 2 | [D_First_element_at_least_X_2.cpp](itmo-segment-tree-part1/step2/D_First_element_at_least_X_2.cpp) | The same walk, limited to indices >= l, skipping subtrees whose max is < x |
| 3 | A. Inversions | [A_Inversions.cpp](itmo-segment-tree-part1/step3/A_Inversions.cpp) | Mark each value as it is seen; count the marked values greater than a[i] |
| 3 | B. Inversions 2 | [B_Inversions_2.cpp](itmo-segment-tree-part1/step3/B_Inversions_2.cpp) | Rebuild the permutation from right to left by taking the k-th largest unused value |
| 3 | C. Nested Segments | [C_Nested_Segments.cpp](itmo-segment-tree-part1/step3/C_Nested_Segments.cpp) | When a segment closes, count the segments that already closed inside it |
| 3 | D. Intersecting Segments | [D_Intersecting_Segments.cpp](itmo-segment-tree-part1/step3/D_Intersecting_Segments.cpp) | Count the open segments between the two endpoints, in a forward pass and a reverse pass |
| 3 | E. Addition to Segment | [E_Addition_to_Segment.cpp](itmo-segment-tree-part1/step3/E_Addition_to_Segment.cpp) | Range add on covering nodes; a point query sums the root-to-leaf path |
| 4 | A. Sign alternation | [A_Sign_alternation.cpp](itmo-segment-tree-part1/step4/A_Sign_alternation.cpp) | Separate sum trees for even and odd indices; subtract one from the other based on the parity of l |
| 4 | B. Cryptography | [B_Cryptography.cpp](itmo-segment-tree-part1/step4/B_Cryptography.cpp) | Tree of 2x2 matrices; the merge is an ordered (non-commutative) matrix product mod r |
| 4 | C. Number of Inversions on Segment | [C_Number_of_Inversions_on_Segment.cpp](itmo-segment-tree-part1/step4/C_Number_of_Inversions_on_Segment.cpp) | Each node stores value counts (1..40) and an inversion count; the merge adds the cross inversions |
| 4 | D. Number of Different on Segment | [D_Number_of_Different_on_Segment.cpp](itmo-segment-tree-part1/step4/D_Number_of_Different_on_Segment.cpp) | Each node stores a bitmask of the values present (1..40); merge with OR, answer with popcount |
| 4 | E. Earthquakes | [E_Earthquakes.cpp](itmo-segment-tree-part1/step4/E_Earthquakes.cpp) | Min tree; descend into every subtree whose min is <= p and destroy those leaves |

## ITMO Academy: Segment Tree, part 2 (mass operations)

Course page: <https://codeforces.com/edu/course/2/lesson/5>

| Step | Problem | Solution | Key idea |
|---|---|---|---|
| 1 | A. Addition to Segment | [A_Addition_to_Segment.cpp](itmo-segment-tree-part2/step1/A_Addition_to_Segment.cpp) | Range add without pushing down; a point query sums the adds on the root-to-leaf path |
| 1 | B. Applying MAX to Segment | [B_Applying_MAX_to_Segment.cpp](itmo-segment-tree-part2/step1/B_Applying_MAX_to_Segment.cpp) | Range chmax; a point query takes the max of the values on the root-to-leaf path |
| 1 | C. Assignment to Segment | [C_Assignment_to_Segment.cpp](itmo-segment-tree-part2/step1/C_Assignment_to_Segment.cpp) | Range assignment with lazy push-down, because assignment does not commute |
| 2 | A. Addition and Minimum | [A_Addition_and_Minimum.cpp](itmo-segment-tree-part2/step2/A_Addition_and_Minimum.cpp) | Lazy range add with range min |
| 2 | B. Multiplication and Sum | [B_Multiplication_and_Sum.cpp](itmo-segment-tree-part2/step2/B_Multiplication_and_Sum.cpp) | Lazy range multiply with range sum, mod 1e9+7 |
| 2 | C. Bitwise OR and AND | [C_Bitwise_OR_and_AND.cpp](itmo-segment-tree-part2/step2/C_Bitwise_OR_and_AND.cpp) | Lazy range OR with range AND |
| 2 | D. Addition and Sum | [D_Addition_and_Sum.cpp](itmo-segment-tree-part2/step2/D_Addition_and_Sum.cpp) | Lazy range add with range sum (a node adds v times its length) |
| 2 | E. Assignment and Minimum | [E_Assignment_and_Minimum.cpp](itmo-segment-tree-part2/step2/E_Assignment_and_Minimum.cpp) | Lazy range assignment with range min |
| 2 | F. Assignment and Sum | [F_Assignment_and_Sum.cpp](itmo-segment-tree-part2/step2/F_Assignment_and_Sum.cpp) | Lazy range assignment with range sum (a node's sum becomes v times its length) |

## CSES Problem Set (range queries)

| Problem | Solution | Key idea |
|---|---|---|
| [1646 Static Range Sum Queries](https://cses.fi/problemset/task/1646) | [Static_Range_Sum_Queries.cpp](cses/Static_Range_Sum_Queries.cpp) | Prefix sums |
| [1647 Static Range Minimum Queries](https://cses.fi/problemset/task/1647) | [Static_Range_Minimum_Queries.cpp](cses/Static_Range_Minimum_Queries.cpp) | Min segment tree |
| [1648 Dynamic Range Sum Queries](https://cses.fi/problemset/task/1648) | [Dynamic_Range_Sum_Queries.cpp](cses/Dynamic_Range_Sum_Queries.cpp) | Sum segment tree with point updates |
| [1649 Dynamic Range Minimum Queries](https://cses.fi/problemset/task/1649) | [Dynamic_Range_Minimum_Queries.cpp](cses/Dynamic_Range_Minimum_Queries.cpp) | Min segment tree with point updates |
| [1749 List Removals](https://cses.fi/problemset/task/1749) | [List_Removals.cpp](cses/List_Removals.cpp) | Each node counts the remaining elements; find the k-th one and remove it |

## Other contest problems

I solved these alongside the course and keep them here for reference.

| Contest | Problem | Solution | Key idea |
|---|---|---|---|
| [Codeforces Round 1095 (Div. 2)](https://codeforces.com/contest/2226) | G. Stop Spot | [G_Stop_Spot.cpp](codeforces/round-1095-div2/G_Stop_Spot.cpp) | Not solved yet (template only) |
| [Codeforces Round 1096 (Div. 3)](https://codeforces.com/contest/2227) | A. Koshary | [A_Koshary.cpp](codeforces/round-1096-div3/A_Koshary.cpp) | Parity check |
| | B. Party Monster | [B_Party_Monster.cpp](codeforces/round-1096-div3/B_Party_Monster.cpp) | Compare the counts of `(` and `)` |
| | C. Snowfall | [C_Snowfall.cpp](codeforces/round-1096-div3/C_Snowfall.cpp) | Group the values by divisibility by 6, 2 and 3, then arrange the groups |
| | D. Palindromex | [D_Palindromex.cpp](codeforces/round-1096-div3/D_Palindromex.cpp) | Expand palindromes around the zeros and keep the best MEX |
| [Codeforces Round 1098 (Div. 2)](https://codeforces.com/contest/2228) | A. Marisa Steals Reimu's Takeout | [A_Marisa_Steals_Reimu_s_Takeout.cpp](codeforces/round-1098-div2/A_Marisa_Steals_Reimu_s_Takeout.cpp) | Count the 0s, 1s and 2s; pair 1s with 2s and group the leftovers in threes |
| | B. Remilia Plays Soku | [B_Remilia_Plays_Soku.cpp](codeforces/round-1098-div2/B_Remilia_Plays_Soku.cpp) | Circular distance `min(d, n - d)` plus k |
| | C1. Cirno and Number (Easy) | [C_1_Cirno_and_Number_Easy_Version.cpp](codeforces/round-1098-div2/C_1_Cirno_and_Number_Easy_Version.cpp) | Generate every pattern of 1s and 2s, then binary search the unimodal distance |
| | C2. Cirno and Number (Hard) | [C_2_Cirno_and_Number_Hard_Version.cpp](codeforces/round-1098-div2/C_2_Cirno_and_Number_Hard_Version.cpp) | Binary search over the k-th number of each candidate length |
| [Educational Round 190](https://codeforces.com/contest/2230) | A. Optimal Purchase | [A_Optimal_Purchase.cpp](codeforces/edu-round-190/A_Optimal_Purchase.cpp) | Compare single-item pricing with bundles of 3 |
| | B. Digit String | [B_Digit_String.cpp](codeforces/edu-round-190/B_Digit_String.cpp) | Prefix and suffix counts to choose the best split point |
| [AtCoder ABC 459](https://atcoder.jp/contests/abc459) | A. Hell, World! | [A_Hell_World.cpp](atcoder/abc459/A_Hell_World.cpp) | Print `HelloWorld` without its n-th character |
| | B | [B_Phone_Keypad.cpp](atcoder/abc459/B_Phone_Keypad.cpp) | Map first letters to phone keypad digits |
| | C. Drop Blocks | [C_Drop_Blocks.cpp](atcoder/abc459/C_Drop_Blocks.cpp) | Ordered set (GNU `pb_ds`) for rank queries |
| | D. Adjacent Distinct String | [D_Adjacent_Distinct_String.cpp](atcoder/abc459/D_Adjacent_Distinct_String.cpp) | Greedy rearrangement so that no two neighbours are equal |
| | E. Select from Subtrees | [E_Select_from_Subtrees.cpp](atcoder/abc459/E_Select_from_Subtrees.cpp) | Tree DP with combinatorics |

## Segment tree complexity

| Operation | Complexity |
|---|---|
| Build | O(n) |
| Point update | O(log n) |
| Range query | O(log n) |
| Range update with lazy propagation | O(log n) |
| Tree walk (k-th one, first element >= x) | O(log n) |

## Author

Prajjawal Singh: <https://github.com/Prajjawalsingh87>


## One-command local verification

Run `python3 scripts/build.py` from any directory. Requires Python 3 and GCC with
C++17 support. Set `CXX` to choose another GCC executable. Binaries keep their
source directory structure under `build/`, so exercises with the same filename
do not overwrite one another. Partial examples without `main` compile to objects.
The command compiles examples; it does not run programs that may wait for stdin.

These are native C++ exercises, not web applications; Vercel hosting is not applicable.
