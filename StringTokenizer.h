//---------------------------------------------------------------------------
#ifndef StringTokenizerH
#define StringTokenizerH
//---------------------------------------------------------------------------
#endif
//Clase que emula a la clase StringTokenizer de JAVA.
//Me perite manejar cadenas de caracteres separadas por delimitadores
//Los token de la cadena deben estar separados por delimitadores.
//Lo que haya entre el último delimitador y el final si se cuenta
class StringTokenizer
{
        private:
                AnsiString Separador; //
                AnsiString str;
        public:
                __fastcall StringTokenizer(AnsiString Cadena, AnsiString Sep); //Constructor de la clase. Tiene como parámetros
                                                                                //la cadena de caracteres original y el caracter separador.
                bool __fastcall HasMoreTokens();        //retorna true si quedan mas tokens en la cadena de entrada
                AnsiString __fastcall NextToken();      //devuelve el siguiente token de la cadena de entrada
};