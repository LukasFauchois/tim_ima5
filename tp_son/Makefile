export CC=g++
export CFLAGS=-W -Wall

MAIN_DIR=main
SON_PUR_DIR=son_pur
SON_ETIRE_DIR=son_etire
TIME_STRETCHING_DIR=time_stretching

EXEC1=$(MAIN_DIR)/main
EXEC2=$(SON_PUR_DIR)/son_pur
EXEC3=$(SON_ETIRE_DIR)/son_etire
EXEC4=$(TIME_STRETCHING_DIR)/time_stretching


all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

$(EXEC1):
	@(cd $(MAIN_DIR) && $(MAKE))

$(EXEC2):
	@(cd $(SON_PUR_DIR) && $(MAKE))

$(EXEC3):
	@(cd $(SON_ETIRE_DIR) && $(MAKE))

$(EXEC4):
	@(cd $(TIME_STRETCHING_DIR) && $(MAKE))


.PHONY: clean mrproper $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)

clean:
	@(cd $(MAIN_DIR) && $(MAKE) $@)
	@(cd $(SON_PUR_DIR) && $(MAKE) $@)
	@(cd $(SON_ETIRE_DIR) && $(MAKE) $@)
	@(cd $(TIME_STRETCHING_DIR) && $(MAKE) $@)
	rm -rf *.o

mrproper: clean
	@(cd $(MAIN_DIR) && $(MAKE) $@)
	@(cd $(SON_PUR_DIR) && $(MAKE) $@)
	@(cd $(SON_ETIRE_DIR) && $(MAKE) $@)
	@(cd $(TIME_STRETCHING_DIR) && $(MAKE) $@)
