//********************************************************************
//********************************************************************
//
//  FSModeInfo
//
//    a class used for the bookkeeping of decay modes
//
//    every decay mode is specified in three different ways:
//                 
//      modeCode -- two integers that count the number of particles
//                  in a decay mode.
//                    code1 = abcdefg
//                         a = #gamma
//                         b = #K+
//                         c = #K-
//                         d = #Ks
//                         e = #pi+
//                         f = #pi-
//                         g = #pi0
//                    code2 = abcdefghi
//                         a = #lambda
//                         b = #alambda
//                         c = #e+
//                         d = #e-
//                         e = #mu+
//                         f = #mu-
//                         g = #p+
//                         h = #p-
//                         i = #eta
//
//      modeString -- puts code1 and code2 in a string format:
//                    "code2_code1".
//                    it can contain a prefix
//                    (for example "FS" or "EXC" or "INC" etc)
//                    that isn't used here.
//
//      modeDescription -- string with a list of space-separated
//                         particle names
//                         (for example "K+ K- pi+ pi+ pi- pi-")
//
//********************************************************************
//********************************************************************


#if !defined(FSMODEINFO_H)
#define FSMODEINFO_H

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <map>
#include "TString.h"
#include "FSBasic/FSString.h"

using namespace std;


class FSModeInfo{

  public:

      // *******************************************************
      // CONSTRUCTORS STARTING FROM:
      //   "modeCode", "modeCode1,modeCode2", "modeString", 
      //     or "modeDescription"
      // *******************************************************

    FSModeInfo (pair < int,int > mCode);
    FSModeInfo (int mCode1, int mCode2);
    FSModeInfo (TString mString);


      // *******************************************************
      // RETURN INFORMATION ABOUT THIS MODE
      //  modeString recognizes and replaces these strings 
      //    if "original" is given:
      //      "MODESTRING"
      //      "MODEDESCRIPTION"
      //      "MODECODE"
      //      "MODECODE1"
      //      "MODECODE2"
      //      "MODEGLUEX"
      //      "MODECOMBO"
      //    if "counter" is also given and non-negative:
      //      "MODECOUNTER"
      //        or "MODECOUNTERXXXX" to pad with zeros
      // *******************************************************

    pair<int,int>  modeCode();
    int            modeCode1();
    int            modeCode2();
    TString        modeString(TString original = "", int counter = -1);
    TString        modeDescription();
    TString        modeGlueXFormat();
    TString        modeComboFormat(int minimumIndex = 1, TString extraTag = "");

    vector<TString> particles();


      // *******************************************************
      // ASSIGN "CATEGORIES" TO THIS MODE
      //   (in addition to standard categories added by default)
      // *******************************************************

    vector<TString> categories();
    void addCategory(TString category);
    void addCategory(vector<TString> categories);
    bool hasCategory(TString category);
    void removeCategory(TString category);


      // *******************************************************
      // DISPLAY INFORMATION ABOUT THIS MODE
      // *******************************************************

    void display(int counter = 0);


      // *******************************************************
      // GET NUMBERS OF EACH PARTICLE TYPE
      // *******************************************************

    int modeNPi0       ();
    int modeNPim       ();
    int modeNPip       ();
    int modeNKs        ();
    int modeNKm        ();
    int modeNKp        ();
    int modeNGamma     ();
    int modeNEta       ();
    int modeNPm        ();
    int modeNPp        ();
    int modeNMm        ();
    int modeNMp        ();
    int modeNEm        ();
    int modeNEp        ();
    int modeNALambda   ();
    int modeNLambda    ();
    int modeNParticles ();

    int modeCharge       ();
    int modeBaryonNumber ();
    int modeStrangeness  ();
    double modeMass      ();


    FSModeInfo modeCC();
    int modeCCNumber();

    bool modeContains(TString mString);


      // *******************************************************
      // GET PARTICLE INDICES
      // *******************************************************

    vector<int> modePi0Indices      ();
    vector<int> modePimIndices      ();
    vector<int> modePipIndices      ();
    vector<int> modePiIndices       ();
    vector<int> modeKsIndices       ();
    vector<int> modeKmIndices       ();
    vector<int> modeKpIndices       ();
    vector<int> modeKIndices        ();
    vector<int> modeGammaIndices    ();
    vector<int> modeEtaIndices      ();
    vector<int> modePmIndices       ();
    vector<int> modePpIndices       ();
    vector<int> modePIndices        ();
    vector<int> modeMmIndices       ();
    vector<int> modeMpIndices       ();
    vector<int> modeMIndices        ();
    vector<int> modeEmIndices       ();
    vector<int> modeEpIndices       ();
    vector<int> modeEIndices        ();
    vector<int> modeTkmIndices      ();
    vector<int> modeTkpIndices      ();
    vector<int> modeTkIndices       ();
    vector<int> modeLmIndices       ();
    vector<int> modeLpIndices       ();
    vector<int> modeLIndices        ();
    vector<int> modeALambdaIndices  ();
    vector<int> modeLambdaIndices   ();
    vector<int> modeParticleIndices (TString particleName = "");


      // *************************************************************
      // USEFUL FOR MAKING CUTS ON INDIVIDIUAL PARTICLE TYPES
      //  examples:  AND(EnP[pi+]>0) --> ((EnP1>0)&&(EnP2>0)&&(EnP3>0))
      //              OR(EnP[pi+]>0) --> ((EnP1>0)||(EnP2>0)||(EnP3>0))
      //   (also allows nested ANDs and ORs although it may not be useful)
      // *************************************************************

    TString modeCuts(TString varString);


      // *************************************************************
      // HANDLES COMBINATORICS
      // *************************************************************

    vector<TString> modeCombinatorics (TString varString, 
                                       bool printCombinatorics = false,
                                       bool removeDuplicates = true);


      // *************************************************************
      // DEFINE SUBMODES FOR MORE COMPLICATED COMBINATORICS
      // *************************************************************

    static void setSubmode (TString particleName,
                     vector<TString> particleDecays);


  private:


      // ****************************************************
      // PRIVATE MEMBER DATA
      // ****************************************************

    pair<int,int> m_modeCode;
    vector<TString> m_categories;
    vector<TString> m_particles;

    static map < TString, vector<TString> > m_submodeMap;


      // *********************************************************
      // ADD STANDARD CATEGORIES ONCE NEEDED
      // *********************************************************

    void addStandardCategories();


      // *******************************************************
      // CHECK IF THIS IS A PROPER "modeDescription"
      // *******************************************************

    bool isModeDescription(TString mDescription);


      // *******************************************************
      // CHECK IF THIS IS A PROPER "modeString"
      // *******************************************************

    bool isModeString(TString mString);

};





#endif

