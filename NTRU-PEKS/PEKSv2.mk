##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PEKSv2
ConfigurationName      :=Debug
WorkspacePath          :=/scratch/nathan_benchmark/Full_PEKS/NTRU-PEKS
ProjectPath            :=/scratch/nathan_benchmark/Full_PEKS/NTRU-PEKS
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Ozgur Ozmen
Date                   :=30/10/17
CodeLitePath           :=/home/ozgur/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
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
ObjectsFileList        :="PEKSv2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lntl -lgmp -lb2 -lzmq
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix) $(IntermediateDirectory)/io.cc$(ObjectSuffix) $(IntermediateDirectory)/FFT.cc$(ObjectSuffix) $(IntermediateDirectory)/Algebra.cc$(ObjectSuffix) $(IntermediateDirectory)/PEKS.cc$(ObjectSuffix) $(IntermediateDirectory)/Random.cc$(ObjectSuffix) $(IntermediateDirectory)/Sampling.cc$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix): Scheme.cc $(IntermediateDirectory)/Scheme.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/Scheme.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scheme.cc$(DependSuffix): Scheme.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Scheme.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/Scheme.cc$(DependSuffix) -MM Scheme.cc

$(IntermediateDirectory)/Scheme.cc$(PreprocessSuffix): Scheme.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scheme.cc$(PreprocessSuffix) Scheme.cc

$(IntermediateDirectory)/io.cc$(ObjectSuffix): io.cc $(IntermediateDirectory)/io.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/io.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/io.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/io.cc$(DependSuffix): io.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/io.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/io.cc$(DependSuffix) -MM io.cc

$(IntermediateDirectory)/io.cc$(PreprocessSuffix): io.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/io.cc$(PreprocessSuffix) io.cc

$(IntermediateDirectory)/FFT.cc$(ObjectSuffix): FFT.cc $(IntermediateDirectory)/FFT.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/FFT.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FFT.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FFT.cc$(DependSuffix): FFT.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FFT.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/FFT.cc$(DependSuffix) -MM FFT.cc

$(IntermediateDirectory)/FFT.cc$(PreprocessSuffix): FFT.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FFT.cc$(PreprocessSuffix) FFT.cc

$(IntermediateDirectory)/Algebra.cc$(ObjectSuffix): Algebra.cc $(IntermediateDirectory)/Algebra.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/Algebra.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Algebra.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Algebra.cc$(DependSuffix): Algebra.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Algebra.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/Algebra.cc$(DependSuffix) -MM Algebra.cc

$(IntermediateDirectory)/Algebra.cc$(PreprocessSuffix): Algebra.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Algebra.cc$(PreprocessSuffix) Algebra.cc

$(IntermediateDirectory)/PEKS.cc$(ObjectSuffix): PEKS.cc $(IntermediateDirectory)/PEKS.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/PEKS.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PEKS.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PEKS.cc$(DependSuffix): PEKS.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PEKS.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/PEKS.cc$(DependSuffix) -MM PEKS.cc

$(IntermediateDirectory)/PEKS.cc$(PreprocessSuffix): PEKS.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PEKS.cc$(PreprocessSuffix) PEKS.cc

$(IntermediateDirectory)/Random.cc$(ObjectSuffix): Random.cc $(IntermediateDirectory)/Random.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/Random.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Random.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Random.cc$(DependSuffix): Random.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Random.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/Random.cc$(DependSuffix) -MM Random.cc

$(IntermediateDirectory)/Random.cc$(PreprocessSuffix): Random.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Random.cc$(PreprocessSuffix) Random.cc

$(IntermediateDirectory)/Sampling.cc$(ObjectSuffix): Sampling.cc $(IntermediateDirectory)/Sampling.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) $(ProjectPath)"/Sampling.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sampling.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Sampling.cc$(DependSuffix): Sampling.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Sampling.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/Sampling.cc$(DependSuffix) -MM Sampling.cc

$(IntermediateDirectory)/Sampling.cc$(PreprocessSuffix): Sampling.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Sampling.cc$(PreprocessSuffix) Sampling.cc


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


