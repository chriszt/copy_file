TGT := copy_file
SRCS := $(wildcard *.c)

CFLAGS += -g

.PHONY: all
all: $(TGT)

$(TGT): $(SRCS:.c=.o)
	$(CC) $^ $(OUTPUT_OPTION)

.PHONY: clean
clean:
	-rm -rf $(SRCS:.c=.o) $(TGT)

.PHONY: rebuild
rebuild: clean $(TGT)
