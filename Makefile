# Client -------------------------------------------------------------------
compile-client:
	g++ -o .compiled/Client client/*.cpp

run-client:
	./.compiled/Client

client: compile-client run-client

# Server -------------------------------------------------------------------
compile-server:
	g++ -o ./.compiled/Server server/*.cpp server/utils/*.cpp

run-server:
	./.compiled/Server

server: compile-server run-server