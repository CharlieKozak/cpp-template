#include <catch2/catch_test_macros.hpp>

#include <treasure/treasure.h>
#include <iostream>

#include <iomanip>

using namespace std;

struct ft_result runFindTreasure(double clue[][2], double region[][2],
                     int CLUE_ROWS, int CLUE_COLS, int REG_ROWS, int REG_COLS)
{

  double distance[CLUE_ROWS][3];

  calculateDistanceMatrix(distance, clue, region, CLUE_ROWS, CLUE_COLS,
                          REG_ROWS, REG_COLS);

  for (int i = 0; i < CLUE_ROWS; i++)
  {
    for (int j = 0; j < REG_ROWS; j++)
    {
      cout << fixed << setprecision(3) << distance[i][j] << " ";
    }
    cout << endl;
  }

  int clue_regions[CLUE_ROWS];
  findClueRegion(distance, clue_regions, CLUE_ROWS, REG_ROWS);
  for (int i = 0; i < CLUE_ROWS; i++)
  {
    cout << clue_regions[i] << " ";
  }
  cout << endl;

  // To print the result
  findTreasure(clue_regions, region, CLUE_ROWS, REG_ROWS, REG_COLS);

  // For assertions
  return _findTreasure(clue_regions, region, CLUE_ROWS, REG_ROWS, REG_COLS);
}


TEST_CASE("sample_run_1") {

  const int CLUE_ROWS = 5;
  const int CLUE_COLS = 2;
  const int REG_ROWS = 3;
  const int REG_COLS = 2;
  double clue[CLUE_ROWS][CLUE_COLS] = {{2, 10}, {2, 5}, {8, 4}, {5, 8}, {1, 2}};
  double region[REG_ROWS][REG_COLS] = {{2, 10}, {5, 8}, {1, 2}};

  struct ft_result r = runFindTreasure(clue, region, CLUE_ROWS, CLUE_COLS, REG_ROWS, REG_COLS);

  REQUIRE(r.region == 1);
  REQUIRE(r.n_clues == 1);
  REQUIRE(r.x == 2.0);
  REQUIRE(r.y == 10.0);
}

TEST_CASE("sample_run_2") {

  const int CLUE_ROWS = 4;
  const int CLUE_COLS = 2;
  const int REG_ROWS = 3;
  const int REG_COLS = 2;
  double clue[CLUE_ROWS][CLUE_COLS] = {{2, 1}, {2, 3}, {4, 4}, {5, 8}};
  double region[REG_ROWS][REG_COLS] = {{1, 2}, {3, 6}, {5, 8}};

  struct ft_result r = runFindTreasure(clue, region, CLUE_ROWS, CLUE_COLS, REG_ROWS, REG_COLS);

  REQUIRE(r.region == 2);
  REQUIRE(r.n_clues == 1);
  REQUIRE(r.x == 3.0);
  REQUIRE(r.y == 6.0);
}

TEST_CASE("sample_run_3") {

  const int CLUE_ROWS = 5;
  const int CLUE_COLS = 2;
  const int REG_ROWS = 3;
  const int REG_COLS = 2;
  double clue[CLUE_ROWS][CLUE_COLS] = {{2, 10}, {2, 5}, {8, 4}, {5, 8}, {1, 2}};
  double region[REG_ROWS][REG_COLS] = {{0, 0}, {5, -1}, {-1, -2}};

  struct ft_result r = runFindTreasure(clue, region, CLUE_ROWS, CLUE_COLS, REG_ROWS, REG_COLS);

  REQUIRE(r.region == 3);
  REQUIRE(r.n_clues == 0);
  REQUIRE(r.x == -1.0);
  REQUIRE(r.y == -2.0);

}

TEST_CASE("one_is_one") {

  REQUIRE(1 == 1);

}
