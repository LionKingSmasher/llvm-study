extern "C"
{
#include <clang-c/Index.h>
}

#include <llvm/Support/CommandLine.h>
#include <iostream>

using namespace llvm;

static cl::opt<std::string> fileName(
    cl::Positional,
    cl::desc("Input File"),
    cl::Required
);

int main(int argc, char** argv)
{
    cl::ParseCommandLineOptions(
        argc,
        argv,
        "Diagonostic"
    );

    CXIndex index = clang_createIndex(0, 0);
    const char* args[] = 
    {
        "-I/usr/include",
        "-I."
    };
    CXTranslationUnit translationUnit = clang_parseTranslationUnit(
        index,
        fileName.c_str(),
        args,
        2,
        nullptr,
        0,
        CXTranslationUnit_None
    );
    
    unsigned diagnosticCount = clang_getNumDiagnostics(translationUnit);
    for(unsigned i = 0; i < diagnosticCount; i++)
    {
        CXDiagnostic diagnostic = clang_getDiagnostic(translationUnit, i);
        CXString category = clang_getDiagnosticCategoryText(diagnostic);
        CXString message = clang_getDiagnosticSpelling(diagnostic);
        unsigned severity = clang_getDiagnosticSeverity(diagnostic);
        CXSourceLocation loc = clang_getDiagnosticLocation(diagnostic);
        CXString fn;
        unsigned line = 0, col = 0;

        clang_getPresumedLocation(loc, &fn, &line, &col);
        std::cout << "Severity: " << severity << std::endl;
        std::cout << "File Name: " << clang_getCString(fn) << std::endl;
        std::cout << "Line: " << line << std::endl;
        std::cout << "Column: " << col << std::endl;
        std::cout << "Category: " << clang_getCString(category) << std::endl;
        std::cout << "Message: " << clang_getCString(message) << std::endl;

        clang_disposeString(fn);
        clang_disposeString(message);
        clang_disposeString(category);
        clang_disposeDiagnostic(diagnostic);
    }

    clang_disposeTranslationUnit(translationUnit);
    clang_disposeIndex(index);

    return 0;
}