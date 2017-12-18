##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=80BonehPeks
ConfigurationName      :=Debug
WorkspacePath          :=/home/bob/Desktop/80BonehPeks
ProjectPath            :=/home/bob/Desktop/80BonehPeks/80BonehPeks
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Bob
Date                   :=03/11/17
CodeLitePath           :=/home/bob/.codelite
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
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="80BonehPeks.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lmiracl  -lzmq
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
CXXFLAGS :=  -g -O2 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/ecn.cpp$(ObjectSuffix) $(IntermediateDirectory)/ecn3.cpp$(ObjectSuffix) $(IntermediateDirectory)/peks.cpp$(ObjectSuffix) $(IntermediateDirectory)/zzn.cpp$(ObjectSuffix) $(IntermediateDirectory)/zzn3.cpp$(ObjectSuffix) $(IntermediateDirectory)/big.cpp$(ObjectSuffix) $(IntermediateDirectory)/zzn18.cpp$(ObjectSuffix) $(IntermediateDirectory)/kss_pair.cpp$(ObjectSuffix) $(IntermediateDirectory)/zzn6.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/ecn.cpp$(ObjectSuffix): ecn.cpp $(IntermediateDirectory)/ecn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/ecn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ecn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ecn.cpp$(DependSuffix): ecn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ecn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ecn.cpp$(DependSuffix) -MM ecn.cpp

$(IntermediateDirectory)/ecn.cpp$(PreprocessSuffix): ecn.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ecn.cpp$(PreprocessSuffix) ecn.cpp

$(IntermediateDirectory)/ecn3.cpp$(ObjectSuffix): ecn3.cpp $(IntermediateDirectory)/ecn3.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/ecn3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ecn3.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ecn3.cpp$(DependSuffix): ecn3.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ecn3.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ecn3.cpp$(DependSuffix) -MM ecn3.cpp

$(IntermediateDirectory)/ecn3.cpp$(PreprocessSuffix): ecn3.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ecn3.cpp$(PreprocessSuffix) ecn3.cpp

$(IntermediateDirectory)/peks.cpp$(ObjectSuffix): peks.cpp $(IntermediateDirectory)/peks.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/peks.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/peks.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/peks.cpp$(DependSuffix): peks.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/peks.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/peks.cpp$(DependSuffix) -MM peks.cpp

$(IntermediateDirectory)/peks.cpp$(PreprocessSuffix): peks.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/peks.cpp$(PreprocessSuffix) peks.cpp

$(IntermediateDirectory)/zzn.cpp$(ObjectSuffix): zzn.cpp $(IntermediateDirectory)/zzn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/zzn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zzn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zzn.cpp$(DependSuffix): zzn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zzn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/zzn.cpp$(DependSuffix) -MM zzn.cpp

$(IntermediateDirectory)/zzn.cpp$(PreprocessSuffix): zzn.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zzn.cpp$(PreprocessSuffix) zzn.cpp

$(IntermediateDirectory)/zzn3.cpp$(ObjectSuffix): zzn3.cpp $(IntermediateDirectory)/zzn3.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/zzn3.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zzn3.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zzn3.cpp$(DependSuffix): zzn3.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zzn3.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/zzn3.cpp$(DependSuffix) -MM zzn3.cpp

$(IntermediateDirectory)/zzn3.cpp$(PreprocessSuffix): zzn3.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zzn3.cpp$(PreprocessSuffix) zzn3.cpp

$(IntermediateDirectory)/big.cpp$(ObjectSuffix): big.cpp $(IntermediateDirectory)/big.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/big.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/big.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/big.cpp$(DependSuffix): big.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/big.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/big.cpp$(DependSuffix) -MM big.cpp

$(IntermediateDirectory)/big.cpp$(PreprocessSuffix): big.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/big.cpp$(PreprocessSuffix) big.cpp

$(IntermediateDirectory)/zzn18.cpp$(ObjectSuffix): zzn18.cpp $(IntermediateDirectory)/zzn18.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/zzn18.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zzn18.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zzn18.cpp$(DependSuffix): zzn18.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zzn18.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/zzn18.cpp$(DependSuffix) -MM zzn18.cpp

$(IntermediateDirectory)/zzn18.cpp$(PreprocessSuffix): zzn18.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zzn18.cpp$(PreprocessSuffix) zzn18.cpp

$(IntermediateDirectory)/kss_pair.cpp$(ObjectSuffix): kss_pair.cpp $(IntermediateDirectory)/kss_pair.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/kss_pair.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kss_pair.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kss_pair.cpp$(DependSuffix): kss_pair.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/kss_pair.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/kss_pair.cpp$(DependSuffix) -MM kss_pair.cpp

$(IntermediateDirectory)/kss_pair.cpp$(PreprocessSuffix): kss_pair.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kss_pair.cpp$(PreprocessSuffix) kss_pair.cpp

$(IntermediateDirectory)/zzn6.cpp$(ObjectSuffix): zzn6.cpp $(IntermediateDirectory)/zzn6.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bob/Desktop/80BonehPeks/80BonehPeks/zzn6.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zzn6.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zzn6.cpp$(DependSuffix): zzn6.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zzn6.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/zzn6.cpp$(DependSuffix) -MM zzn6.cpp

$(IntermediateDirectory)/zzn6.cpp$(PreprocessSuffix): zzn6.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zzn6.cpp$(PreprocessSuffix) zzn6.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


