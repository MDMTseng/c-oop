
TESTS=test_dcast_null test_destructor test_omni_cast test_heap_alloc test_virtual_destroy test_extends_macro
CFLAGS=-Wall -std=c99 -I../CxOOP_lib -I../example
OBJ_SRCS=../example/PARENT_OBJ.c ../example/CHILD_OBJ.c ../example/DECEN_OBJ.c

all: $(TESTS)
	@echo ""
	@echo "=== Running all tests ==="
	@fail=0; \
	for t in $(TESTS); do \
		echo "--- $$t ---"; \
		./$$t || fail=1; \
		echo ""; \
	done; \
	if [ $$fail -eq 0 ]; then \
		echo "=== ALL TEST SUITES PASSED ==="; \
	else \
		echo "=== SOME TEST SUITES FAILED ==="; \
		exit 1; \
	fi

%: %.c $(OBJ_SRCS)
	$(CC) $(CFLAGS) $< $(OBJ_SRCS) -o $@

clean:
	rm -f $(TESTS)
