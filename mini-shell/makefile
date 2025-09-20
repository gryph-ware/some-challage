cc = clang
cflags = -Wall -Wextra -g
src = chall1_week1
target = out

all: $(target)

$(target): $(src)
	$(cc) $(cflags) $(src).c -o $(target)

run:
	./$(target)

clear:
	rm -rf $(target) *~ out $(src)
