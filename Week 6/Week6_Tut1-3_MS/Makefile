VULKAN_SDK_PATH=/Users/sabeeh/VulkanSDK/1.3.275.0/macOS
CFLAGS = -std=c++17 -I. -I/opt/homebrew/opt/glm/include -I$(VULKAN_SDK_PATH)/include -I/usr/local/include -I./glfw-3.3.9.bin.MACOS/include
LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib `pkg-config --static --libs glfw3` -lvulkan -L./glfw-3.3.9.bin.MACOS/lib-arm64

a.out: main.cpp
	g++ $(CFLAGS) -o a.out main.cpp $(LDFLAGS)

.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out