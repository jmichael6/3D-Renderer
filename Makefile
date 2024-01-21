#BUILD VARIABLES

SRCS         :=  \
	pattern.c \
	shape.c \
	sphere.c \
	plane.c \
	ray_casting.c \
	lighting.c \
	transform.c \
	matrix.c \
	tuple.c  \
	canvas.c  \
	tests/unit_test.c \
	world.c 

SRC_DIR      := src
SRCS         := $(SRCS:%=$(SRC_DIR)/%)


TESTS        := \
	test_tuple \
	test_matrix \
	test_canvas \
	test_transform \
	test_lighting \
	test_sphere \
	test_ray_casting \
	test_world 

TEST_SRC_DIR := src/tests
TEST_BIN_DIR := tests
TEST_SRCS    := $(TESTS:%=$(TEST_SRC_DIR)/%.c)
TESTS        := $(TESTS:%=$(TEST_BIN_DIR)/%)

TARGETS      := \
	clock \
	projectile \
	render_sphere \
	render_scene 

BIN_DIR      := bin
TARGET_SRCS  := $(TARGETS:%=$(SRC_DIR)/%.c)
TARGETS      := $(TARGETS:%=$(BIN_DIR)/%)


BUILD_DIR    := obj
OBJS         := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS         := $(OBJS:.o=.d) $(TESTS:%=%.d) $(TARGETS:%=%.d)

CC           := gcc
CFLAGS       := -Wall -Wextra -Werror
CPPFLAGS     := -MMD -I include 
CPP_NODEP    := -I include
LDFLAGS      := -lm
 

# UTILITIES USED

RM         := rm -f
DIR_DUP     = mkdir -p $(@D)
MAKE       := make

# BUILD RECIPES

all: $(TESTS) $(TARGETS)

$(TARGETS) : $(OBJS) $(TARGET_SRCS)
	$(CC) $(CFLAGS) $(CPP_NODEP) $(SRC_DIR)/$(@F).c  $(OBJS) -o $@ $(LDFLAGS)
	$(info CREATED $(@F:.c=))

$(TESTS) : $(OBJS) $(TEST_SRCS)
	$(CC) $(CFLAGS) $(CPP_NODEP) $(TEST_SRC_DIR)/$(@F).c  $(OBJS) -o $@ $(LDFLAGS)
	$(info CREATED $(@F:.c=))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< $(LDFLAGS)
	$(info CREATED $@)

-include $(DEPS)

clean: 
	$(RM) $(OBJS) $(DEPS)

fclean: 
	$(MAKE) clean
	$(RM) $(TARGETS) $(TESTS)

re: 
	$(MAKE) fclean
	$(MAKE) all

# SPECIAL 

.PHONY: clean fclean re 
.SILENT:


