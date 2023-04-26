#ifndef ARTENGINE_CUBIC_SPLINE_H
#define ARTENGINE_CUBIC_SPLINE_H

#include "../../include/pch.h"
#include "../../include/ArtEngine.h"

// truncated power function
double truncated_power_function(double t, float c, unsigned d)
{
  if (t < c)
    return 0.0;
  return pow(t - c, d);
}

int FindPivot(std::vector<std::vector<double>> const &input, int startRow, int col, int rowCount)
{
  for (int i = startRow; i < rowCount; ++i)
    if (input[i][col] != 0)
      return i;

  return -1;
}

void SwitchRows(std::vector<std::vector<double>> &input, int row1, int row2, int colCount)
{
  if (row1 == row2)
    return;

  for (int col = 0; col < colCount; ++col)
  {
    double temp = input[row1][col];
    input[row1][col] = input[row2][col];
    input[row2][col] = temp;
  }
}

void ReduceRow(std::vector<std::vector<double>> &input, int row, int col, int colCount)
{
  double coefficient = 1.0 / input[row][col];

  if (coefficient == 1)
    return;

  for (; col < colCount; col++)
    input[row][col] *= coefficient;
}

void EliminateRow(std::vector<std::vector<double>> &input, int row, int pivotRow, int pivotCol, int colCount)
{
  if (pivotRow == row)
    return;

  if (input[row][pivotCol] == 0)
    return;

  double coefficient = input[row][pivotCol];

  for (int col = pivotCol; col < colCount; col++)
    input[row][col] -= input[pivotRow][col] * coefficient;
}

void Eliminate(int r, int c, std::vector<std::vector<double>> &output)
{
  int totalRowCount = r;
  int totalColCount = c;

  // number of pivots found
  int numPivots = 0;

  // loop through columns, exclude augmented columns
  for (int col = 0; col < totalColCount; col++)
  {
    int pivotRow = FindPivot(output, numPivots, col, totalRowCount);

    if (pivotRow == -1)
      continue; // no pivots, go to another column

    ReduceRow(output, pivotRow, col, totalColCount);

    SwitchRows(output, pivotRow, numPivots, totalColCount);

    pivotRow = numPivots;
    numPivots++;

    // Eliminate Previous Rows
    for (int tmpRow = 0; tmpRow < pivotRow; tmpRow++)
      EliminateRow(output, tmpRow, pivotRow, col, totalColCount);

    // Eliminate Next Rows
    for (int tmpRow = pivotRow; tmpRow < totalRowCount; tmpRow++)
      EliminateRow(output, tmpRow, pivotRow, col, totalColCount);
  }
}

std::vector<glm::vec3> CubicSpline(std::deque<glm::vec3> const &points)
{
    int k = 0;
    int const n = static_cast<int>(points.size());

    std::vector<std::vector<double>> mx(n + 2);
    for (auto &v : mx)
        v.resize(n + 3);

  // compute the rows of the matrix (minus the last column)
  for (int i = 0; i < n + 2; ++i)
  {
    int c = 0;
    if (i < n)
    {
      for (int j = 0; j < n + 2; ++j)
      {
        if (j < 4)
          mx[i][j] = pow(k, j);
        else
        {
          ++c;
          mx[i][j] = truncated_power_function(k, c, 3);
        }
      }
    }
    else
    {
      // final two rows are the second derivative
      // first uses 0, second uses k
      if (i == n)
        k = 0;
      else
        k = n - 1;

      for (int j = 0; j < n + 2; ++j)
      {
        if (j < 2)
          mx[i][j] = 0;
        else if (j == 2)
          mx[i][j] = 2;
        else if (j == 3)
          mx[i][j] = 6 * k;
        else
        {
          ++c;
          mx[i][j] = 6 * truncated_power_function(k, c, 1);
        }
      }
    }
    ++k;
  }

  // make 2 copies of the matrix for computing y and z
  std::vector<std::vector<double>> my = mx;
  std::vector<std::vector<double>> mz = mx;

  // set the last column of each matrix
  for (int i = 0; i < n + 2; ++i)
  {
    mx[i][n + 2] = i < n ? static_cast<double>(points[i].x) : 0.0f;
    my[i][n + 2] = i < n ? static_cast<double>(points[i].y) : 0.0f;
    mz[i][n + 2] = i < n ? static_cast<double>(points[i].z) : 0.0f;
  }

  // perform gauss elimination (row reduced echelon form)
  // to solve the linear system of equations to compute
  // all coefficients for the cubic spline
  Eliminate(n + 2, n + 3, mx);
  Eliminate(n + 2, n + 3, my);
  Eliminate(n + 2, n + 3, mz);

  // copy results into a more easily used format
  std::vector<glm::vec3> result(n + 2);
  for (int i = 0; i < n + 2; ++i)
    result[i] = {mx[i][n + 2], my[i][n + 2], mz[i][n + 2]};

  return result;
}

#endif // ARTENGINE_CUBIC_SPLINE_H
