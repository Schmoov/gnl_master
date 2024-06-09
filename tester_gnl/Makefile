CC := cc
CFLAGS := -Wall -Wextra -Werror

GNL_MSRC := ../get_next_line.c ../get_next_line_utils.c
GNL_BSRC := ../get_next_line_bonus.c ../get_next_line_utils_bonus.c

SRC_DIR := src/
SRCS := $(wildcard $(SRC_DIR)*.c)

BIN_DIR := .bin/
GNL_MOBJS := $(patsubst ../%.c, $(BIN_DIR)%.o, $(GNL_MSRC))
GNL_BOBJS := $(patsubst ../%.c, $(BIN_DIR)%.o, $(GNL_BSRC))
OBJS := $(patsubst $(SRC_DIR)%.c, $(BIN_DIR)%.o, $(SRCS))

TST_DIR := tests/
TSTS := $(patsubst $(BIN_DIR)%.o, $(TST_DIR)%, $(OBJS))

CRIT := -L criterion -lcriterion
CRIT_ENV := LD_LIBRARY_PATH=criterion

ASAN := -fsanitize=address
LOG_DIR := .logs/
ASAN_ENV := ASAN_OPTIONS=log_path=$(LOG_DIR):abort_on_error=1:allocator_may_return_null=1

###############################################################################

all: test

test: $(OBJS) $(GNL_MOBJS) $(GNL_BOBJS) $(TSTS) 

$(BIN_DIR)%_mandatory.memtest.o: $(SRC_DIR)%_mandatory.memtest.c $(GNL_MOBJS)
	@ mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(ASAN) -I ./ -c $< -o $@

$(BIN_DIR)%_bonus.memtest.o: $(SRC_DIR)%_bonus.memtest.c $(GNL_BOBJS)
	@ mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(ASAN) -I ./ -c $< -o $@

$(BIN_DIR)%.o: ../%.c
	@ mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


$(TST_DIR)%_mandatory.memtest: $(BIN_DIR)%_mandatory.memtest.o $(GNL_MOBJS)
	@ mkdir -p $(TST_DIR)
	@ mkdir -p $(LOG_DIR)
	$(CC) $(CFLAGS) $(ASAN) $^ $(CRIT) -o $@
	$(ASAN_ENV) $(CRIT_ENV) ./$@

$(TST_DIR)%_bonus.memtest: $(BIN_DIR)%_bonus.memtest.o $(GNL_BOBJS)
	@ mkdir -p $(TST_DIR)
	@ mkdir -p $(LOG_DIR)
	$(CC) $(CFLAGS) $(ASAN) $^ $(CRIT) -o $@
	$(ASAN_ENV) $(CRIT_ENV) ./$@

print-%  : ; @echo $* = $($*)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(LOG_DIR)

fclean: clean
	rm -rf $(TST_DIR)

re: fclean all

.PHONY: all test clean fclean re
