CXX = g++
CXXFLAGS = -O2 -std=c++17

SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data
REPORT_DIR = report
BENCHMARK_FILE = benchmark.txt
DATA_FILE = data.txt
INPUTS := $(wildcard $(DATA_DIR)/*.txt)

PROFILE_BUILD_DIR = build-gprof
INPUT_FILE_GPROF = $(DATA_DIR)/input1.txt

VERSIONS := $(basename $(notdir $(wildcard $(SRC_DIR)/normalize*.cpp)))

all: $(addprefix $(BUILD_DIR)/, $(VERSIONS))

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(PROFILE_BUILD_DIR):
	@mkdir -p $(PROFILE_BUILD_DIR)

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)

test: all | ${REPORT_DIR}
	
	@rm -f $(REPORT_DIR)/${BENCHMARK_FILE}
	@rm -f $(REPORT_DIR)/${DATA_FILE}
	@touch $(REPORT_DIR)/${BENCHMARK_FILE}
	@touch $(REPORT_DIR)/${DATA_FILE}

	@echo "==== TESTING ====" > $(REPORT_DIR)/${BENCHMARK_FILE}
	@echo "" >> $(REPORT_DIR)/${BENCHMARK_FILE}
	@for prog in $(VERSIONS); do \
		echo "==== $$prog ===="; \
		echo "==== $$prog ====" >> $(REPORT_DIR)/${BENCHMARK_FILE}; \
		for INPUT in $(INPUTS); do \
			echo "Testing input: $$INPUT"; \
			echo "Testing input: $$INPUT" >> $(REPORT_DIR)/${BENCHMARK_FILE}; \
			echo -n "\t" >> $(REPORT_DIR)/${BENCHMARK_FILE}; \
			./$(BUILD_DIR)/$$prog $(REPORT_DIR)/${DATA_FILE} < $$INPUT >> $(REPORT_DIR)/${BENCHMARK_FILE}; \
		done; \
		echo "" >> $(REPORT_DIR)/${BENCHMARK_FILE}; \
		echo "" >> $(REPORT_DIR)/${DATA_FILE}; \
	done



gprof: | $(PROFILE_BUILD_DIR) $(REPORT_DIR)
	@for prog in $(VERSIONS); do \
		SRC=$(SRC_DIR)/$$prog.cpp; \
		OUT=$(PROFILE_BUILD_DIR)/$$prog; \
		$(CXX) -pg -std=c++17 -o $$OUT $$SRC; \
		./$$OUT /dev/null < $(INPUT_FILE_GPROF) > /dev/null; \
		echo "Generating gprof report for $$prog..."; \
		gprof $$OUT gmon.out > $(REPORT_DIR)/$$prog.gprof.txt; \
		rm -f gmon.out; \
		rm -rf $(PROFILE_BUILD_DIR)/$$prog; \
	done

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(PROFILE_BUILD_DIR)
	@rm -rf $(REPORT_DIR)
