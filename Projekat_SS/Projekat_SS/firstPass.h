#pragma once
#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <regex>
#include <iostream>
#include <string>
using namespace std;

class FirstPass {
    struct regexi {
        // [ \t]* razmak(tab) 0 ili vise puta
        // \\w* slovo ili broj 0 ili vise puta. Sme da pocne velikim slovom
        // [A-Za-z]* slova samo
        regex emptyLine{						//samo labela u redu
            "^[ \t]*$" };
        regex labelLineOnly{					//samo labela u redu
            "^[ \t]*(\\w|_)+[ \t]*\\:[ \t]*$" };
        regex labelLineWithCommand{				// labela pa bilo sta
            "^[ \t]*(\\w|_)+[ \t]*\\:[ \t]*.*" };
        regex identfier{						// rec, naziv ili sta god
            "[a-zA-Z](\\w|_)*"};
        regex identfierOrNumber{
            "(\\w|_)+" };
        regex number{							// broj
            "\\d+" };
        regex everything{
            ".*"};
        regex literal{
            "^[ \t]*((\\d+)|((\\d+)|(0x(\\d|[a-f]|[A-F])+))|(\\d_\\d+)|(\\d+\\.\\d+)"	// Sta sve spada u literale je nadjeno na
            "|(TRUE|FALSE)|('[a-zA-Z]'))[ \t]*$" };				// keil.com literals
        // PROVERI OVAJ $ NA KRAJU ! ! ! NE ZABORAVI DA POSTOJI
        regex simbol{						// rec, naziv ili sta god
            "^[ \t]*[a-zA-Z](\\w|_)*[ \t]*$" };

        ////////////////////////////////////////////
        // Regeksi za direktive
        regex global{
            "[ \t]*\\.global[ \t]+(\\w|_)+([ \t]*,[ \t]*(\\w|_)+)*[ \t]*$"};	// Ovde imas \\. umesto \.
        regex exterN{
            "[ \t]*\\.extern[ \t]+(\\w|_)+([ \t]*,[ \t]*(\\w|_)+)*[ \t]*$" };	// kao i \\w umesto \w
        regex section{
            "[ \t]*\\.section[ \t]+(\\w|_)+[ \t]*$" };
        regex dataSection{
            "[ \t]*\\.data[ \t]*$" };
        regex textSection{
            "[ \t]*\\.text[ \t]*$" };
        regex bssSection{
            "[ \t]*\\.bss[ \t]*$" };
        regex word{
            "[ \t]*\\.word[ \t]+(\\w|_)+([ \t]*,[ \t]*(\\w|_)+)*[ \t]*$" };	// kao i \\w umesto \w
        regex skip{
            "[ \t]*\\.skip[ \t]+\\d+[ \t]*$" };
        regex equ{
            "[ \t]*\\.equ[ \t]+(\\w|_)+[ \t]*,[ \t]*((\\d+)|(0x(\\d|[a-f]|[A-F])+))[ \t]*$" };
        regex end{
            "[ \t]*\\.end[ \t]*$" };
        regex noOper{
            "[ \t]*\\w+[ \t]*$" };
        regex oneOper{
            "[ \t]*\\w+[ \t]+([(\\w|_)\\*\\.\\+\\[\\]\\%\\$ ])+[ \t]*$" };  // Prekopiraj ovo dole za twoOper
        regex twoOper{
            "[ \t]*\\w+[ \t]+(r[0-9])[ \t]*,[ \t]*([(\\w|_)\\*\\.\\+\\[\\]\\%\\$ ])+[ \t]*$" };
        ////////////////////////////////////////////////////
        // Regeksi vezani za operande i tako to
        // Moras da proveris prvo slovo da li je $%[ ili sta vec
        regex regDir{
            "^[ \t]*(r[0-9]|sp|pc|psw)[ \t]*$"}; //regX, to je valjda i regD i regS

    };
    static regexi mojRegex;
    static string currSection;
    static int currOffset;
    static int numOfLine; // nepotrebno, cisto onako da znas
    static bool end;
    // Bilo kakva greska
    static void error(string msg, string line);

    static bool emptyLine(string line);
    static bool checkOperand(string line);
    // Labela
    static bool label(string line);
    static string deleteLabelFromCommand(string line);
    // Komentar
    static string newLineWithoutComment(string line);
    // global direktiva
    static bool globalDirective(string line);
    // extern direktiva
    static bool externDirective(string line);
    // section direktiva
    static bool sectionDirective(string line);
    // section DATA direktiva
    static bool sectionDataDirective(string line);
    // section Text direktiva
    static bool sectionTextDirective(string line);
    // section Bss direktiva
    static bool sectionBssDirective(string line);
    // word direktiva
    static bool wordDirective(string line);
    // skip direktiva
    static bool skipDirective(string line);
    // equ direktiva
    static bool equDirective(string line);
    // end direktiva
    static bool endDirective(string line);

    // instrk bez operanada;
    static bool noOperInstr(string line);
    // instrk sa 1 operandom;
    static bool oneOperInstr(string line);
    // instrk sa 2 operanda;
    static bool twoOperInstr(string line);

public:
    static void testRegex();
    static void startFirstPass();
};


#endif // !FIRSTPASS_H
