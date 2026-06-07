# THIS README IS DEDCATIED TO THE CHESS ENGINE ARCHITECTURE AND DESIGN CHOICES I MADE, AND THE CHALLENGES I FACED WHILE BUILDING THIS PROJECT. AND SOME VERY VERY OBIVIOUS MISTAKES I MADE 🤣🤣🤣🤣

SO I started writing this engine back in last saturday I am writing this markdown on the night(Morning) of the next sunday at 2:27am. This took longer than I anticipated and I wish to never do it again for the sake of my sanity. Just Kidding. I got to learn so much with this project I don't I ever will be the same. So many basics got cleared. I had never thought I would be this grateful. What was suppose to be just a weekend project took a whole lot more. And I think my decision on guidance while I figure out the code myself was worth it.

## Challenge 1: How do Camels Move through the DESERT??
The Bishop movement Identification became a painful. It may have seemed like a simple diagonal move but 
It made sure I cook my brains and just cry. I couldn't figure out how to generate its moves even though it was obivious. THE ANSWER WAS MULTIPLICATION !!!!. You iterate throught each of the movements{i.e these moves in genmoves.cpp} and just multiply. That was it. but boy I spend a lot of time it was still the early stage of the project. after this the rest of the movemenet generation became easier for other pieces. 


## Challenge 2: How did I miss this 🤡🤡🤡 Its the Elephant in the room 🐘🐘.
Halfway through the Alpha-Beta Pruning right as I was to jump to the PST. I realized.... I forgot to add the logics and legalities for (Drumroll🥁🥁🥁). EnPassant, Castling and Most Importantly Pawn Promotion🤡💔😭😭.As if already legality check wasn't painful enough. EnPassant required a separate state to maintain it as a valid move and then again it has a custom movement than a regular pawn capture and after which came the painful validatiy check for castling(My hands are paining so here is chatGPT on the legality of Castling) 
Castling is legal only if all of these conditions are met:

The king has never moved.
The rook involved has never moved.
There are no pieces between the king and that rook.
The king is not currently in check.
The king does not pass through a square that is under attack.
The king does not end up on a square that is under attack.

So yes it was painful because legality was already trouble some and to visit it again was just a nightmare. I lived through it no worries. Pawn Promition was what I did first and in fact the order I did was Promotion, Castling and Enpassant. Promotion was relativly simple to implement and was pretty much straight forward but hey again I had to you know just break my head around where to fit all these moves back in the genmoves and validate them


# Challenge 3: The &Fault in Our *Stars🥀🥀🥀🥀🥀

I faced my very first MAJOR MAJOR PROGRAMMER Bug(NGL I really felt too much aura in me when I read the "corruption" when I read about this error). While iterating through for the search the pieces would seemingly appear out of nowhere after an undo operation. First instinct was move generation got fudged up due while adding the special moves. But no it was State restoration. Castling rights, enpassant, capturedPieces all had to be restored in the correct order. And I did not so the complier put in garbage values. and viola you have your Black King turn into a Pawn in the next move 😲😲😲. Or heck king move in "CHECKMATE🤣🤣". Bascially it was an issue of makeMove/UndoMove symmetry.

# Challenge 4: Earth is Round 🌏🌎🌍🌐🫨
Ok SO I got this error while my 4th test file and it was because 
well genmoves -> makeMove -> genmoves -> makeMove -> (You get the idea)
and complier started throughing error to generateLegalMoves(Like dude are you fr?)
but ok got that done by moving the entire Struct Move to new file move.h dedicated to handling the Move.

# Challenge 5: Forever...... young I wanna be forever🌱🌱
Arena sends position moves e2e4 go engine bestmove e7e5 arena found e7-e5
do that again and its an illegal move (Don't asked how I solved it 🙏🙏).


### OK BUT THERE WHERE SOME HAPPY MOVEMENTS

LIKE THE PERFT 5 GOT IT ALL DONE IT ONE GO AND IT WAS SOOTHING. I WAS LIKE OK ALL MOVES ARE GENERATED RIGHT.  But hey My life happens to be interesting

For starters I Got rejected by a girl I liked (ASKED OUT FOR A DATE TOTALLY SAID NO.) AND THEN I HAD A WISDOM TOOTH EXTRACTION AND I HAD TO BE RUSHED TO THE HOSPITAL LAST SUNDAY BECAUSE I HAD SEVERE DIZZENESS AND WEAKNESS. CAUSE HEY WHO WANTS A PROPER SLEEP WHEN YOU ARE WRITING A CHESS ENGINE(i would probably do this again in golang for the heck of it). And yes about my seniors(Go read the README.md) who helped me well let me just tell you it was like the "The Demolition Man" Mission for GTA Vice City with you all 😭. 

But thank you I learnt a lot more than just some stupid Datas and Structures,I feel. I had friends who I talked to for the project.And People who encouraged me to write this project. And people who believed I could do this on my own. And those people,those moments they are my real takeways from this project. It was tuff week but I made it through. I am really sleepy cause I am imagining PrimeTime's(famous dev tuber) voice writing this.

Ok so this part is after the sun has risen(10:45 am). I slept halfway through writing this. And this project will go down in my core memory. It was difficult It was tuff
alpha beta minimax and all that theoritical stuff I studied in college(taught very well BTW by college professors (Shoutout to them)) to implement it in
action well thats a whole another story

I did make some weird chocices thought Like a 9 x 9 representation because I wanted labels. and then not using Objects but hey I did use vectors so not completely write a "c program in c++". Which I think should have not made in the first place. Even though the responsibilites of each of these files had been fixed in the beginning I still some how managed to over look them for the convenience and it is now readable but not helpful as I expected.

But I know I lot more than I did before. SO I guess it is a win-win situation. I just hope to find a job at this point. You know what someday i would love to sit with linus torvalds and ask him about his favourite childhood memory. But yes a job would be better. 

Lastly I would like to thank all my friends who called up, Especially the bastards of that Audit Firm(Yes you guys 😉).
I hope right now to master DSA first and probably work in some good company simulatanously. But the market is kinda disappointing. I have applied to a lot of companies its definetly 50+ but I had rejection from mail only from say less than 10. Rest I assume just didnt bother. Which is disheartining to be honest but ok. I will keep trying.
Already I guess thats more than I had expected to write.(Now let me throw this to claude to improve the writing style(Just kidding)).

THANK YOU FOR READING THIS THROUGH AND KEEP CODING.




