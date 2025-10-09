.PHONY: build
build:
	west build

.PHONY: flash-usb
flash-usb:
	west flash --runner stm32cubeprogrammer --port=USB1

.PHONY: flash-swd
flash-swd:
	west flash

.PHONY: clean
clean:
	rm -rf build