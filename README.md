# n_puzzle
A program designed to solve the classic N-Puzzle using an A* Algorithm. The A* is not a SMA* (Simplified Memory Bounded A*) or IDA* (Iterative deepening A*).

To use the puzzle genorator:
```
python generator.py [-su] size
```
'Size' will be the dimension of the puzzle (0 - 8, size = 3)

To compile and run
```
make
./n_puzzle start_puzzle goal_puzzle
```

A solution to a size 3 puzzle is given in the tests directory
