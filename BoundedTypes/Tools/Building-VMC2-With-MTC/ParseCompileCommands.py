from ctypes.util import find_library
from os import path
from re import search, sub

from clang import cindex

cindex.Config.set_library_file(find_library('clang-8'))
index = cindex.Index.create()
compilation_database_path = path.dirname(
    '/media/rad2rng/Rai-Data/VMC2/Azure/vmc2/Application/build/compile_commands.json')
compdb = cindex.CompilationDatabase.fromDirectory(compilation_database_path)
allCompilationCommands = compdb.getAllCompileCommands()

# Blacklist: Translation Units that are not to be passed to MTC
translationUnitBlackList = ("MockComponent",  # All parts of the MockComponent
                            "Tests"  # All Tests
                            )
includeUnitBlackList = ("MockComponent",  # All parts of the MockComponent
                        "Tests"  # All Tests
                        )

allTranslationUnits = list()
allIncludeDirectories = list()
allBlackListedTranslationUnitPatterns = '(?:%s)' % '|'.join(translationUnitBlackList)
allIncludeDirectoriesBlackList = '(?:%s)' % '|'.join(includeUnitBlackList)
for thisCompileCommand in allCompilationCommands:
    # print ("\n--------------------------------")
    # print(thisCompileCommand.filename)
    if thisCompileCommand.filename not in allTranslationUnits:
        # Check if this translation unit is blacklisted
        if search(allBlackListedTranslationUnitPatterns, thisCompileCommand.filename) is None:
            allTranslationUnits.append(thisCompileCommand.filename)

    allArguments = thisCompileCommand.arguments
    for thisArgument in allArguments:
        # print(thisArgument)
        allTokens = search("^-I/(.*)", thisArgument)
        if allTokens is not None:
            thisIncludeDirectory = allTokens.group(1)
            if thisIncludeDirectory not in allIncludeDirectories:
                if search(allIncludeDirectoriesBlackList, thisIncludeDirectory) is None:
                    # print("Include Directory: " + thisIncludeDirectory)
                    allIncludeDirectories.append(thisIncludeDirectory)
        # print( "--------------------------------\n" )

# print out all translation units
# for thisTranslationUnit in allTranslationUnits:
# print("File to be compiled: " + thisTranslationUnit)

# print out all include directories
for thisUniqueIncludeDirectory in allIncludeDirectories:
    print("Unique Include Directory: " + thisUniqueIncludeDirectory)

# Write out the BCFG File
try:
    with open("./Cfg_Build_Master.bcfg", 'w') as bcfgFile:
        bcfgFile.write('#define GENPRODB_ACTIVE 0\n')
        bcfgFile.write('module "/MTCConfig"\n')
        bcfgFile.write('{\n')
        bcfgFile.write('\tfiles { \n')
        bcfgFile.write('\t\t#if GENPRODB_ACTIVE\n')
        bcfgFile.write('\t\t\txcp_events{"xcp_events.xml"}\n')
        bcfgFile.write('\t\t\tasap_tpl {"ASAP_Template_XCP.a2l_tpl" }\n')
        bcfgFile.write('\t\t#endif\n')
        bcfgFile.write('\t}\n')
        bcfgFile.write('}\n')
        bcfgFile.write('\n')
        bcfgFile.write('module "/vmc2"\n')
        bcfgFile.write('\t{\n')

        # Write include directories
        bcfgFile.write('\t\texport {\n')
        for thisIncludeDirectory in allIncludeDirectories:
            # Do not write system directories
            if search("usr/", thisIncludeDirectory) is None:
                # Correct the relative path of the include directory
                includeDirectoryWithCorrectRelativePath = sub("^.*/vmc2/", "", thisIncludeDirectory)
                bcfgFile.write("\t\t\t" + "\"" + includeDirectoryWithCorrectRelativePath + "\"" + ";\n")
        bcfgFile.write('\t\t       }\n')

        # Write files to parse

        bcfgFile.write('\t\tfiles  {\n')
        bcfgFile.write('\t\t\tc++  {\n')
        for thisTranslationUnit in allTranslationUnits:
            # Correct the relative path of the include directory
            translationUnitWithCorrectRelativePath = sub("^.*/vmc2/", "", thisTranslationUnit)
            bcfgFile.write("\t\t\t\t" + "\"" + translationUnitWithCorrectRelativePath + "\"" + ";\n")
        bcfgFile.write('\t\t\t     }\n')  # close c++ {...}
        bcfgFile.write('\t\t#if GENPRODB_ACTIVE\n')
        bcfgFile.write('\t\t// genprodb scanner for measurements \n')
        bcfgFile.write('\t\t\tgenprodb {"**/*.*"}\n')
        bcfgFile.write('\t\t#endif\n')
        bcfgFile.write('\t\t       }\n')  # close files {...}
        bcfgFile.write('}\n')  # close module "/vmc2 {...}
except IOError:
    pass
