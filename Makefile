# Client -------------------------------------------------------------------
compile-client:
	g++ -o .compiled/Client client/*.cpp client/ui/*.cpp client/internal/*.cpp

run-client:
	./.compiled/Client

client: compile-client run-client

# Server -------------------------------------------------------------------
compile-server:
	g++ -o ./.compiled/Server server/*.cpp server/utils/*.cpp server/internal/*.cpp server/service/*.cpp

run-server:
	./.compiled/Server

server: compile-server run-server