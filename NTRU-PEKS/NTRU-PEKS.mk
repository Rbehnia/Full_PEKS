##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=NTRU-PEKS
ConfigurationName      :=Release
WorkspacePath          := "/home/bob/Documents/MyCode"
ProjectPath            := "/home/bob/Documents/MyCode/ozgur"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Bob
Date                   :=14/09/17
CodeLitePath           :="/home/bob/.codelite"
LinkerName             :=clang++
SharedObjectLinkerName :=clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="NTRU-PEKS.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lntl -lgmp 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := clang++
CC       := clang
CXXFLAGS :=  -O2 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix) $(IntermediateDirectory)/Sampling.cc$(ObjectSuffix) $(IntermediateDirectory)/Random.cc$(ObjectSuffix) $(IntermediateDirectory)/PEKS.cc$(ObjectSuffix) $(IntermediateDirectory)/io.cc$(ObjectSuffix) $(IntermediateDirectory)/FFT.cc$(ObjectSuffix) $(IntermediateDirectory)/Algebra.cc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix): Scheme.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/Scheme.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scheme.cc$(PreprocessSuffix): Scheme.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scheme.cc$(PreprocessSuffix) "Scheme.cc"

$(IntermediateDirectory)/Sampling.cc$(ObjectSuffix): Sampling.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/Sampling.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sampling.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sampling.cc$(PreprocessSuffix): Sampling.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sampling.cc$(PreprocessSuffix) "Sampling.cc"

$(IntermediateDirectory)/Random.cc$(ObjectSuffix): Random.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/Random.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Random.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Random.cc$(PreprocessSuffix): Random.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Random.cc$(PreprocessSuffix) "Random.cc"

$(IntermediateDirectory)/PEKS.cc$(ObjectSuffix): PEKS.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/PEKS.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PEKS.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PEKS.cc$(PreprocessSuffix): PEKS.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PEKS.cc$(PreprocessSuffix) "PEKS.cc"

$(IntermediateDirectory)/io.cc$(ObjectSuffix): io.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/io.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/io.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/io.cc$(PreprocessSuffix): io.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/io.cc$(PreprocessSuffix) "io.cc"

$(IntermediateDirectory)/FFT.cc$(ObjectSuffix): FFT.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/FFT.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FFT.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FFT.cc$(PreprocessSuffix): FFT.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FFT.cc$(PreprocessSuffix) "FFT.cc"

$(IntermediateDirectory)/Algebra.cc$(ObjectSuffix): Algebra.cc 
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Documents/MyCode/ozgur/Algebra.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Algebra.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Algebra.cc$(PreprocessSuffix): Algebra.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Algebra.cc$(PreprocessSuffix) "Algebra.cc"

##
## Clean
##
clean:
	$(RM) -r ./Release/


