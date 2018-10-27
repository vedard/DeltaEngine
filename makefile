all:
	@$(MAKE) --no-print-directory -C Delta
	@$(MAKE) --no-print-directory -C DeltaTest

Delta:
	@$(MAKE) --no-print-directory -C Delta

DeltaTest:
	@$(MAKE) --no-print-directory -C DeltaTest

clean:
	@$(MAKE) --no-print-directory -C Delta clean
	@$(MAKE) --no-print-directory -C DeltaTest clean

.PHONY: clean Delta DeltaTest