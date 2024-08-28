exFile := race.exe
srcDirs := src src/caps libs/myRealTime/src libs/cli/src
incDirs := ./include ./include/caps ./libs/myRealTime/include ./libs/myRealTime/mod_include ./libs/cli/include

#Flags to make rules for .h dependencies (look for changes in included files)
DEPFLAGS := -MP -MD

#Add -I into each include directory
INCLUDES := $(foreach D,$(incDirs),-I$(D))

#Find all .cpp files and put into variable
CPPFiles := $(foreach D,$(srcDirs),$(wildcard $(D)/*.cpp))

#Get all object (.o) files from CPPFiles. Put them in obj/ folder (ignoring ./ prefix since obj/./main.o is wrong)
objFiles := $(addprefix build/,$(patsubst ./%,%,$(patsubst %.cpp,%.o,$(CPPFiles))))
#do the same with dependecy (.d) files
depFiles := $(addprefix build/,$(patsubst ./%,%,$(patsubst %.cpp,%.d,$(CPPFiles))))

all: $(exFile)

#Create executable from object files
$(exFile): $(objFiles)
	g++ -std=c++20 -o $@ $^
	echo $(depFiles)

#create object files and dependency files (create build folder if it does not exist)
build/%.o:%.cpp
	@mkdir -p $(dir $@)
	g++ -std=c++20 $(INCLUDES) $(DEPFLAGS) -c -o $@ $<

#Remove executable file and build folder container all object files and dependency files
clean:
	rm -f $(exFile)
	rm -rf ./build

# include the dependencies
-include $(depFiles)