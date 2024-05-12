RM_DIR = powershell "if (Test-Path $(1)) {Remove-Item -Path $(1) -Recurse -Force}"
CP_DIR = powershell -Command "Copy-Item -Path $(1) -Destination $(2) -Recurse -Force"


BUILD_FLAGS = --onefile
NAME = map_builder


build:
	@echo Building $(SCRIPT) into executable.
	@pyinstaller $(BUILD_FLAGS) $(NAME).py
	@$(call CP_DIR, dist/$(NAME).exe, $(NAME).exe)
	@$(call RM_DIR, build)
	@$(call RM_DIR, dist)
	@del $(NAME).spec
	@$(NAME).exe

run:
	@$(NAME).exe

clean:
	@$(call RM_DIR, build)
	@$(call RM_DIR, dist)
	@del $(NAME).spec
