Q = @
.PHONY: rebuild build clean retest
rebuild: clean build
#Tool Definitions
CC = gcc
CPPFLAGS = -I. -Iutils/ -IConsoleUser2_Interrupt/ -IConsoleUser1_Task/ -IConsolePublisher/ -LBuild/Archives/
LDFLAGS += -LBuild/Archives/
CFLAGS = -std=c99
build:
	#Build libraries
	$(Q) $(MAKE) build -C ./GCQueue
	$(Q) $(MAKE) build -C ./ConsolePublisher
	$(Q) $(MAKE) build -C ./ConsoleUser1_Task
	$(Q) $(MAKE) build -C ./ConsoleUser2_Interrupt
	#Link All and get the output
	gcc $(CPPFLAGS) $(LDFLAGS) main.c -o ./build/main.exe  -lConsoleUser1_Task -lConsoleUser2_Interrupt -lConsolePublisher -lGCQueue
	./build/main.exe
clean:
	$(Q)rm -f ./build/Archives/*.*
	$(Q)rm -f ./build/*.*
retest:
	$(Q)$(MAKE) retest -C ./GCQueue/Test
test:
	$(Q)$(MAKE) test -C ./GCQueue/Test