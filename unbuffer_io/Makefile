TGT := main
SRCS := $(wildcard *.c)

CFLAGS += -g

.PHONY: all
all: $(TGT)

$(TGT): $(SRCS:.c=.o)
	$(CC) $^ $(OUTPUT_OPTION)

.PHONY: clean
clean:
	-rm -rf $(TGT) $(SRCS:.c=.o)

.PHONY: rebuild
rebuild: clean $(TGT)
