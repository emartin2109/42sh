##
## EPITECH PROJECT, 2022
## shell
## File description:
## Makefile
##

SRC				:=	src/builtin/cd.c \
					src/builtin/alias.c \
					src/builtin/env.c \
					src/builtin/exec.c \
					src/builtin/exit.c \
					src/builtin/history.c \
					src/builtin/local.c \
					src/command/data.c \
					src/builtin/source.c \
					src/command/free.c \
					src/command/parse_command.c \
					src/command/parse_redirect.c \
					src/command/parse.c \
					src/env/parse.c \
					src/env/update.c \
					src/execute/bind.c \
					src/execute/execute.c \
					src/execute/group.c \
					src/execute/run.c \
					src/history/file.c \
					src/history/history.c \
					src/inhibitors.c \
					src/prompt/buffer.c \
					src/prompt/history.c \
					src/prompt/line.c \
					src/prompt/move.c \
					src/prompt/print.c \
					src/prompt/prompt.c \
					src/resolve/fd.c \
					src/resolve/group.c \
					src/resolve/home.c \
					src/resolve/path.c \
					src/string/string_parse.c \
					src/string/string_split.c \
					src/string/string.c \
					src/tokenizer/aliases.c \
					src/tokenizer/token_syntax.c \
					src/tokenizer/token.c \
					src/tokenizer/tokenizer.c \
					src/util/error.c \
					src/util/mem.c \
					src/util/path.c \

MAIN_SRC		:=	src/main.c

TEST_SRC 		:= 	tests/test_tokenizer.c

TESTER_SCRIPT	:= 	bonus/tester.sh
TESTER_FILE		:= 	tests/integration.json

RELEASE_OUT		:= 	42sh
DEBUG_OUT		:= 	42sh_debug
TEST_OUT		:= 	42sh_test
UNIT_OUT	:= 	unit_tests

BUILD_DIR		:=  build
RELEASE_DIR 	:= 	build/release
DEBUG_DIR		:= 	build/debug
TEST_DIR		:= 	build/test

CC				:=	gcc
CFLAGS			+=	-I./include/ -MMD -MP
LDFLAGS			:=

RELEASE_OBJ 	:= 	$(addprefix $(RELEASE_DIR)/,$(SRC:.c=.o) $(MAIN_SRC:.c=.o))
RELEASE_FLAGS	:=	-O2

DEBUG_OBJ		:= 	$(addprefix $(DEBUG_DIR)/,$(SRC:.c=.o) $(MAIN_SRC:.c=.o))
SANITIZERS		:=	-fsanitize=address -fsanitize=undefined
DEBUG_FLAGS		:=	-g3 -Wall -Wextra -Wpedantic -Wshadow
DEBUG_FLAGS     +=	$(if $(NO_SANITIZE),, $(SANITIZERS))

TEST_OBJ		:= 	$(addprefix $(TEST_DIR)/,$(SRC:.c=.o) $(MAIN_SRC:.c=.o))
TEST_UNIT_OBJ	:= 	$(addprefix $(TEST_DIR)/,$(SRC:.c=.o) $(TEST_SRC:.c=.o))
TEST_FLAGS		:=	--coverage
TEST_LIBS		:=	-lcriterion

reset			:=  \033[0m
bold			:= 	\033[1m
underline		:= 	\033[4m
green			:=  \033[32m
blue			:= 	\033[34m
grey 			:= 	\033[90m

all: release

-include $(RELEASE_OBJ:.o=.d)
-include $(DEBUG_OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)

## BUILD ##

release: $(RELEASE_OUT)
	@printf "$(bold)$(green)$(RELEASE_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)release$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(RELEASE_OUT)$(reset)\n"

debug: $(DEBUG_OUT)
	@printf "$(bold)$(green)$(DEBUG_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)debug$(reset) "
	@printf "$(grey)sanitizers:$(reset)$(underline)$(grey)"
	@printf "$(if $(NO_SANITIZE),disabled,enabled)$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(DEBUG_OUT)$(reset)\n"

test: $(TEST_OUT) $(UNIT_OUT)
	@printf "$(bold)$(green)$(TEST_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)test$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(TEST_OUT)$(reset)\n"

	@printf "$(bold)$(green)$(UNIT_OUT) compiled$(reset) "
	@printf "$(grey)mode:$(reset)$(underline)$(grey)test$(reset) "
	@printf "$(grey)output:$(reset)$(underline)$(grey)$(UNIT_OUT)$(reset)\n"

$(RELEASE_OUT): CFLAGS += $(RELEASE_FLAGS)
$(RELEASE_OUT): $(RELEASE_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(DEBUG_OUT): CFLAGS += $(DEBUG_FLAGS)
$(DEBUG_OUT): $(DEBUG_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(TEST_OUT): CFLAGS += $(TEST_FLAGS)
$(TEST_OUT): $(TEST_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(UNIT_OUT): CFLAGS += $(TEST_FLAGS)
$(UNIT_OUT): LDLIBS += $(TEST_LIBS)
$(UNIT_OUT): $(TEST_UNIT_OBJ)
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

## OBJECTS ##

$(RELEASE_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(grey)compiling %-50s$(reset)" $<
	@$(CC) -o $@ -c $< $(CFLAGS)
	@printf "$(green)done$(reset)\n"

$(DEBUG_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(grey)compiling %-50s$(reset)" $<
	@$(CC) -o $@ -c $< $(CFLAGS)
	@printf "$(green)done$(reset)\n"

$(TEST_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(grey)compiling %-50s$(reset)" $<
	@$(CC) -o $@ -c $< $(CFLAGS)
	@printf "$(green)done$(reset)\n"

## RUN ##

run: release
	@printf "$(blue)running $(RELEASE_OUT)$(reset)\n"
	@./$(RELEASE_OUT)

run_debug: debug
	@printf "$(blue)running $(DEBUG_OUT)$(reset)\n"
	@./$(DEBUG_OUT)

tests_run: test
	@printf "$(blue)running $(UNIT_OUT)$(reset)\n"
	./$(UNIT_OUT)

	@printf "$(blue)generating coverage$(reset)\n"
	gcovr --exclude tests/ --exclude src/main.c
	gcovr --branches --exclude tests/ --exclude src/main.c

## CLEANING ##

clean:
	@printf "$(blue)cleaning build$(reset)\n"
	@$(RM) -r $(BUILD_DIR)

fclean: clean
	@printf "$(blue)cleaning binaries$(reset)\n"
	@$(RM) $(RELEASE_OUT) $(DEBUG_OUT) $(TEST_OUT)

re: fclean all

## HELP ##

help:
	@printf "$(bold)$(green)TARGETS$(reset)\n"

	@printf "make $(bold)release$(reset)\toptimize for performance "
	@printf "\t\t$(grey)output: $(underline)$(RELEASE_OUT)$(reset)\n"
	@printf "make $(bold)debug$(reset)\tdebug infos and sanitizers enabled "
	@printf "\t$(grey)output: $(underline)$(DEBUG_OUT)$(reset)\n"
	@printf "make $(bold)test$(reset)\tcompile tests "
	@printf "\t\t\t\t$(grey)output: $(underline)$(TEST_OUT)$(reset)\n"

	@printf "\n$(bold)$(green)VARIABLES$(reset)\n"
	@printf "$(bold)CFLAGS$(reset)\t\tadditional compiler flags\n"
	@printf "$(bold)NO_SANITIZE$(reset)\tdisable sanitizers\n"

.PHONY: all release debug run run_debug clean fclean re help
