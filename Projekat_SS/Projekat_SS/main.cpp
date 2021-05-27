#pragma once

#include <iostream>
#include <string>

#include "MainClass_ASM.h"
#include "firstPass.h"
#include "SecondPass.h"
#include "parsedTokens.h"
#include "SymbolTable.h"
#include "RelTable.h"
#include "SectionTable.h"

const bool ISPIS_NA_KONZOLU_PRE_DRUGOG_PROLAZA = false;
const bool ISPIS_NA_KONZOLU_POSLE_DRUGOG_PROLAZA = false;
const bool ISPIS_U_FAJL = true;
const bool ISPIS_TOKENA = false;

using namespace std;

int main(int argc, char *argv[]) {
    /*
    	! ! ! ! ! ! NAPOMENA ! ! ! ! ! !
    	Pretrazi ceo projekat, trazi "PC", gde god se to pojavi, tu ti je PC relativno,
    	tj. %simbol i tu ne znam sta treba da radim. Pre predaje nauci kako to treba da radi i samo
    	skloni "PC" jer ima podraz vrednost, ili ga ostavi ako mislis da treba
    	ili za skok odradi neposredno ili kako vec

    */


    cout << "\tProgram pokrenut" << endl;

    // FirstPass::testRegex();


    MainClass_ASM::passArgAndOpenFiles(argc, argv);


    FirstPass::startFirstPass();
    MainClass_ASM::closeInputFile();

    if (ISPIS_TOKENA)
        // Ispis mora da stoji pre drugog prolaza, jer se u drugom prolazu lista tokena brise
        ParsedTokens::printParsedTokens();


    if (ISPIS_NA_KONZOLU_PRE_DRUGOG_PROLAZA) {
        SymbolTable::printSymbolTable(cout);
        SectionTable::printSections(cout);
        RelTable::printRelTable(cout);
    }

    SecondPass::startSecondPass();

    if (ISPIS_NA_KONZOLU_POSLE_DRUGOG_PROLAZA) {
        SymbolTable::printSymbolTable(cout);
        SectionTable::printSections(cout);
        RelTable::printRelTable(cout);
    }


    if (ISPIS_U_FAJL) {
        SymbolTable::printSymbolTable((ostream&)MainClass_ASM::outputFileTxt);
        SectionTable::printSections((ostream&)MainClass_ASM::outputFileTxt);

        // Cela rel tabela
        // RelTable::printRelTable((ostream&)MainClass::outputFileTxt);
        // binarni fajl
        // SymbolTable::printSymbolTableBinary((ostream&)MainClass_ASM::outputFile);
    }

    MainClass_ASM::closeOutputFile();
    MainClass_ASM::assemblyDoneSayBye();

}