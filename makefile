SRCDIR = ../simple-computer/console
OBJDIR = ../simple-computer/build
CC = gcc
CFLAGS = -Wall -Wextra -g

PROGRAMS = test test1 test3

all: $(PROGRAMS) run

$(PROGRAMS): %: $(OBJDIR)/%.o
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

run: $(PROGRAMS)
	@for prog in $(PROGRAMS); do \
		echo "$$prog"; \
		./$$prog; \
		echo " "; \
	done

clean:
	rm -rf $(OBJDIR) $(PROGRAMS)

.PHONY: all clean run
