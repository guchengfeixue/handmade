#include <stdio.h>
#include <stdlib.h>

char *ReadEntireFileIntoMemoryAndNullTerminate(char *Filename)
{
    char *Result = 0;

    FILE *File = fopen(Filename, "r");
    if (File) {
        fseek(File, 0, SEEK_END);
        size_t FileSize = ftell(File);
        fseek(File, 0, SEEK_SET);

        Result = (char *)malloc(FileSize + 1);
        fread(Result, FileSize, 1, File);
        Result[FileSize] = 0;

        fclose(File);
    }

    return Result;
}

enum token_type {
    Token_OpenParen,
    Token_Colon,
    Token_CloseParen,
    Token_Semicolon,
    Token_Asterisk,
    Token_OpenBracket,
    Token_CloseBracket,
    Token_OpenBrace,
    Token_CloseBrace,

    Token_Identifier,
    Token_String,

    Token_EndOfStream,
};

struct token {
    token_type Type;

    int TextLength;
    char *Text;
};

struct tokenizer {
    char *At;
};

inline bool IsEndOfLine(char C)
{
    bool Result = ((C == '\n') ||
                   (C == '\r'));
    return Result;
}

inline bool IsWhitespace(char C)
{
    bool Result = ((C == ' ') ||
                   (C == '\t') ||
                   IsEndOfLine(C));

    return Result;
}

static void EatAllWhitespace(tokenizer *Tokenizer)
{

    for (;;) {
        if (IsWhitespace(Tokenizer->At[0])) {
            ++Tokenizer->At;
        } else if (Tokenizer->At[0] == '/' && Tokenizer->At[1] == '/') {
            Tokenizer->At += 2;
            while (Tokenizer->At[0] && !IsEndOfLine(Tokenizer->At[0])) {
                ++Tokenizer->At;
            }
        } else if (Tokenizer->At[0] == '/' && Tokenizer->At[1] == '*') {
            Tokenizer->At += 2;
            while (Tokenizer->At[0] && !(Tokenizer->At[0] == '*' && Tokenizer->At[1] == '/')) {
                ++Tokenizer->At;
            }

            if (Tokenizer->At[0] == '*') {
                Tokenizer->At += 2;
            }
        } else {
            break;
        }
    }


}

static token GetToken(tokenizer *Tokenizer)
{
    EatAllWhitespace(Tokenizer);

    token Token = {};
    Token.TextLength = 1;
    Token.Text = Tokenizer->At;

    switch (Tokenizer->At[0]) {
        case '\0': { Token.Type = Token_EndOfStream; } break;

        case '(': { Token.Type = Token_OpenParen; } break;
        case ')': { Token.Type = Token_CloseParen; } break;
        case ':': { Token.Type = Token_Colon; } break;
        case ';': { Token.Type = Token_Semicolon; } break;
        case '*': { Token.Type = Token_Asterisk; } break;
        case '[': { Token.Type = Token_OpenBracket; } break;
        case ']': { Token.Type = Token_CloseBracket; } break;
        case '{': { Token.Type = Token_OpenBrace; } break;
        case '}': { Token.Type = Token_CloseBrace; } break;

        case '""': {
            ++Tokenizer->At;
            Token.Text = Tokenizer->At;
            while (Tokenizer->At[0] && Tokenizer->At[0] != '"') {
                if (Tokenizer->At[0] == '\\' && Tokenizer->At[1]) {
                    ++Tokenizer->At;
                }
                ++Tokenizer->At;
            }
        } break;

        default: {
            if (IsAlpha(Tokenizer->At[0])) {
                ParseIdentifier();
            } else if (IsNumberic(Tokenizer->At[0])) {
                ParseNumber();
            }
        } break;
    }
}

int main(int argc, char *argv[])
{
    char *FileContents = ReadEntireFileIntoMemoryAndNullTerminate("handmade_sim_region.h");

    tokenizer Tokenizer = {};
    Tokenizer.At = FileContents;

    bool Parsing = true;
    while (Parsing) {
        token Token = GetToken(&Tokenizer);
        switch (Token.Type) {
            default: {
                printf("%d: %.*s\n", Token.Type, Token.TextLength, Token.Text);
            } break;

            case Token_EndOfStream: {
                Parsing = false;
            } break;
        }
    }

    return 0;
}
