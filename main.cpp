#include <iostream>
#include <fstream>

#include "src/Lexer/Lexer.h"
#include "src/Token/TokenType.h"
#include "src/Decimal/decimal.h"
#include "src/ErrorHandler/ErrorReporter.h"
#include "src/ErrorHandler/InterpreterExceptions.h"
#include "src/Parser/Parser.h"

#include "src/Visitors/LogVisitor/LogVisitor.h"
#include "src/Visitors/SemanticVisitor/SemanticVisitor.h"
#include "src/Visitors/InterpreterVisitor/InterpreterVisitor.h"

#include "src/ConfigParser/ConfigParser.h"
#include "src/ErrorHandler/Errors.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "\x1B[2J\x1B[H";
    if (argc >= 2)
    {
        string fileName = argv[1];
        
        string mainFuncion = "main";
        string configFile = "currency_config.cfg";
        if (argc > 2)
            mainFuncion = argv[2];
        if (argc > 3)
            configFile = argv[3];

        Token::initLogger();
        ifstream fileStream;

        try
        {
            fileStream.open(configFile);
            if (!fileStream.good())
            {
                MissingFile error;
                ErrorReporter::reportWarning(error);
            }
            Lexer configLexer(fileStream);
            ConfigParser configParser(configLexer);
            configParser.parseConfigFile();
            fileStream.close();
            ErrorReporter::printAll(cout, configFile);

            fileStream.open(fileName);
            if (!fileStream.good())
                throw FileError("file not found");
            Lexer lexer(fileStream);
            Parser parser(lexer, configParser);
            Program prog = parser.parse();
            prog.addEmbededFunctions();
            // LogVisitor logger;
            // logger.visit(prog);
            SemanticVisitor semanticValidation(prog);
            semanticValidation.visit(prog);
            InterpreterVisitor interpreter(prog, mainFuncion, configParser.getCurrencyMap());
            
            fileStream.close();
        }
        catch (FileError const &e)
        {
            MissingFile error;
            ErrorReporter::reportError(error);
            fileStream.close();
        }
        catch (FatalError const &e)
        {
            fileStream.close();
        }
        catch (FatalConfigError const &e)
        {
            ErrorReporter::printAll(cout, configFile);
            fileStream.close();
        }
        catch (RunTimeError const &e)
        {
            ErrorReporter::printRuntime(cout);
            fileStream.close();
        }
        ErrorReporter::printAll(cout, fileName);
    }
    else
    {
        cout << "Invalid usage!" << endl;
        cout << "Example usage: " << argv[0] << " file_input [main_function_name] [configuration_file]" << endl;
        cout << "Where:" << endl;
        cout << "file_input - is file to interpret" << endl;
        cout << "main_function_name - is function to be called on start Default is main" << endl;
        cout << "configuration_file - path to configuration file with currancy denominations" << endl;
    }
}
