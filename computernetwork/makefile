CC = g++
CFLAGS = -Wall -g

all: exp1 exp2 exp3

exp1: webserver.cpp
    $(CC) $(CFLAGS) -lboost_filesystem -o $@ $^

exp2: smtpemail.cpp pop3email.cpp
    $(CC) $(CFLAGS) -lcurl -o $@ $^

exp3: gbnsender.cpp gbnreceiver.cpp
    $(CC) $(CFLAGS) -lpthread -o $@ $^

clean:
    rm -f exp1 exp2 exp3

.PHONY: all exp1 exp2 exp3 clean