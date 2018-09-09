# CS140 makefile
# original by robobenklein / bklein3@utk
# GPLv3 license
# contact me if this breaks for some reason,
# but it's not my fault if you delete your programs using this

CC:=g++

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

venv_dir := ~/.cs140-cfapi-venv
canvas_dir := cs140/makefile_uploaded

dirname = $(patsubst %/,%,$(dir $1))

lab:=$(notdir $(current_dir))
tardir:=$(abspath $(dir $(mkfile_path)))
tarfile:=$(tardir)/$(lab)_$(shell date --rfc-3339=date 2>/dev/null || python -c 'import datetime;print(str(datetime.date.today()))').tar.gz
SOURCEDIR := .

CPP_FILES := $(shell find $(SOURCEDIR) -name '*.cpp')
HPP_FILES := $(shell find $(SOURCEDIR) -name '*.hpp' -o -name '*.h')

CPP_MAINS := $(shell grep -nwl -e '^int main' $(CPP_FILES) /dev/null | tr '\n' ' ' )
PROGS = $(patsubst %.cpp,%,$(CPP_MAINS))

CC_FLAGS := -std=c++11 -g

# Check that given variables are set and all have non-empty values,
# die with an error otherwise.
# https://stackoverflow.com/questions/10858261/abort-makefile-if-variable-not-set
# Params:
#   1. Variable name(s) to test.
#   2. (optional) Error message to print.
check_defined = \
    $(strip $(foreach 1,$1, \
        $(call __check_defined,$1,$(strip $(value 2)))))
__check_defined = \
    $(if $(value $1),, \
      $(error Undefined $1$(if $2, ($2))))

all: $(PROGS)
	# sources: $(CPP_MAINS)
	# outputs: $(PROGS)

%: %.cpp
	# building: $@
	$(CC) $(CC_FLAGS)  -o $@ $<

clean:
	# removing built programs: $(PROGS)
	gvfs-trash --force $(PROGS)

tar:
	# lab: $(lab)
	tar -cvzf $(TAR_FLAGS) $(tarfile) $(CPP_FILES) $(HPP_FILES)

upload: update-cfapi
	@:$(call check_defined, FILE, usage: `make upload FILE=path/to/file`)
	$(venv_dir)/bin/python $(venv_dir)/cfapi/post-file.py "$(FILE)" -D $(canvas_dir)
	@echo -e 'File uploaded to \033[36mhttps://utk.instructure.com/files/folder/self/$(canvas_dir)'

uptar: tar update-cfapi
	$(venv_dir)/bin/python $(venv_dir)/cfapi/post-file.py $(tarfile) -D tars
	@echo -e 'File uploaded to \033[36mhttps://utk.instructure.com/files/folder/self/tars\033[0m'

update:
	which curl
	$(eval updatefile = /tmp/${USER}.update.makefile )
	curl -fsSL https://gist.githubusercontent.com/robobenklein/9c67cfebed431003aa11cabbbf4438a3/raw/Makefile > $(updatefile)
	test -s $(updatefile)
	gvfs-trash $(mkfile_path)
	mv $(updatefile) $(mkfile_path)
	test -s $(mkfile_path)
	# if the updated version doesn't work, the old Makefile is in your trash, probably ~/.local/share/Trash/
	# if there's a problem with the latest version, report bugs to bklein3@vols.utk.edu
	# thanks for using my Makefile!

update-cfapi:
	test -d $(venv_dir) || virtualenv $(venv_dir)
	$(venv_dir)/bin/pip install -U requests
	$(eval updatefile = /tmp/${USER}.update.makefile.post-file.py )
	curl -fsSL https://gist.githubusercontent.com/robobenklein/9c67cfebed431003aa11cabbbf4438a3/raw/post-file.py > $(updatefile)
	test -s $(updatefile)
	mkdir -p $(venv_dir)/cfapi
	mv $(updatefile) $(venv_dir)/cfapi/post-file.py

help:
	@echo -e '\033[36mCS140 makefile\033[0m by \033[31mrobobenklein\033[0m aka \033[36mbklein3\033[0m'
	@echo -e 'Running \033[36mmake\033[0m will compile these files: '
	@echo -e '    \033[44m$(CPP_MAINS)\033[0m'
	@echo -e 'into these output programs: '
	@echo -e '    \033[44m$(PROGS)\033[0m'
	@echo -e 'only if the source files have changed, so no need to recompile irrelevant parts'
	@echo -e ''
	@echo -e 'When done with a lab, you can use `make tar` to tar.gz your .cpp files'
	@echo -e 'which will put all of these files: '
	@echo -e '    \033[44m$(CPP_FILES) $(HPP_FILES)\033[0m'
	@echo -e 'into a tar.gz file here: \033[36m$(tarfile)\033[0m'
	@echo -e ''
	@echo -e 'If you want to upload this file to canvas, you can use \033[36mmake uptar\033[0m to tar and upload to canvas.'
	@echo -e 'You will be prompted for the information needed as you run it for the first time.'
	@echo -e 'If you just want to upload a single file or want to do so manually, use \033[36mmake upload FILE=folder/something.cpp\033[0m'
	@echo -e ''
	@echo -e 'If you want to know what a make command will do before you run it,'
	@echo -e ' use \033[36mmake -n\033[0m in place of \033[36mmake\033[0m and make will show you the commands without running them'
	@echo -e 'Note that things beginning with a \033[36m#\033[0m are comments!'
	@echo -e ''
	@echo -e 'If you have feedback, bugs, or suggestions, email me! <\033[36mbklein3@vols.utk.edu\033[0m>'
