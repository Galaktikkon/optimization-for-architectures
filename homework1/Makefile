CXX = g++
CXXFLAGS = -O3 -std=c++17

SRC_DIR = src
BUILD_DIR = build
DATA_DIR = data
REPORT_DIR = report
BENCHMARK_FILE = benchmark.txt
DATA_FILE = data.txt
INPUTS := $(wildcard $(DATA_DIR)/*.txt)

VERSIONS := $(basename $(notdir $(wildcard $(SRC_DIR)/normalize*.cpp)))

all: $(addprefix $(BUILD_DIR)/, $(VERSIONS))

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

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

clean:
	@rm -rf $(BUILD_DIR)
