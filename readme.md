# Objective 
The goal of this project is to write a program that generates code for a given flowchart.  

# Context
Code generation from a flowchart is the process of automatically translating a flowchart diagram 
into executable code in a programming language. It is a technique commonly used in software 
development, especially in the development of graphical programming languages or visual 
programming environments.  

### Input File
Input file:
 
0 START 
1 IF expression1 
2 BLOCK statement1 
3 BLOCK statement2 
4 END 
 
0 1 
1 2 3 
2 4 
3 4 
4 
 
The first number represents the number of nodes in the flowchart. Later for each of the nodes, we 
the input file gives the type, and the expression or statement depending on the type of the node. 
This is followed by the adjacency list. Below is an explanation:  
- 0 is the START node and its out arrow goes to node 1.  
- 1 is the IF condition for which the true goes to node 2 and false flow goes to node 3. Note 
that always the first node will represent the true flow and the second node will represent 
the false flow.  
- 2 is a BLOCK that has an statement1 that flows to the END node 4.  
- 3 is a BLOCK that has an statement2 that flows to the END node 4.  
- 4 is the END node itself so there is no flow going out. 

### Running Program

Run the program by running the makefile commands:
```console
make all
make run
```