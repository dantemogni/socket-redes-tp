# Variables -------------------------------------------------------------------
COMPILED_FLD =  ${PWD}/.compiled
CLIENT_FLD = ${PWD}/client
SERVER_FLD = ${PWD}/server

# Client -------------------------------------------------------------------
compile-client:
	g++ -o ${COMPILED_FLD}/Client  ${CLIENT_FLD}/*.cpp  ${CLIENT_FLD}/ui/*.cpp  ${CLIENT_FLD}/internal/*.cpp

run-client $(PORT):
	${COMPILED_FLD}/Client $(PORT)

.PHONY: client
client $(PORT): compile-client run-client $(PORT)


# Server -------------------------------------------------------------------
compile-server:
	g++ -o ${COMPILED_FLD}/Server ${SERVER_FLD}/*.cpp ${SERVER_FLD}/utils/*.cpp ${SERVER_FLD}/internal/*.cpp ${SERVER_FLD}/service/*.cpp

run-server $(PORT):
	${COMPILED_FLD}/Server $(PORT)

.PHONY: server
server $(PORT): compile-server run-server $(PORT)