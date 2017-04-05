% CSCI 310 - Logic Assignment (using Prolog)
% Author: Jordan Rosenberg
% 2/25/2017
% --------------------------------------

% Function: hlbackwards
% Description: Takes a list as input, and returns a list in which the elements of the toplevel list are in reverse order
hlbackwards([],[]). 
hlbackwards([H|T],R):-
    hlbackwards(T,RevT),
    append(RevT,[H],R).
% --------------------------

% Function: llbackwards
% Description: Takes a list as input, and returns a list in which every list and sublist is in reverse order.
llbackwards([], []) :- !. % "!" to exclude choices left because of the last statement.
llbackwards([H|T], X) :-
    !,
    llbackwards(H, NewH),
    llbackwards(T, NewT),
    append(NewT, [NewH], X).

llbackwards(X, X).
% --------------------------         

% Function: palindrome
% Description: Takes a list as input and returns the list if the list is a palindrome, 
% ie reads the same in both directions, and otherwise returns the original list made into a 
% palindrome by reversing it and appending it to itself, but not replicating the last element.
cdr([_|Y],Y).
palindrome([]).
palindrome(L,L):- llbackwards(L,L).
palindrome(L,R):- 
    llbackwards(L,Revlist),
    cdr(Revlist,CDRRevlist),
    append(L,CDRRevlist,R),
    L\=CDRRevlist.
% --------------------------

% Function: permutations
% Description: Takes a list as input and generates a list containing all possible permutations of the list elements
permutations(L,X) :-
  % Built in 'findall' predicate that collects all the solutions to a query and put them in a single list
  % X is the result
  % L is the passed in list
  % R is the collected solutions added to resulting X
  findall(R, perm(L, R), X).

perm([], []).
perm([X], [X]) :-!. % "!" to exclude choices left because of the last statement.
perm([T|H], X) :- 
    perm(H, H1), 
    append(L1, L2, H1), 
    append(L1, [T], X1), 
    append(X1, L2, X).
% --------------------------

% Function: ionah (Tower of Hanoi solution)
% Description: Take single number as input and prints out the solution to the inverted disk problem for that many disks. 
% This is the problem of moving a stack of k disks of increasing size from bottom to top, from the first peg to the third peg with 
% another peg that may be used as well, subject to the condition that a smaller disk is never put on top of a larger one, 
% and only one disk may be moved at a time
ionah(N) :- move(N, 'peg 1', 'peg 3', 'peg 2').

move(1,X,Y,_) :-  
    write('move disk from '), 
    write(X), 
    write(' to '), 
    write(Y), 
    nl. 
move(N,X,Y,Z) :- 
    N>1, 
    M is N-1, 
    move(M,X,Z,Y), 
    move(1,X,Y,_), 
    move(M,Z,Y,X).
% --------------------------

% Function: sequence
% Description: Main function that takes a single integer as input and prints out a list containing that many terms of the sequence defined by:
% Sn = {0 if n = 1, 1 if n = 2, 2s(n-1) + s(n-2) if n > 2}
sequence(1,[0]).
sequence(2,[0,1]).
sequence(N,R) :- 
    M is N-1,
	sequence(M,X),
	seq(N,Y),
	append(X,[Y],R),!. % "!" to exclude choices left because of the last statement.

seq(1,0).
seq(2,1).
seq(N,End) :- 
    B is N-1,
    C is B-1,
	seq(C,SeqB),
	seq(B,SeqA),
	D is 2*SeqA,
	End is D+SeqB.
% --------------------------

% Function: argue
% Description: A program that argues with the user, accepts a list as input
argue([are],[am, not]). 

% the ';' symbol means the 'OR' operand
argue([H|T],X) :- H == you, argue2(T,X); H == i, argue3(T,X).

argue2([H|T],X) :- H == are, append([i, am, not],T,X).
argue3([H|T],X) :- H == am, append([you, are, not],T,X).
% --------------------------

% Function: bubblesort
% Description: Takes a list of numbers as input and returns the list sorted in ascending order using a bubblesort. 
bubblesort(List,Sorted):-bsort(List,[],Sorted).

bsort([], Acc, Acc).
bsort([H|T], Acc, Sorted):-
    bubble(H, T, NT, MaxL),
    bsort(NT, [MaxL|Acc], Sorted).
   
bubble(X, [], [], X).
bubble(X, [Y|T], [Y|NT], MaxL):- 
    X > Y, 
    bubble(X, T, NT, MaxL).

bubble(X, [Y|T], [X|NT], MaxL):-
    X =< Y,
    bubble(Y, T, NT, MaxL).
% --------------------------
