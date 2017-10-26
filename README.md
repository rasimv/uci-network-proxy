A client-server kit to run a uci-compatible chess engine on another computer

Build https://drive.google.com/file/d/0B2ulp3O-I6E7Z2lwcFFadGFfQ3c/view?usp=sharing

How to use
Run and start the server (unp-server.exe) on the computer where the chess engine should work.
The client (unp-client.exe) is a placeholder for the chess engine on the computer where the chess UI application runs. Select the client executable (unp-client.exe) as a chess engine executable instead of the real engine's.
UCI parsing is not implemented, so any external files (like ending books) which are passed to the chess engine by UI application MUST be on both computers and MUST be on identical paths
