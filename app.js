const game = new Chess();
const statusElement = document.getElementById("status");
const historyElement = document.getElementById("move-history");
const newGameButton = document.getElementById("new-game");

let engineLoaded = false;
let engineThinking = false;
let pendingEngineMove = null;
let gameVersion = 0;

const board = Chessboard("board", {
    position: "start",
    orientation: "white",
    draggable: !("ontouchstart" in window),
    pieceTheme: function (piece) {
        const pieceImages = {
            wP: "pieces/white-pawn.png",
            wN: "pieces/white-knight.png",
            wB: "pieces/white-bishop.png",
            wR: "pieces/white-rook.png",
            wQ: "pieces/white-queen.png",
            wK: "pieces/white-king.png",
            bP: "pieces/black-pawn.png",
            bN: "pieces/black-knight.png",
            bB: "pieces/black-bishop.png",
            bR: "pieces/black-rook.png",
            bQ: "pieces/black-queen.png",
            bK: "pieces/black-king.png"
        };

        return pieceImages[piece];
    },
    onDragStart: onDragStart,
    onDrop: onDrop,
    onSnapEnd: function () {
        board.position(game.fen());
    }
});

function onDragStart(source, piece) {
    clearSelection();
    if (
        !engineLoaded ||
        engineThinking ||
        game.game_over() ||
        game.turn() !== "w" ||
        piece.startsWith("b")
    ) {
        return false;
    }
}

function onDrop(source, target) {
    suppressNextClick = true;
    window.setTimeout(function () {
        suppressNextClick = false;
    }, 250);

    if (!attemptMove(source, target, { syncBoard: false })) {
        return "snapback";
    }
}

function makeEngineMove(requestedVersion) {
    pendingEngineMove = null;

    if (requestedVersion !== gameVersion || game.game_over()) {
        engineThinking = false;
        updateDisplay();
        return;
    }

    try {
        const uciMove = window.findBestMove(game.fen(), 4);

        if (!uciMove || uciMove === "0000") {
            engineThinking = false;
            updateDisplay("The engine did not return a legal move.");
            return;
        }

        const move = game.move({
            from: uciMove.slice(0, 2),
            to: uciMove.slice(2, 4),
            promotion: uciMove.length > 4 ? uciMove[4] : "q"
        });

        if (move === null) {
            engineThinking = false;
            updateDisplay("The engine returned an invalid move: " + uciMove);
            return;
        }
    } catch (error) {
        console.error(error);
        engineThinking = false;
        updateDisplay("The engine could not calculate a move.");
        return;
    }

    engineThinking = false;
    board.position(game.fen());
    updateDisplay();
}

function updateDisplay(message) {
    updateHistory();
    updateStatus(message);
}

function updateStatus(message) {
    if (message) {
        statusElement.textContent = message;
        return;
    }

    if (!engineLoaded) {
        statusElement.textContent = "Loading engine…";
        return;
    }

    if (game.in_checkmate()) {
        const winner = game.turn() === "w" ? "Black" : "White";
        statusElement.textContent = "Checkmate — " + winner + " wins.";
        return;
    }

    if (game.in_stalemate()) {
        statusElement.textContent = "Stalemate — draw.";
        return;
    }

    if (game.insufficient_material()) {
        statusElement.textContent = "Draw by insufficient material.";
        return;
    }

    if (game.in_threefold_repetition()) {
        statusElement.textContent = "Draw by threefold repetition.";
        return;
    }

    if (game.in_draw()) {
        statusElement.textContent = "Draw.";
        return;
    }

    if (engineThinking) {
        statusElement.textContent = "Black is thinking…";
        return;
    }

    const sideToMove = game.turn() === "w" ? "White" : "Black";
    const checkText = game.in_check() ? " — in check" : "";
    statusElement.textContent = sideToMove + " to move" + checkText + ".";
}

function updateHistory() {
    const moves = game.history();

    if (moves.length === 0) {
        historyElement.textContent = "No moves yet.";
        return;
    }

    const turns = [];

    for (let index = 0; index < moves.length; index += 2) {
        const turnNumber = index / 2 + 1;
        const whiteMove = moves[index];
        const blackMove = moves[index + 1] || "";
        turns.push(turnNumber + ". " + whiteMove + " " + blackMove);
    }

    historyElement.textContent = turns.join("  ");
}

function startNewGame() {
    gameVersion += 1;
    clearSelection();

    if (pendingEngineMove !== null) {
        window.clearTimeout(pendingEngineMove);
        pendingEngineMove = null;
    }

    engineThinking = false;
    game.reset();
    board.start();
    updateDisplay();
}

let selectedSquare = null;
let suppressNextClick = false;

function squareFromElement(el) {
    const match = el.className.match(/square-([a-h][1-8])\b/);
    return match ? match[1] : null;
}

function clearSelection() {
    if (selectedSquare) {
        $("#board .square-55d63").removeClass(
            "selected-square legal-target"
        );
        selectedSquare = null;
    }
}

function highlightMoves(square) {
    $("#board .square-" + square).addClass("selected-square");
    game.moves({ square: square, verbose: true }).forEach(function (move) {
        $("#board .square-" + move.to).addClass("legal-target");
    });
}

function attemptMove(from, to, options) {
    options = options || {};
    const move = game.move({
        from: from,
        to: to,
        promotion: "q"
    });

    if (move === null) {
        return false;
    }

    clearSelection();

    if (options.syncBoard !== false) {
        board.position(game.fen());
    }

    updateDisplay();

    if (!game.game_over()) {
        engineThinking = true;
        updateStatus();

        const requestedVersion = gameVersion;
        pendingEngineMove = window.setTimeout(function () {
            makeEngineMove(requestedVersion);
        }, 100);
    }

    return true;
}

function onSquareTap(square) {
    if (
        !engineLoaded ||
        engineThinking ||
        game.game_over() ||
        game.turn() !== "w"
    ) {
        return;
    }

    if (selectedSquare) {
        if (square === selectedSquare) {
            clearSelection();
            return;
        }

        if (attemptMove(selectedSquare, square)) {
            return;
        }

        clearSelection();
    }

    const piece = game.get(square);

    if (piece && piece.color === "w") {
        selectedSquare = square;
        highlightMoves(square);
    }
}

$("#board").on("click", ".square-55d63", function () {
    if (suppressNextClick) {
        suppressNextClick = false;
        return;
    }

    const square = squareFromElement(this);

    if (square) {
        onSquareTap(square);
    }
});

newGameButton.addEventListener("click", startNewGame);

window.addEventListener("resize", function () {
    board.resize();
});

window.engineReady
    .then(function () {
        engineLoaded = true;
        updateDisplay();
    })
    .catch(function (error) {
        console.error(error);
        statusElement.textContent = "The chess engine failed to load.";
    });

updateDisplay();
