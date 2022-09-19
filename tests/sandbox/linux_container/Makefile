NAME=ub1804
VOLUME_NAME=workspaceFolder
VOLUME_DIR=/opt/$(VOLUME_NAME)
WORKDIR=/Users/user/42cursus/containers_ft/tests/sandbox/std=
SCRIPT=compile_test.sh

PIPE=$(WORKDIR)/pipe
COMMAND=$(WORKDIR)/command
LOG_INFO=$(WORKDIR)/eval.log
LOG_ERROR=$(WORKDIR)/errors.log

DOCKER_SHELL=/bin/bash
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
	touch $(PIPE) && touch $(COMMAND)
	docker build -f ./Dockerfile -t $(NAME) .
	docker run --rm $(RUNMODE) --name $(NAME) \
		-v $(WORKDIR):$(VOLUME_DIR) \
		 $(NAME) $(DOCKER_SHELL)

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
	rm -rf $(LOG_INFO)
	rm -rf $(LOG_ERROR)
	$(MAKE) stop
	-docker rm $(NAME)
fclean: clean
	-docker stop $(NAME)
	-docker kill $(NAME)
	-yes | docker builder prune
	-yes | docker volume prune
	-yes | docker rm -vf $(docker ps -aq)
	-yes | docker rmi -f $(docker images -aq)

re: clean all
