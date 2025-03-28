.PHONY: build
build:
	west build app

.PHONY: flash-usb
flash-usb:
	west flash --runner stm32cubeprogrammer --port=USB1

.PHONY: flash-swd
flash-swd:
	west flash