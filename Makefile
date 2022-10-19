# Client -------------------------------------------------------------------
compile-client:
	g++ -o .compiled/Client client/Client.cpp

run-client:
	./.compiled/Client

# Server -------------------------------------------------------------------
compile-server:
	g++ -o .compiled/Server server/Server.cpp server/Calculator.cpp

run-server:
	./.compiled/Server