#include <random>
#include <ctime>

#include "zobrist.h"

unsigned long long Zobrist::PiecePositionHash[COLOR_NB][PIECE_NB][SQUARE_NB] = { 0 };
unsigned long long Zobrist::BlackMovesHash = { 0 };
unsigned long long Zobrist::CastlingRightsHash[16] = { 0 };
unsigned long long Zobrist::EnPassantFileHash[FILE_NB] = { 0 };

void Zobrist::initZobristHashing()
{
	std::random_device rd;
	std::mt19937_64 e2(std::mt19937_64::default_seed);

	std::uniform_int_distribution<unsigned long long> dist;

	for (PieceType piece_type : PieceTypes)
	{
		for (Square square : Squares)
		{
			unsigned long long d = dist(e2);
			PiecePositionHash[WHITE][piece_type][square] = dist(e2);
			PiecePositionHash[BLACK][piece_type][square] = dist(e2);
		}
	}

	BlackMovesHash = dist(e2);

	unsigned long long castling_rights_hash[COLOR_NB][SIDE_NB];
	for (Color color : Colors)
	{
		for (Side side : Sides)
		{
			castling_rights_hash[color][side] = dist(e2);
		}
	}

	for (int i = 0; i < 16; ++i)
	{
		for (Color color : Colors)
		{
			for (Side side : Sides)
			{
				if (i & Board::CastleFlag[color][side])
				{
					CastlingRightsHash[i] ^= castling_rights_hash[color][side];
				}
			}
		}
	}

	for (File file : Files)
	{
		EnPassantFileHash[file] = dist(e2);
	}
}

unsigned long long Zobrist::getBoardHash(const Board & board)
{
	unsigned long long hash = 0;

	if (board.toMove() == BLACK)
		hash ^= BlackMovesHash;

	for (Color color : Colors)
	{
		for (PieceType piece_type : PieceTypes)
		{
			for (Square square : BitboardIterator<Square>(board.pieces(color, piece_type)))
			{
				hash ^= PiecePositionHash[color][piece_type][square];
			}
		}
	}

	hash ^= CastlingRightsHash[board._castling_rights];

	if (board.enPassantTarget() != NO_PIECE)
		hash ^= EnPassantFileHash[Util::getFile(board.enPassantTarget())];

	return hash;
}