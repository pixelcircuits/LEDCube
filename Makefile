#************************************************************************
# Options and configuration
#************************************************************************

# The name of your project (used to name the compiled .hex file)
TARGET= driver

# set your MCU type here, or make command line `make MCU=MK20DX256`
MCU= MK20DX256
#MCU= MKL26Z64
#MCU= MK64FX512
#MCU= MK66FX1M0

# make it lower case
LOWER_MCU:= $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$(MCU)))))))))))))))))))))))))))
MCU_LD= $(LOWER_MCU).ld

# configurable options
OPTIONS= -DF_CPU=96000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH
#F_CPU=96000000
#F_CPU=72000000
#F_CPU=48000000
#F_CPU=24000000
#F_CPU=16000000
#F_CPU=8000000
#F_CPU=4000000
#F_CPU=2000000

# options needed by many Arduino libraries to configure for Teensy 3.x
OPTIONS+= -D__$(MCU)__ -DARDUINO=10805 -DTEENSYDUINO=144

# use "cortex-m4" for Teensy 3.x
# use "cortex-m0plus" for Teensy LC
CPUARCH= cortex-m4
#CPUARCH= cortex-m0plus


#************************************************************************
# Location of Teensyduino utilities, Toolchain, and Code
#************************************************************************

# path location for Teensy Loader, teensy_post_compile and teensy_reboot (on Linux)
TOOLSPATH= tools

# path location for Teensy 3 core
COREPATH= teensy3

# path location for Teensy 3 core
SRCPATH= src

# path location for the arm-none-eabi compiler
COMPILERPATH= tools/arm/bin

# path location for build directory
BUILDDIR= build


#************************************************************************
# Build rules (settings below this point usually do not need to be edited)
#************************************************************************

# CPPFLAGS = compiler options for C and C++
CPPFLAGS= -Wall -g -Os -mcpu=$(CPUARCH) -mthumb -MMD $(OPTIONS) -I$(COREPATH) -I$(SRCPATH)

# compiler options for C++ only
CXXFLAGS= -std=gnu++14 -felide-constructors -fno-exceptions -fno-rtti

# compiler options for C only
CFLAGS=

# linker options
LDFLAGS= -Os -Wl,--gc-sections,--defsym=__rtc_localtime=0 --specs=nano.specs -mcpu=$(CPUARCH) -mthumb -T$(COREPATH)/$(MCU_LD)

# additional libraries to link
LIBS= -lm


# names for the compiler programs
CC= $(abspath $(COMPILERPATH))/arm-none-eabi-gcc
CXX= $(abspath $(COMPILERPATH))/arm-none-eabi-g++
OBJCOPY= $(abspath $(COMPILERPATH))/arm-none-eabi-objcopy
SIZE= $(abspath $(COMPILERPATH))/arm-none-eabi-size

# automatically create lists of the sources and objects
TC_FILES:= $(wildcard $(COREPATH)/*.c)
TCPP_FILES:= $(wildcard $(COREPATH)/*.cpp)
C_FILES:= $(wildcard $(SRCPATH)/*.c)
CPP_FILES:= $(wildcard $(SRCPATH)/*.cpp)
SOURCES:= $(TC_FILES:.c=.o) $(TCPP_FILES:.cpp=.o) $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)
OBJS:= $(foreach src,$(SOURCES), $(BUILDDIR)/$(src))


all: hex

build: $(TARGET).elf

hex: $(TARGET).hex

post_compile: $(TARGET).hex
	@$(abspath $(TOOLSPATH))/teensy_post_compile -file="$(basename $<)" -path=$(CURDIR) -tools="$(abspath $(TOOLSPATH))"

reboot:
	@-$(abspath $(TOOLSPATH))/teensy_reboot

upload: post_compile reboot

$(BUILDDIR)/%.o: %.c
	@echo [CC] $<
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) -o "$@" -c "$<"

$(BUILDDIR)/%.o: %.cpp
	@echo [CXX] $<
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o "$@" -c "$<"

$(TARGET).elf: $(OBJS) $(COREPATH)/$(MCU_LD)
	@echo [ELF] $@
	@$(CC) $(LDFLAGS) -o "$@" $(OBJS) $(LIBS)

%.hex: %.elf
	@echo [HEX] $@
	@$(SIZE) "$<"
	@$(OBJCOPY) -O ihex -R .eeprom "$<" "$@"

clean:
	@echo Cleaning...
	@rmdir /q /s "$(BUILDDIR)"
	@del /f "$(TARGET).elf" "$(TARGET).hex"
