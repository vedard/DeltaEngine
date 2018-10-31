all:
	@$(MAKE) --no-print-directory -C Delta
	@$(MAKE) --no-print-directory -C DeltaPlayground

Delta:
	@$(MAKE) --no-print-directory -C Delta

DeltaPlayground:
	@$(MAKE) --no-print-directory -C DeltaPlayground

clean:
	@$(MAKE) --no-print-directory -C Delta clean
	@$(MAKE) --no-print-directory -C DeltaPlayground clean

.PHONY: clean Delta DeltaPlayground