hlbackwards([],[]). 
hlbackwards([H|T],R):-
    rev(T,RevT),
    append(RevT,[H],R).

llbackwards([], []) :- !. % "!" to exclude choices left because of the last statement.
llbackwards([H|T], X) :-
    !,
    llbackwards(H, NewH),
    llbackwards(T, NewT),
    append(NewT, [NewH], X).

llbackwards(X, X).
          
palindrome([]).
palindrome(L,L):- llbackwards(L,L).
palindrome(L,R):- 
    llbackwards(L,Revlist),
    append(L,Revlist,R),
    L\=Revlist.


permutations([], []).
permutations([X], [X]) :-!.
permutations([T|H], X) :- 
    permutations(H, H1), 
    append(L1, L2, H1), 
    append(L1, [T], X1), 
    append(X1, L2, X).


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


sequence(1,[0]).
sequence(2,[0,1]).
sequence(N,R) :- 
    M is N-1,
	sequence(M,X),
	seq(N,Y),
	append(X,[Y],R),!.

seq(1,0).
seq(2,1).
seq(N,End) :- 
    B is N-1,
    C is B-1,
	seq(C,SeqB),
	seq(B,SeqA),
	D is 2*SeqA,
	End is D+SeqB.


bubble_sort(List,Sorted):-b_sort(List,[],Sorted).

b_sort([], Acc, Acc).
b_sort([H|T], Acc, Sorted):-
    bubble(H, T, NT, MaxL),
    b_sort(NT, [MaxL|Acc], Sorted).
   
bubble(X, [], [], X).

bubble(X, [Y|T], [Y|NT], MaxL):- 
    X > Y, 
    bubble(X, T, NT, MaxL).

bubble(X, [Y|T], [X|NT], MaxL):-
    X =< Y,
    bubble(Y, T, NT, MaxL).
