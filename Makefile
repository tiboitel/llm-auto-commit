NAME = llm-auto-commit
SRCS = \
	main.c
SRCSPATH = src/
INCLUDES = includes
BUILDDIR = build/
BUILD = $(addprefix $(BUILDDIR), $(NAME))

CC = gcc
CGLAGS  = \
	  -Wall \
	  -Werror \
	  -Wextra

INCLUDES_C = -lcurl -ljson-c
INCLUDES_O = -I $(INCLUDES)


SRC = $(addprefix $(SRCSPATH), $(SRCS))
OBJS = $(SRC:.c=.o)

all:	$(BUILD)

$(BUILD):	$(OBJS)
	$(CC) -o $(BUILD) $(OBJS) $(CFLAGS) $(INCLUDES_C)

%.o: $.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES_O) -c $<

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(BUILD)

re:	fclean	all
