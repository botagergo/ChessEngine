#pragma once

#include <string>

enum Direction
{
	NORTH, NORTHWEST, WEST, SOUTHWEST, SOUTH, SOUTHEAST,EAST, NORTHEAST,
	DIRECTION_NB
};

enum File {
	A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE, FILE_NB
};

enum Rank {
	RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8
};

enum Color {
	NO_COLOR = -1, WHITE, BLACK, COLOR_NB
};

const Color Colors[] = { WHITE, BLACK };

constexpr Color operator ~(Color other)
{
	return Color(other ^ BLACK);
}

enum Side
{
	KINGSIDE, QUEENSIDE, SIDE_NB
};

enum PieceType {
	NO_PIECE_TYPE = -1, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, PIECE_TYPE_NB
};

enum Piece {
	NO_PIECE = -1,
	WHITE_PAWN, BLACK_PAWN,
	WHITE_KNIGHT, BLACK_KNIGHT,
	WHITE_BISHOP, BLACK_BISHOP,
	WHITE_ROOK, BLACK_ROOK,
	WHITE_QUEEN, BLACK_QUEEN,
	WHITE_KING, BLACK_KING,
	PIECE_NB
};

PieceType toPieceType(Piece piece);
Piece toPiece(PieceType piece_type, Color color);

PieceType charToPieceType(char c);
Piece charToPiece(char c);

char pieceTypeToChar(PieceType p);
char pieceToChar(Piece p);

Color pieceColor(Piece piece);

const PieceType PieceTypes[] = { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
const PieceType MinorMajorPieces[] = { KNIGHT, BISHOP, ROOK, QUEEN };

enum Square {
	NO_SQUARE = -1,
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,
	SQUARE_NB
};

const Square Squares [] = {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8,
};

const Side Sides[] = {
	KINGSIDE, QUEENSIDE
};

const File Files[] = {
	A_FILE, B_FILE, C_FILE, D_FILE, E_FILE, F_FILE, G_FILE, H_FILE, FILE_NB
};

Square parseSquare(const std::string &s);

Piece operator++(Piece &piece);
PieceType operator++(PieceType &piece);

Square operator++(Square &square);

struct Score
{
	Score(int mg = 0, int eg = 0) : mg(mg), eg(eg) {}

	int mg;
	int eg;

	void operator+=(const Score &s) { mg += s.mg; eg += s.eg; }
	void operator-=(const Score &s) { mg -= s.mg; eg -= s.eg; }

	Score operator-() const { return Score(-mg, -eg); }
	Score operator*(double d) const { return Score((int)(mg * d), (int)(eg * d)); }
};

enum ScoreConstant
{
	MAX_SCORE = 32768,
	INVALID_SCORE = 32769
};