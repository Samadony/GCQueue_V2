#We try to detect the OS we are running on, and adjust commands as needed
CLEANUP = rm -f
MKDIR = mkdir


#Path Definitions
PATHS = ./
PATHI = ./
PATHB = ../Build/
PATHA = $(PATHB)/Archives/

SRCS = $(wildcard $(PATHS)*.c)
OBJS = $(patsubst $(PATHS)%.c,$(PATHB)%.o,$(SRCS))
TGT = $(PATHA)libConsolePublisher.a

CPPFLAGS += -I../GCQueue/ -I../utils/

#targets
.PHONY: rebuild clean build test retest

rebuild: clean build
	
build: $(TGT)
	
$(TGT) : $(OBJS)
	$(Q)$(AR) $(ARFLAGS) $@ $^
	rm -f $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^ -o $@

clean:
	$(CLEANUP) $(TGT)