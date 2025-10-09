## installation of zephyr env

download and install stm32 cube prog 
https://www.st.com/en/development-tools/stm32cubeprog.html


### clone this repo
```bash
git clone git@github.com:aesirkth/atlas_load_cell.git
```

### move to the software directory
```bash
cd atlas_load_cell/software
```

### add udev rules
if the stm32cubeprog didn't add the udev files you can do this manually by:
```bash
cp 49-stlinkv3.rules /etc/udev/rules.d/
sudo udevadm trigger 
```

### setup python env

with pip:
```bash
python3 -m venv .venv
source .venv/bin/activate
pip install .
```

or with uv:
```bash
uv venv
source .venv/bin/activate
uv sync
```

### download zephyr

```bash
west update
```

### register zephyr as cmake package

```bash
west zephyr-export
```


### install zephyr python packages

with pip:
```bash
pip install -r ext/zephyr/scripts/requirements-base.txt
```

or with uv:
```bash
uv pip install -r ext/zephyr/scripts/requirements-base.txt
```

### install zephyr sdk

```bash
west sdk install --toolchains arm-zephyr-eabi
```


## build app

to build:
```bash
make
```

to flash over usb enter bootloader by holding the upper button while pressing the
lower button briefly. and then:
```bash
make flash-swd
```


## installation of dashboard env

```bash
cd dashboard
```

with pip:
```bash
python3 -m venv .venv
source .venv/bin/activate
pip install .
```

or with uv:
```bash
uv venv
source .venv/bin/activate
uv sync
```