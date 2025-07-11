# Programming Assignment 1: Integer Sum and Average Calculation

## Team Information
1. Team members: Kip Schetnan, Richard Sartell
2. x500: schet076, sarte016
3. Division of tasks: Richard has worked on child.c. Kip has worked on calculator.c/.h. In phase 2, both of us worked across both files as needed.
4. Lab machine used: Richard - Linux Mint PC & laptop, Kip - login01

## Design Specifications
calculator.c: Recurses input directory, spawns children to read file data, pipes the children's findings, uses overall findings for final print results.

child.c: Reads values from each file found by children, send findings back.

### Phase 1 Design
- Process creation strategy: Parent program reads files.
- File handling approach: Uses fopen/fscanf to examine file contents
- Results storage method: Create .results file for storing values (didn't work, however)

### Phase 2 Design
- Pipe communication strategy: For each file, calls fork() and pipe(). Child writes to parent.
- Data transmission format: Two writes for count, sum.
- Synchronization approach: Given pipe nature, no synchronization/critical sections were used to get a functioning result.

## Challenges Faced
Challenges: most notably, correcting handling of the test1 situation (absence of a file). File recursion also sucked.

## AI Tools Usage
(Richard) ChatGPT o3: Use as a reference for function arguments (ex: "function definition for fopen"). Also used GPT to help me organize my thoughts to complete this README.

## Additional Notes
N/A.
