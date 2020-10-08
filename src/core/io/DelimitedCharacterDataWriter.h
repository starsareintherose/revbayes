#ifndef DelimitedCharacterDataWriter_H
#define DelimitedCharacterDataWriter_H

#include <fstream>
#include <string>

namespace RevBayesCore {
class HomologousCharacterData;
    
    /**
     * This class represents an object that writers character data objects into delimited text files.
     *
     *
     * @copyright Copyright 2009-
     * @author The RevBayes Development Core Team (Will Freyman)
     * @since 2013-04-15, version 1.0
     */
    class DelimitedCharacterDataWriter {
        
    public:
        DelimitedCharacterDataWriter();
        
        void                    writeData(const std::string& fn, const HomologousCharacterData &d, char del='\t');
//        void                    writeData(const std::string& fn, const Abstr &d, char del='\t');

        
    };
    
}


#endif
