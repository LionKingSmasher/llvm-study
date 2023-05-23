# LLVM Tutorial 1

## Very Simple Source code
```cpp
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/Bitcode/BitcodeWriter.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Support/Error.h"

#include <iostream>
#include <memory>

static llvm::cl::opt<std::string> fileName(  // command option for file name
    llvm::cl::Positional,
    llvm::cl::desc("Bitcodefile"), // for .bc file
    llvm::cl::Required
);

int main(int argc, char** argv)
{
    llvm::cl::ParseCommandLineOptions(argc, argv, "Hello, LLVM!\n"); // get parameter
    llvm::LLVMContext context;
    std::string error;
    std::unique_ptr<llvm::Module> pModule = nullptr;

    auto buf = llvm::MemoryBuffer::getFile(fileName /* This is option */); // get filename (from parameter... maybe?)
    if(buf.getError())
    {
        std::error_code err = buf.getError();
        std::cout << err.value() << " : " << err.message();

        return err.value();
    }

    auto refMemBuf = llvm::MemoryBufferRef(*buf.get().get());

    auto expected = llvm::parseBitcodeFile(refMemBuf, context); // parse bitcode file
    if(auto err = expected.takeError())
    {
        llvm::errs() << "Failed parseBitcodeFile function" << llvm::toString(std::move(err)) << "\n";
        return -1;
    }
    pModule = std::move(expected.get());

    llvm::raw_os_ostream os(std::cout);
    for(auto i = pModule->getFunctionList().begin(), e = pModule->getFunctionList().end(); i != e; ++i)
    {
        if(!i->isDeclaration())
        {
            os << i->getName() << " has " << i->size() << " blocks\n";
        }
    }

    return 0;
}
```

## How to use this program

```
./example1 <.bc file for llvm>
```

## Very Very Important on this god damn source code
* **llvm::cl::opt** : Command Line option for llvm
* **llvm::MemoryBuffer::getFile()** : get file with options that are your command line options
* **llvm::parseBitcodeFile()** : parse bitcode file(.bc) function
* **llvm::ErrorOr** : It looks like rust's 'Result\<T\>'
* **llvm::Expected** : Similar than 'llvm::ErrorOr'