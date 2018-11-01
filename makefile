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

install:
	@$(MAKE) --no-print-directory -C Delta install

uninstall:
	@$(MAKE) --no-print-directory -C Delta uninstall

format:
	@find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;

.PHONY: clean Delta DeltaPlayground install uninstall format