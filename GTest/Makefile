
.PHONY: all build_gtest build_gmock clean clean_gtest clean_gmock

all: build_gtest build_gmock
clean: clean_gtest clean_gmock

build_gtest:
	$(MAKE) all -C ./googletest 
build_gmock:
	$(MAKE) all -C ./googlemock
	
clean_gtest:
	$(MAKE) clean -C ./googletest
clean_gmock:
	$(MAKE) clean -C ./googlemock