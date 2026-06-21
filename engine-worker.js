let findBestMove = null;
let resolveEngineReady;

const engineReady = new Promise(function (resolve) {
    resolveEngineReady = resolve;
});

var Module = {
    locateFile: function (path) {
        if (path.endsWith(".wasm")) {
            return new URL("chess_engine.wasm", self.location.href).href;
        }

        return path;
    },
    onRuntimeInitialized: function () {
        findBestMove = Module.cwrap(
            "findBestMove",
            "string",
            ["string", "number"]
        );

        resolveEngineReady();
        self.postMessage({ type: "ready" });
    }
};

self.onmessage = async function (event) {
    const message = event.data;

    if (!message || message.type !== "search") {
        return;
    }

    try {
        await engineReady;

        const bestMove = findBestMove(message.fen, message.depth);

        self.postMessage({
            type: "result",
            requestId: message.requestId,
            gameVersion: message.gameVersion,
            bestMove: bestMove
        });
    } catch (error) {
        self.postMessage({
            type: "error",
            requestId: message.requestId,
            gameVersion: message.gameVersion,
            error: error instanceof Error ? error.message : String(error)
        });
    }
};

try {
    importScripts("chess_engine.js");
} catch (error) {
    self.postMessage({
        type: "init-error",
        error: error instanceof Error ? error.message : String(error)
    });
}
