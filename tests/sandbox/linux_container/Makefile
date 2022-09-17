NAME=ub1804
VOLUME_NAME=workspaceFolder
VOLUME_DIR=/opt/$(VOLUME_NAME)
WORKDIR=/Users/user/42cursus/containers_ft/tests/sandbox/std=
SCRIPT=compile_test.sh

PIPE=$(WORKDIR)/pipe

BACKGR=-d
FOREGR=-it

RUNMODE=$(FOREGR)

DM_NAME=default

ifeq ($(mode),daemon)
	RUNMODE := $(BACKGR)
endif

.PHONY: $(NAME) pre-build

all: $(NAME)

$(NAME): pre-build
	cp $(SCRIPT) $(WORKDIR)
	touch $(PIPE)
	docker build -t $(NAME) .
	docker run --rm --name $(NAME) $(RUNMODE) \
		-v $(WORKDIR):$(VOLUME_DIR)  $(NAME)

pre-build:
	. ./start_docker_machine.sh
submerge:
	docker exec $(FOREGR) $(NAME) /bin/bash
compile:
	docker exec $(NAME) $(VOLUME_DIR)/$(SCRIPT)
#watch:
#	tail -f my.sock

stop:
	docker stop $(NAME)
clean: 
	rm -rf $(PIPE)
	$(MAKE) stop
	-docker rm $(NAME)
fclean: clean
	rm -rf $(PIPE)
	-docker stop $(NAME)
	-docker kill $(NAME)
	-yes | docker builder prune
	-yes | docker volume prune
	-yes | docker rm -vf $(docker ps -aq)
	-yes | docker rmi -f $(docker images -aq)

re: clean all
