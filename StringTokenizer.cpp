//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "StringTokenizer.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall StringTokenizer::StringTokenizer(AnsiString Cadena, AnsiString Sep)
{
        str = AnsiString(Cadena);
        Separador =  AnsiString(Sep);
}

bool __fastcall StringTokenizer::HasMoreTokens()
{
        return !str.IsEmpty();
}

AnsiString __fastcall StringTokenizer::NextToken()
{
        AnsiString Token;
        int PosTok = str.Pos(Separador);
        if (PosTok == 0) {
                Token = str;
                str = "";
        }else{
                Token = str.SubString(1,PosTok-1);
                str = str.SubString(PosTok+Separador.Length(),str.Length());
        }
        return Token;
}