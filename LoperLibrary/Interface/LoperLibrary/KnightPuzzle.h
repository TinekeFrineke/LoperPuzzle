#pragma once

#include <vector>

#include "KnightBoard.h"

#include <iostream>

namespace knight
{

void Print(const Moves& moves) {
  for (const auto& move : moves)
    std::cout << (move.knight == Colour::White ? "White" : move.knight == Colour::Black ? "Black" : "Fixed")
    << " bisshop from row " << move.from.row << " col " << move.from.column
    << " to row " << move.to.row << " col " << move.to.column << std::endl;
}

template<int ROWS, int COLUMNS>
class Puzzle {
public:
  using MyBoard = KnightBoard<ROWS, COLUMNS>;
  using MyBoardSet = std::set<MyBoard>;
  using MyBoardMoves = std::map<MyBoard, size_t>;

  Puzzle(const MyBoard& start, const MyBoard& target) : startboard(start), targetboard(target) {}

  void SetStart(const MyBoard& board) { startboard = board; }
  void SetTarget(const MyBoard & board) { targetboard = board; }

  MyBoard GetStart() const { return startboard; }
  MyBoard GetTarget() const { return targetboard; }

  bool MakeMove(const Move& move);
  bool Solve(int minimumIterations, int maximumIterations);
  bool Solve(MyBoardMoves& alreadyDone, Moves& moves, const unsigned int maxdepth);


private:
  bool UndoMove(const Move& move);


  MyBoard startboard;
  MyBoard targetboard;
};

template<int ROWS, int COLUMNS>
inline bool Puzzle<ROWS, COLUMNS>::MakeMove(const Move& move) {
  return startboard.Place(Knight(move.knight), move.from, move.to);
}

template<int ROWS, int COLUMNS>
inline bool Puzzle<ROWS, COLUMNS>::UndoMove(const Move& move) {
  return startboard.Place(Knight(move.knight), move.to, move.from);
}

template<int ROWS, int COLUMNS>
inline bool Puzzle<ROWS, COLUMNS>::Solve(MyBoardMoves& alreadyDone, Moves& moves, const unsigned int maxdepth) {
  static int stackdepth = 0;
  std::cout << "stackdepth: " << stackdepth++ << std::endl;

  KnightMap knights(startboard.GetPieces());
  for (const auto& knight : knights) {
    PositionSet positions(startboard.ReachablePositions(knight.first, knight.second));
    for (const auto& position : positions) {
      Move move({ knight.second.GetColour(), knight.first, position });
      if (MakeMove(move)) {
        auto findResult(alreadyDone.find(startboard));
        if (findResult != alreadyDone.end()) {
          if (findResult->second > moves.size() + 1) {
            findResult->second = moves.size() + 1;
          }
          else {
            UndoMove(move);
            continue;
          }
        }

        moves.push_back(move);

        // See whether we reached our goal:
        if (startboard == targetboard)
          return true;

        if (moves.size() >= maxdepth) {
          UndoMove(move);
          moves.pop_back();
          continue;
        }

        alreadyDone[startboard] = moves.size();
        if (Solve(alreadyDone, moves, maxdepth))
          return true;

        UndoMove(move);
        moves.pop_back();
      }
    }
  }

  --stackdepth;
  return false;
}

template<int ROWS, int COLUMNS>
inline bool Puzzle<ROWS, COLUMNS>::Solve(const int minimumIterations, const int maximumIterations) {
  for (int i = minimumIterations; i <= maximumIterations; ++i) {
    try {
      MyBoardMoves alreadyDone;
      Moves moves;
      alreadyDone[startboard] = 0;

      if (Solve(alreadyDone, moves, i)) {
        if (!(startboard == targetboard))
          throw std::runtime_error("Incorrect solution");

        Print(moves);
        return true;
      }
    }
    catch (const PuzzleException&) {
      // Nothing found...
    }
  }

  return false;
}

/*
//
///*
//expected:
//White bisshop from row 0 col 4 to row 1 col 3
//Black bisshop from row 2 col 0 to row 1 col 1
//White bisshop from row 1 col 3 to row 0 col 4
//White bisshop from row 0 col 4 to row 3 col 1
//actual:
//Black bisshop from row 0 col 0 to row 1 col 1
//White bisshop from row 0 col 4 to row 1 col 3
//Black bisshop from row 1 col 1 to row 0 col 0
//Black bisshop from row 2 col 0 to row 1 col 1
//White bisshop from row 1 col 3 to row 0 col 4
//White bisshop from row 0 col 4 to row 3 col 1
//*/
//
//  */
} // namespace knight