CXXFLAGS = --std=c++17 -O0 -g
BUILD_DIR = ./build
TARGET = sbem_decode
	
all: prepare executable

release: CXXFLAGS = --std=c++17 -O2
release: prepare executable

prepare:
	mkdir -p $(BUILD_DIR)

executable:
	g++ -o $(BUILD_DIR)/$(TARGET) \
		$(CXXFLAGS) \
		-I./src \
		./src/types/activity.cpp \
		./src/types/ecg.cpp \
		./src/types/gesture.cpp \
		./src/types/hr.cpp \
		./src/types/temperature.cpp \
		./src/samples/samples.cpp \
		./src/samples/sample_utils.cpp \
		./src/samples/sample_csv.cpp \
		./src/sbem/sbem_loader.cpp \
		./src/sbem/sbem_utils.cpp \
		./src/main.cpp

clean:
	rm -r $(BUILD_DIR)

.PHONY: all clean release executable
