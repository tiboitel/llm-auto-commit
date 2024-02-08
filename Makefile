NAME = llm-auto-commit
SRCS = main.c \
	   api_request.c \
	   json_parser.c
SRCSPATH = src/
INCLUDES = include
BUILDDIR = build/
BUILD = $(BUILDDIR)$(NAME)

CC = gcc
CFLAGS = \
	  -Wall \
	  -Werror \
	  -Wextra

LIBS = -lcurl -ljson-c
INCLUDES_O = -I$(INCLUDES)

SRC = $(addprefix $(SRCSPATH), $(SRCS))
OBJS = $(addprefix $(BUILDDIR), $(SRCS:.c=.o))

$(shell mkdir -p $(BUILDDIR))

all: $(BUILD)

$(BUILD): $(OBJS)
	$(CC) -o $(BUILD) $(OBJS) $(CFLAGS) $(LIBS)

$(BUILDDIR)%.o: $(SRCSPATH)%.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES_O) -c $<

clean:
	rm -rf $(BUILDDIR)*.o

fclean: clean
	rm -rf $(BUILD)

re: fclean all

