# CORE ARCHITECTURE

## Why this file exists

I did not want this engine to become one of those projects where the code "works somehow" and then slowly turns into a forest nobody wants to enter again.

This project was never just about making a machine push pieces on a board.
It was about learning.
It was about fighting confusion one at a time.
It was about respecting C++ enough to not treat it like a dumping ground for random logic FR .

So this document exists for one simple reason:
if someone opens this repository after me, or even if FUTURE ME opens it after a long break, I want the structure to feel human.
Not "enterprise architecture" for the sake of sounding smart.
I want it to say:
"Here is what the engine is trying to do, here is how it thinks, and here is where everything lives."

If `README.md` is the heart of the project, this file is the nervous system map.

---

## The big picture

At its core, this engine follows a very classical chess-engine pipeline:

1. Store a board position.
2. Generate candidate moves.
3. Filter illegal moves.
4. Search the legal moves.
5. Evaluate the resulting positions.
6. Return the best move.
7. If a GUI like Arena is connected, translate that move through UCI and send it back.

That is the soul of the engine.
Nothing magical is happening.
The engine is simply asking honest questions again and again:

- What moves are possible?
- Which of those are legal?
- If I play this, what can the opponent do?
- If they respond well, am I still okay?
- Which line leaves me with the best final position?

That repeated questioning is what eventually looks like "intelligence".

---

## High-level flow

The most important runtime path today looks like this:

`uci.cpp`
-> `ucihelper.cpp`
-> `position.h` / `position.cpp`
-> `genmoves.cpp`
-> `makemove.cpp`
-> `validatemove.cpp`
-> `search.cpp`
-> `evaluate.cpp` + `pst.cpp`
-> back to `uci.cpp`

In plain English:

- the GUI sends a command
- the engine loads the current position
- the engine generates and validates moves
- the search chooses the best continuation
- the chosen move is converted back to UCI text
- the GUI receives `bestmove ...`

---

## Repository shape

### `programfiles/`

This is where the actual engine code lives.
Almost every meaningful chess component is here.

### `README.md`

This is the emotional and personal introduction to the project.
It explains why the project exists.

### `README/architecture.md`

This file.
The technical map with the same spirit as the README.

---

## The engine's mental model

Before talking about files, it is important to understand the engine's model of the world.

This engine does not think in terms of "beautiful chess ideas".
It thinks in terms of:

- a `Position`
- a list of `Move`s
- recursive search
- a score

Everything else is built on top of that.

---

## 1. Position and board representation

### Files involved

- `programfiles/position.h`
- `programfiles/position.cpp`

### Core structs

The engine starts with two simple data types:

- `Square`
- `Position`

`Square` is just coordinates:

- `row`
- `col`

`Position` is the real state container of the game.
It stores:

- `board[9][9]`
- `sideToMove`
- castling-right state through king/rook movement flags
- en passant target square

### Why the board is `9 x 9`

This engine uses a slightly unusual board representation.
The playable board is still the normal 8x8 chessboard, but one extra row and one extra column are used for labels.

That means:

- rows `0..7` are actual chess ranks
- columns `1..8` are actual chess files
- column `0` stores rank labels like `8`, `7`, `6`
- row `8` stores file labels like `a`, `b`, `c`

So for example:

- `board[0][1]` is `a8`
- `board[7][5]` is `e1`
- `board[7][8]` is `h1`

This is not the most common engine representation, but it is very readable for a human who is learning and debugging.
That matters.
Sometimes clarity is worth more than cleverness.-M3

### Side to move

`sideToMove` uses:

- `White`
- `Black`

This is critical because every search, validation, and evaluation decision depends on whose turn it is.

### Castling and en passant state

The engine also stores:

- whether each king has moved
- whether each rook relevant to castling has moved
- the current en passant square

Without these values, the engine would know where pieces are, but not the full rights of the position.
And in chess, legal state is more than piece placement.

### Coordinate conversion

`convertSquare(std::string square)` in `position.cpp` converts normal algebraic text like `e2` into internal row/column coordinates.

This function becomes especially useful when talking to GUIs through UCI.

---

## 2. Move representation

### File involved

- `programfiles/move.h`

The `Move` struct is more important than it first appears.
It stores:

- source square
- destination square
- captured piece
- promotion piece
- en passant information
- previous castling rights
- previous en passant state

This is a BIG deal.

The move is not just "from here to there".
It also carries enough historical information to allow `undoMove()` to restore the exact earlier state.

That is what makes recursive search practical.
Instead of copying the whole position for every branch, the engine can:

1. make a move
2. search deeper
3. undo the move

and trust that the board returns to the exact previous reality.

That trust is everything in a search engine.

---

## 3. Board display utilities

### Files involved

- `programfiles/board.h`
- `programfiles/board.cpp`

This module is intentionally simple.
Its main visible job is printing the board in a human-readable way through `printBoard(...)`.

This is not the brain of the engine.
It is the mirror.

When debugging move generation, legality, castling, en passant, or search bugs, being able to print the current board clearly is extremely valuable.

There is also an older/simple board-level move helper here.
But the real engine-grade move logic lives in `makemove.cpp`.

---

## 4. Pseudo-legal move generation

### Files involved

- `programfiles/genmoves.h`
- `programfiles/genmoves.cpp`

This is where the engine first begins to "move".

The key philosophy of this file is:

generate movement first,
ask legality questions later.

That means `genmoves.cpp` is responsible for piece movement patterns, not full chess legality.

It answers questions like:

- Where can a knight jump?
- How far can a bishop slide?
- Can this pawn move one or two squares?
- Is there a capturable piece on a diagonal?

It does NOT answer:

- Does this leave my king in check?
- Am I castling through attack?
- Is this move actually legal in the current full position?

That separation is intentional.
It keeps responsibilities cleaner.

### Piece-specific generators

There are dedicated functions for each color and piece type:

- white pawn
- white knight
- white bishop
- white rook
- white queen
- white king
- black pawn
- black knight
- black bishop
- black rook
- black queen
- black king

These functions mostly return `std::vector<Square>`.
That is important.
At this stage, the engine is saying:
"These are reachable destinations."
Not yet:
"These are final legal chess moves."

### En passant generation

`generateEnPassantMoves(Position&)` also lives here.

En passant is special because it depends on the remembered en passant square from the previous move.
This function checks that square and produces the pseudo-legal en passant candidates for the side to move.
Also because the code became a mess, checkout the choicesAndChallenges.md for info.

---

## 5. Building full moves and applying them

### Files involved

- `programfiles/makemove.h`
- `programfiles/makemove.cpp`

This file carries more responsibility than its name first suggests.

It does three major things:

1. builds full `Move` objects for each side
2. applies a move to the position
3. undoes a move later

### Why move assembly is here

`genmoves.cpp` mostly gives raw destination squares.
`makemove.cpp` upgrades those into full engine moves by attaching:

- from-square
- to-square
- captured piece
- promotion data
- special move flags

This is where the engine turns geometry into actual move records.

### `generateAllWhiteMoves()` and `generateAllBlackMoves()`

These functions collect all pseudo-legal moves for one side by:

- scanning the board
- identifying which pieces belong to the side to move
- calling the piece-specific generators
- wrapping results into `Move`
- adding promotions
- adding castling candidates
- appending en passant moves

These are not final legal moves yet.
They are the side's complete candidate move set before king-safety filtering.

### `makeMove(Position&, Move&)`

This function is one of the most sensitive places in the project.
It handles:

- normal piece movement
- captures
- promotions
- en passant captures
- updating en passant squares after double pawn pushes
- saving old castling rights into the move
- updating castling-right flags
- rook movement during castling
- SO I HIGHLY RECOMMEND NOT FUCKING AROUND THIS ONE. Instead create a copy and try break and make it their not a on the main copy itself.
This is the file where board state actually changes.

### `undoMove(Position&, Move&)`

This function reverses what `makeMove()` did.
It restores:

- piece placement
- captured piece
- promotion reversal
- rook restoration after castling
- previous castling-right flags
- previous en passant square
- captured pawn restoration for en passant

Search lives or dies by how accurate this function is.
If `undoMove()` is even slightly wrong, the search tree becomes corrupted in silent ways.
BUT JUST MAKE IT WHAT THE OPPOSITE OF makeMove() should be
That is the kind of bug that can make a chess engine feel haunted.

### `switchSideToMove(Position&)`

Very simple function.
Very important effect.

Every recursive search branch depends on flipping the side correctly between plies.

---

## 6. Legal move validation

### Files involved

- `programfiles/validatemove.h`
- `programfiles/validatemove.cpp`

This is where chess stops being "piece movement" and becomes actual law.

### What this layer does

The validation layer is responsible for answering:

- Where is the king?
- Is the king in check?
- Does this move leave the king in check?
- Is castling passing through attacked squares?
- Are there any legal moves left?
- You know the legal stuff

### `isKingInCheck(...)`

This function finds the king square and then generates the opponent's pseudo-legal moves to see whether any of them attack the king.

That may sound simple, but conceptually it is the core of legality.

If the king is attackable, the position is unsafe.

### `generateLegalMoves(Position&)`

This is one of the most important functions in the whole engine.

Its pattern is:

1. generate pseudo-legal moves
2. for each move:
3. handle special castling-through-check logic
4. make the move
5. test whether own king is safe
6. undo the move
7. keep the move only if it is legal

This is a very classical and very teachable architecture.
It may not be the fastest style in the world, but it is honest and correct-minded.

### Checkmate and stalemate

This layer also defines:

- `isCheckmate(...)`
- `isStalemate(...)`

These are derived from two things:

- whether the king is in check
- whether any legal moves exist

That is exactly how those game states should be thought about.

---

## 7. Evaluation

### Files involved

- `programfiles/evaluate.h`
- `programfiles/evaluate.cpp`
- `programfiles/pst.h`
- `programfiles/pst.cpp`

Once the engine reaches a position in search, it needs a way to judge it.
That is what evaluation does.

### Material evaluation

The engine currently uses classical piece values:

- pawn = 100
- knight = 300
- bishop = 300
- rook = 500
- queen = 900
- king = 20000

White pieces contribute positive score.
Black pieces contribute negative score.

So:

- positive evaluation means White is better
- negative evaluation means Black is better

This keeps the search logic very straightforward.
SO This is what MiniMax heavily relies on.

### Positional evaluation with piece-square tables

Material alone is not enough.
Where a piece stands also matters.

That is where `pst.cpp` comes in.
The engine currently has piece-square tables for:

- pawns
- knights
- bishops
- rooks
- queens

The idea is simple:

- central knights are usually better than edge knights
- advanced pawns may gain value
- rooks and queens like useful activity

The king table is currently commented out, cause the scope was going out of bounds now.

### `evaluate(Position&)`

This function walks the board and sums:

- material value
- positional bonus from the piece-square tables

This is the scoring voice of the engine.

It is not trying to be grandmaster-level wisdom yet.
It is trying to be stable, understandable, and useful for search.

That is the right order.

---

## 8. Search

### Files involved

- `programfiles/search.h`
- `programfiles/search.cpp`

This is the tactical brain of the project.

If move generation gives the engine possible futures,
search is the part that asks:
"Which future hurts me least or helps me most?"

### Main ideas used

The search currently uses:

- minimax
- alpha-beta pruning
- move ordering
- quiescence search

That is a very classical engine foundation from what I read.

### `bestMoveFinder(Position&, int depth)`

This is the top-level selector.
It gets the legal moves, searches them, and returns the move with the best score for the current side.

- White tries to maximize the score
- Black tries to minimize the score

That matches the evaluation convention.

### `minimax(...)`

This performs the recursive tree search.

At each node:

1. generate legal moves
2. order them
3. recursively search deeper positions
4. update alpha/beta
5. prune branches that cannot improve the result

This is where the engine saves time by NOT searching obviously useless branches.
But the node count was very high ![Minimax Implementation raw Nodes searched 11676](<Screenshot 2026-06-04 222022.png>)

### Alpha-beta pruning

Without alpha-beta, minimax becomes painfully expensive very quickly.
Alpha-beta says:

- if White already has a better option elsewhere, no need to continue this bad branch
- if Black already has a better defense elsewhere, no need to keep exploring this line either

This is one of the first big leaps from "toy search" to "real engine thinking".
This also reduced the no. of nodes to be searched significantly
![Addition of Alpha-Beta pruning nodes searched 2310 for the same search ](<Screenshot 2026-06-04 222034.png>)

### Move ordering

Before searching, the engine sorts moves using `moveScore(...)`.
At the moment, the priority mostly rewards:

- promotions
- captures of more valuable pieces

Good move ordering helps alpha-beta cut more branches earlier.

Even a simple ordering scheme can make a noticeable difference.
This basically made Alpha beta more awsome
![Results of adding Move ordering nodes searched 1579](<Screenshot 2026-06-05 090259.png>)

### Quiescence search

When normal depth reaches zero, the engine does not always stop immediately.
Instead, `quiescence(...)` continues exploring tactical capture sequences.

Why?

Because evaluating a position right in the middle of a noisy capture sequence can be misleading.

Quiescence search tries to avoid the classic horizon effect by saying:
"Let me at least resolve the obvious tactical violence before I judge this position."
It is A VERY BASIC IMPLEMENTATION QUIET LITERALLY ONLY SIMILAR TO ANOTHER MINIMAX ALGORITHM

### Node counting

`nodes` is tracked globally for search statistics and UCI info reporting.

That makes it easier to understand how much work the engine is doing.

---

## 9. Perft and correctness testing

### Files involved

- `programfiles/perft.h`
- `programfiles/perft.cpp`

Perft is one of the most honest tools a chess programmer can have.
It does not care how beautiful your code looks.
It does not care how emotionally attached you are to your move generator.
It only asks:

"When I recursively count all legal positions to this depth, do I get the correct number?"

### `perft(Position&, int depth)`

This recursively counts legal move tree nodes.
It is extremely useful for validating:

- move generation
- castling
- en passant
- legality filtering
- make/undo correctness

### `divide(Position&, int depth)`

This breaks the total perft count down move by move.

That is incredibly helpful when debugging because it tells you WHICH move subtree is wrong, not just that the total count is wrong.

Perft is less glamorous than search, but honestly, it is one of the reasons chess engines become trustworthy.

AND AND OFCOURSE THE TEST RESULTS CAME CORRECT IN ONE GO
![Perft results](<Screenshot 2026-06-06 171515.png>)

---

## 10. UCI and GUI communication

### Files involved

- `programfiles/uci.cpp`
- `programfiles/ucihelper.h`
- `programfiles/ucihelper.cpp`

This layer exists so the engine can speak to tools like Arena Chess GUI.

Without this layer, the engine may think well internally, but it cannot participate in a real GUI ecosystem.

### What `uci.cpp` does

`uci.cpp` is the communication loop.
It reads lines from standard input and responds to protocol commands such as:

- `uci`
- `isready`
- `ucinewgame`
- `position startpos ...`
- `position fen ...`
- `go depth ...`
- `quit`

When `go` arrives, this file:

1. ensures there are legal moves
2. resets node count
3. parses the requested depth
4. asks search for the best move
5. prints UCI output back to the GUI

### What `ucihelper.cpp` does

This helper file handles protocol-related conversion tasks such as:

- loading the start position
- loading a FEN string
- converting internal `Move` to UCI text like `e2e4`
- parsing UCI move text and matching it to a legal internal move

This is a bridge between human-standard chess notation and the engine's internal board coordinates.

### Why this matters

This module is what lets the engine stop being a private console experiment and start becoming a chess program that can live inside Arena.

That is a meaningful step.

It is one thing to print perft counts.
It is another thing entirely to let a GUI send you a real game and trust you to respond.

---

## 11. Entry points and scratch files

### Files involved

- `programfiles/main.cpp`
- `programfiles/main2.cpp`
- `programfiles/main3.cpp`
- `programfiles/test4.cpp`
The above files are more like scratch pads for testing and used during development.
- `programfiles/uci.cpp`

Not every file here exists because of some perfect top-down architectural plan.
Some files exist because experimentation is how understanding was built.

### What these files represent

- `uci.cpp` is the actual protocol-facing engine entry point for GUI play.
- `main.cpp`, `main2.cpp`, `main3.cpp`, and `test4.cpp` are more like workbenches.

These workbench files have been used for:

- perft testing
- move-generation testing
- legality debugging
- search debugging
- en passant and castling validation

This is the laboratory side of the project.
And honestly, every real engine project has one(Thats what chatGPT says when i asked whether to push them or not).


---

## 12. Full move lifecycle

If I had to explain the entire engine in one end-to-end example, it would look like this:

1. Arena or another caller sends a position through UCI.
2. `uci.cpp` receives the command.
3. `ucihelper.cpp` loads the board and side-to-move state.
4. Search starts with `bestMoveFinder(...)`.
5. Search asks for `generateLegalMoves(...)`.
6. Validation asks pseudo-move generation for candidate moves.
7. Each candidate is tested through `makeMove(...)` and `undoMove(...)`.
8. Legal moves are searched recursively with minimax + alpha-beta.
9. Quiet positions are scored by `evaluate(...)`.
10. Noisy tactical leaf positions are extended through quiescence search.
11. The best move is chosen.
12. The internal move is converted back to UCI text.
13. `bestmove ...` is printed back to the GUI.

That is the full circulation of thought in this engine.

---

## 13. Design strengths

There are a few things about this architecture that I genuinely like.

### It is readable

It is trying to be straightforward and honest,not a try hard.
That makes it easier to debug and extend.

### It separates movement from legality

This is one of the healthiest architectural decisions in the project.
Pseudo-legal generation and legal filtering are not mixed into one unreadable mess.
Not followed perfectly but the intention is there to some extent

### It has proper make/undo structure

That is foundational for search.
And it is already present.

### It has perft as a correctness tool

This shows good engineering instinct.
Not just "does it run?", but "is it actually correct?"
Well It ran perft in 1 go for depth and the results were correct 🙏🙏🙏

### It now has a UCI layer

That means the engine is no longer trapped inside local test code.
It can talk to real GUIs.

---

## 14. Current limitations and honest future work

No architecture document is complete if it only talks about strengths and pretends the work is finished.
So here is the honest part.

At its current stage, the engine is promising, but still growing.

### Areas that can improve

- stronger evaluation heuristics
- king safety beyond raw material and PST scoring
- better time management for UCI `go` commands
- iterative deepening
- transposition tables
- repetition detection
- fifty-move rule handling
- opening knowledge
- endgame improvements
- more systematic testing positions
- This what CHAGPT told me but i think there is always room for improvement not the time for one right now.

### Architectural cleanup ideas

- move some responsibilities into more sharply separated modules
- reduce duplication between white and black move generation patterns
- centralize test harnesses
- create a cleaner build target layout for debug vs GUI mode

None of these are embarrassments.
They are simply the next mountains.

And good projects are not the ones with no mountains left.
They are the ones worth climbing.

---

## 15. Final note

I want to say one thing very clearly:

this engine is not special because it is perfect.
It is special because it was built with care.

There is something deeply beautiful about learning a hard subject honestly.
About writing code, getting stuck, questioning yourself, reading again, fixing again, and still returning because you love the craft.

That spirit is part of the architecture too.

Architecture is not only files and function calls.
It is also the shape of the thinking behind them.

This project thinks in a straightforward, courageous, improving way.
And I believe that matters.

If someone extends this engine further, I hope this file helps them not just understand the code, but feel invited into it(Some fire quote 😭😭NGL).

THANK YOU do check out the README/choicesAndChallenges.md for more insights on the design decisions and challenges faced during development it will be fun.
